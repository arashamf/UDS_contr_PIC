// файл log.c
// Функции записи строк в журнал CF
//
#ifndef    def_Board
    #include        "def_Board.h"
#endif

char date_string[10] = " 00/00/00";
char time_string[10] = " 00:00:00";
char ip_string[17] = "000.000.000.000.";
char tmp_string[40];

void Get_Ip_Time(void );


extern unsigned char   myIpAddr[4];             // my IP address
extern unsigned char   dyna[122] ; // строка для хранения промежуточных данных
//  RTC часы реального времени
extern unsigned char month, day, date, year, hour, minute, second;
extern unsigned int file_number;  // номер лог - файла на CF
extern void rtc_read(void);     //  Чтение RTC  в dyna[]

extern void Read_Time(void);    //Reads time and date information from RTC


extern unsigned char Set_fnum(void);      // обновление номера файла журнала =0-err, =1-файл пуст, =2-год соответствует текущему, =3-прошлогодний
void l_w_port3(unsigned char cmd_port_num);   //запись в строку dyna начала строки с номером порта (15 символов)

extern  unsigned char  cf_line_num[41];    // [1..40] признак записи: для записи на CF  =0-нет записи =1 запись
extern  unsigned char  cf_line_state[41];    // [1..40] состояние линии шлейфа: для записи на CF
extern  unsigned char  cf_port_state[41];    // [1..40] состояние ячейки: для записи на CF
extern  unsigned char  cf_door_state[41];    // [1..40] состояние микровыключателя (дверцы):для записи на CF

extern  unsigned char  flag_read_fat;  // FAT в состоянии read =1, иначе 0
//

char log_write ( char type, char *inf , char regim)      // возвращает результат выполнения записи =1  - ok, =0 - error
{
  // type - тип записи
  //             POWER     1
  //             COMMAND   2
  //             CMD       3
  //             PORT___   4
  //             IP        5
  //             TIME      6

  // inf  - инф-я строка
  //regim - результат обновления номера файла журнала =0-err, =1-файл пуст, =2-год соответствует текущему, =3-прошлогодний

  unsigned char    tmp,i;
  char LOG_TXT[13] = "LOG__001.TXT";
  char NUM_TXT[7] = "   001";
  unsigned char   dyna2[130]= ""; // строка для хранения промежуточных данных

  Led_R=0;  // включить красный сд
  flag_read_fat = 0;  // FAT в состоянии read =1, иначе 0

  tmp =Set_fnum();  // обновление номера файла журнала =0-err, =1-файл пуст, =2-год соответствует текущему, =3-прошлогодний
  if ( tmp == 0 ) {Led_R=1; return 0; } // =0-err  Set_fnum
  regim = tmp;
  //
  if ( (type < 1) || (type > 6) )  {Led_R=1;  return 0;} //"type_err=" // проверка допустимых типов записей

  //file_number = 1;   //
  Get_Ip_Time();
  tmp =  Cf_Fat_Init(&PORTH,&PORTE);
  if ( tmp != 0) {Led_R=1;  return 0;} //"init_err="

  IntToStr(file_number, NUM_TXT) ;
  if (NUM_TXT[3]==' ')  NUM_TXT[3] = '0';
  if (NUM_TXT[4]==' ')  NUM_TXT[4] = '0';
  LOG_TXT[5] = NUM_TXT[3];
  LOG_TXT[6] = NUM_TXT[4];
  LOG_TXT[7] = NUM_TXT[5];
  tmp = Cf_Fat_Assign(LOG_TXT,0xA0);
  if ( tmp != 1) {Led_R=1; return 0;} //"ass_err="
  //
  if( (regim==1) || (regim==2) )  Cf_Fat_Append();
  else                            Cf_Fat_Rewrite();

  // строка 126 символов + CR LF 0x0D 0x0A
  if ( type == POWER )  {
    strncat (dyna2, ip_string, 16);
    strncat (dyna2, date_string, 9);
    strncat (dyna2, time_string, 9);
    //  итого 34 символа
    strncat (dyna2," power_on_____________________________________________________________________________________", 92);
    strncat (dyna2,"\r\n", 2);
    Cf_Fat_Write (dyna2, 128);
  }
  else if ( type == COMMAND ) {
    strncat (dyna2, ip_string, 16);
    strncat (dyna2, date_string, 9);
    strncat (dyna2, time_string, 9);
    //  итого 34 символа
    strncat (dyna2," command", 8);
    strncat (dyna2,inf, 84);    //
    strncat (dyna2,"\r\n", 2);
    Cf_Fat_Write (dyna2, 128);
  }
  else if ( type == CMD )  {
    strncat (dyna2, ip_string, 16);
    strncat (dyna2, date_string, 9);
    strncat (dyna2, time_string, 9);
    //  итого 34 символа
    strncat (dyna2,"     cmd", 8);
    strncat (dyna2,inf, 28);
    strncat (dyna2,"                                                        ", 56);
    strncat (dyna2,"\r\n", 2);
    Cf_Fat_Write (dyna2, 128);
  }

  else if ( type == IP )  {
    strncat (dyna2, ip_string, 16);
    strncat (dyna2, date_string, 9);
    strncat (dyna2, time_string, 9);
    //  итого 34 символа
    strncat (dyna2,"      ip", 8);
    strncat (dyna2,inf, 28);
    strncat (dyna2,"                                                        ", 56);
    strncat (dyna2,"\r\n", 2);
    Cf_Fat_Write (dyna2, 128);
  }
  else if ( type == PORT___ )  {
    strncat (dyna2, ip_string, 16);
    strncat (dyna2, date_string, 9);
    strncat (dyna2, time_string, 9);
    strncat (dyna2, inf, 20);
    strncat (dyna2,"                                                                         \r\n", 75);
    Cf_Fat_Write (dyna2, 128);
  }

  Led_R=1;  // выключить красный сд
  return 1;
}

