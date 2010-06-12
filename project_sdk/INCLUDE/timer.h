#ifndef _TIMER_H
#define _TIMER_H

#define PERIOD 10

static unsigned long time = 0; // переменная для выполнения функции задержки
static unsigned char time_ctr = 0;
bit sound_enabled = 0; //флаг разрешения проигрывания
bit count_enabled = 0; //флаг разрешения счета
unsigned char count = 0; //количество замыканий входа Т1

void set_vector( unsigned char xdata * address, void * vector );
void init_timer(void);
void delay_melody (unsigned long t);
void T0_ISR( void ) __interrupt ( 1 );
void T1_ISR( void ) __interrupt ( 2 );
void resetTime( void );

#endif //_TIMER_H
