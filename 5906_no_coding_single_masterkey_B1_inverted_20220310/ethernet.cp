#line 1 "E:/Work/УДС/UDS_controller/ПО (контроллер Раицкого)/5906_no_coding_single_masterkey_B1_inverted_20220310/ethernet.c"
#line 1 "e:/work/УДС/uds_controller/ПО (контроллер Раицкого)/5906_no_coding_single_masterkey_b1_inverted_20220310/def_board.h"
#line 1 "e:/work/УДС/uds_controller/ПО (контроллер Раицкого)/5906_no_coding_single_masterkey_b1_inverted_20220310/ethernet.h"





const unsigned char httpHeader[] = "HTTP/1.1 200 OK\nContent-type: " ;
const unsigned char httpMimeTypeHTML[] = "text/html\n\n" ;
const unsigned char httpMimeTypeScript[] = "text/plain\n\n" ;



unsigned char myMacAddr[6] = {0x00, 0x14, 0xA5, 0x01, 0x01, 0x01} ;
unsigned char myIpAddr[4] = {192, 1, 1, 1 } ;
unsigned char gwIpAddr[4] = {192, 1, 2, 1 } ;
unsigned char ipMask[4] = {255, 0, 0, 0 } ;
unsigned char dnsIpAddr[4] = {192, 1, 2, 1 } ;

unsigned char httpMethod[] = "GET /";

unsigned char txt_command[] = "?command=port" ;
unsigned char txt_port[] = "port" ;
unsigned char txt_open[] = "open" ;
unsigned char txt_close[] = "close" ;
unsigned char txt_status[] = "status" ;
unsigned char txt_st22[] = "st22" ;
unsigned char txt_clear[] = "clear" ;
unsigned char txt_lim_vent[] = "lim_vent" ;

unsigned char txt_ass0[] = "ass0" ;
unsigned char txt_assA[] = "assA" ;
unsigned char txt_reset[] = "reset" ;
unsigned char txt_append[] = "append" ;
unsigned char txt_rewrite[] = "rewrite" ;

unsigned char txt_read[] = "read" ;
unsigned char txt_0read[] = "0read" ;

unsigned char txt_cf_d[] = "cf_d" ;

unsigned char txt_rtcr[] = "rtcr" ;
unsigned char txt_rtds[] = "rtds" ;
unsigned char txt_rtss[] = "rtss" ;

unsigned char txt_iset[] = "iset" ;
unsigned char txt_ip__[] = "&ip=" ;

unsigned char txt_term[] = "term" ;


unsigned char getRequest[128] ;
unsigned char dyna[122] ;
unsigned long httpCounter = 0 ;
unsigned char len;


unsigned char key_byte;

