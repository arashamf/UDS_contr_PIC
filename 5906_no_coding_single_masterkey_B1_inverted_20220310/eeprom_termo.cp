#line 1 "D:/_BOB/___WORK/_RTC EEPROM/30_testIP/eeprom_termo.c"
#line 1 "d:/_bob/___work/_rtc eeprom/30_testip/def_board.h"
#line 11 "D:/_BOB/___WORK/_RTC EEPROM/30_testIP/eeprom_termo.c"
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

myIpAddr[3] =I2C_Rd(1);

 I2C_Stop();


}
