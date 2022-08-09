// ������������ ����   test18f97.h


// ���������� ����������
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

unsigned char  cmd_port_num;      // 0..40 ����� �����, �� ������� ������ �������

unsigned char cellState[15][5];        // ������� ��������� �����, ���������� �� ��� � �������� ����������� ������
unsigned char prevCellState[15][5];    // ���������� ��������� ����� - ����� ��� ����������� ��������� � ������ � ���
unsigned int chkSum1[15],chkSum2[15];  // "����������� �����", ������������ ��� ���������� ��������� ������� ����������� ������� �� �����

unsigned char lim_ventil;   // 0..5 ����� ���������������� ������, �� ����� 5
//  RTC ���� ��������� �������
unsigned char month, day, date, year, hour, minute, second;

unsigned int file_number;  // ����� ��� - ����� �� CF
unsigned char visocosny;


unsigned char  ip_new_flag; // - ���� ������� � ������ ��������� ������ IP (=1)

unsigned char l_st_ok ; // ���� ��� ������ ��������� =1 - ������ � �����, ��� �� ; =  0 ���� ��   (line_analyze.c)
unsigned char lines_st_ok ; // ����- ������� ��� ������ ��������� =1 - ������ � �����, �� ���� �� ; =  0 ���� ��

unsigned char  flag_cf_log;  // ���� ������ ��� ������ �� CF =1
unsigned char  flag_read_fat;  // FAT � ��������� read =1, ����� 0
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

//������� ���������� � �������
//  RAM variables   ��� �������������  Ethernet �����������

extern unsigned char   myMacAddr[6];            // my MAC address
extern unsigned char   myIpAddr[4];             // my IP address
extern unsigned char   gwIpAddr[4];             // gateway (router) IP address
extern unsigned char	  ipMask[4];              // network mask (for example : 255.255.255.0)
extern unsigned char	  dnsIpAddr[4];	          // DNS server IP address
extern unsigned long  cf_r_ptr ;                // ����� ����� - ������ ���� ����� � �������� ����������

extern char log_write ( char type, char *inf , char regim);      // ������� ������ ����� � ������ CF
extern unsigned char Set_fnum(void);      // ���������� ������ ����� ������� =0-err, =1-���� ����, =2-��� ������������� ��������, =3-������������

extern void ip_set( void);                 // ������ IP � EEPROM
extern void ip_get( void);                 // ������ IP �� EEPROM  ��� ��������� ������� ��� ����� �����������
void WriteChangesLog(unsigned char cell);  // ���� ������� ��������� ������ ���������� �� �����������, ������� ��� � ���



//