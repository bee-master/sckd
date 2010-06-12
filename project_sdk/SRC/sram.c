#include "aduc812.h"
#include "lsd.h"

void read_sram_to_lsd (int page)
{
	unsigned char oldDPP;
	unsigned char xdata *regnum = 0x00;
	unsigned char i = 0;

	home();
	oldDPP = DPP;
	DPP = page;
	
	for (i; i < 32; i++)
	{
		char_out_utf(*regnum);
		regnum++;
	}
	
	DPP = oldDPP;
}

void write_sram (int page, unsigned char xdata *regnum, unsigned char * str_to_write)
{
	unsigned char oldDPP = DPP;
	
	DPP = page;
	
	while (*str_to_write)
	{
		*regnum = *str_to_write;
		str_to_write++;
		regnum++;
	}
	
	DPP = oldDPP;
}

