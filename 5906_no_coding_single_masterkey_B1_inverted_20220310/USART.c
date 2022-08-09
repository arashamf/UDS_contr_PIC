// USART
#ifndef    def_Board
    #include        "def_Board.h"
#endif

volatile unsigned char rxCounter = 0;       // ������� �������� �� UART ������
volatile unsigned char rxReadyFlag  = 0;    // ���� ���������� ��������� ������. =1 ����� ����� ��� �������� ����� 5-� �������
unsigned char rxBuf[10];                    // ����� ��� ������� �� �����
volatile unsigned char timer1Flag = 0;      // ���� ���� ��� ����� �����
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
 while(TXSTA1.TRMT==0);   // ���� ���� �� �����������
 TXREG1 = x;              // ���������� ����
}


// ���������� ������� �� 4-� ������ �������� ������
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
  TXREG1 = 0x02;                             //  ���� �1  - ������� ������ ������
  Ethernet_doPacket();
  while(TXSTA1.TRMT==0)
  {
    Ethernet_doPacket();
  }
  TXREG1 = 0x30+number/10;                   //  ���� �2   - ������� �� ������ ������ (dec)
  Ethernet_doPacket();
  while(TXSTA1.TRMT==0)
  {
    Ethernet_doPacket();
  }
  TXREG1 = 0x30+number%10;                   //  ���� �3   - ������� ������ (dec)
  Ethernet_doPacket();
  while(TXSTA1.TRMT==0)
  {
    Ethernet_doPacket();
  }
  TXREG1 = '0' + cellCommand[number];       //  ���� �4   - ���������, � ������� ����� �������� �������� (� ������������ � �������� ��  Ethernet)
  while(TXSTA1.TRMT==0);                    // ���� ���� �� ����������� ���������� USART
  SET_RS485_IN;
  delay_us(3);
  RCSTA1.CREN=0;                            // ������� ������ ���������, ��������� ��-�� ������������ ADM3485
  RCSTA1.CREN=1;
  rxBuf[0]='8';rxBuf[1]='8';rxBuf[2]='8';rxBuf[3]='8';rxBuf[4]='8';rxBuf[5]='8'; // �������� ���������� ��������� ������ ����� ����� �����, ������ ���-�� ����� ��� ���
  rxReadyFlag = 0;                          // ����� ����� ���������� ��������� ������
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
 
 if(PIR1.RC1IF) {           // ���������� �� ������ ����� �� USART
  PIR1.RC1IF = 0;

  tmp = RCREG1;
  if (tmp==0x03) {          // 0x03 - ������� ������ �������
   rxCounter = 1;
  }
  if (rxCounter!=0) {
   rxBuf[rxCounter-1] = tmp;
   rxCounter++;
   if(rxCounter>=7) {       // ���� ��� ������� ��� �������� (6 ����),
    rxCounter = 0;          // �������� �������
    rxReadyFlag = 1;        // ������ ���� ����������
   }
  }
 }
 if (PIR1.F0) {             // ��������� ���������� �� TMR1
  PIR1.F0=0;
  T1CON=0;
  timer1Flag = 1;           // ����� �����
 }
}

