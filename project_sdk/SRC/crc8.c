#include "aduc812.h"
#include "max.h"

/*
  Name  : CRC-8
  Poly  : 0x31	x^8 + x^5 + x^4 + 1
  Init  : 0xFF
  Revert: false
  XorOut: 0x00
  Check : 0xF7 ("123456789")
  MaxLen: 15 байт(127 бит) - обнаружение
    одинарных, двойных, тройных и всех нечетных ошибок
*/

unsigned char crc8(int page, short regnum, unsigned char len)
{
		
	unsigned char crc = 0xFF;
	unsigned char i;
	
	while (len--)
	{
		crc ^= read_max(page, regnum);
		regnum++;
 
		for (i = 0; i < 8; i++)
			crc = crc & 0x80 ? (crc << 1) ^ 0x31 : crc << 1;
	}
	return crc;
}
