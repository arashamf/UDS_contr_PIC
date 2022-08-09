#line 1 "D:/_BOB/___WORK/__format ETHERNET/31_test/cf_read.c"
#line 1 "d:/_bob/___work/__format ethernet/31_test/def_board.h"
#line 8 "D:/_BOB/___WORK/__format ETHERNET/31_test/cf_read.c"
extern char caracter[2];
extern unsigned long i, size;
extern char cf_r_flag ;


void cf_read(void)
{



 len += putConstString("\n\Cf_Fat_Read=\n") ;

 for (i = 1; i < (size+1) ; i++)
 {
 if ( i > 1280 ) {len += putConstString("\n\continued\n"); cf_r_flag =1; break; }
 else cf_r_flag =0;

 Cf_Fat_Read(caracter);
 caracter[1] = '\0';
 len += putString(caracter) ;
 }
 len += putConstString("\n\End\n") ;

}
