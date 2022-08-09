#line 1 "E:/Work/УДС/UDS_controller/ПО (контроллер Раицкого)/5906_no_coding_single_masterkey_B1_inverted_20220310/USART.c"
#line 1 "e:/work/УДС/uds_controller/ПО (контроллер Раицкого)/5906_no_coding_single_masterkey_b1_inverted_20220310/def_board.h"
#line 6 "E:/Work/УДС/UDS_controller/ПО (контроллер Раицкого)/5906_no_coding_single_masterkey_B1_inverted_20220310/USART.c"
volatile unsigned char rxCounter = 0;
volatile unsigned char rxReadyFlag = 0;
unsigned char rxBuf[10];
volatile unsigned char timer1Flag = 0;
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
 while(TXSTA1.TRMT==0);
 TXREG1 = x;
}



void SendCommandToCell(unsigned char number)
{
  PORTB.F6 =1; PORTB.F7 =1; ;
 Ethernet_doPacket();
 delay_us(10);
 Ethernet_doPacket();
 while(TXSTA1.TRMT==0)
 {
 Ethernet_doPacket();
 }
 TXREG1 = 0x02;
 Ethernet_doPacket();
 while(TXSTA1.TRMT==0)
 {
 Ethernet_doPacket();
 }
 TXREG1 = 0x30+number/10;
 Ethernet_doPacket();
 while(TXSTA1.TRMT==0)
 {
 Ethernet_doPacket();
 }
 TXREG1 = 0x30+number%10;
 Ethernet_doPacket();
 while(TXSTA1.TRMT==0)
 {
 Ethernet_doPacket();
 }
 TXREG1 = '0' + cellCommand[number];
 while(TXSTA1.TRMT==0);
  PORTB.F6 =0; PORTB.F7 =0; ;
 delay_us(3);
 RCSTA1.CREN=0;
 RCSTA1.CREN=1;
 rxBuf[0]='8';rxBuf[1]='8';rxBuf[2]='8';rxBuf[3]='8';rxBuf[4]='8';rxBuf[5]='8';
 rxReadyFlag = 0;
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

 if(PIR1.RC1IF) {
 PIR1.RC1IF = 0;

 tmp = RCREG1;
 if (tmp==0x03) {
 rxCounter = 1;
 }
 if (rxCounter!=0) {
 rxBuf[rxCounter-1] = tmp;
 rxCounter++;
 if(rxCounter>=7) {
 rxCounter = 0;
 rxReadyFlag = 1;
 }
 }
 }
 if (PIR1.F0) {
 PIR1.F0=0;
 T1CON=0;
 timer1Flag = 1;
 }
}
