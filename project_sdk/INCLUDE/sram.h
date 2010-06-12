#ifndef __SRAM__H
#define __sRAM__H

void read_sram_to_lsd (int page);
void write_sram (int page, unsigned char xdata *regnum, unsigned char * str_to_write);

#endif

