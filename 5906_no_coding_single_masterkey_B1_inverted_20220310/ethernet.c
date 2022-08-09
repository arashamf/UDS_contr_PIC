// ���� ethernet.c
//������������ ������������ ethernet
// � ��������� �������� ������

#ifndef    def_Board
    #include        "def_Board.h"
#endif
#include        "ethernet.h"


unsigned int    Ethernet_UserTCP(unsigned char *remoteHost, unsigned int remotePort, unsigned int localPort, unsigned int reqLength)
{
  unsigned int    len = 0 ;                   // my reply length
  unsigned long  i, size;
  unsigned int    tmp, j ;                    // general purpose char

  // encrypt
  unsigned char tmph, tmpl;         // �������/������� 4 ���� ������������� �����
  unsigned char tmp_inbyte, tmp_outbyte ;         //  ������������/ �������������� ����
  unsigned char start_0addr, start_1addr, start_2addr, start_3addr;
  // ����� ������ ����� ��� ����������  - 4������� 0..1023

  char  caracter[2]= "0";         //   cf
  char  fread_num[4]= "000";                     // ����� ����� ��� ������ CF
  unsigned char tmpBuf[20];

  if(localPort != 25006)  {                      // I listen only to web request on port 80
   return(0) ;
  }

  Led_Y  = 0;  // �������� ������ ��
///////////////////////////  SHIFR
#ifdef    def_Shifr

  for(i = 0 ; i < 6 ; i++)
  {
   getRequest[i] = Ethernet_getByte() ;  // 0..4 GET, 5 - ? /
  }
  start_0addr = Ethernet_getByte()-0x30 ;   // ����� ������ ����� ��� ���������� ������ - �������
  start_1addr = Ethernet_getByte()-0x30 ;   // ����� ������ ����� ��� ����������
  start_2addr = Ethernet_getByte()-0x30 ;   // ����� ������ ����� ��� ����������
  start_3addr = Ethernet_getByte()-0x30 ;   // ����� ������ ����� ��� ����������
  key_addr0 = start_0addr*1000;
  key_addr0 += start_1addr*100;
  key_addr0 += start_2addr*10;
  key_addr0 += start_3addr;

  for(i = 6 ; i < 127 ; i++)          //76  // �������������
  {
    tmph = Ethernet_getByte()- 0x41 ;  //  ������� 4 ���� ������������� �����  (0 <=  0x41 "A" ... f <= 0x50 "P")
    tmpl = Ethernet_getByte()- 0x41 ;  // ������� 4 ���� ������������� �����
    tmp_inbyte = tmpl + (tmph<<4);
    key_addr = (key_addr0 +i -6)& 0x03ff;
    tmp_outbyte = tmp_inbyte ^ key_arr[key_addr];
    getRequest[i] = tmp_outbyte;  //
  }
  getRequest[127] = 0 ;   // '\0' = 0 -����� ������

  key_addr = (key_addr0 + 0x100 );  // ��������� ����� ������ ��� ������
#endif
///////////////////////////  SHIFR
///////////////////////////  NO SHIFR
#ifndef    def_Shifr

  for(i = 0 ; i < 127 ; i++)
  {
   getRequest[i] = Ethernet_getByte() ;  // 0..4 GET, 5 - ? /
  }
  getRequest[127] = 0 ;   // '\0' = 0 -����� ������

#endif
///////////////////////////  NO SHIFR

  if(memcmp(getRequest, httpMethod, 5)) {      // only GET method is supported here
   Led_Y  = 1; return(0) ;
  }

  len =  putConstString(httpHeader) ;             // HTTP header
  len += putConstString(httpMimeTypeScript) ;       // with HTML MIME type

  if ( (memcmp(getRequest+21, txt_0read, 4 )) && (memcmp(getRequest+21, txt_read, 4)) && (memcmp(getRequest+21, txt_status, 4 )) )  {
    // �������� � ��� ������� ����� 0read, read, state
    My_str_n(dyna, getRequest, 84);  // �������� /��������� 84 �������
    log_write ( COMMAND, dyna, tmp );   // �������� � ������ - �������  84 �������
  }

  len += putShConstString("stoika=") ;

  Num_to_0str(myIpAddr[0], dyna);  // ����������� ����� (0..255) � ������ �� ���� ��������  ���������� - ����
  len += putShString(dyna) ;
  len += putShConstString(".") ;

  Num_to_0str(myIpAddr[1], dyna);  // ����������� ����� (0..255) � ������ �� ���� ��������  ���������� - ����
  len += putShString(dyna) ;
  len += putShConstString(".") ;

  Num_to_0str(myIpAddr[2], dyna);  // ����������� ����� (0..255) � ������ �� ���� ��������  ���������� - ����
  len += putShString(dyna) ;
  len += putShConstString(".") ;

  Num_to_0str(myIpAddr[3], dyna);  // ����������� ����� (0..255) � ������ �� ���� ��������  ���������� - ����
  len += putShString(dyna) ;
        
  if (!memcmp(getRequest+5, txt_command, 13)) {         // ������ �������: command port
    cmd_port_num =  (getRequest[19] - '0') + 10*(getRequest[18] - '0');  // ��������� ����� �����, ���� ���� ���������
    if (ip_new_flag) {     // - ���� ������� � ������ ��������� ������ IP (=1)
      if (! ( cmd_port_num == 0)  )  goto ERR_CMD;   // ������� ��� ���� ������
      if(!memcmp(getRequest+21, txt_iset, 4))  {     // ������� IP SET ������
        myIpAddr[0] =  10*(getRequest[30] - '0') + (getRequest[31] - '0');   // ���������� ������� ����� IP
        if  (getRequest[29] == '1')   myIpAddr[0] +=  100;
        else if  (getRequest[29] == '2') myIpAddr[0] +=  200;

        myIpAddr[1] =  10*(getRequest[34] - '0') + (getRequest[35] - '0');    // ���������� 2 ����� IP
        if  (getRequest[33] == '1')   myIpAddr[1] +=  100;
        else if  (getRequest[33] == '2') myIpAddr[1] +=  200;

        myIpAddr[2] =  10*(getRequest[38] - '0') + (getRequest[39] - '0');    // ���������� 3 ����� IP
        if  (getRequest[37] == '1')   myIpAddr[2] +=  100;
        else if  (getRequest[37] == '2') myIpAddr[2] +=  200;

        myIpAddr[3] =  10*(getRequest[42] - '0') + (getRequest[43] - '0');    // ���������� 4 ����� IP
        if  (getRequest[41] == '1')   myIpAddr[3] +=  100;
        else if  (getRequest[41] == '2') myIpAddr[3] +=  200;
        tmp =Set_fnum();
        //if ( tmp != 0 )  // ���������� ������ ����� �������
        log_write ( IP, " :new_ip                    ", tmp );   // �������� � ������ - �������  (28 �������� )
        ip_new_flag = 0; // ����� - ���� ������� � ������ ��������� ������ IP (=1)
      }
      else goto ERR_CMD;

      len += putShConstString("result=accepted") ;
      Led_Y  = 1;
      return(len) ;

      ERR_CMD:                  len += putShConstString("result=error_ip_command") ;
      tmp =Set_fnum();
      //if ( tmp != 0 )  // ���������� ������ ����� �������
      log_write ( CMD, " error_ip_command           ", tmp );   // �������� � ������ - �������  (28 �������� )
      Led_Y  = 1;
      return(len) ;                                             // return to the library with the number of bytes to transmit
    }

    if ( cmd_port_num == 0) { // ������� ��� ���� ������
      if(!memcmp(getRequest+21, txt_status, 4)) {   // ������� status ������
        len += putShConstString("&state=OK\r\n");
        for (tmp=1;tmp<15;tmp++)
        {
          sprintf(tmpBuf,"cell_%02d=",tmp);
          len += putShString(tmpBuf);
          if(cellState[tmp][4]=='8') {
            len += putShConstString("no\r\n");
          }
          else {
            if (tmp == 14)            //��� 14 ������ ������ �������
            {
              sprintf(tmpBuf,"%c,",cellState[tmp][0]);
              len += putShString(tmpBuf);
              if (cellState[tmp][1] == '0')   //�������� 2-�� �����
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
              if (cellState[tmp][2] == '0')  //�������� 3-�� �����
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
                                   
//////////////////////////   RTC     ////////////////////////////////////////////////////////////////
      else if(!memcmp(getRequest+21, txt_rtcr, 4))  {  // ������� 	rtcr:
        len += putShConstString("&rtcr=") ;
        rtc_read();     //  ������ RTC  � dyna[]
        len += putShString(dyna) ;
      }
                                   
      else if(!memcmp(getRequest+21, txt_rtds, 4)) {   // ������� 	rtds:
        len += putConstString("&rtds=") ;
        //�������� ���������� ��������� ����
        if (   ( ( (getRequest[28] - '0')*10 ) + (getRequest[29] - '0')  )  >31 )
        { len += putConstString("error") ; goto ILLEGAL_COMMAND;  }  //  date
        if (   ( ( (getRequest[33] - '0')*10 ) + (getRequest[34] - '0')  )  >12 )
        { len += putConstString("error") ; goto ILLEGAL_COMMAND;  }   //  month
        if (   ( ( (getRequest[38] - '0')*10 ) + (getRequest[39] - '0')  )  >99 )
        { len += putConstString("error") ; goto ILLEGAL_COMMAND;  }   //  year

        rtc_read();
        date =     ( (getRequest[28] - '0')*10 ) + (getRequest[29] - '0');
        month =    ( (getRequest[33] - '0')*10 ) + (getRequest[34] - '0');
        year =     ( (getRequest[38] - '0')*10 ) + (getRequest[39] - '0');
        rtc_set();  // ��������� �����

        len += putString(dyna) ;
      }


      else if(!memcmp(getRequest+21, txt_rtss, 4)) {   // ������� 	rtss:
        len += putConstString("&rtss=") ;
        //�������� ���������� ��������� �������
        if (   ( ( (getRequest[28] - '0')*10 ) + (getRequest[29] - '0')  )  >24 )
        { len += putConstString("error") ; goto ILLEGAL_COMMAND;  } //  hour
        if (   ( ( (getRequest[33] - '0')*10 ) + (getRequest[34] - '0')  )  >59 )
        { len += putConstString("error") ; goto ILLEGAL_COMMAND;  }   //  minute
        if (   ( ( (getRequest[38] - '0')*10 ) + (getRequest[39] - '0')  )  >59 )
        { len += putConstString("error") ; goto ILLEGAL_COMMAND;  }   //  second

        rtc_read();
        hour =     ( (getRequest[28] - '0')*10 ) + (getRequest[29] - '0');
        minute =   ( (getRequest[33] - '0')*10 ) + (getRequest[34] - '0');
        second =   ( (getRequest[38] - '0')*10 ) + (getRequest[39] - '0');
        rtc_set();  // ��������� �����

        len += putString(dyna) ;
      }
                                   
      else if(!memcmp(getRequest+21, txt_term, 4)) {   // ������� 	term:
        len += putShConstString("&term=") ;
        Num_to_0str(Termo_measure(), dyna);  //����������� ����� (0..255) � ������ �� ���� ��������  ���������� - ����
        len += putShString(dyna) ;
      }

///////////////////////  COMPACT FLASH     ///////////////////////////////////////////////////////////

      else if(!memcmp(getRequest+21, txt_0read, 4))   {    //  ������  �������, 0read
        cf_r_ptr =0;             // - �������� ����������� read
        len += putShConstString("&cf_fat_0read=ok") ;
      }

      else if(!memcmp(getRequest+21, txt_read, 4)) {   // ������� 	read:
        fread_num[0] =  getRequest[35];
        fread_num[1] =  getRequest[36];
        fread_num[2] =  getRequest[37];
        if ( (LOG_TXT[5] !=  fread_num[0]) || (LOG_TXT[6] !=  fread_num[1]) || (LOG_TXT[7] !=  fread_num[2]) ) {
           cf_r_ptr =0;  // ��������� ������� ������ ������� �����
        }
        LOG_TXT[5] =  fread_num[0];
        LOG_TXT[6] =  fread_num[1];
        LOG_TXT[7] =  fread_num[2];

        if(cf_r_ptr ==0) flag_read_fat = 0;  //flag_read_fat: FAT � ��������� read =1, ����� 0
        len += putShConstString("&file_num=");
        len += putShString(fread_num) ;

        if(flag_read_fat != 1) { //flag_read_fat: FAT � ��������� read =1, ����� 0
          len += putShConstString("&cf_fat_init=") ;
          tmp =  Cf_Fat_Init(&portH,&portE);
          if ( tmp != 0)  {// Cf_Fat_Init err
            intToStr(tmp, dyna) ;     // Cf_Fat_Init err
            len += putShString(dyna) ;
            goto  TXT_READ_END;
          }
          len += putShConstString("ok") ;
          len += putShConstString("&cf_fat_assign0x00=") ;
          tmp = Cf_Fat_Assign(LOG_TXT,0x00);
          if ( tmp != 1) { // Cf_Fat_Assign   if file does not exist and no new file is created.
            len += putShConstString("no_file") ;
            goto  TXT_READ_END;
          }
          len += putShConstString("file_ok") ;
          Cf_Fat_Reset(&size);            // To read file, procedure returns size of file
          len += putShConstString("&size=") ;
          My_long_to_str( size, dyna );  // ����������� long ����� � ������ �� 11 ��������, ���������� ����

          len += putShString(dyna) ;
        } // end    if(flag_read_fat != 1)
        len += putShConstString("&cf_fat_read=\n") ;
        if (cf_r_ptr !=0 )    {      // ���������� ������� ��� ������
          if(flag_read_fat != 1) { //flag_read_fat: FAT � ��������� read =1, ����� 0
            for (i = 1; i < cf_r_ptr ; i++)  // 1..1280
            {
             Cf_Fat_Read(caracter);    // ������ ��� ���������
            }
          }
        }
        else  cf_r_ptr =1;
        flag_read_fat = 1;  //flag_read_fat: FAT � ��������� read =1, ����� 0
        j = 0; // ����� ��������� �����
        for (i = 1; i < 1361 ; i++)    // i=1..1281
        {
          Cf_Fat_Read(caracter);
          caracter[1] = '\0';
          len += putShString(caracter) ;
          cf_r_ptr++;
          if (cf_r_ptr > size) {cf_r_ptr = 0; len += putShConstString("\n&continued=false") ; break; } // ����� ��������
          if (caracter[0]=='\n') j++;
          if (j==4) { len+= putShConstString("&continued=true"); break;}   // ����� 10 ����� ��������
          if ( i == 1360 )  {len += putShConstString("\n&continued=error"); break; }  // ������ ������� ������ :����� ���� ����� �������� ��������
          // ���� ����� ���� � Ethernet ������ ~ 1400 =1490
        }
        TXT_READ_END:  tmp =0;
      } // end else if(!memcmp(getRequest+21, txt_read, 4))    // ������� 	read:



      else if(!memcmp(getRequest+21, txt_cf_d, 4))   { // ������� 	cf_d:
        len += putShConstString("&\ncf_fat_init=") ;
        tmp =  Cf_Fat_Init(&portH,&portE);
        if ( tmp == 0) { // Cf_Fat_Init
          len += putShConstString(" ok ") ;
          len += putShConstString("\ncf_fat_assign0x00=") ;
          tmp = Cf_Fat_Assign(LOG_TXT,0x00);
          if ( tmp == 0) { // Cf_Fat_Assign
             len += putShConstString("no file") ;
          }
          else if ( tmp == 1) { // Cf_Fat_Assign
            len += putShConstString("file ok") ;
            len += putShConstString("\ncf_fat_delete=") ;
            Cf_Fat_Delete();
            cf_r_ptr = 0;
            len += putShConstString(" ok ") ;
          } // end else if ( tmp == 1)  // Cf_Fat_Assign
          else {
            intToStr(tmp, dyna) ;     // Cf_Fat_Assign err
            len += putShString(dyna) ;
          }
        }   // end if ( tmp == 0)  // Cf_Fat_Init
        else  {
          intToStr(tmp, dyna) ;     // Cf_Fat_Init err
          len += putShString(dyna) ;
        }
      }
      
      else   goto ILLEGAL_COMMAND;

    } // end if ( cmd_port_num == 0)  // ������� ��� ���� ������

    else {   // ������� ��� ������ � ������
      if(!memcmp(getRequest+21, txt_open, 4))  { // ������� open
        len += putShConstString("&open_port=") ;
        Num_to_0str(cmd_port_num, dyna);  // ����������� ����� (0..255) � ������ �� ���� ��������  ���������� - ����
        // dyna[30] ���������� ���������� ��� �������������� ����������
        len += putShString(dyna) ;
        if ( (cmd_port_num > 40) || (cmd_port_num < 1) ) goto ILLEGAL_COMMAND;
        open_port(cmd_port_num);
        l_w_port(cmd_port_num);   //������ � ������ dyna ������ ������ � ������� �����( 7 ��������)
        // �������� � ������ - �������  (28 �������� )
        len += putShConstString("&result=accepted") ;
      }

      else if(!memcmp(getRequest+21, txt_close, 4))  {  // ������� CLOSE
        len += putShConstString("&close_port=") ;
        Num_to_0str(cmd_port_num, dyna);  // ����������� ����� (0..255) � ������ �� ���� ��������  ���������� - ����
        // dyna[30] ���������� ���������� ��� �������������� ����������
        len += putShString(dyna) ;
        if ( (cmd_port_num > 40) || (cmd_port_num < 1) ) goto ILLEGAL_COMMAND;
        close_port(cmd_port_num);
        l_w_port(cmd_port_num);   //������ � ������ dyna ������ ������ � ������� �����( 7 ��������)
        // �������� � ������ - �������  (28 �������� )
        len += putShConstString("&result=accepted") ;
      }

      else if(!memcmp(getRequest+21, txt_status, 4)) {   // ������� status  �����
        l_w_port(cmd_port_num);   //������ � ������ dyna ������ ������ � ������� �����( 7 ��������)
        // �������� � ������ - �������  (28 �������� )
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
      }  // end  if(!memcmp(getRequest+21, txt_status, 4))    // ������� status

      else   goto ILLEGAL_COMMAND;

    }  // end  else    // ������� ��� ������ � ������

  }  // end          if(!memcmp(getRequest+5, txt_port, 4))                          // ������ �������:  port
  else   {
ILLEGAL_COMMAND:   len += putShConstString("result=illegal_command") ;
                   tmp =Set_fnum();
                   log_write ( CMD, " illegal_command             ", tmp );   // �������� � ������ - �������  (28 �������� )
  }
  Led_Y  = 1;  // ��������� ������ ��
  return(len) ;                                           // return to the library with the number of bytes to transmit
}

/*
 * this function is called by the library
 * the user accesses to the UDP request by successive calls to Ethernet_getByte()
 * the user puts data in the transmit buffer by successive calls to Ethernet_putByte()
 * the function must return the length in bytes of the UDP reply, or 0 if nothing to transmit
 *
 * if you don't need to reply to UDP requests,
 * just define this function with a return(0) as single statement
 *
 */
unsigned int    Ethernet_UserUDP(unsigned char *remoteHost, unsigned int remotePort, unsigned int destPort, unsigned int reqLength)
{
  unsigned int    len ;                           // my reply length
  len=0;
  return(len) ;           // back to the library with the length of the UDP reply
}


void My_str_n(unsigned char *s_out, unsigned char *s_source, unsigned char n )  // �������� /��������� n ��������
{
 unsigned char i, k, tmp, tmp1, tmp2, tmp3;
  tmp1= tmp2= tmp3 =0;
  for (i=1; i<(n+1); i++)  // i=1..84      !!!
  {
    tmp1= tmp2;               // ����������� ����� ��������  tmp1, tmp2, tmp3, tmp
    tmp2= tmp3;
    tmp3= tmp;
    tmp = *(s_source + (i+4) );
    //

    if (tmp == '\0') break;
    //    else if (tmp == '&') tmp = '*';           // �������� ������� (��� �������� � ETHERNET)
    //    else if (tmp == '=') tmp = '#';
    //    else if (tmp == ' ') tmp = '_';
    if ( (tmp != 0x0D) && (tmp != 0x0A) )   // �������� �������� �����
    {
     *(s_out + (i-1) ) = tmp ;
    }
    if ( (tmp1 == 'H') &&  (tmp2 == 'T') &&  (tmp3 == 'T') &&  (tmp == 'P') )
    {
      i++;
      break;     //  HTTP - ����� ���-���
    }
  }
  for (k=i; k<85; k++)  // k=1..84              // �������� �� 84 ��������
  {
   *(s_out + (k-1) ) = '_' ;
  }
}


void l_w_port(unsigned char cmd_port_num)   //������ � ������ dyna ������ ������ � ������� �����
{
  char    tmp[4];
  //
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


void My_long_to_str( unsigned long size, unsigned char *s_out )  // ����������� long ����� � ������ �� 11 ��������, ���������� ����
{
  unsigned char i, tmp[12];
  //
  LongToStr(size, tmp) ;
  for (i=0; i< 12; i++)  // i=  0..11
  {
    if (tmp[i] == ' ') tmp[i] = '0';
    *(s_out + i ) = tmp[i];
  }
}


unsigned int  putShConstString(const unsigned char *ptr )  //
{
unsigned int    len2 = 0 ;                   // my reply length
unsigned char tmp_h, tmp_l;         // �������/������� 4 ���� ����������� �����  +0x41
unsigned char cod_inbyte, cod_outbyte[3] ;         //  ����������/ ������������ �����
unsigned int  i=0;

#ifdef    def_Shifr
while (*ptr != 0)
      {
//Num_to_0str(key_addr, dyna);  // ����������� ����� (0..255) � ������ �� ���� ��������  ���������� - ����
//len2+= putString(dyna) ;

//Num_to_0str((key_arr[key_addr]), dyna);  // ����������� ����� (0..255) � ������ �� ���� ��������  ���������� - ����
//len2+= putString(dyna) ;
      
      cod_inbyte = (*ptr) ^ (key_arr[key_addr]);
      tmp_h =  cod_inbyte>>4;
      tmp_l =  cod_inbyte & 0x0F;
      cod_outbyte[0] = tmp_h + 0x41;
      cod_outbyte[1] = tmp_l + 0x41;
      cod_outbyte[2] = 0;
      len2+= putString(cod_outbyte) ;
      ptr++;
      key_addr = (key_addr +1 )& 0x03ff;
      }

return (len2);
#endif
#ifndef    def_Shifr
while (*ptr != 0)
      {
      cod_inbyte = (*ptr) ;
      cod_outbyte[0] = cod_inbyte;
      cod_outbyte[1] = 0;
      len2+= putString(cod_outbyte) ;
      ptr++;
      }
return (len2);
#endif
}




unsigned int  putShString(unsigned char *ptr )  //
{
unsigned int    len2 = 0 ;                   // my reply length
unsigned char tmp_h, tmp_l;         // �������/������� 4 ���� ����������� �����  +0x41
unsigned char cod_inbyte, cod_outbyte[3] ;         //  ����������/ ������������ �����
unsigned int  i=0;

#ifdef    def_Shifr
while (*ptr != 0)
      {
//Num_to_0str(key_addr, dyna);  // ����������� ����� (0..255) � ������ �� ���� ��������  ���������� - ����
//len2+= putString(dyna) ;

//Num_to_0str((key_arr[key_addr]), dyna);  // ����������� ����� (0..255) � ������ �� ���� ��������  ���������� - ����
//len2+= putString(dyna) ;

      cod_inbyte = (*ptr) ^ (key_arr[key_addr]);
      tmp_h =  cod_inbyte>>4;
      tmp_l =  cod_inbyte & 0x0F;
      cod_outbyte[0] = tmp_h + 0x41;
      cod_outbyte[1] = tmp_l + 0x41;
      cod_outbyte[2] = 0;
      len2+= putString(cod_outbyte) ;
      ptr++;
      key_addr = (key_addr +1 )& 0x03ff;
      }

return (len2);
#endif
#ifndef    def_Shifr
while (*ptr != 0)
      {
      cod_inbyte = (*ptr) ;
      cod_outbyte[0] = cod_inbyte;
      cod_outbyte[1] = 0;
      len2+= putString(cod_outbyte) ;
      ptr++;
      }
return (len2);
#endif
}