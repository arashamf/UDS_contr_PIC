
// ethernet.h

// ROM constant strings

const unsigned char httpHeader[] = "HTTP/1.1 200 OK\nContent-type: " ;  // HTTP header
const unsigned char httpMimeTypeHTML[] = "text/html\n\n" ;              // HTML MIME type
const unsigned char httpMimeTypeScript[] = "text/plain\n\n" ;           // TEXT MIME type

//  RAM variables   ??? ?????????????  Ethernet ???????????

unsigned char   myMacAddr[6] = {0x00, 0x14, 0xA5, 0x01, 0x01, 0x01} ;   // my MAC address
unsigned char   myIpAddr[4]  = {192, 1, 1, 1 } ;                   // my IP address
unsigned char   gwIpAddr[4]  = {192, 1, 2, 1 } ;                   // gateway (router) IP address
unsigned char	  ipMask[4]    = {255, 0, 0, 0 } ;                   // network mask (for example : 255.255.255.0)
unsigned char	  dnsIpAddr[4] = {192, 1, 2, 1 } ;	                  // DNS server IP address

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


unsigned char   getRequest[128] ;                                        // HTTP request buffer
unsigned char   dyna[122] ; // ?????? ??? ???????? ????????????? ??????
unsigned long   httpCounter = 0 ;                                       // counter of HTTP requests
unsigned char len;

// shifr
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


unsigned int  key_addr;         // ????? ????? ??? ??????????
unsigned int key_addr0;         //
unsigned int  putShConstString(const unsigned char *ptr ) ;   // ???????? ?????? ????????
unsigned int  putShString(unsigned char *ptr ) ;   // ???????? ??????
unsigned int  putShString2(unsigned char *ptr ) ;   // ???????? ??????


//   cf
char  LOG_TXT[13] = "LOG__001.TXT";                 // ??? ????? ??? ??????
unsigned long  cf_r_ptr ;      // ????? ????? - ?????? ???? ????? ? ???????? ??????????

void l_w_port(unsigned char cmd_port_num);   //?????? ? ?????? dyna ?????? ?????? ? ??????? ?????
void My_str_n(unsigned char *s_out, unsigned char *s_source, unsigned char n );  // ???????? /????????? n ????????
void My_long_to_str( unsigned long size, unsigned char *s_out );  // ??????????? long ????? ? ?????? ?? 11 ????????, ?????????? ????

extern unsigned char  flag_read_fat;  // FAT ? ????????? read =1, ????? 0
extern unsigned char   myIpAddr[4];      // my IP address // ????????? ?  test18f97.c

extern unsigned char  cmd_port_num;      // ????? ?????, ?? ??????? ?????? ???????  0..40
extern unsigned char cellState[13][5];
extern unsigned int chkSum1[14],chkSum2[14];
extern unsigned char cellCommand[14];
extern unsigned char lim_ventil;   // 0..5 ????? ???????????????? ??????, ?? ????? 5

extern unsigned char l_st_ok ; // ???? ??? ?????? ????????? =1 - ?????? ? ?????, ??? ?? ; =  0 ???? ??   (line_analyze.c)
extern unsigned char lines_st_ok ; //// ????- ??????? ??? ?????? ????????? =1 - ?????? ? ?????, ?? ???? ?? ; =  0 ???? ??

extern void open_port ( unsigned char  cmd_port_num  );    // ???????????? ????????/ ???????? CMOS- ??????
extern void close_port (  unsigned char  cmd_port_num  );

extern char log_write ( char type, char *inf , char regim);       // ??????? ?????? ????? ? ?????? CF
extern unsigned char Set_fnum(void);      // ?????????? ?????? ????? ??????? =0-err, =1-???? ????, =2-??? ????????????? ????????, =3-????????????

extern unsigned char month, day, date, year, hour, minute, second;
extern  void rtc_read(void); //  ?????? RTC (?????) ? dyna[]
extern void rtc_set(void);  // ????????? ?????

extern void Num_to_0str(unsigned char num, unsigned char *p_str);  // ??????????? ????? (0..255) ? ?????? ?? ???? ????????  ?????????? - ???? (log.c)

extern unsigned char  ip_new_flag; // - ???? ??????? ? ?????? ????????? ?????? IP (=1)

extern unsigned int Termo_measure();   // ?????e ???????????  DS18B20 ???? termo.c
extern unsigned char temperature;





#define putConstString  Ethernet_putConstString

#define putString  Ethernet_putString