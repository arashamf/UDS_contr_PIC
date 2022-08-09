#line 1 "E:/Work/УДС/UDS_controller/ПО (контроллер Раицкого)/5906_no_coding_single_masterkey_B1_inverted_20220310/ip_set.c"
#line 1 "e:/work/УДС/uds_controller/ПО (контроллер Раицкого)/5906_no_coding_single_masterkey_b1_inverted_20220310/def_board.h"
#line 13 "E:/Work/УДС/UDS_controller/ПО (контроллер Раицкого)/5906_no_coding_single_masterkey_B1_inverted_20220310/ip_set.c"
extern unsigned char myMacAddr[6];
extern unsigned char myIpAddr[4];
extern unsigned char gwIpAddr[4];
extern unsigned char ipMask[4];
extern unsigned char dnsIpAddr[4];

extern unsigned char ip_new_flag;

extern void ip_read(void);
extern void ip_write(void);




void ip_get( void)
{
ip_read();

}



void ip_set( void)
{
unsigned int cntr_1, cntr_2 ;


 while(1)
 {
 Ethernet_doPacket() ;

 asm CLRWDT;
 if (!ip_new_flag) break;

 if (cntr_1 <= 6400 ) cntr_1++ ;
 else {
 cntr_1 =0;
  PORTC.F2  = ! PORTC.F2 ;
 }

 if (cntr_2 <= 640 ) cntr_2++ ;
 else {
 cntr_2 =0;
  PORTC.F1  = ! PORTC.F1 ;
 }
 }
 ip_write();
}
