#line 1 "E:/Work/УДС/UDS_controller/ПО (контроллер Раицкого)/5906_no_coding_single_masterkey_B1_inverted_20220310/termo.c"
#line 1 "e:/work/УДС/uds_controller/ПО (контроллер Раицкого)/5906_no_coding_single_masterkey_b1_inverted_20220310/def_board.h"
#line 9 "E:/Work/УДС/UDS_controller/ПО (контроллер Раицкого)/5906_no_coding_single_masterkey_B1_inverted_20220310/termo.c"
unsigned char temperature;



void OneWireDirOut (void)
{
 TRISD.F7 = 0;
}
void OneWireDirIn (void)
{
 TRISD.F7 = 1;
}
void OneWireOn (void)
{
 LATD.F7 = 1;
}
void OneWireOff (void)
{
 LATD.F7 = 0;
}
unsigned int OneWireLevel (void)
{
 if(PORTD.F7==0) return 0;
 if(PORTD.F7!=0) return 1;
}


 unsigned char OneWireReset(void)
{
 OneWireOff();
 OneWireDirOut();
 delay_us(500);
 OneWireDirIn();
 delay_us(70);
 if ((OneWireLevel()) == 0)
 {
 delay_us(500);
 return 1;
 }
 delay_us(500);
 return 0;
}
#line 59 "E:/Work/УДС/UDS_controller/ПО (контроллер Раицкого)/5906_no_coding_single_masterkey_B1_inverted_20220310/termo.c"
void OneWireWriteByte(unsigned char dat)
{
 unsigned char i;

 OneWireDirIn();OneWireOff();
 for (i=0;i<=7;i++)
 {
 OneWireDirOut();
 if (dat & 0x01) {
 delay_us(7);
 OneWireDirIn();
 delay_us(70);
 }
 else {
 delay_us(70);
 OneWireDirIn();
 delay_us(7);
 }
 dat>>=1;
 }
}
#line 87 "E:/Work/УДС/UDS_controller/ПО (контроллер Раицкого)/5906_no_coding_single_masterkey_B1_inverted_20220310/termo.c"
unsigned char OneWireReadByte(void)
{
 unsigned char dat = 0;
 unsigned char i;

 OneWireDirIn();OneWireOff();
 for (i=0;i<=7;i++) {
 OneWireDirOut();
 delay_us(7);
 OneWireDirIn();
 delay_us(7);
 dat >>=1;
 if ((OneWireLevel())) { dat |= 0x80; }
 else { dat &= 0x7f; }
 delay_us(70);
 }
 return dat;
}




unsigned int Termo_measure (void)
{
 unsigned char crc8=0, i=0;
 unsigned char memory[9];

 if(OneWireReset()) {
 OneWireWriteByte(0xCC);
 OneWireWriteByte(0x44);

 while(!OneWireLevel()){}

 OneWireReset();
 OneWireWriteByte(0xCC);
 OneWireWriteByte(0xBE);

 for (i=0;i<9;i++)
 {
 memory[i]=OneWireReadByte();
 }
 return ((memory[1]<<8)+(memory[0]))>>1;
 }
}
