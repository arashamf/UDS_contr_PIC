// USART
#ifndef    def_Board
    #include        "def_Board.h"
#endif

volatile unsigned char rxCounter = 0;       // счетчик прин€тых по UART байтов
volatile unsigned char rxReadyFlag  = 0;    // флаг готовности приемного буфера. =1 когда буфер уже заполнен всеми 5-ю байтами
unsigned char rxBuf[10];                    // буфер дл€ ответов от €чеек
volatile unsigned char timer1Flag = 0;      // флаг того что врем€ вышло
unsigned char cellCommand[15];

void MyInitUsart1_115200(void)
{
 TRISC.F7=1;
 TRISC.F6=0;
 
 TXSTA1.TXEN = 1;
 TXSTA1.SYNC = 0;
 TXSTA1.BRGH = 1;
 RCSTA1.SPEN=1;
 RCSTA1.CREN=1;
 BAUDCON1.BRG16 = 1;
 SPBRGH1 = 0;
 SPBRG1 = 53;

 PIR1.RC1IF = 0;
 IPR1.RC1IP = 0;
 PIE1.RC1IE = 1;
 
 INTCON.GIE = 1;
 INTCON.PEIE = 1;
}


unsigned char MyUsartRead1 (void)
{
 unsigned char tmp;
 while(PIR1.RC1IF==0);
 tmp = RCREG1;
 RCSTA1.CREN=0;
 return tmp;
}


void MyUsartWrite1(unsigned char x)
{
 while(TXSTA1.TRMT==0);   // ждем пока не освободитс€
 TXREG1 = x;              // отправл€ем байт
}


// отправл€ет команду из 4-х байтов заданной €чейке
void SendCommandToCell(unsigned char number)
{
  SET_RS485_OUT;
  Ethernet_doPacket();
  delay_us(10);
  Ethernet_doPacket();
  while(TXSTA1.TRMT==0)
  {
    Ethernet_doPacket();
  }
  TXREG1 = 0x02;                             //  байт є1  - признак начала пакета
  Ethernet_doPacket();
  while(TXSTA1.TRMT==0)
  {
    Ethernet_doPacket();
  }
  TXREG1 = 0x30+number/10;                   //  байт є2   - дес€тки от номера €чейки (dec)
  Ethernet_doPacket();
  while(TXSTA1.TRMT==0)
  {
    Ethernet_doPacket();
  }
  TXREG1 = 0x30+number%10;                   //  байт є3   - единицы номера (dec)
  Ethernet_doPacket();
  while(TXSTA1.TRMT==0)
  {
    Ethernet_doPacket();
  }
  TXREG1 = '0' + cellCommand[number];       //  байт є4   - состо€ние, в которое нужно привести соленоид (в соответствии с командой по  Ethernet)
  while(TXSTA1.TRMT==0);                    // ждем пока не освободитс€ передатчик USART
  SET_RS485_IN;
  delay_us(3);
  RCSTA1.CREN=0;                            // очистим ошибки фрейминга, возникшие из-за переключени€ ADM3485
  RCSTA1.CREN=1;
  rxBuf[0]='8';rxBuf[1]='8';rxBuf[2]='8';rxBuf[3]='8';rxBuf[4]='8';rxBuf[5]='8'; // испортим содержимое приемного буфера чтобы потом знать, пришло что-то новое или нет
  rxReadyFlag = 0;                          // сброс флага готовности приемного буфера
}


void UsartSendBuf(char* str)
{
  while((*str)!=0)
  {
   MyUsartWrite1(*str++);
  }
  MyUsartWrite1(0x0d);
  MyUsartWrite1(0x0a);
}


void Interrupt(void)
{
 unsigned char tmp;
 
 if(PIR1.RC1IF) {           // прерывание по приему байта по USART
  PIR1.RC1IF = 0;

  tmp = RCREG1;
  if (tmp==0x03) {          // 0x03 - признак начала посылки
   rxCounter = 1;
  }
  if (rxCounter!=0) {
   rxBuf[rxCounter-1] = tmp;
   rxCounter++;
   if(rxCounter>=7) {       // если вс€ посылка уже получена (6 байт),
    rxCounter = 0;          // обнул€ем счетчик
    rxReadyFlag = 1;        // ставим флаг готовности
   }
  }
 }
 if (PIR1.F0) {             // ѕроизошло прерывание от TMR1
  PIR1.F0=0;
  T1CON=0;
  timer1Flag = 1;           // врем€ вышло
 }
}

