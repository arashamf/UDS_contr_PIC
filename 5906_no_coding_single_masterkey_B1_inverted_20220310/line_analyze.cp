#line 1 "E:/Work/УДС/UDS_controller/ПО (контроллер Раицкого)/5906_no_coding_single_masterkey_B1_inverted_20220310/line_analyze.c"
#line 1 "e:/work/УДС/uds_controller/ПО (контроллер Раицкого)/5906_no_coding_single_masterkey_b1_inverted_20220310/def_board.h"
#line 8 "E:/Work/УДС/UDS_controller/ПО (контроллер Раицкого)/5906_no_coding_single_masterkey_B1_inverted_20220310/line_analyze.c"
extern unsigned char lim_ventil;

extern unsigned char dyna[122] ;

extern void close_port ( unsigned char cmd_port_num );
extern char log_write ( char type, char *inf , char regim);
extern unsigned char Set_fnum(void);


extern unsigned char flag_cf_log;
