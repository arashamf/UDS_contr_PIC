//   open_port.c
   // подпрограммы открыти€/ закрыти€ CMOS- ключей

#ifndef    def_Board
    #include        "def_Board.h"
#endif


//  mask_ventil[0]  исправность источников питани€ и схемы защиты  =0-норма, !=0- неисправность (27v не готов или сработала схема защиты и питание соленоидов отключено)
extern unsigned char lim_ventil;   // 0..5 число разблокированных портов, не более 5
extern unsigned char cellCommand[15];
extern unsigned char fMasterKey;

// команда включить соленоид
void open_port (  unsigned char  cmd_port_num )
{
  if(fMasterKey==1) {return;}           // нельз€ открывать и закрывать €чейки когда повернут мастер ключ
  if (cellCommand[cmd_port_num] == 1) {return;}  // чо открывать если уже и так открыто
  //if( lim_ventil > 5) { return;}   // lim_ventil 0..5 число разблокированных портов, не более 5
  cellCommand[cmd_port_num] = 1;
  //lim_ventil++;
}


// команда выключить соленоид
void close_port (  unsigned char  cmd_port_num )
{
  if(fMasterKey==1) {return;}           // нельз€ открывать и закрывать €чейки когда повернут мастер ключ
  if (cellCommand[cmd_port_num] == 0) {return;}
  cellCommand[cmd_port_num] = 0;
  //if( lim_ventil > 0) { lim_ventil--; }
}



