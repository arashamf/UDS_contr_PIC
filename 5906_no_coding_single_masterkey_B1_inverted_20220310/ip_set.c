// файл  ip_set.c
//  подпрограммы инициализации IP стойки
//

#ifndef    def_Board
    #include        "def_Board.h"
#endif


//Внешние переменные и функции
//  RAM variables   для инициализации  Ethernet контроллера

extern unsigned char   myMacAddr[6];            // my MAC address
extern unsigned char   myIpAddr[4];             // my IP address
extern unsigned char   gwIpAddr[4];             // gateway (router) IP address
extern unsigned char	  ipMask[4];              // network mask (for example : 255.255.255.0)
extern unsigned char	  dnsIpAddr[4];	          // DNS server IP address

extern unsigned char  ip_new_flag; // - флаг запуска в режиме установки нового IP (=1)

extern void ip_read(void);    // чтение IP из EEPROM       файл eeprom.c
extern void ip_write(void);    // запись IP в EEPROM       файл eeprom.c



//
void ip_get( void)                 // чтение IP из EEPROM  при включении питания или после перезапуска
{
ip_read();    // чтение IP из EEPROM
//             myIpAddr[3]  = 1 ;                   // my IP address  !!!
}



void ip_set( void)                 // запись IP в EEPROM
{
unsigned int    cntr_1, cntr_2 ;


  while(1)                        // do forever
  {
    Ethernet_doPacket() ;   // process incoming Ethernet packets
    // прием команды с новым IP - в функции Ethernet_UserTCP
    asm CLRWDT;        // сброс сторожевого таймера
    if (!ip_new_flag) break;     // выход в основной режим
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
  ip_write();    // запись IP в EEPROM
}