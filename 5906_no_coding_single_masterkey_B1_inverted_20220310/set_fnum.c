// ���� set_fnum.c
//
//
#ifndef    def_Board
    #include        "def_Board.h"
#endif


 //������� ���������� � �������
 
 //  RTC ���� ��������� �������
extern  unsigned char month, day, date, year, hour, minute, second;

extern unsigned int file_number;  // ����� ��� - ����� �� CF
extern unsigned char visocosny;

extern  unsigned char  flag_read_fat;  // FAT � ��������� read =1, ����� 0

extern void Read_Time(void);    //Reads time and date information from RTC


//  ������� ���������� ���������� ���� � ���������� ������� (������ ������ ==0- �� ����������, =1-���������� ���, ������ ������ = �����-1)
const unsigned int pred_sum [2] [12] = { {0,31,59,90,120,151,181,212,243,273,304,334}, {0,31,60,91,121,152,182,213,244,274,305,335} };



unsigned char Set_fnum(void)    // ���������� ������ ����� ������� =0-err, =1-���� ����, =2-��� ������������� ��������, =3-������������
{
unsigned int date_num;
unsigned char i, tmp;
unsigned long  size;
char LOG_TXT[13] = "LOG__001.TXT";
char NUM_TXT[7] = "   001";
char   caracter;

 Read_Time();    //Reads time and date information from RTC
 if ( year & 0x03  ) visocosny =0;  // ��� ������� ���� year =0 -> ��� ����������
 else  visocosny =1;
 date_num = date + pred_sum [visocosny] [month-1];

 if( file_number != date_num )
     {
      flag_read_fat = 0;  // FAT � ��������� read =1, ����� 0
      file_number = date_num ;
////
      if( !visocosny && (file_number==365) )
          {
                                         LOG_TXT[5] = '3';
                                         LOG_TXT[6] = '6';
                                         LOG_TXT[7] = '6';
          tmp =  Cf_Fat_Init(&PORTH,&PORTE);
          if ( tmp != 0 ) return 0;
          tmp = Cf_Fat_Assign(LOG_TXT,0xA0);
          if ( tmp != 1 ) return 0;
          Cf_Fat_Rewrite();

          }
////
      
      
                                         IntToStr(file_number, NUM_TXT) ;
                                         if (NUM_TXT[3]==' ')  NUM_TXT[3] = '0';
                                         if (NUM_TXT[4]==' ')  NUM_TXT[4] = '0';
                                         LOG_TXT[5] = NUM_TXT[3];
                                         LOG_TXT[6] = NUM_TXT[4];
                                         LOG_TXT[7] = NUM_TXT[5];
      tmp =  Cf_Fat_Init(&PORTH,&PORTE);
      if ( tmp != 0 ) return 0;      // init error
      tmp = Cf_Fat_Assign(LOG_TXT,0xA0);
      if ( tmp != 1 ) return 0;      //  assign error
      Cf_Fat_Reset(&size);            // To read file, procedure returns size of file
      if (size == 0)  return 1;     // ������ ����, Rewrite ��� Append
      for (i = 1; i < 26 ; i++)  // ��� - � 24 � 25 ��������
          {
          Cf_Fat_Read(&caracter);    // ������ ��� ���������
          if(i==24) tmp = (caracter - '0')*10;      //
          if(i==25) tmp += caracter - '0';      //
          }
      if ( tmp == year ) return 2;     // ��� ������������� ��������, Append
      else  return 3;     // ��� �� ������������� ��������, Rewrite
    } //
 else   // file_number == date_num
 file_number = date_num ;
 return 2;
 
}


