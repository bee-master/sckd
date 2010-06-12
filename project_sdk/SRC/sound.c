#include "aduc812.h"
#include "max.h"
#include "timer.h"

extern unsigned char cTH1, cTL1; // значения ТН и ТL для частоты текущей ноты
extern unsigned char time_to_sing;

void sound_generation( void )
{
	static unsigned char regENA = read_max(8, ENA );
	TH1 = cTH1;
	TL1 = cTL1;
	regENA = regENA ^ 0x1C; // переключаем звуковые биты (с 000 на 111)
	write_max (8, ENA, regENA); // запись в регистр ENA
}

void play_melody (int num_page)
{
	unsigned int dlina;
	int i = 0;
	ET0 = 1;
	EA = 1;
	ET1 = 1;

	TMOD = 0x11; // таймер 0 и таймер 1 работают в режиме 16-ти битного таймера
	resetTime();
	
	dlina = read_max(num_page, 0x0300);
	for (i = 0; i < dlina; i++)
	{
		cTH1 = read_max(num_page, i);
		cTL1 = read_max(num_page, i + 0x0100);
		time_to_sing = read_max(num_page, 0x0200 + i);
		delay_melody( time_to_sing ); // ms * 1000 = s
	}

	ET0 = 0;
	ET1 = 0;
	EA = 0;
}