const unsigned char key_arr[1024]={
 0x8C, 0x5F, 0x37, 0xC2, 0xBB, 0xE3, 0x3C, 0x8A, 0x20, 0x57, 0xC3, 0xBB, 0xEE, 0x24, 0xB2, 0x78,
 0xAB, 0xB4, 0x13, 0xEB, 0x8D, 0x3E, 0x8F, 0x50, 0xC9, 0x3B, 0x65, 0x8D, 0x49, 0x5A, 0xBD, 0xF3,
 0x6E, 0x09, 0xE7, 0x57, 0xF4, 0x62, 0xEE, 0x57, 0xB9, 0x35, 0xDE, 0xD1, 0x79, 0xC4, 0x0F, 0x50,
 0xE5, 0xF0, 0x14, 0xE1, 0x6F, 0x83, 0x77, 0x92, 0xB5, 0x46, 0x9B, 0x45, 0x23, 0xCA, 0xF2, 0x24,
 0x9A, 0x96, 0x77, 0x96, 0x68, 0x08, 0x23, 0x44, 0x52, 0x2B, 0xEF, 0x28, 0x20, 0x5B, 0xD7, 0x65,
 0x03, 0xE0, 0x14, 0x77, 0x58, 0x7D, 0x5F, 0x48, 0x4C, 0x9F, 0x5F, 0x8C, 0x77, 0x45, 0x7F, 0x3C,
 0x7E, 0xD5, 0x55, 0x13, 0xC9, 0x7C, 0xA9, 0xB4, 0xC9, 0xF2, 0xC3, 0x9C, 0x70, 0x47, 0xA0, 0x83,
 0xDD, 0xAD, 0x21, 0x0F, 0xA8, 0x64, 0xC2, 0xEE, 0xF7, 0x68, 0x15, 0xE3, 0x0E, 0x13, 0xCE, 0x71,
 0x95, 0x8A, 0x11, 0x37, 0x92, 0x99, 0x57, 0xC3, 0x9A, 0xB1, 0x68, 0xC7, 0x66, 0xF2, 0x30, 0xE1,
 0x57, 0x8A, 0xD9, 0x67, 0xF2, 0xED, 0x9C, 0xEE, 0x1B, 0x1B, 0xCF, 0x7D, 0x8A, 0x1E, 0x76, 0x71,
 0x53, 0x3C, 0xEC, 0x4F, 0xAE, 0xD9, 0xD4, 0xAD, 0x94, 0x7D, 0xE8, 0x5E, 0x62, 0x66, 0x7E, 0x78,
 0x26, 0x2B, 0xC1, 0x6E, 0x76, 0x78, 0x02, 0xBD, 0xA8, 0x87, 0x4F, 0x1F, 0x9E, 0x0F, 0xBF, 0xD2,
 0xB8, 0xCC, 0xD3, 0x38, 0x93, 0x3F, 0xAA, 0xAC, 0x26, 0xFA, 0xDC, 0x17, 0xE6, 0x5F, 0xE7, 0x8E,
 0x22, 0x06, 0x15, 0x0E, 0xD4, 0x84, 0x1A, 0x21, 0xD5, 0x91, 0xC2, 0x20, 0x56, 0x5B, 0x20, 0x7D,
 0x52, 0x49, 0x77, 0x14, 0xAC, 0x3E, 0xED, 0x8E, 0xE4, 0x90, 0x79, 0x85, 0x90, 0x3B, 0x98, 0x79,
 0xB2, 0x75, 0x47, 0x64, 0xA4, 0x52, 0xA3, 0x79, 0xA7, 0xE4, 0x3F, 0x6F, 0x6E, 0x79, 0xE7, 0xFF,
 0x79, 0x45, 0xDE, 0x29, 0xCA, 0x84, 0x68, 0xAB, 0x81, 0xDD, 0x68, 0xDE, 0xA9, 0xC2, 0x4A, 0x36,
 0x39, 0xD5, 0x44, 0x8C, 0x77, 0xD6, 0x8E, 0xFA, 0x1A, 0xA9, 0x94, 0xA2, 0xC8, 0x96, 0xB0, 0xAF,
 0xA3, 0xAA, 0xBE, 0xCC, 0xC7, 0x10, 0x64, 0x95, 0x0D, 0x0A, 0x01, 0x57, 0xCF, 0xBB, 0x55, 0xBE,
 0x3A, 0xEB, 0xEB, 0xBC, 0xF3, 0xEE, 0x20, 0x67, 0x3C, 0x6D, 0x5F, 0xA1, 0x35, 0x5F, 0xCB, 0x3C,
 0xF3, 0x2F, 0x87, 0x04, 0x2E, 0xBC, 0xC3, 0x85, 0xDE, 0x1D, 0xF1, 0xCE, 0x9F, 0x47, 0x95, 0x0E,
 0x57, 0x0D, 0x0A, 0x73, 0x3E, 0xAB, 0x20, 0xFF, 0x5E, 0x72, 0x3E, 0x32, 0xB1, 0x3C, 0x13, 0x02,
 0x48, 0x31, 0xC8, 0xE6, 0xC0, 0xF9, 0x61, 0x53, 0x2E, 0x34, 0x52, 0xA9, 0x6B, 0xF1, 0xAE, 0x48,
 0x34, 0xB5, 0xDC, 0x3B, 0x45, 0xAD, 0xBC, 0x63, 0xE0, 0x3B, 0x51, 0x21, 0x83, 0x6A, 0xDA, 0xD6,
 0x50, 0xAC, 0xBE, 0x66, 0x12, 0xE3, 0x1D, 0x76, 0xBD, 0x84, 0xDB, 0x3F, 0xFC, 0x79, 0x64, 0x4B,
 0x18, 0xEF, 0xF4, 0x34, 0x19, 0xE6, 0x7E, 0x08, 0xB2, 0x4A, 0x85, 0x80, 0x1B, 0xC1, 0x3B, 0xCC,
 0x63, 0xEF, 0xBC, 0x4B, 0x62, 0xE3, 0x89, 0x5D, 0x60, 0xA7, 0xA1, 0x41, 0xAB, 0x25, 0x49, 0xF8,
 0xCB, 0xFC, 0x12, 0x5E, 0x12, 0xE3, 0x5D, 0xBA, 0x5F, 0x65, 0x51, 0x8D, 0x0F, 0x7F, 0x54, 0x59,
 0x4D, 0xEB, 0xB6, 0xCF, 0x3B, 0xD5, 0xA9, 0x64, 0x63, 0x6B, 0x3F, 0x74, 0xD8, 0xFA, 0xAF, 0xCC,
 0xA6, 0x7C, 0x8E, 0x39, 0x3F, 0x34, 0xB2, 0xC8, 0xF9, 0x58, 0xD3, 0x84, 0xE5, 0x99, 0x10, 0x40,
 0xF3, 0x12, 0xEF, 0x54, 0x26, 0x7C, 0x1B, 0xBC, 0x7B, 0x1E, 0xF6, 0x30, 0x5F, 0xCC, 0xDE, 0xE6,
 0x15, 0x79, 0x37, 0x21, 0xF5, 0x6A, 0x18, 0x74, 0x4A, 0x5B, 0x54, 0x6B, 0xFD, 0x70, 0x7D, 0x87,
 0xD5, 0x42, 0xDE, 0xCD, 0x87, 0x19, 0x21, 0x7F, 0x62, 0xDB, 0x35, 0xEC, 0x6D, 0x1E, 0x27, 0x48,
 0x9E, 0x49, 0x42, 0x90, 0x55, 0x2A, 0x04, 0x5C, 0x13, 0xEF, 0x54, 0x1E, 0x5B, 0xC0, 0x11, 0xBD,
 0xF3, 0xAE, 0xA8, 0x74, 0xA9, 0x71, 0x31, 0x6C, 0x8B, 0xA5, 0x6F, 0x0D, 0x0A, 0x8B, 0x1F, 0xF4,
 0xFE, 0x58, 0xA6, 0xE5, 0x90, 0xED, 0x31, 0xBA, 0xC4, 0x72, 0xFA, 0xF3, 0xC5, 0x5C, 0xC5, 0x2B,
 0xAA, 0xAB, 0xB3, 0xC8, 0x41, 0x60, 0xC3, 0xAF, 0x52, 0xCC, 0x82, 0xF5, 0xBC, 0x9E, 0x77, 0x98,
 0x8D, 0xAD, 0x7D, 0x2C, 0xA9, 0xF4, 0x5F, 0xCC, 0x62, 0x26, 0x67, 0x5D, 0xCC, 0x61, 0x8B, 0x78,
 0x99, 0xEF, 0x6D, 0x32, 0xC7, 0xCA, 0xFE, 0x90, 0x3C, 0xC3, 0xB8, 0x83, 0x42, 0xEE, 0xD0, 0x74,
 0x1A, 0x19, 0xA9, 0xD4, 0xBD, 0xF0, 0x2E, 0x24, 0x94, 0xD6, 0xB5, 0x79, 0x57, 0x09, 0xA0, 0x13,
 0x9B, 0x8B, 0x5A, 0xEB, 0x33, 0xDE, 0xD9, 0x92, 0xDE, 0x3E, 0x89, 0xF3, 0x14, 0x45, 0xB6, 0x64,
 0x49, 0x78, 0xC7, 0x26, 0x69, 0x08, 0xB2, 0x4A, 0x85, 0x80, 0xAB, 0xE4, 0x5D, 0x31, 0x89, 0x2D,
 0x6E, 0x8F, 0x77, 0x61, 0xC3, 0xA2, 0x9D, 0x71, 0x6D, 0x51, 0x17, 0xE0, 0x9D, 0x0D, 0x0A, 0x30,
 0xF4, 0x5C, 0x3E, 0x7A, 0x19, 0x7E, 0x1E, 0x88, 0x09, 0x6F, 0x56, 0x59, 0x98, 0xCB, 0xCD, 0xAD,
 0xCA, 0x32, 0x3C, 0x8F, 0x9C, 0x7D, 0xC9, 0xE3, 0x97, 0xA2, 0x8A, 0xA6, 0x8A, 0xF3, 0xA8, 0x58,
 0xAD, 0xD8, 0x7B, 0xD1, 0xC3, 0xF9, 0x70, 0x20, 0x9A, 0xF0, 0xAE, 0xD8, 0xDC, 0xFE, 0x39, 0xE7,
 0x37, 0x81, 0x3B, 0x62, 0x79, 0x26, 0x04, 0x90, 0x62, 0x50, 0x11, 0x2E, 0xD6, 0x9F, 0xD1, 0xBA,
 0x22, 0xEF, 0xEC, 0xA2, 0xEC, 0x16, 0x78, 0x17, 0x82, 0x2C, 0x54, 0x13, 0x7A, 0x7C, 0x23, 0xAA,
 0x32, 0x83, 0xD1, 0x72, 0x52, 0xDE, 0xA1, 0x8E, 0xF6, 0x49, 0x9C, 0xCF, 0xF3, 0x04, 0x22, 0x85,
 0xCA, 0xCE, 0x51, 0x79, 0x5A, 0x90, 0x56, 0x21, 0xC8, 0x2A, 0x15, 0x02, 0xAE, 0x9E, 0x77, 0x58,
 0x22, 0x87, 0xF6, 0xCE, 0xBB, 0x24, 0x36, 0x9E, 0xD8, 0x05, 0x76, 0x1A, 0x1A, 0x54, 0xD2, 0xE9,
 0x74, 0x30, 0x88, 0x61, 0x96, 0x22, 0xED, 0xF9, 0xF0, 0xE2, 0x68, 0x67, 0x71, 0xD7, 0xD5, 0x91,
 0x56, 0x73, 0x83, 0xCE, 0x26, 0x59, 0x97, 0xD4, 0x91, 0x8A, 0x87, 0x8C, 0x77, 0xAB, 0xFC, 0x14,
 0xE0, 0x81, 0xCC, 0xA7, 0xE3, 0x9D, 0xCA, 0xED, 0xB3, 0xC3, 0x0D, 0x0A, 0xB7, 0xA6, 0xAD, 0x34,
 0x54, 0x98, 0x60, 0x6E, 0x1C, 0x6D, 0xB2, 0xBC, 0x44, 0xEA, 0x33, 0x06, 0x21, 0xE3, 0x44, 0x21,
 0xC5, 0xEA, 0x75, 0x2D, 0xDE, 0xF9, 0x7F, 0x5E, 0x9E, 0x77, 0x0E, 0xB3, 0x4E, 0x51, 0xC8, 0x9D,
 0xFA, 0xB6, 0x45, 0x3C, 0x15, 0xED, 0x84, 0x9D, 0x2E, 0x39, 0xEF, 0x96, 0x04, 0x55, 0x5E, 0xA8,
 0x97, 0x26, 0x4E, 0xC8, 0x3B, 0x95, 0xBB, 0x42, 0x90, 0x55, 0x2A, 0x04, 0xDC, 0x08, 0xDE, 0xA1,
 0x9F, 0xEF, 0xBC, 0x4B, 0x72, 0xC6, 0xD3, 0xF6, 0x15, 0x5A, 0xB3, 0xC2, 0xD0, 0xC2, 0x72, 0x39,
 0x17, 0xE9, 0x1F, 0xF3, 0x88, 0x77, 0x5D, 0x2A, 0x93, 0xCA, 0x8B, 0xDB, 0xE0, 0x9D, 0x1D, 0x9F,
 0xE5, 0x70, 0x7F, 0x88, 0xB5, 0x5F, 0x3F, 0xE9, 0xD0, 0x8E, 0x95, 0xEF, 0xF9, 0x92, 0xEF, 0x64,
 0xDA, 0xE6, 0x65, 0x7F, 0x58, 0x5E, 0x22, 0xF5, 0x19, 0x83, 0x9E, 0xBF, 0x1F, 0x35, 0xFB, 0xF1,
 0x39, 0x69, 0xC4, 0x73, 0x16, 0x4C, 0xD7, 0xE2, 0xDD, 0x4B, 0xE3, 0xF3, 0x08, 0x31, 0xE0, 0x26,
 0xE2, 0x5D, 0x88, 0xB0, 0x7A, 0x85, 0xD0, 0x59, 0x56, 0xF3, 0xCE, 0xC1, 0x93, 0xB5, 0x13, 0x76
};


