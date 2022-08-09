//   open_port.c
   // ������������ ��������/ �������� CMOS- ������

#ifndef    def_Board
    #include        "def_Board.h"
#endif


//  mask_ventil[0]  ����������� ���������� ������� � ����� ������  =0-�����, !=0- ������������� (27v �� ����� ��� ��������� ����� ������ � ������� ���������� ���������)
extern unsigned char lim_ventil;   // 0..5 ����� ���������������� ������, �� ����� 5
extern unsigned char cellCommand[15];
extern unsigned char fMasterKey;

// ������� �������� ��������
void open_port (  unsigned char  cmd_port_num )
{
  if(fMasterKey==1) {return;}           // ������ ��������� � ��������� ������ ����� �������� ������ ����
  if (cellCommand[cmd_port_num] == 1) {return;}  // �� ��������� ���� ��� � ��� �������
  //if( lim_ventil > 5) { return;}   // lim_ventil 0..5 ����� ���������������� ������, �� ����� 5
  cellCommand[cmd_port_num] = 1;
  //lim_ventil++;
}


// ������� ��������� ��������
void close_port (  unsigned char  cmd_port_num )
{
  if(fMasterKey==1) {return;}           // ������ ��������� � ��������� ������ ����� �������� ������ ����
  if (cellCommand[cmd_port_num] == 0) {return;}
  cellCommand[cmd_port_num] = 0;
  //if( lim_ventil > 0) { lim_ventil--; }
}



