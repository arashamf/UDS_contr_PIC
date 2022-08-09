#line 1 "D:/сдя/он/5906_no_coding_single_masterkey_20170821/rg_setup.c"
#line 1 "d:/сдя/он/5906_no_coding_single_masterkey_20170821/def_board.h"
#line 7 "D:/сдя/он/5906_no_coding_single_masterkey_20170821/rg_setup.c"
extern unsigned char ventil[41];


 void rg_setup ( void )
{

const unsigned char RG_RENUM[40]= {3,1,0,2,5,7,6,4,12,10,9,11,14,15,8,13,21,19,18,20,22,23,17,16,25,28,27,29,30,31,24,26,34,32,36,37,38,39,33,35};

unsigned char i,j;

 for (i=40; i>0; i--)
 {
  PORTB.F1  = ventil[RG_RENUM[i-1] +1] &1;
 asm nop;
 asm nop;
  PORTB.F2  = 1;
 asm nop;
 asm nop;
  PORTB.F2  = 0;
 asm nop;
 asm nop;
 }
  PORTB.F3  = 1;
 asm nop;
 asm nop;
  PORTB.F3  = 0;

}
