
// ПРОВЕРКА ЛИНИЙ - ШЛЕЙФОВ

#ifndef    def_Board
    #include        "def_Board.h"
#endif

extern unsigned char lim_ventil;   // 0..5 число разблокированных портов, не более 5
//
extern unsigned char   dyna[122] ; // строка для хранения промежуточных данных

extern void close_port (  unsigned char  cmd_port_num  );      // подпрограммы открытия/ закрытия CMOS- ключей  open_port.c
extern char log_write ( char type, char *inf , char regim);      // Функции записи строк в журнал CF
extern unsigned char Set_fnum(void);      // обновление номера файла журнала =0-err, =1-файл пуст, =2-год соответствует текущему, =3-прошлогодний


extern  unsigned char  flag_cf_log;  // есть строки для записи на CF =1
//