unsigned int key_addr;
unsigned int key_addr0;
unsigned int putShConstString(const unsigned char *ptr ) ;
unsigned int putShString(unsigned char *ptr ) ;
unsigned int putShString2(unsigned char *ptr ) ;



char LOG_TXT[13] = "LOG__001.TXT";
unsigned long cf_r_ptr ;

void l_w_port(unsigned char cmd_port_num);
void My_str_n(unsigned char *s_out, unsigned char *s_source, unsigned char n );
void My_long_to_str( unsigned long size, unsigned char *s_out );

extern unsigned char flag_read_fat;
extern unsigned char myIpAddr[4];

extern unsigned char cmd_port_num;
extern unsigned char cellState[13][5];
extern unsigned int chkSum1[14],chkSum2[14];
extern unsigned char cellCommand[14];
extern unsigned char lim_ventil;

extern unsigned char l_st_ok ;
extern unsigned char lines_st_ok ;

extern void open_port ( unsigned char cmd_port_num );
extern void close_port ( unsigned char cmd_port_num );

extern char log_write ( char type, char *inf , char regim);
extern unsigned char Set_fnum(void);

extern unsigned char month, day, date, year, hour, minute, second;
extern void rtc_read(void);
extern void rtc_set(void);

extern void Num_to_0str(unsigned char num, unsigned char *p_str);

