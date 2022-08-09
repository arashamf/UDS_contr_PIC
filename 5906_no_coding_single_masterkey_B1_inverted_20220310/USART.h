
extern volatile unsigned char rxCounter;
extern volatile unsigned char rxReadyFlag;
extern unsigned char rxBuf[6];
extern volatile unsigned char timer1Flag;
extern unsigned char cellCommand[14];
 
void sendCommandToCell(unsigned char number);
void MyInitUsart1_115200(void);
unsigned char MyUsartRead1 (void);
void MyUsartWrite1(unsigned char x);
void RS485SendAuto(unsigned char a1,unsigned char a2,unsigned char a3,unsigned char a4);
