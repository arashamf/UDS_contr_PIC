 //  ������������� � ������� ����

#include        "def_Board.h"
#include        "test18f97.h"
#include        "USART.h"

unsigned int Termo_measure();
unsigned char fMasterKey = 0;         // ���� = 1 ����� �������� ������ ����. ��������� ���������� ����������� �� Ethernet

void InitPort(void)
{
  ADCON1 = 0x0F ;         //  ��� ���������
  CMCON  = 0x07 ;         //  ���������� ����������� ���������
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

  LATF =0b01101100;       // ������ ����� 1
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
  //  ������������� ������� ��������� ��������� � ��������� � ���� CMOS ������
  REN_ = 1;  // TURN ON/OFF CMOS VENTILES  =0/1
  Delay_us(1);  /* 1 microsecond pause */
  SRCLR_= 0;   // RESET REGISTERS
  Delay_us(1);  /* 1 microsecond pause */
  SRCLR_= 1;
  Delay_us(1);  /* 1 microsecond pause */
  Delay_us(1);  /* 1 microsecond pause */
  REN_ = 0;  // // TURN ON/OFF CMOS VENTILES  =0/1

  CP_CTL0=1; //  ��������� ������ ���� ������ �� ����
  CP_CTL1=1; //
  CP_CTL2=1; //
  CP_RST_=1; //  ����� �������  ������ �� ����
  while(i<100) i++;  // ��������
  CP_RST_=0; //
  VLO_CTL = 1;     // 12�����

  PIR1=0;                                  //�������� ����� ����������
  PIR2=0;
  PIR3=0;
  PIE1=0b00000001;                         //��������� ���������� �� TMR1
  PIE2=0;                                  //��������� ���������
  PIE3=0;                                  //������������� TCP-IP ����� ���� ���� ���������
  IPR1.RC1IP = 1;                          //���������� �� RX USART1 ����� ������� ���������
  IPR2.ETHIP = 1;                          //Ethernet ������ ����� ������� ���������
}


// ������������� ����� ������������ ������� ������ 100���.
void SetTimer100us(unsigned int value)
{
  unsigned int tmp;

  T1CON=0b00000100;
  tmp = 65535 - value*624;
  TMR1H=(unsigned char) (tmp>>8);
  TMR1L=(unsigned char) tmp;
  timer1Flag=0;
  T1CON.TMR1ON=1; // ��������� ������ 1
}


// ��������� ������ �� ��������� ������ � ������� cellState
// � ��� ������ ���� ������ 2 ���� ������ �������� ���� � �� ��.
void SaveCellState(unsigned char number)
{
  chkSum1[number] = rxBuf[1] + rxBuf[2] + rxBuf[3] + rxBuf[4] + rxBuf[5];   // ����������� �����
  if(chkSum1[number]==chkSum2[number]) {                                    // ���� � ������� ��� ����������� ����� ���� ����� ��
    if (number == 14)        //������ ������� ��� 14 ������
    {
      cellState[number][0] = rxBuf[1];
      cellState[number][1] = rxBuf[2];  //������� ������, ���� ����� 2, �� �������� ����� �� �������. ���� ����� 0, �� �� ���������� �������, ���� ����� 1, �� � ���� �������

      if (rxBuf[3] == '1')              //�������� ����� , ���� 1, �� ������� ������ ������� � ����, ���� 0, �� �� ���������� �������
        cellState[number][2] =  '0';
      else
      {
        if (rxBuf[3] == '0')
          cellState[number][2] =  '1';
        else
          cellState[number][2] = rxBuf[3];
      }

 //     cellState[number][2] = rxBuf[3];
      cellState[number][3] = rxBuf[4];    //������ ����
      cellState[number][4] = rxBuf[5];
    }
    else                          //��� ����� � 1 �� 13     */
    {
      cellState[number][0] = rxBuf[1];
      if(rxBuf[2]=='0')            //��������, ���� ������� '0' � '1' // 20200929 - ���������� NO/NC � ������� B1. ���������� ���������� ����������
       {cellState[number][1] = '1';}
      else
      {
        if(rxBuf[2]=='1')
          {cellState[number][1] = '0';}
        else
          {cellState[number][1] = rxBuf[2];} //���� �������� '2', �� ���������
      }
      cellState[number][2] = rxBuf[3];
      cellState[number][3] = rxBuf[4];
      cellState[number][4] = rxBuf[5];
    }
  }
  chkSum2[number] = chkSum1[number];
}