extern unsigned char ip_new_flag;

extern unsigned int Termo_measure();
extern unsigned char temperature;
#line 11 "E:/Work/УДС/UDS_controller/ПО (контроллер Раицкого)/5906_no_coding_single_masterkey_B1_inverted_20220310/ethernet.c"
unsigned int Ethernet_UserTCP(unsigned char *remoteHost, unsigned int remotePort, unsigned int localPort, unsigned int reqLength)
{
 unsigned int len = 0 ;
 unsigned long i, size;
 unsigned int tmp, j ;


 unsigned char tmph, tmpl;
 unsigned char tmp_inbyte, tmp_outbyte ;
 unsigned char start_0addr, start_1addr, start_2addr, start_3addr;


 char caracter[2]= "0";
 char fread_num[4]= "000";
 unsigned char tmpBuf[20];

 if(localPort != 25006) {
 return(0) ;
 }

  PORTC.F1  = 0;
#line 65 "E:/Work/УДС/UDS_controller/ПО (контроллер Раицкого)/5906_no_coding_single_masterkey_B1_inverted_20220310/ethernet.c"
 for(i = 0 ; i < 127 ; i++)
 {
 getRequest[i] = Ethernet_getByte() ;
 }
 getRequest[127] = 0 ;




 if(memcmp(getRequest, httpMethod, 5)) {
  PORTC.F1  = 1; return(0) ;
 }

 len =  Ethernet_putConstString (httpHeader) ;
 len +=  Ethernet_putConstString (httpMimeTypeScript) ;

 if ( (memcmp(getRequest+21, txt_0read, 4 )) && (memcmp(getRequest+21, txt_read, 4)) && (memcmp(getRequest+21, txt_status, 4 )) ) {

 My_str_n(dyna, getRequest, 84);
 log_write (  2 , dyna, tmp );
 }

 len += putShConstString("stoika=") ;

 Num_to_0str(myIpAddr[0], dyna);
 len += putShString(dyna) ;
 len += putShConstString(".") ;

 Num_to_0str(myIpAddr[1], dyna);
 len += putShString(dyna) ;
 len += putShConstString(".") ;

 Num_to_0str(myIpAddr[2], dyna);
 len += putShString(dyna) ;
 len += putShConstString(".") ;

 Num_to_0str(myIpAddr[3], dyna);
 len += putShString(dyna) ;

 if (!memcmp(getRequest+5, txt_command, 13)) {
 cmd_port_num = (getRequest[19] - '0') + 10*(getRequest[18] - '0');
 if (ip_new_flag) {
 if (! ( cmd_port_num == 0) ) goto ERR_CMD;
 if(!memcmp(getRequest+21, txt_iset, 4)) {
 myIpAddr[0] = 10*(getRequest[30] - '0') + (getRequest[31] - '0');
 if (getRequest[29] == '1') myIpAddr[0] += 100;
 else if (getRequest[29] == '2') myIpAddr[0] += 200;

 myIpAddr[1] = 10*(getRequest[34] - '0') + (getRequest[35] - '0');
 if (getRequest[33] == '1') myIpAddr[1] += 100;
 else if (getRequest[33] == '2') myIpAddr[1] += 200;

 myIpAddr[2] = 10*(getRequest[38] - '0') + (getRequest[39] - '0');
 if (getRequest[37] == '1') myIpAddr[2] += 100;
 else if (getRequest[37] == '2') myIpAddr[2] += 200;

 myIpAddr[3] = 10*(getRequest[42] - '0') + (getRequest[43] - '0');
 if (getRequest[41] == '1') myIpAddr[3] += 100;
 else if (getRequest[41] == '2') myIpAddr[3] += 200;
 tmp =Set_fnum();

 log_write (  5 , " :new_ip                    ", tmp );
 ip_new_flag = 0;
 }
 else goto ERR_CMD;

 len += putShConstString("result=accepted") ;
  PORTC.F1  = 1;
 return(len) ;

 ERR_CMD: len += putShConstString("result=error_ip_command") ;
 tmp =Set_fnum();

 log_write (  3 , " error_ip_command           ", tmp );
  PORTC.F1  = 1;
 return(len) ;
 }

 if ( cmd_port_num == 0) {
 if(!memcmp(getRequest+21, txt_status, 4)) {
 len += putShConstString("&state=OK\r\n");
 for (tmp=1;tmp<15;tmp++)
 {
 sprintf(tmpBuf,"cell_%02d=",tmp);
 len += putShString(tmpBuf);
 if(cellState[tmp][4]=='8') {
 len += putShConstString("no\r\n");
 }
 else {
 if (tmp == 14)
 {
 sprintf(tmpBuf,"%c,",cellState[tmp][0]);
 len += putShString(tmpBuf);
 if (cellState[tmp][1] == '0')
 {
 sprintf(tmpBuf,"%c,",'1');
 len += putShString(tmpBuf);
 }
 else
 {
 if (cellState[tmp][1] == '1')
 {
 sprintf(tmpBuf,"%c,",'0');
 len += putShString(tmpBuf);
 }
 else
 {
 sprintf(tmpBuf,"%c,",cellState[tmp][1]);
 len += putShString(tmpBuf);
 }
 }
 if (cellState[tmp][2] == '0')
 {
 sprintf(tmpBuf,"%c,",'1');
 len += putShString(tmpBuf);
 }
 else
 {
 if (cellState[tmp][2] == '1')
 {
 sprintf(tmpBuf,"%c,",'0');
 len += putShString(tmpBuf);
 }
 else
 {
 sprintf(tmpBuf,"%c,",cellState[tmp][2]);
 len += putShString(tmpBuf);
 }
 }
 sprintf(tmpBuf,"%c,",cellState[tmp][3]);
 len += putShString(tmpBuf);
 sprintf(tmpBuf,"%c\r\n",cellState[tmp][4]);
 len += putShString(tmpBuf);
 }
 else
 {
 sprintf(tmpBuf,"%c,",cellState[tmp][0]);
 len += putShString(tmpBuf);
 sprintf(tmpBuf,"%c,",cellState[tmp][1]);
 len += putShString(tmpBuf);
 sprintf(tmpBuf,"%c,",cellState[tmp][2]);
 len += putShString(tmpBuf);
 sprintf(tmpBuf,"%c,",cellState[tmp][3]);
 len += putShString(tmpBuf);
 sprintf(tmpBuf,"%c\r\n",cellState[tmp][4]);
 len += putShString(tmpBuf);
 }
 }
 }
 }


 else if(!memcmp(getRequest+21, txt_rtcr, 4)) {
 len += putShConstString("&rtcr=") ;
 rtc_read();
 len += putShString(dyna) ;
 }

 else if(!memcmp(getRequest+21, txt_rtds, 4)) {
 len +=  Ethernet_putConstString ("&rtds=") ;

 if ( ( ( (getRequest[28] - '0')*10 ) + (getRequest[29] - '0') ) >31 )
 { len +=  Ethernet_putConstString ("error") ; goto ILLEGAL_COMMAND; }
 if ( ( ( (getRequest[33] - '0')*10 ) + (getRequest[34] - '0') ) >12 )
 { len +=  Ethernet_putConstString ("error") ; goto ILLEGAL_COMMAND; }
 if ( ( ( (getRequest[38] - '0')*10 ) + (getRequest[39] - '0') ) >99 )
 { len +=  Ethernet_putConstString ("error") ; goto ILLEGAL_COMMAND; }

 rtc_read();
 date = ( (getRequest[28] - '0')*10 ) + (getRequest[29] - '0');
 month = ( (getRequest[33] - '0')*10 ) + (getRequest[34] - '0');
 year = ( (getRequest[38] - '0')*10 ) + (getRequest[39] - '0');
 rtc_set();

 len +=  Ethernet_putString (dyna) ;
 }


 else if(!memcmp(getRequest+21, txt_rtss, 4)) {
 len +=  Ethernet_putConstString ("&rtss=") ;

 if ( ( ( (getRequest[28] - '0')*10 ) + (getRequest[29] - '0') ) >24 )
 { len +=  Ethernet_putConstString ("error") ; goto ILLEGAL_COMMAND; }
 if ( ( ( (getRequest[33] - '0')*10 ) + (getRequest[34] - '0') ) >59 )
 { len +=  Ethernet_putConstString ("error") ; goto ILLEGAL_COMMAND; }
 if ( ( ( (getRequest[38] - '0')*10 ) + (getRequest[39] - '0') ) >59 )
 { len +=  Ethernet_putConstString ("error") ; goto ILLEGAL_COMMAND; }

 rtc_read();
 hour = ( (getRequest[28] - '0')*10 ) + (getRequest[29] - '0');
 minute = ( (getRequest[33] - '0')*10 ) + (getRequest[34] - '0');
 second = ( (getRequest[38] - '0')*10 ) + (getRequest[39] - '0');
 rtc_set();

 len +=  Ethernet_putString (dyna) ;
 }

 else if(!memcmp(getRequest+21, txt_term, 4)) {
 len += putShConstString("&term=") ;
 Num_to_0str(Termo_measure(), dyna);
 len += putShString(dyna) ;
 }



 else if(!memcmp(getRequest+21, txt_0read, 4)) {
 cf_r_ptr =0;
 len += putShConstString("&cf_fat_0read=ok") ;
 }

 else if(!memcmp(getRequest+21, txt_read, 4)) {
 fread_num[0] = getRequest[35];
 fread_num[1] = getRequest[36];
 fread_num[2] = getRequest[37];
 if ( (LOG_TXT[5] != fread_num[0]) || (LOG_TXT[6] != fread_num[1]) || (LOG_TXT[7] != fread_num[2]) ) {
 cf_r_ptr =0;
 }
 LOG_TXT[5] = fread_num[0];
 LOG_TXT[6] = fread_num[1];
 LOG_TXT[7] = fread_num[2];

 if(cf_r_ptr ==0) flag_read_fat = 0;
 len += putShConstString("&file_num=");
 len += putShString(fread_num) ;

 if(flag_read_fat != 1) {
 len += putShConstString("&cf_fat_init=") ;
 tmp = Cf_Fat_Init(&portH,&portE);
 if ( tmp != 0) {
 intToStr(tmp, dyna) ;
 len += putShString(dyna) ;
 goto TXT_READ_END;
 }
 len += putShConstString("ok") ;
 len += putShConstString("&cf_fat_assign0x00=") ;
 tmp = Cf_Fat_Assign(LOG_TXT,0x00);
 if ( tmp != 1) {
 len += putShConstString("no_file") ;
 goto TXT_READ_END;
 }
 len += putShConstString("file_ok") ;
 Cf_Fat_Reset(&size);
 len += putShConstString("&size=") ;
 My_long_to_str( size, dyna );

 len += putShString(dyna) ;
 }
 len += putShConstString("&cf_fat_read=\n") ;
 if (cf_r_ptr !=0 ) {
 if(flag_read_fat != 1) {
 for (i = 1; i < cf_r_ptr ; i++)
 {
 Cf_Fat_Read(caracter);
 }
 }
 }
 else cf_r_ptr =1;
 flag_read_fat = 1;
 j = 0;
 for (i = 1; i < 1361 ; i++)
 {
 Cf_Fat_Read(caracter);
 caracter[1] = '\0';
 len += putShString(caracter) ;
 cf_r_ptr++;
 if (cf_r_ptr > size) {cf_r_ptr = 0; len += putShConstString("\n&continued=false") ; break; }
 if (caracter[0]=='\n') j++;
 if (j==4) { len+= putShConstString("&continued=true"); break;}
 if ( i == 1360 ) {len += putShConstString("\n&continued=error"); break; }

 }
 TXT_READ_END: tmp =0;
 }



 else if(!memcmp(getRequest+21, txt_cf_d, 4)) {
 len += putShConstString("&\ncf_fat_init=") ;
 tmp = Cf_Fat_Init(&portH,&portE);
 if ( tmp == 0) {
 len += putShConstString(" ok ") ;
 len += putShConstString("\ncf_fat_assign0x00=") ;
 tmp = Cf_Fat_Assign(LOG_TXT,0x00);
 if ( tmp == 0) {
 len += putShConstString("no file") ;
 }
 else if ( tmp == 1) {
 len += putShConstString("file ok") ;
 len += putShConstString("\ncf_fat_delete=") ;
 Cf_Fat_Delete();
 cf_r_ptr = 0;
 len += putShConstString(" ok ") ;
 }
 else {
 intToStr(tmp, dyna) ;
 len += putShString(dyna) ;
 }
 }
 else {
 intToStr(tmp, dyna) ;
 len += putShString(dyna) ;
 }
 }

 else goto ILLEGAL_COMMAND;

 }

 else {
 if(!memcmp(getRequest+21, txt_open, 4)) {
 len += putShConstString("&open_port=") ;
 Num_to_0str(cmd_port_num, dyna);

 len += putShString(dyna) ;
 if ( (cmd_port_num > 40) || (cmd_port_num < 1) ) goto ILLEGAL_COMMAND;
 open_port(cmd_port_num);
 l_w_port(cmd_port_num);

 len += putShConstString("&result=accepted") ;
 }

 else if(!memcmp(getRequest+21, txt_close, 4)) {
 len += putShConstString("&close_port=") ;
 Num_to_0str(cmd_port_num, dyna);

 len += putShString(dyna) ;
 if ( (cmd_port_num > 40) || (cmd_port_num < 1) ) goto ILLEGAL_COMMAND;
 close_port(cmd_port_num);
 l_w_port(cmd_port_num);

 len += putShConstString("&result=accepted") ;
 }

 else if(!memcmp(getRequest+21, txt_status, 4)) {
 l_w_port(cmd_port_num);

 if (cmd_port_num > 40) goto ILLEGAL_COMMAND;
 len += putShConstString("&state=ok") ;
 sprintf(tmpBuf,"&cell_%02d=",cmd_port_num);
 len += putShString(tmpBuf);
 if(cellState[cmd_port_num][4]=='8') {
 len += putShConstString("no\r\n");
 }
 else {
 sprintf(tmpBuf,"%c,",cellState[cmd_port_num][0]);
 len += putShString(tmpBuf);
 sprintf(tmpBuf,"%c,",cellState[cmd_port_num][1]);
 len += putShString(tmpBuf);
 sprintf(tmpBuf,"%c,",cellState[cmd_port_num][2]);
 len += putShString(tmpBuf);
 sprintf(tmpBuf,"%c,",cellState[cmd_port_num][3]);
 len += putShString(tmpBuf);
 sprintf(tmpBuf,"%c",cellState[cmd_port_num][4]);
 len += putShString(tmpBuf);
 }
 }

 else goto ILLEGAL_COMMAND;

 }

 }
 else {
ILLEGAL_COMMAND: len += putShConstString("result=illegal_command") ;
 tmp =Set_fnum();
 log_write (  3 , " illegal_command             ", tmp );
 }
  PORTC.F1  = 1;
 return(len) ;
}
#line 446 "E:/Work/УДС/UDS_controller/ПО (контроллер Раицкого)/5906_no_coding_single_masterkey_B1_inverted_20220310/ethernet.c"
unsigned int Ethernet_UserUDP(unsigned char *remoteHost, unsigned int remotePort, unsigned int destPort, unsigned int reqLength)
{
 unsigned int len ;
 len=0;
 return(len) ;
}


