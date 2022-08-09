 //  Инициализация и главный цикл

#include        "def_Board.h"
#include        "test18f97.h"
#include        "USART.h"

unsigned int Termo_measure();
unsigned char fMasterKey = 0;         // флаг = 1 когда повернут мастер ключ. Блокируем управление соленоидами по Ethernet

void InitPort(void)
{
  ADCON1 = 0x0F ;         //  АЦП отключены
  CMCON  = 0x07 ;         //  внутренние компараторы отключены
  PORTA.F7 = 1;           //  RA7=1 PJPU ,
  LATA =0b00000000;       //  LATA7=1 PDPU ,  LATA6=1 PEPU ,
  TRISA=0b11111100;       // RA5 <- FB_B, RA4 <- FB_A

  LATB =0b00000000;
  TRISB=0b00110001;       // RB3 -> RCLK, RB2 -> SRCLK, RB1 -> SIN, RB0 <- SOUT

  LATC =0b00011111;       //  LEDS - G, R, Y - OFF
  TRISC=0b10111000;       // RC2..0 -> LEDS - G, R, Y - OUTPUT, RC4..3 <- INPUTs for I2C

  LATD =0b00000000;
  TRISD=0b10100000;       // RD7 <-  TERMO,  RD6 -> VLO_CTL, RD5 <- CP_OUT, RD4 -> VSW_CTL,
                          // RD3 -> CP_CTL2, RD2 -> CP_CTL1, RD1 -> CP_CTL0, RD0 -> CP_RST
  LATE =0b00000000;
  TRISE=0b11111111;       //

  LATF =0b01101100;       // выбран шлейф 1
  TRISF=0b00000011;       // RF7..2 -> FBS

  LATG =0b11011111;       //                 RG6 -> REN_=1, RG5 -> SRCLR_=0
  TRISG=0b10011111;       // RG7 <- VLO_OK,  RG6 -> REN_, RG5 -> SRCLR_

  LATH =0b00000000;
  TRISH=0b11111111;       //

  LATJ =0b00000000;
  TRISJ=0b11111111;       // RJ7 <- VHI_OK,  RJ5 <- SW2, RJ4 <- SW3, RJ1 <- SW0, RJ0 <- SW1
}


void InitBoard(void)
{
  unsigned char i;

  for (i=0; i<15; i++)
  {
    cellState[i][0]=cellState[i][1]=cellState[i][2]=cellState[i][3]=cellState[i][4]= 0;
    prevCellState[i][0]=prevCellState[i][1]=prevCellState[i][2]=prevCellState[i][3]=prevCellState[i][4]= 0;
    chkSum1[i] = chkSum2[i] = 0;
    cellCommand[i] = 0;
  }
  rxBuf[0]='8';rxBuf[1]='8';rxBuf[2]='8';rxBuf[3]='8';rxBuf[4]='8';rxBuf[5]='8';
  //  инициализация линейки сдвиговых регистров и связанных с ними CMOS ключей
  REN_ = 1;  // TURN ON/OFF CMOS VENTILES  =0/1
  Delay_us(1);  /* 1 microsecond pause */
  SRCLR_= 0;   // RESET REGISTERS
  Delay_us(1);  /* 1 microsecond pause */
  SRCLR_= 1;
  Delay_us(1);  /* 1 microsecond pause */
  Delay_us(1);  /* 1 microsecond pause */
  REN_ = 0;  // // TURN ON/OFF CMOS VENTILES  =0/1

  CP_CTL0=1; //  установка порога сраб защиты по току
  CP_CTL1=1; //
  CP_CTL2=1; //
  CP_RST_=1; //  сброс защелки  защиты по току
  while(i<100) i++;  // задержка
  CP_RST_=0; //
  VLO_CTL = 1;     // 12вольт

  PIR1=0;                                  //Очистили флаги прерываний
  PIR2=0;
  PIR3=0;
  PIE1=0b00000001;                         //Разрешили прерывания от TMR1
  PIE2=0;                                  //Остальные запретили
  PIE3=0;                                  //Инициализация TCP-IP пусть сама себе разрешает
  IPR1.RC1IP = 1;                          //Прерывания по RX USART1 имеют высокий приоритет
  IPR2.ETHIP = 1;                          //Ethernet модуль имеет высокий приоритет
}


// устанавливает время срабатывания таймера кратно 100мкс.
void SetTimer100us(unsigned int value)
{
  unsigned int tmp;

  T1CON=0b00000100;
  tmp = 65535 - value*624;
  TMR1H=(unsigned char) (tmp>>8);
  TMR1L=(unsigned char) tmp;
  timer1Flag=0;
  T1CON.TMR1ON=1; // Запускаем таймер 1
}


