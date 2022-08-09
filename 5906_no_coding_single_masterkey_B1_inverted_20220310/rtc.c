//

//

char tnum[4];

extern unsigned char month, day, date, year, hour, minute, second;
extern unsigned char   dyna[122] ; // строка для хранения промежуточных данных


void form_num (unsigned char num)   //запись в строку  tnum числа  num, замена пробелов на 0
{
  ByteToStr(num, tnum) ;
  if (tnum[0] == ' ')  tnum[0] = '0';
  if (tnum[1] == ' ')  tnum[1] = '0';
  tnum[3] = '\0';
}

//--------------------- Reads time and date information from RTC
void Read_Time(void)    //чтение часов
{
  unsigned char tsecond,tminute,thour,tday,tdate,tmonth,tyear;
  
  I2C_Init(100000);         // initialize I2C
  I2C_Start();
  I2C_Wr(0xD0);                 // Slave address DS1338, write to RTC
  I2C_Wr(0x00);                 // Byte adress
  I2C_Repeated_Start();
  I2C_Wr(0xD1);                 // Slave address DS1338, read from RTC
  tsecond =I2C_Rd(1);
  tminute =I2C_Rd(1);
  thour =I2C_Rd(1);
  tday =I2C_Rd(1);
  tdate =I2C_Rd(1);
  tmonth =I2C_Rd(1);
  tyear =I2C_Rd(0);              // LAST DATA BYTE IS FOLLOWED BY A NACK
  I2C_Stop();

  second  =  ((tsecond & 0xF0) >> 4)*10 + (tsecond & 0x0F);
  minute  =  ((tminute & 0xF0) >> 4)*10 + (tminute & 0x0F);
  hour    =  ((thour & 0xF0) >> 4)*10 + (thour & 0x0F);
  date    =  ((tdate & 0xF0) >> 4)*10 + (tdate & 0x0F);
  month   =  ((tmonth & 0xF0) >> 4)*10 + (tmonth & 0x0F);
  year    =  ((tyear & 0xF0) >> 4)*10 + (tyear & 0x0F);
}//~


//-------------------- Output values to LCD
void Display_Time()
{
   dyna[0] = '\0';
   form_num (date);   //запись в строку  tnum числа  day
   strncat (dyna, tnum, 3);
   form_num (month);
   strncat (dyna, tnum, 3);
   form_num (year);
   strncat (dyna, tnum, 3);

   form_num (hour);   //запись в строку  tnum числа  hr
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

}//~


//-----------------
void rtc_read(void)     //  Чтение RTC  в dyna[]  18 символов
{
  Read_Time();      // чтение часов
  Display_Time();    // вывод в ETHERNET
}


////////////////////////////////////////////////////////////////////////////////////////////

void rtc_set(void)
{

   I2C_Init(100000);      // initialize full master mode
   I2C_Start();          // issue start signal
   I2C_Wr(0xD0);                 // Slave address DS1338, write to RTC
   I2C_Wr(0x00);                 // Byte adress
   //
   I2C_Wr(((second/10)<<4)+(second%10));            // write 0 to seconds word
   I2C_Wr(((minute/10)<<4)+(minute%10));         // write  to minutes word
   I2C_Wr(((hour/10)<<4)+(hour%10));         // write  to hours word
   I2C_Wr(0x07);         // write  to day word
   I2C_Wr(((date/10)<<4)+(date%10));         // write  to date
   I2C_Wr(((month/10)<<4)+(month%10));         // write  to month
   I2C_Wr(((year/10)<<4)+(year%10));         // write  to year
   I2C_Wr(0x00);         // write  to control
   I2C_Stop();           // issue stop signal

}