void My_str_n(unsigned char *s_out, unsigned char *s_source, unsigned char n )
{
 unsigned char i, k, tmp, tmp1, tmp2, tmp3;
 tmp1= tmp2= tmp3 =0;
 for (i=1; i<(n+1); i++)
 {
 tmp1= tmp2;
 tmp2= tmp3;
 tmp3= tmp;
 tmp = *(s_source + (i+4) );


 if (tmp == '\0') break;



 if ( (tmp != 0x0D) && (tmp != 0x0A) )
 {
 *(s_out + (i-1) ) = tmp ;
 }
 if ( (tmp1 == 'H') && (tmp2 == 'T') && (tmp3 == 'T') && (tmp == 'P') )
 {
 i++;
 break;
 }
 }
 for (k=i; k<85; k++)
 {
 *(s_out + (k-1) ) = '_' ;
 }
}


void l_w_port(unsigned char cmd_port_num)
{
 char tmp[4];

 dyna[0] = '_';
 dyna[1] = 'p';
 dyna[2] = 'o';
 dyna[3] = 'r';
 dyna[4] = 't';
 ByteToStr(cmd_port_num, tmp) ;
 dyna[5] = tmp[1];
 dyna[6] = tmp[2];
 dyna[7] = '\0';
}


void My_long_to_str( unsigned long size, unsigned char *s_out )
{
 unsigned char i, tmp[12];

 LongToStr(size, tmp) ;
 for (i=0; i< 12; i++)
 {
 if (tmp[i] == ' ') tmp[i] = '0';
 *(s_out + i ) = tmp[i];
 }
}


