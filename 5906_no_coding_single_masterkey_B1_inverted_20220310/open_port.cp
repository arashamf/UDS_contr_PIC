#line 1 "E:/Work/УДС/UDS_controller/ПО (контроллер Раицкого)/5906_no_coding_single_masterkey_B1_inverted_20220310/open_port.c"
#line 1 "e:/work/УДС/uds_controller/ПО (контроллер Раицкого)/5906_no_coding_single_masterkey_b1_inverted_20220310/def_board.h"
#line 10 "E:/Work/УДС/UDS_controller/ПО (контроллер Раицкого)/5906_no_coding_single_masterkey_B1_inverted_20220310/open_port.c"
extern unsigned char lim_ventil;
extern unsigned char cellCommand[15];
extern unsigned char fMasterKey;


void open_port ( unsigned char cmd_port_num )
{
 if(fMasterKey==1) {return;}
 if (cellCommand[cmd_port_num] == 1) {return;}

 cellCommand[cmd_port_num] = 1;

}



void close_port ( unsigned char cmd_port_num )
{
 if(fMasterKey==1) {return;}
 if (cellCommand[cmd_port_num] == 0) {return;}
 cellCommand[cmd_port_num] = 0;

}
