
// �������� ����� - �������

#ifndef    def_Board
    #include        "def_Board.h"
#endif

extern unsigned char lim_ventil;   // 0..5 ����� ���������������� ������, �� ����� 5
//
extern unsigned char   dyna[122] ; // ������ ��� �������� ������������� ������

extern void close_port (  unsigned char  cmd_port_num  );      // ������������ ��������/ �������� CMOS- ������  open_port.c
extern char log_write ( char type, char *inf , char regim);      // ������� ������ ����� � ������ CF
extern unsigned char Set_fnum(void);      // ���������� ������ ����� ������� =0-err, =1-���� ����, =2-��� ������������� ��������, =3-������������


extern  unsigned char  flag_cf_log;  // ���� ������ ��� ������ �� CF =1
//