// сохраняет данные от очередной ячейки в массивы cellState
// в том случае если ячейка 2 раза подряд ответила одно и то же.
void SaveCellState(unsigned char number)
{
  chkSum1[number] = rxBuf[1] + rxBuf[2] + rxBuf[3] + rxBuf[4] + rxBuf[5];   // контрольная сумма
  if(chkSum1[number]==chkSum2[number]) {                                    // если в прошлый раз контрольная сумма была такой же
    if (number == 14)        //особые условия для 14 ячейки
    {
      cellState[number][0] = rxBuf[1];
      cellState[number][1] = rxBuf[2];  //боковая крышка, если равно 2, то теряется связь со стойкой. если равно 0, то на мнемосхеме открыта, если равна 1, то в логе открыта

      if (rxBuf[3] == '1')              //концевик двери , если 1, то верхняя крышка открыта в логе, если 0, то на мнемосхеме открыта
        cellState[number][2] =  '0';
      else
      {
        if (rxBuf[3] == '0')
          cellState[number][2] =  '1';
        else
          cellState[number][2] = rxBuf[3];
      }

 //     cellState[number][2] = rxBuf[3];
      cellState[number][3] = rxBuf[4];    //мастер ключ
      cellState[number][4] = rxBuf[5];
    }
    else                          //для ячеек с 1 по 13     */
    {
      cellState[number][0] = rxBuf[1];
      if(rxBuf[2]=='0')            //инверсия, если получен '0' и '1' // 20200929 - перепутали NO/NC у микрика B1. Приходится исправлять программно
       {cellState[number][1] = '1';}
      else
      {
        if(rxBuf[2]=='1')
          {cellState[number][1] = '0';}
        else
          {cellState[number][1] = rxBuf[2];} //если получена '2', то оставляем
      }
      cellState[number][2] = rxBuf[3];
      cellState[number][3] = rxBuf[4];
      cellState[number][4] = rxBuf[5];
    }
  }
  chkSum2[number] = chkSum1[number];
}


void WriteChangesLog(unsigned char cell)                  // если текущее состояние ячейки отличается от предыдущего, запишем это в лоХ
{
  unsigned char tmpBuf[30];
  
  if(cell>14) {return;}

  if((prevCellState[cell][0]!=cellState[cell][0])|| \
       (prevCellState[cell][1]!=cellState[cell][1])|| \
       (prevCellState[cell][2]!=cellState[cell][2])|| \
       (prevCellState[cell][3]!=cellState[cell][3])|| \
       (prevCellState[cell][4]!=cellState[cell][4]))  {

     if(cellState[cell][4]!='8') {
       tmpBuf[0] = '_';                                 // в этом чертовом microC нестабильно работает sprintf();
       tmpBuf[1] = '_';
       tmpBuf[2] = 'c';
       tmpBuf[3] = 'e';
       tmpBuf[4] = 'l';
       tmpBuf[5] = 'l';
       tmpBuf[6] = '_';
       tmpBuf[7] = '0'+(cell/10);
       tmpBuf[8] = '0'+(cell%10);
       tmpBuf[9] = '=';

       if((cellState[cell][0]>='0')&&(cellState[cell][0]<'5')) { tmpBuf[10] = cellState[cell][0];}
       else {tmpBuf[10] = '5';}
       tmpBuf[11] =  ',';
       if((cellState[cell][1]>='0')&&(cellState[cell][1]<'5')) { tmpBuf[12] = cellState[cell][1];}
       else {tmpBuf[12] = '5';}
       tmpBuf[13] =  ',';
       if((cellState[cell][2]>='0')&&(cellState[cell][2]<'5')) { tmpBuf[14] = cellState[cell][2];}
       else {tmpBuf[14] = '5';}
       tmpBuf[15] =  ',';
       if((cellState[cell][3]>='0')&&(cellState[cell][3]<'5')) { tmpBuf[16] = cellState[cell][3];}
       else {tmpBuf[16] = '5';}
       tmpBuf[17] =  ',';
       if((cellState[cell][4]>='0')&&(cellState[cell][4]<'5')) { tmpBuf[18] = cellState[cell][4];}
       else {tmpBuf[18] = '5';}
       tmpBuf[19] =  0;
       
       log_write(PORT___,tmpBuf,0);                         // 20 байт
     }
  }
  prevCellState[cell][0] = cellState[cell][0];            // сохраним для следующего раза
  prevCellState[cell][1] = cellState[cell][1];
  prevCellState[cell][2] = cellState[cell][2];
  prevCellState[cell][3] = cellState[cell][3];
  prevCellState[cell][4] = cellState[cell][4];
}


