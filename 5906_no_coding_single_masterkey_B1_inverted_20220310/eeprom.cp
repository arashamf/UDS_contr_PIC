#line 1 "E:/Work/УДС/UDS_controller/ПО (контроллер Раицкого)/5906_no_coding_single_masterkey_B1_inverted_20220310/eeprom.c"
#line 1 "e:/work/УДС/uds_controller/ПО (контроллер Раицкого)/5906_no_coding_single_masterkey_b1_inverted_20220310/def_board.h"
#line 10 "E:/Work/УДС/UDS_controller/ПО (контроллер Раицкого)/5906_no_coding_single_masterkey_B1_inverted_20220310/eeprom.c"
extern unsigned char myMacAddr[6];
extern unsigned char myIpAddr[4];





void ip_write(void)
{

 I2C_Init(100000);
 I2C_Start();
 I2C_Wr(0xA0);
 I2C_Wr(0x00);

 I2C_Wr(myIpAddr[0]);
 I2C_Wr(myIpAddr[1]);
 I2C_Wr(myIpAddr[2]);
 I2C_Wr(myIpAddr[3]);
 I2C_Stop();

 I2C_Start();
 I2C_Wr(0xA0);
 I2C_Wr(0x01);

 I2C_Wr('E');
 I2C_Wr('E');
 I2C_Wr('E');
 I2C_Wr('E');
 I2C_Stop();

 myMacAddr[3] = myIpAddr[1];
 myMacAddr[4] = myIpAddr[2];
 myMacAddr[5] = myIpAddr[3];
}



void ip_read(void)
{
 I2C_Init(100000);
 I2C_Start();
 I2C_Wr(0xA0);
 I2C_Wr(0x00);
 I2C_Repeated_Start();
 I2C_Wr(0xA1);

 myIpAddr[0] =I2C_Rd(1);
 myIpAddr[1] =I2C_Rd(1);
 myIpAddr[2] =I2C_Rd(1);
 myIpAddr[3] =I2C_Rd(0);
 I2C_Stop();

 myMacAddr[3] = myIpAddr[1];
 myMacAddr[4] = myIpAddr[2];
 myMacAddr[5] = myIpAddr[3];
}