void WriteChangesLog(unsigned char cell)                  // ���� ������� ��������� ������ ���������� �� �����������, ������� ��� � ���
{
  unsigned char tmpBuf[30];
  
  if(cell>14) {return;}

  if((prevCellState[cell][0]!=cellState[cell][0])|| \
       (prevCellState[cell][1]!=cellState[cell][1])|| \
       (prevCellState[cell][2]!=cellState[cell][2])|| \
       (prevCellState[cell][3]!=cellState[cell][3])|| \
       (prevCellState[cell][4]!=cellState[cell][4]))  {

     if(cellState[cell][4]!='8') {
       tmpBuf[0] = '_';                                 // � ���� �������� microC ����������� �������� sprintf();
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
       
       log_write(PORT___,tmpBuf,0);                         // 20 ����
     }
  }
  prevCellState[cell][0] = cellState[cell][0];            // �������� ��� ���������� ����
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

  Led_R=0;  // �������� ������� ��
  asm CLRWDT;        // ����� ����������� �������
  
  Led_Y=0; delay_ms(100);
  Led_Y=1; delay_ms(100);
  Led_Y=0; delay_ms(100);
  Led_Y=1; delay_ms(100);
  Led_Y=0; delay_ms(100);
  Led_Y=1; delay_ms(100);

  cf_r_ptr = 0;
  file_number = 0;   // ����� ��� - ����� �� CF
  flag_read_fat = 0;  // FAT � ��������� read =1, ����� 0

  ip_get();                            // ������ IP �� EEPROM  ��� ��������� ������� ��� ����� �����������
  log_write ( POWER, "", tmp );   // �������� � ������ - ���������
  asm CLRWDT;
  if ( PORTJ.F1 == 0 ) {   // =0 - ON, =1 - OFF
    myIpAddr[0]  = 192;
    myIpAddr[1]  = 168;
    myIpAddr[2]  = 1;
    myIpAddr[3]  = 60;
    Ethernet_Init(myMacAddr, myIpAddr, Ethernet_HALFDUPLEX) ;
    Ethernet_confNetwork(ipMask, gwIpAddr, dnsIpAddr) ;
    ip_new_flag = 1;          // - ���� ������� � ������ ��������� ������ IP (=1)
    ip_set();                 // ��������� ������ IP � ������ ��� � EEPROM
  }

  ip_new_flag = 0;          // �����  - ���� ������� � ������ ��������� ������ IP (=1)

  Ethernet_Init(myMacAddr, myIpAddr, Ethernet_HALFDUPLEX) ; //Ethernet_Init(myMacAddr, myIpAddr, Ethernet_FULLDUPLEX) ;
  Ethernet_confNetwork(ipMask, gwIpAddr, dnsIpAddr) ; // dhcp will not be used here, so use preconfigured addresses

  Led_R=1;  // ��������� ������� ��

  while(1)                                      // do forever
  {
    for(i=1;i<15;i++)
    {
      asm CLRWDT;                               // ����� ����������� �������
      SendCommandToCell(i);                     // �������� ������� ������ ����� i, �.�. ��������� ��� ���������� ���������
      SetTimer100us(8);                         // ��������� ������ �� 0.8��
      while(timer1Flag==0)                      // �������� ���� �� ���������� �����, ���������� �� ����� � ��������� �������, 0,8��
      {
        Ethernet_doPacket() ;                   // process incoming Ethernet packets
      }
      SaveCellState(i);                         // ������� �� ���������� ������ � ��������� ��������� ������ � ����� ���� ��� �������� 2 ���� ���� � �� ��
      WriteChangesLog(i);                       // ������� ��� ��������� ��������� ����� ���� ������� ������� (������� ������� � ������� ���������)
    }
    /*
    if((cellState[14][0] == '0')&&(cellState[14][4]!='8')) {   // ���� ������� �������� ������� (s=0), �������� Ethernet
      ECON2.F5=0;
      fNoEth = 1;                               // ���� ��������� Ethernet
    }
    else {
      if (fNoEth == 1) {                        // ���� �������� ������� ������������� �� ����� ���������, ������ �������� Ethernet ����� ������������
        asm{ RESET }
        fNoEth = 0;
      }
    }
    */
    if((cellState[14][3] == '1')&&(cellState[14][4]!='8')) {    // ���� ��������� ������ ���� (b3=1), ����� �������������� ������
      cnt6=0, cnt7=0;
      fMasterKey = 1;
      cnt2++;
      if (cnt2>20)  {
        cnt2=0;
        if(cnt3<13) {
          cnt3++;
          cellCommand[cnt3] = 1;
        }
        if(cnt4<200) {cnt4++;}                  // ���� ���������� ���� ��� (1 ������), ����� ����� ����������� ������ ��� �������� ������ ������������
        else {
          if(cnt5<13) {
            cnt5++;
            cellCommand[cnt5] = 0;
          }
        }
      }
    }
    else {                                      // ���� ������ ���� �����������,
      cnt2=cnt3=cnt4=cnt5=0;
      if(fMasterKey==1) {                       // �� ��� ������ ��� ����������,
        cnt7++;
        if (cnt7>20)  {
          cnt7=0;
          if(cnt6<13) {
            cnt6++;
            cellCommand[cnt6] = 0;             // ��������� ��� ������
          }
          else { fMasterKey = 0; }
        }
      }
    }
      
    cnt++;                                     // ������� �����������
    if(cnt>10) {
      Led_G = !Led_G;
      cnt=0;
    }
  }
}

