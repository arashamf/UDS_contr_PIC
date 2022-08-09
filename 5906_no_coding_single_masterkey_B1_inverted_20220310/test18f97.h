// Заголовочный файл   test18f97.h


// Глобальные переменные
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

unsigned char  cmd_port_num;      // 0..40 номер порта, на который подана команда

unsigned char cellState[15][5];        // текущее состояние ячеек, полученное от них в процессе регулярного опроса
unsigned char prevCellState[15][5];    // предыдущее состояние ячеек - нужно для обнаружения изменений и записи в лоХ
unsigned int chkSum1[15],chkSum2[15];  // "контрольные суммы", используются для устранения единичных случаев неполучения ответов от ячеек

unsigned char lim_ventil;   // 0..5 число разблокированных портов, не более 5
//  RTC часы реального времени
unsigned char month, day, date, year, hour, minute, second;

unsigned int file_number;  // номер лог - файла на CF
unsigned char visocosny;


unsigned char  ip_new_flag; // - флаг запуска в режиме установки нового IP (=1)

unsigned char l_st_ok ; // флаг для вывода состояния =1 - шлейфы в норме, нет КЗ ; =  0 есть КЗ   (line_analyze.c)
unsigned char lines_st_ok ; // флаг- защелка для вывода состояния =1 - шлейфы в норме, не было КЗ ; =  0 было КЗ

unsigned char  flag_cf_log;  // есть строки для записи на CF =1
unsigned char  flag_read_fat;  // FAT в состоянии read =1, иначе 0
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

//Внешние переменные и функции
//  RAM variables   для инициализации  Ethernet контроллера

extern unsigned char   myMacAddr[6];            // my MAC address
extern unsigned char   myIpAddr[4];             // my IP address
extern unsigned char   gwIpAddr[4];             // gateway (router) IP address
extern unsigned char	  ipMask[4];              // network mask (for example : 255.255.255.0)
extern unsigned char	  dnsIpAddr[4];	          // DNS server IP address
extern unsigned long  cf_r_ptr ;                // адрес байта - чтение флэш карты в процессе выполнения

extern char log_write ( char type, char *inf , char regim);      // Функции записи строк в журнал CF
extern unsigned char Set_fnum(void);      // обновление номера файла журнала =0-err, =1-файл пуст, =2-год соответствует текущему, =3-прошлогодний

extern void ip_set( void);                 // запись IP в EEPROM
extern void ip_get( void);                 // чтение IP из EEPROM  при включении питания или после перезапуска
void WriteChangesLog(unsigned char cell);  // если текущее состояние ячейки отличается от предыдущего, запишем это в лоХ



//