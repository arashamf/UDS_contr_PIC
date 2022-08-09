  // ������������ ������ � �������� �������� CMOS-������
  
#ifndef    def_Board
    #include        "def_Board.h"
#endif

extern unsigned char ventil[41];   //  ������ �������� CMOS-������ =0-������, =1-������
//

  void rg_setup ( void )
{
 // ������ ��� �������������� ������� CMOS ������ � ��������� � ���������� ������ ������ (�����)
const unsigned char RG_RENUM[40]= {3,1,0,2,5,7,6,4,12,10,9,11,14,15,8,13,21,19,18,20,22,23,17,16,25,28,27,29,30,31,24,26,34,32,36,37,38,39,33,35};

unsigned char i,j;
//
 for (i=40; i>0; i--)  // i-1 = ����� � ��������� ������
     {
      SIN = ventil[RG_RENUM[i-1] +1] &1;    //  RG_RENUM[i-1]   = OUT number
       asm nop;
       asm nop;
      SRCLK = 1;                  // WRITE TO REGISTER
       asm nop;
       asm nop;
      SRCLK = 0;
       asm nop;
       asm nop;
     }
 RCLK = 1;  // WRITE TO PARALLEL BUFFER
       asm nop;
       asm nop;
 RCLK = 0;

}