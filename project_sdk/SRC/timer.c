#include "timer.h"
#include "aduc812.h"
#include "max.h"
#include "sound.h"

void set_vector( unsigned char xdata * address, void * vector )
{
	unsigned char xdata * tmp_vector;  // временная переменная
	// первым байтом по указанному адресу записывается
	// код команды передачи управления ljmp, равный 02h
	*address = 0x02;
	// Далее записывается адрес перехода vector
	tmp_vector = (unsigned char xdata *)( address + 1 );
	*tmp_vector= (unsigned char) ( (unsigned short)vector >> 8 );
	++tmp_vector;
	*tmp_vector = (unsigned char) vector;
	// таким образом, по адресу address теперь располагается
	// инструкция ljmp vector
}

void init_timer(void)
{
	TH0 = 0xFC; // инициализация таймера 0
	TL0 = 0x66;
	TMOD = 0x11; // таймер 0 и таймер 1 работают в режиме 16-ти битного таймера
	TCON = 0x50; // TR1=TR0=1 запуск таймера 0 и таймера 1
	 
	ET0 = 1;	 // enable interrupt 
	ET1 = 1;
}

void delay_melody ( unsigned long time_delay )
{
	unsigned long t_start, time_val;
	
	ET0 = 0;
	ET1 = 0;
	t_start = time;
	time_val = time - t_start;
	ET0 = 1;
	ET1 = 1;
	
	while ( time_val <= time_delay ) 
	{
		ET0 = 0;
		ET1 = 0;
		time_val = time - t_start;
		ET0 = 1;
		ET1 = 1;
	};
}

void T0_ISR (void) __interrupt ( 1 )
{
	TH0 = 0xdb;   // значение таймера для переаолнение спустя 10 мс
	TL0 = 0xff;
	time++;
}

void T1_ISR( void ) __interrupt ( 2 )
{
	sound_generation();
}

void resetTime( void )
{
   time = 0;
}
