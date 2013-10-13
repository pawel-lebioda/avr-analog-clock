#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>
#include <i2c.h>
#include <analog_clock.h>
//#include <timer.h>
#include <pin.h>

void interrupt_timer0_init()
{
	TCCR0 &= ~((1<<CS02)|(1<<CS01)|(1<<CS00));
	TCCR0 |= (1<<CS02)|(0<<CS01)|(0<<CS00);	
	TIMSK |= (1<<TOIE0);
}

/*
void timer_callback(timer_t timer, void * arg)
{
	static uint8_t c = 0;
	//timer_set(timer, 1000);
}
*/
int
main(void)
{
	uint8_t c =0;
	//timer_init();
	analog_clock_init();
	interrupt_timer0_init();
	DDRB |= (1<<0)|(1<<1)|(1<<2)|(1<<3);
	PORTB &= ~(1<<1);
	DDRD |= (1<<0)|(1<<1)|(1<<2)|(1<<3);
	//timer_t timer = timer_alloc(timer_callback);
	//timer_set(timer, 1000);
	sei();
	while(1)
	{
		PORTD &= ~((1<<0)|(1<<1)|(1<<2)|(1<<3));
		PORTD |= (c%10)&0x0f;
		analog_clock_set(c);
		c = (c+1)%60;
		_delay_ms(1000);
	}
}

ISR(TIMER0_OVF0_vect)
{
	//timer_tick();
	TCNT0 = 255-43;
}

