#include "aduc812.h"
#include "math.h"
#include "max.h"
#include "uart.h"

extern unsigned char temp;
unsigned int num_char = 0;
char melody_char;

char read_char_melody (void)
{
	char result;
	result = read_max(4, 0x102 + num_char);
	num_char++;
	melody_char = result;
	return result;
}

void str_to_notes (unsigned int num_page)
{
	unsigned short buff_freq;
	int buff = 0;
	unsigned char buff_time;
	float n;
	unsigned char i = 0;
	unsigned int dlina = 0;

	i = 0;
	num_char = 0;
	
	while (read_char_melody ())
	{
		switch (melody_char)
		{
			case 'A' : buff = 0; break;
			case 'B' : buff = 2; break;
			case 'C' : buff = -9; break;
			case 'D' : buff = -7; break;
			case 'E' : buff = -5; break;
			case 'F' : buff = -4; break;
			case 'G' : buff = -2; break;
		}
		read_char_melody ();
		if (melody_char == '#')
		{
			buff += 1;
			read_char_melody ();
		}

		n = buff + 0x0c * (melody_char - 0x2f);
		
		buff_freq = 27.5 * powf(2, n/12);
		buff_freq = 0xffff - (921600 / buff_freq);
		read_char_melody ();
		buff_time = temp / (melody_char - 0x30);

		write_max (num_page, i, buff_freq >> 8);
		write_max (num_page, i + 0x0100, buff_freq);

		write_max (num_page, i + 0x0200, buff_time);

		i++;
		dlina++;
	}
	write_max (num_page, 0x0300, dlina);
}
