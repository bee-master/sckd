#include "aduc812.h"
#include "max.h"
#include "lsd.h"
#include "sram.h"
#include "conv.h"
#include "package.h"

extern int yes_no_posl;

unsigned char scan_key(unsigned char reg)
{
	write_max(8, KB, 0x07);
	if( ( read_max(8, KB) & 0xF0 ) != 0xF0 )	
	{
		switch (reg)
		{
			case 0xE0:
				return 'A';
			case 0xD0:
				return 'B';
			case 0xB0:
				return 'C';
			case 0x70:
				return 'D';
		}
	}
	write_max(8, KB, 0x0B);
	if( ( read_max(8, KB) & 0xF0 ) != 0xF0 ){	
		switch (reg){
			case 0xE0:
				return '3';
			case 0xD0:
				return '6';
			case 0xB0:
				return '9';
			case 0x70:
				return '#';
		}
	}
	write_max(8, KB, 0x0D);
	if( ( read_max(8, KB) & 0xF0 ) != 0xF0 ){
			switch (reg){
			case 0xE0:
				return '2';
			case 0xD0:
				return '5';
			case 0xB0:
				return '8';
			case 0x70:
				return '0';
		}
	}
	write_max(8, KB, 0x0E);
	if( ( read_max(8, KB) & 0xF0 ) != 0xF0 ){
		switch (reg)
			{
			case 0xE0:
				return '1'; 
			case 0xD0:
				return '4';
			case 0xB0:
				return '7';
			case 0x70:
				return '*';
			}
	}
	return '!';
}

void key_press(unsigned char button)
{
	unsigned char bf_ac;

	if (button == '*')
	{
		bf_ac = get_bf_ac() & 0x7f;
		if (bf_ac > 0x40)
		{
			write_sram(2, bf_ac - 0x31, " ");
			read_sram_to_lsd(2);
			goto_x(bf_ac - 1);
		}
	}

	else if (button == '#')
	{
		if ((get_bf_ac() & 0x7f) != 0x40)
		{
			yes_no_posl = 1;
			send_data();
			write_sram(2, 0x10, "            ");
			read_sram_to_lsd(2);
			goto_x(0x40);
		}
	}

	else if (button != '!')
	{
		bf_ac = get_bf_ac() & 0x7f;
		if (bf_ac < 0x4C)
		{
			write_max(2, 0x100, bf_ac - 0x3f);
			write_sram(2, bf_ac - 0x30, &button);
			write_sram(2, bf_ac - 0x2f, " ");
			write_sram(2, bf_ac - 0x2e, " ");
			read_sram_to_lsd(2);
			goto_x(bf_ac + 1);
		}
	}
}
