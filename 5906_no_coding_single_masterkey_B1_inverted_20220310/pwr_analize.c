
// �������� ��������� ���������� ������� � ����� ������ �� ���������� �� ����

#ifndef    def_Board
    #include        "def_Board.h"
#endif


extern unsigned char cellState[15][5];
extern unsigned char prevCellState[15][5];
extern unsigned int chkSum1[15],chkSum2[15];

extern unsigned char   dyna[122] ; // ������ ��� �������� ������������� ������

extern  void l_w_port2(unsigned char cmd_port_num);   //������ � ������ dyna ������ ������ � ������� ����� (15 ��������)  line_analyze.c
extern char log_write ( char type, char *inf , char regim);      // ������� ������ ����� � ������ CF
extern unsigned char Set_fnum(void);      // ���������� ������ ����� ������� =0-err, =1-���� ����, =2-��� ������������� ��������, =3-������������

extern  unsigned char  flag_cf_log;  // ���� ������ ��� ������ �� CF =1