unsigned int putShConstString(const unsigned char *ptr )
{
unsigned int len2 = 0 ;
unsigned char tmp_h, tmp_l;
unsigned char cod_inbyte, cod_outbyte[3] ;
unsigned int i=0;
#line 546 "E:/Work/УДС/UDS_controller/ПО (контроллер Раицкого)/5906_no_coding_single_masterkey_B1_inverted_20220310/ethernet.c"
while (*ptr != 0)
 {
 cod_inbyte = (*ptr) ;
 cod_outbyte[0] = cod_inbyte;
 cod_outbyte[1] = 0;
 len2+=  Ethernet_putString (cod_outbyte) ;
 ptr++;
 }
return (len2);

}




unsigned int putShString(unsigned char *ptr )
{
unsigned int len2 = 0 ;
unsigned char tmp_h, tmp_l;
unsigned char cod_inbyte, cod_outbyte[3] ;
unsigned int i=0;
#line 591 "E:/Work/УДС/UDS_controller/ПО (контроллер Раицкого)/5906_no_coding_single_masterkey_B1_inverted_20220310/ethernet.c"
while (*ptr != 0)
 {
 cod_inbyte = (*ptr) ;
 cod_outbyte[0] = cod_inbyte;
 cod_outbyte[1] = 0;
 len2+=  Ethernet_putString (cod_outbyte) ;
 ptr++;
 }
return (len2);

}
