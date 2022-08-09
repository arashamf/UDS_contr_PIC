// файл termo.c
// чтениe температуры  DS18B20
//
#ifndef    def_Board
    #include        "def_Board.h"
#endif


unsigned char temperature;
 
 

void OneWireDirOut (void)
{
  TRISD.F7 = 0;
}
void OneWireDirIn (void)
{
  TRISD.F7 = 1;
}
void OneWireOn (void)
{
  LATD.F7 = 1;
}
void OneWireOff (void)
{
  LATD.F7 = 0;
}
unsigned int OneWireLevel (void)
{
  if(PORTD.F7==0) return 0;
  if(PORTD.F7!=0) return 1;
}


 unsigned char OneWireReset(void)
{
	OneWireOff();                               // Normal input no pull up
	OneWireDirOut();                            // out at 0
	delay_us(500);
	OneWireDirIn();                             // Set to input
	delay_us(70);
	if ((OneWireLevel()) == 0)
	{
		delay_us(500);
		return 1;
	}
	delay_us(500);
	return 0;
}

/**********************************************************
Name:               void OneWireWriteByte(unsigned char mask,unsigned char data)
Description:        Write a byte on the OneWire buss,
Input:              mask : Where the device are on the port,
                    data : Data to write on the port
Output:             none
**********************************************************/
void OneWireWriteByte(unsigned char dat)
{
	unsigned char i;

	OneWireDirIn();OneWireOff();     	//input 0
	for (i=0;i<=7;i++)
	{
		OneWireDirOut();  						//out0
		if (dat & 0x01) {
			delay_us(7);              // Send 1
			OneWireDirIn();        			// input
			delay_us(70);
		}
		else {
			delay_us(70);            	// Send 0
			OneWireDirIn();
			delay_us(7);
		}
		dat>>=1;
	}
}

/**********************************************************
Name:               unsigned char OneWireReadByte(unsigned char mask)
Description:        Read a byte on the OneWire buss,
Input:              mask : Where the device are on the port
Output:             data that had been read
**********************************************************/
unsigned char OneWireReadByte(void)
{
	unsigned char dat = 0;
	unsigned char i;

	OneWireDirIn();OneWireOff();                  // Output '0' or input without pullup
	for (i=0;i<=7;i++)	{
		OneWireDirOut();                          // Set output to '0'
		delay_us(7);
		OneWireDirIn();                           // Set to input
		delay_us(7);
		dat >>=1;
		if ((OneWireLevel())) { dat |= 0x80; }
		else { dat &= 0x7f; }
		delay_us(70);
	}
	return dat;
}


//Программа измерения температуры
//Возврат: 0x0000XXXX, где XXXX-два байта температуры, если 0xFFFFFFFF - ошибка
unsigned int Termo_measure (void)
{
	unsigned char crc8=0, i=0;
	unsigned char memory[9];		// Буфер для записи памяти температурного датчика

	if(OneWireReset()) {
  	OneWireWriteByte(0xCC);		//пропуск идентификации
  	OneWireWriteByte(0x44);		//запуск преобразования температуры

  	while(!OneWireLevel()){}    //ожидание преобразования

  	OneWireReset();						//сброс
  	OneWireWriteByte(0xCC);		//пропуск идентификации
  	OneWireWriteByte(0xBE);		//чтение памяти

  	for (i=0;i<9;i++)         //чтение памяти термодатчика
    {
    	memory[i]=OneWireReadByte();
    }
  	return ((memory[1]<<8)+(memory[0]))>>1;
  }
}