//////////////////////////////////////////////////////
void    main()
{
  unsigned int i, cnt4;
  unsigned char tmp=0, cnt=0, cnt2=0, cnt3=0, cnt5=0, cnt6=0, cnt7=0;
  unsigned char fNoEth = 0;

  InitPort();
  InitBoard();
  MyInitUsart1_115200();
  Termo_measure();

  Led_R=0;  // включить красный сд
  asm CLRWDT;        // сброс сторожевого таймера
  
  Led_Y=0; delay_ms(100);
  Led_Y=1; delay_ms(100);
  Led_Y=0; delay_ms(100);
  Led_Y=1; delay_ms(100);
  Led_Y=0; delay_ms(100);
  Led_Y=1; delay_ms(100);

  cf_r_ptr = 0;
  file_number = 0;   // номер лог - файла на CF
  flag_read_fat = 0;  // FAT в состоянии read =1, иначе 0

  ip_get();                            // чтение IP из EEPROM  при включении питания или после перезапуска
  log_write ( POWER, "", tmp );   // записать в журнал - включение
  asm CLRWDT;
  if ( PORTJ.F1 == 0 ) {   // =0 - ON, =1 - OFF
    myIpAddr[0]  = 192;
    myIpAddr[1]  = 168;
    myIpAddr[2]  = 1;
    myIpAddr[3]  = 60;
    Ethernet_Init(myMacAddr, myIpAddr, Ethernet_HALFDUPLEX) ;
    Ethernet_confNetwork(ipMask, gwIpAddr, dnsIpAddr) ;
    ip_new_flag = 1;          // - флаг запуска в режиме установки нового IP (=1)
    ip_set();                 // установка нового IP и запись его в EEPROM
  }

  ip_new_flag = 0;          // сброс  - флаг запуска в режиме установки нового IP (=1)

  Ethernet_Init(myMacAddr, myIpAddr, Ethernet_HALFDUPLEX) ; //Ethernet_Init(myMacAddr, myIpAddr, Ethernet_FULLDUPLEX) ;
  Ethernet_confNetwork(ipMask, gwIpAddr, dnsIpAddr) ; // dhcp will not be used here, so use preconfigured addresses

  Led_R=1;  // выключить красный сд

  while(1)                                      // do forever
  {
    for(i=1;i<15;i++)
    {
      asm CLRWDT;                               // сброс сторожевого таймера
      SendCommandToCell(i);                     // отправка команды ячейке номер i, т.е. включение или отключение соленоида
      SetTimer100us(8);                         // установим таймер на 0.8мс
      while(timer1Flag==0)                      // крутимся пока не закончится время, отведенное на прием с некоторым запасом, 0,8мс
      {
        Ethernet_doPacket() ;                   // process incoming Ethernet packets
      }
      SaveCellState(i);                         // смотрим на содержимое буфера и сохраняем состояние ячейки в масив если она ответила 2 раза одно и то же
      WriteChangesLog(i);                       // запишем все изменения состояний ячеек если таковые имеются (сравним прошлое и текущее состояние)
    }
    /*
    if((cellState[14][0] == '0')&&(cellState[14][4]!='8')) {   // если пропало основное питание (s=0), отключаю Ethernet
      ECON2.F5=0;
      fNoEth = 1;                               // флаг отсутсвия Ethernet
    }
    else {
      if (fNoEth == 1) {                        // если основное питание отсутствовало но снова появилось, заново запустим Ethernet путем перезагрузки
        asm{ RESET }
        fNoEth = 0;
      }
    }
    */
    if((cellState[14][3] == '1')&&(cellState[14][4]!='8')) {    // если повернули мастер ключ (b3=1), начну разблокировать ячейки
      cnt6=0, cnt7=0;
      fMasterKey = 1;
      cnt2++;
      if (cnt2>20)  {
        cnt2=0;
        if(cnt3<13) {
          cnt3++;
          cellCommand[cnt3] = 1;
        }
        if(cnt4<200) {cnt4++;}                  // если закончился тайм аут (1 минута), начну снова блокировать ячейки для экономии заряда аккумулятора
        else {
          if(cnt5<13) {
            cnt5++;
            cellCommand[cnt5] = 0;
          }
        }
      }
    }
    else {                                      // если мастер ключ отсутствует,
      cnt2=cnt3=cnt4=cnt5=0;
      if(fMasterKey==1) {                       // но был только что установлен,
        cnt7++;
        if (cnt7>20)  {
          cnt7=0;
          if(cnt6<13) {
            cnt6++;
            cellCommand[cnt6] = 0;             // блокируем все ячейки
          }
          else { fMasterKey = 0; }
        }
      }
    }
      
    cnt++;                                     // моргаем светодиодом
    if(cnt>10) {
      Led_G = !Led_G;
      cnt=0;
    }
  }
}

