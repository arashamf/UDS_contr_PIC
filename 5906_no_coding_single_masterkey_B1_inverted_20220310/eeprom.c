// файл eeprom.c
// запись и чтениe IP в EEPROM
//
#ifndef    def_Board
    #include        "def_Board.h"
#endif


 //Внешние переменные и функции
extern unsigned char   myMacAddr[6];            // my MAC address
extern unsigned char   myIpAddr[4];                   // my IP address




//
void ip_write(void)    // запись IP в EEPROM
{
  // запись нового IP
  I2C_Init(100000);      // initialize full master mode
  I2C_Start();          // issue start signal
  I2C_Wr(0xA0);         // Slave address m24c16, write
  I2C_Wr(0x00);         // Byte adress
  //
  I2C_Wr(myIpAddr[0]);            // запись 1-го байта IP
  I2C_Wr(myIpAddr[1]);         // 2
  I2C_Wr(myIpAddr[2]);         // 3
  I2C_Wr(myIpAddr[3]);         // 4
  I2C_Stop();           // issue stop signal
  // запись символов окончания записи
  I2C_Start();          // issue start signal
  I2C_Wr(0xA0);         // Slave address m24c16, write
  I2C_Wr(0x01);         // Byte adress
  //
  I2C_Wr('E');            // запись 1-го символа
  I2C_Wr('E');         // 2
  I2C_Wr('E');         // 3
  I2C_Wr('E');         // 4
  I2C_Stop();           // issue stop signal

  myMacAddr[3] = myIpAddr[1];
  myMacAddr[4] = myIpAddr[2];
  myMacAddr[5] = myIpAddr[3];
}//~


//
void ip_read(void)    // чтение IP из EEPROM
{
  I2C_Init(100000);         // initialize I2C
  I2C_Start();
  I2C_Wr(0xA0);                 // Slave address m24c16, write
  I2C_Wr(0x00);                 // Byte adress
  I2C_Repeated_Start();
  I2C_Wr(0xA1);                 // Slave address m24c16, read

  myIpAddr[0] =I2C_Rd(1);         // чтение 1-го байта IP
  myIpAddr[1] =I2C_Rd(1);         //
  myIpAddr[2] =I2C_Rd(1);         //
  myIpAddr[3] =I2C_Rd(0);         //
  I2C_Stop();

  myMacAddr[3] = myIpAddr[1];
  myMacAddr[4] = myIpAddr[2];
  myMacAddr[5] = myIpAddr[3];
}//~