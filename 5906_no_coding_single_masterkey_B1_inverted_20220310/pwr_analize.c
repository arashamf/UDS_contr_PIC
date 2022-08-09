
// ПРОВЕРКА состояния источников питания и схемы защиты от перегрузки по току

#ifndef    def_Board
    #include        "def_Board.h"
#endif


extern unsigned char cellState[15][5];
extern unsigned char prevCellState[15][5];
extern unsigned int chkSum1[15],chkSum2[15];

extern unsigned char   dyna[122] ; // строка для хранения промежуточных данных

extern  void l_w_port2(unsigned char cmd_port_num);   //запись в строку dyna начала строки с номером порта (15 символов)  line_analyze.c
extern char log_write ( char type, char *inf , char regim);      // Функции записи строк в журнал CF
extern unsigned char Set_fnum(void);      // обновление номера файла журнала =0-err, =1-файл пуст, =2-год соответствует текущему, =3-прошлогодний

extern  unsigned char  flag_cf_log;  // есть строки для записи на CF =1



