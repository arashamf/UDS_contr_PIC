// ����  ip_set.c
//  ������������ ������������� IP ������
//

#ifndef    def_Board
    #include        "def_Board.h"
#endif


//������� ���������� � �������
//  RAM variables   ��� �������������  Ethernet �����������

extern unsigned char   myMacAddr[6];            // my MAC address
extern unsigned char   myIpAddr[4];             // my IP address
extern unsigned char   gwIpAddr[4];             // gateway (router) IP address
extern unsigned char	  ipMask[4];              // network mask (for example : 255.255.255.0)
extern unsigned char	  dnsIpAddr[4];	          // DNS server IP address

extern unsigned char  ip_new_flag; // - ���� ������� � ������ ��������� ������ IP (=1)

extern void ip_read(void);    // ������ IP �� EEPROM       ���� eeprom.c
extern void ip_write(void);    // ������ IP � EEPROM       ���� eeprom.c



//
void ip_get( void)                 // ������ IP �� EEPROM  ��� ��������� ������� ��� ����� �����������
{
ip_read();    // ������ IP �� EEPROM
//             myIpAddr[3]  = 1 ;                   // my IP address  !!!
}



void ip_set( void)                 // ������ IP � EEPROM
{
unsigned int    cntr_1, cntr_2 ;


  while(1)                        // do forever
  {
    Ethernet_doPacket() ;   // process incoming Ethernet packets
    // ����� ������� � ����� IP - � ������� Ethernet_UserTCP
    asm CLRWDT;        // ����� ����������� �������
    if (!ip_new_flag) break;     // ����� � �������� �����
    //
    if (cntr_1  <= 6400 )  cntr_1++ ;
    else  {
      cntr_1 =0;
      Led_G  = !Led_G;     //
    }

    if (cntr_2  <= 640 )  cntr_2++ ;
    else  {
      cntr_2 =0;
      Led_Y  = !Led_Y;     //
    }
  }  // end   while(1)
  ip_write();    // ������ IP � EEPROM
}