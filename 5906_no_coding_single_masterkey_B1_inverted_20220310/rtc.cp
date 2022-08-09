#line 1 "E:/Work/УДС/UDS_controller/ПО (контроллер Раицкого)/5906_no_coding_single_masterkey_B1_inverted_20220310/rtc.c"




char tnum[4];

extern unsigned char month, day, date, year, hour, minute, second;
extern unsigned char dyna[122] ;


void form_num (unsigned char num)
{
 ByteToStr(num, tnum) ;
 if (tnum[0] == ' ') tnum[0] = '0';
 if (tnum[1] == ' ') tnum[1] = '0';
 tnum[3] = '\0';
}


void Read_Time(void)
{
 unsigned char tsecond,tminute,thour,tday,tdate,tmonth,tyear;

 I2C_Init(100000);
 I2C_Start();
 I2C_Wr(0xD0);
 I2C_Wr(0x00);
 I2C_Repeated_Start();
 I2C_Wr(0xD1);
 tsecond =I2C_Rd(1);
 tminute =I2C_Rd(1);
 thour =I2C_Rd(1);
 tday =I2C_Rd(1);
 tdate =I2C_Rd(1);
 tmonth =I2C_Rd(1);
 tyear =I2C_Rd(0);
 I2C_Stop();

 second = ((tsecond & 0xF0) >> 4)*10 + (tsecond & 0x0F);
 minute = ((tminute & 0xF0) >> 4)*10 + (tminute & 0x0F);
 hour = ((thour & 0xF0) >> 4)*10 + (thour & 0x0F);
 date = ((tdate & 0xF0) >> 4)*10 + (tdate & 0x0F);
 month = ((tmonth & 0xF0) >> 4)*10 + (tmonth & 0x0F);
 year = ((tyear & 0xF0) >> 4)*10 + (tyear & 0x0F);
}



void Display_Time()
{
 dyna[0] = '\0';
 form_num (date);
 strncat (dyna, tnum, 3);
 form_num (month);
 strncat (dyna, tnum, 3);
 form_num (year);
 strncat (dyna, tnum, 3);

 form_num (hour);
 strncat (dyna, tnum, 3);
 form_num (minute);
 strncat (dyna, tnum, 3);
 form_num (second);
 strncat (dyna, tnum, 3);
 dyna[0] = '_';
 dyna[3] = '/';
 dyna[6] = '/';
 dyna[9] = '_';
 dyna[12] = ':';
 dyna[15] = ':';

}



void rtc_read(void)
{
 Read_Time();
 Display_Time();
}




void rtc_set(void)
{

 I2C_Init(100000);
 I2C_Start();
 I2C_Wr(0xD0);
 I2C_Wr(0x00);

 I2C_Wr(((second/10)<<4)+(second%10));
 I2C_Wr(((minute/10)<<4)+(minute%10));
 I2C_Wr(((hour/10)<<4)+(hour%10));
 I2C_Wr(0x07);
 I2C_Wr(((date/10)<<4)+(date%10));
 I2C_Wr(((month/10)<<4)+(month%10));
 I2C_Wr(((year/10)<<4)+(year%10));
 I2C_Wr(0x00);
 I2C_Stop();

}
