#include "aduc812.h"
#include "lsd.h"
#include "key.h"
#include "max.h"
#include "sram.h"
#include "timer.h"
#include "uart.h"
#include "sound.h"
#include "parser.h"
#include "conv.h"
#include "package.h"
#include "crc8.h"

#define FOSC_DIV_12 921600
#define BIT_SOUND 0x01
#define BIT_COUNT 0x80

unsigned char cTH1, cTL1; 
unsigned short temp = 24000 / 300;
unsigned int dlina = 0;
unsigned char time_to_sing;

int yes_no_posl = 0;
int is_bad_melody = 0;
int is_good_melody = 0;

void main()
{
	unsigned char button;
	unsigned char prev_kb = 0xf0;
	int i = 0;

	set_vector( 0x200B, (void *)T0_ISR );
	set_vector( 0x201B, (void *)T1_ISR );

	write_max(2, 0x102, 0xAA);
	write_max(2, 0x103, 0xFF);

	init_uart ();

	write_sram(2, 0x00, "Введите пароль:                 ");
	read_sram_to_lsd(2);

	goto_x(0x40);

	write_max(8, KB, 0x00);
	
	while(1)
	{	
		if (RI)
			if (yes_no_posl)
				recieve_string();
		if ((read_max(8, KB) & 0xf0) != prev_kb)
		{
			prev_kb = read_max(8, KB) & 0xf0;
			button = scan_key(read_max(8, KB));
			write_max(8, KB, 0x00);
			key_press(button);
		}
	}
}
