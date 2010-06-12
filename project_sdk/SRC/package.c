#include "aduc812.h"
#include "max.h"
#include "package.h"
#include "conv.h"
#include "uart.h"
#include "max.h"
#include "parser.h"
#include "sound.h"
#include "timer.h"
#include "sram.h"
#include "lsd.h"
#include "crc8.h"

char new_mas[pack_len];
extern int is_good_melody;
extern int is_bad_melody;

int if_ri(void)
{
	long i = 0;
	for (i; i< 5000; i++)
	{
		if (RI)
			return 1;
		delay(1);
	}
	return 0;	
}

void send_first (int nume)
{
	int go;	

	new_mas[0] = read_max(2, 0x102);
	new_mas[pack_len - 1] = read_max(2, 0x103);
	
	new_mas[1] = 0x30;
	new_mas[2] = nume + 0x30;

	for (go = 0; go < pack_len; go++)
	{
		TI = 0;
		SBUF = new_mas[go];
		while(!TI);	
	}
}


void send_end (int nume)
{
	int go;
	
	new_mas[0] = read_max(2, 0x102);
	new_mas[pack_len - 1] = read_max(2, 0x103);

	new_mas[1] = crc8(2, 0x10, nume);
	new_mas[2] = 0x41;

	for (go = 0; go < pack_len; go++)
	{
		TI = 0;
		SBUF = new_mas[go];
		while(!TI);	
	}
	TI = 0;
	SBUF = 10;
	while(!TI);
}

void send_data (void)
{
	int num;
	char new_mas[pack_len];
	int i = 0;
	int go;
	
	
	num = read_max(2, 0x100);
	new_mas[0] = read_max(2, 0x102);
	new_mas[pack_len - 1] = read_max(2, 0x103);
	send_first(num);	

	while (i < num)
	{
		new_mas[1] = read_max(2, 0x10 + i);
		i++;
		new_mas[2] = read_max(2, 0x10 + i);
		i++;

		for (go = 0; go < pack_len; go++)
		{
			TI = 0;
			SBUF = new_mas[go];
			while(!TI);
		}
	}
	send_end(num);
}

int recieve_string (void)
{
	unsigned char start, stop;
	unsigned char buff;
	unsigned int i = 0;
	unsigned short kol_vo_not;
	unsigned char good_or_bad;
	unsigned char num_page;
	
	start = read_max(2, 0x102);
	stop = read_max(2, 0x103);
	buff = SBUF;
	RI = 0;

	if (!if_ri())
		return 0;
	buff = SBUF;
	RI = 0;
	
	if (!(buff & 0x80))
	{
		good_or_bad = buff & 0x40;
		kol_vo_not = (buff & 0x3f) << 8;
		if (!if_ri())
			return 0;
		buff = SBUF;
		RI = 0;
		kol_vo_not += buff;
		
		while (kol_vo_not)
		{
			if (!if_ri())
				return 0;
			buff = SBUF;
			RI = 0;
			if ((buff != start) && (buff != stop))
			{
				write_max(4, 0x102+i, buff);
				i++;
				kol_vo_not--;
			}
		}
		write_max(4, 0x102+i, 0);

		
		if (good_or_bad)
		{
			num_page = 5;
			is_good_melody = 1;
		}
		else
		{
			num_page = 6;
			is_bad_melody = 1;
		}
		
		init_timer();
		str_to_notes (num_page);
		play_melody (num_page);
		init_uart();
	}
	else
	{
		init_timer();
		if (buff & 0x40)
		{
			write_sram(2, 0x00, "Оки-доки!                      ");
			read_sram_to_lsd(2);
			if (is_good_melody)
				play_melody (5);
			else
				delay(65535);
		}
		else
		{
			write_sram(2, 0x00, "Фигня какая-то...              ");
			read_sram_to_lsd(2);
			if (is_bad_melody)
				play_melody (6);	
			else
				delay(65535);
		}
		write_sram(2, 0x00, "Введите пароль:                 ");
		read_sram_to_lsd(2);
		goto_x(0x40);
		init_uart();
	}
	return 0;
}
