#line 1 "E:/Work/УДС/UDS_controller/ПО (контроллер Раицкого)/5906_no_coding_single_masterkey_B1_inverted_20220310/test18f97.c"
#line 1 "e:/work/УДС/uds_controller/ПО (контроллер Раицкого)/5906_no_coding_single_masterkey_b1_inverted_20220310/def_board.h"
#line 1 "e:/work/УДС/uds_controller/ПО (контроллер Раицкого)/5906_no_coding_single_masterkey_b1_inverted_20220310/test18f97.h"






unsigned char cmd_port_num;

unsigned char cellState[15][5];
unsigned char prevCellState[15][5];
unsigned int chkSum1[15],chkSum2[15];

unsigned char lim_ventil;

unsigned char month, day, date, year, hour, minute, second;

unsigned int file_number;
unsigned char visocosny;


unsigned char ip_new_flag;

unsigned char l_st_ok ;
unsigned char lines_st_ok ;

unsigned char flag_cf_log;
unsigned char flag_read_fat;





extern unsigned char myMacAddr[6];
extern unsigned char myIpAddr[4];
extern unsigned char gwIpAddr[4];
extern unsigned char ipMask[4];
extern unsigned char dnsIpAddr[4];
extern unsigned long cf_r_ptr ;

extern char log_write ( char type, char *inf , char regim);
extern unsigned char Set_fnum(void);

extern void ip_set( void);
extern void ip_get( void);
void WriteChangesLog(unsigned char cell);
#line 1 "e:/work/УДС/uds_controller/ПО (контроллер Раицкого)/5906_no_coding_single_masterkey_b1_inverted_20220310/usart.h"

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
#line 7 "E:/Work/УДС/UDS_controller/ПО (контроллер Раицкого)/5906_no_coding_single_masterkey_B1_inverted_20220310/test18f97.c"
unsigned int Termo_measure();
unsigned char fMasterKey = 0;

void InitPort(void)
{
 ADCON1 = 0x0F ;
 CMCON = 0x07 ;
 PORTA.F7 = 1;
 LATA =0b00000000;
 TRISA=0b11111100;

 LATB =0b00000000;
 TRISB=0b00110001;

 LATC =0b00011111;
 TRISC=0b10111000;

 LATD =0b00000000;
 TRISD=0b10100000;

 LATE =0b00000000;
 TRISE=0b11111111;

 LATF =0b01101100;
 TRISF=0b00000011;

 LATG =0b11011111;
 TRISG=0b10011111;

 LATH =0b00000000;
 TRISH=0b11111111;

 LATJ =0b00000000;
 TRISJ=0b11111111;
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

  PORTG.F6  = 1;
 Delay_us(1);
  PORTG.F5 = 0;
 Delay_us(1);
  PORTG.F5 = 1;
 Delay_us(1);
 Delay_us(1);
  PORTG.F6  = 0;

  PORTD.F1 =1;
  PORTD.F2 =1;
  PORTD.F3 =1;
  PORTD.F0 =1;
 while(i<100) i++;
  PORTD.F0 =0;
  PORTD.F6  = 1;

 PIR1=0;
 PIR2=0;
 PIR3=0;
 PIE1=0b00000001;
 PIE2=0;
 PIE3=0;
 IPR1.RC1IP = 1;
 IPR2.ETHIP = 1;
}



void SetTimer100us(unsigned int value)
{
 unsigned int tmp;

 T1CON=0b00000100;
 tmp = 65535 - value*624;
 TMR1H=(unsigned char) (tmp>>8);
 TMR1L=(unsigned char) tmp;
 timer1Flag=0;
 T1CON.TMR1ON=1;
}




void SaveCellState(unsigned char number)
{
 chkSum1[number] = rxBuf[1] + rxBuf[2] + rxBuf[3] + rxBuf[4] + rxBuf[5];
 if(chkSum1[number]==chkSum2[number]) {
 if (number == 14)
 {
 cellState[number][0] = rxBuf[1];
 cellState[number][1] = rxBuf[2];

 if (rxBuf[3] == '1')
 cellState[number][2] = '0';
 else
 {
 if (rxBuf[3] == '0')
 cellState[number][2] = '1';
 else
 cellState[number][2] = rxBuf[3];
 }


 cellState[number][3] = rxBuf[4];
 cellState[number][4] = rxBuf[5];
 }
 else
 {
 cellState[number][0] = rxBuf[1];
 if(rxBuf[2]=='0')
 {cellState[number][1] = '1';}
 else
 {
 if(rxBuf[2]=='1')
 {cellState[number][1] = '0';}
 else
 {cellState[number][1] = rxBuf[2];}
 }
 cellState[number][2] = rxBuf[3];
 cellState[number][3] = rxBuf[4];
 cellState[number][4] = rxBuf[5];
 }
 }
 chkSum2[number] = chkSum1[number];
}