void l_w_port3(unsigned char cmd_port_num)   //запись в строку dyna начала строки с номером порта (15 символов)
{
  char    tmp[4];
 //  extern unsigned char   dyna[30] ; // строка для хранения промежуточных данных
  dyna[0] = ' ';
  ByteToStr(cmd_port_num, tmp) ;
  dyna[1] = tmp[1];
  dyna[2] = tmp[2];
  dyna[3] = ' ';
  ByteToStr(cf_line_state[cmd_port_num], tmp) ;
  dyna[4] = tmp[0];
  dyna[5] = tmp[1];
  dyna[6] = tmp[2];
  ByteToStr(cf_port_state[cmd_port_num], tmp) ;
  dyna[7] = ' ';
  dyna[8] = tmp[0];
  dyna[9] = tmp[1];
  dyna[10] = tmp[2];
  ByteToStr(cf_door_state[cmd_port_num], tmp) ;
  dyna[11] = ' ';
  dyna[12] = tmp[0];
  dyna[13] = tmp[1];
  dyna[14] = tmp[2];
  dyna[15] = '\0';
}



void Num_to_0str(unsigned char num, unsigned char *p_str)  // преобразует число (0..255) в строку из трех символов  лидирующие - нули
{
ByteToStr(num, p_str) ;
if (*p_str == ' ') *p_str = '0';
if (*(p_str+1) == ' ') *(p_str+1) = '0';
}



///
void Get_Ip_Time(void )
{
//
Read_Time();      // read time from RTC
//
   ip_string[0] = 0;
   Num_to_0str(myIpAddr[0],tmp_string);
   strncat (ip_string, tmp_string, 3);
   strncat (ip_string, ".", 1);
   //
   Num_to_0str(myIpAddr[1],tmp_string);
   strncat (ip_string, tmp_string, 3);
   strncat (ip_string, ".", 1);
   //
   Num_to_0str(myIpAddr[2],tmp_string);
   strncat (ip_string, tmp_string, 3);
   strncat (ip_string, ".", 1);
   //
   Num_to_0str(myIpAddr[3],tmp_string);
   strncat (ip_string, tmp_string, 3);
   strncat (ip_string, " ", 1);
//
   date_string[0] = 0;
   Num_to_0str(date,tmp_string);
   strncat (date_string, tmp_string, 3);
   date_string[0] =  ' ' ;
   //
   Num_to_0str(month,tmp_string);
   strncat (date_string, tmp_string, 3);
   date_string[3] =  '/' ;
   //
   Num_to_0str(year,tmp_string);
   strncat (date_string, tmp_string, 3);
   date_string[6] =  '/' ;
//
   time_string[0] = 0;
   Num_to_0str(hour,tmp_string);
   strncat (time_string, tmp_string, 3);
   time_string[0] =  ' ' ;
   //
   Num_to_0str(minute,tmp_string);
   strncat (time_string, tmp_string, 3);
   time_string[3] = ':' ;
   //
   Num_to_0str(second,tmp_string);
   strncat (time_string, tmp_string, 3);
   time_string[6] =  ':' ;

}//~
