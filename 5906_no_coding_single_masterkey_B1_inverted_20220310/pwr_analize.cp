#line 1 "E:/Work/УДС/UDS_controller/ПО (контроллер Раицкого)/5906_no_coding_single_masterkey_B1_inverted_20220310/pwr_analize.c"
#line 1 "e:/work/УДС/uds_controller/ПО (контроллер Раицкого)/5906_no_coding_single_masterkey_b1_inverted_20220310/def_board.h"
#line 9 "E:/Work/УДС/UDS_controller/ПО (контроллер Раицкого)/5906_no_coding_single_masterkey_B1_inverted_20220310/pwr_analize.c"
extern unsigned char cellState[15][5];
extern unsigned char prevCellState[15][5];
extern unsigned int chkSum1[15],chkSum2[15];

extern unsigned char dyna[122] ;

extern void l_w_port2(unsigned char cmd_port_num);
extern char log_write ( char type, char *inf , char regim);
extern unsigned char Set_fnum(void);

extern unsigned char flag_cf_log;