void WriteChangesLog(unsigned char cell)
{
 unsigned char tmpBuf[30];

 if(cell>14) {return;}
#line 155 "E:/Work/УДС/UDS_controller/ПО (контроллер Раицкого)/5906_no_coding_single_masterkey_B1_inverted_20220310/test18f97.c"
 if((prevCellState[cell][0]!=cellState[cell][0])|| (prevCellState[cell][1]!=cellState[cell][1])|| (prevCellState[cell][2]!=cellState[cell][2])|| (prevCellState[cell][3]!=cellState[cell][3])|| (prevCellState[cell][4]!=cellState[cell][4])) {

 if(cellState[cell][4]!='8') {
 tmpBuf[0] = '_';
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
 tmpBuf[11] = ',';
 if((cellState[cell][1]>='0')&&(cellState[cell][1]<'5')) { tmpBuf[12] = cellState[cell][1];}
 else {tmpBuf[12] = '5';}
 tmpBuf[13] = ',';
 if((cellState[cell][2]>='0')&&(cellState[cell][2]<'5')) { tmpBuf[14] = cellState[cell][2];}
 else {tmpBuf[14] = '5';}
 tmpBuf[15] = ',';
 if((cellState[cell][3]>='0')&&(cellState[cell][3]<'5')) { tmpBuf[16] = cellState[cell][3];}
 else {tmpBuf[16] = '5';}
 tmpBuf[17] = ',';
 if((cellState[cell][4]>='0')&&(cellState[cell][4]<'5')) { tmpBuf[18] = cellState[cell][4];}
 else {tmpBuf[18] = '5';}
 tmpBuf[19] = 0;

 log_write( 4 ,tmpBuf,0);
 }
 }
 prevCellState[cell][0] = cellState[cell][0];
 prevCellState[cell][1] = cellState[cell][1];
 prevCellState[cell][2] = cellState[cell][2];
 prevCellState[cell][3] = cellState[cell][3];
 prevCellState[cell][4] = cellState[cell][4];
}



void main()
{
 unsigned int i, cnt4;
 unsigned char tmp=0, cnt=0, cnt2=0, cnt3=0, cnt5=0, cnt6=0, cnt7=0;
 unsigned char fNoEth = 0;

 InitPort();
 InitBoard();
 MyInitUsart1_115200();
 Termo_measure();

  PORTC.F0 =0;
 asm CLRWDT;

  PORTC.F1 =0; delay_ms(100);
  PORTC.F1 =1; delay_ms(100);
  PORTC.F1 =0; delay_ms(100);
  PORTC.F1 =1; delay_ms(100);
  PORTC.F1 =0; delay_ms(100);
  PORTC.F1 =1; delay_ms(100);

 cf_r_ptr = 0;
 file_number = 0;
 flag_read_fat = 0;

 ip_get();
 log_write (  1 , "", tmp );
 asm CLRWDT;
 if ( PORTJ.F1 == 0 ) {
 myIpAddr[0] = 192;
 myIpAddr[1] = 168;
 myIpAddr[2] = 1;
 myIpAddr[3] = 60;
 Ethernet_Init(myMacAddr, myIpAddr,  0 ) ;
 Ethernet_confNetwork(ipMask, gwIpAddr, dnsIpAddr) ;
 ip_new_flag = 1;
 ip_set();
 }

 ip_new_flag = 0;

 Ethernet_Init(myMacAddr, myIpAddr,  0 ) ;
 Ethernet_confNetwork(ipMask, gwIpAddr, dnsIpAddr) ;

  PORTC.F0 =1;

 while(1)
 {
 for(i=1;i<15;i++)
 {
 asm CLRWDT;
 SendCommandToCell(i);
 SetTimer100us(8);
 while(timer1Flag==0)
 {
 Ethernet_doPacket() ;
 }
 SaveCellState(i);
 WriteChangesLog(i);
 }
#line 269 "E:/Work/УДС/UDS_controller/ПО (контроллер Раицкого)/5906_no_coding_single_masterkey_B1_inverted_20220310/test18f97.c"
 if((cellState[14][3] == '1')&&(cellState[14][4]!='8')) {
 cnt6=0, cnt7=0;
 fMasterKey = 1;
 cnt2++;
 if (cnt2>20) {
 cnt2=0;
 if(cnt3<13) {
 cnt3++;
 cellCommand[cnt3] = 1;
 }
 if(cnt4<200) {cnt4++;}
 else {
 if(cnt5<13) {
 cnt5++;
 cellCommand[cnt5] = 0;
 }
 }
 }
 }
 else {
 cnt2=cnt3=cnt4=cnt5=0;
 if(fMasterKey==1) {
 cnt7++;
 if (cnt7>20) {
 cnt7=0;
 if(cnt6<13) {
 cnt6++;
 cellCommand[cnt6] = 0;
 }
 else { fMasterKey = 0; }
 }
 }
 }

 cnt++;
 if(cnt>10) {
  PORTC.F2  = ! PORTC.F2 ;
 cnt=0;
 }
 }
}
