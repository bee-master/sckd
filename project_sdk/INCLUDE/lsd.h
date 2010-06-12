#ifndef __LSD__H
#define __LSD__H

void delay(unsigned short x);
unsigned char get_bf_ac();
unsigned char bf_clear(void);
void goto_x (unsigned char position);
void char_out_sdk(unsigned char ch);
void char_out_utf(unsigned char ch);
unsigned char utf2sdk (unsigned char ch);
void print_str (unsigned char * str);
void clrscr(void);
void home(void);

#endif
