#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>
#include <i2c.h>
#include <analog_clock.h>
#include <pin.h>
#include <display.h>
#include <time.h>
#include <pcf8583.h>

enum state
{
	STATE_CLOCK,
	STATE_SETTING,
	STATE_SETTING_HOURS,
	STATE_SETTING_MINUTES
} g_state = STATE_CLOCK;

struct time g_time;

void interrupt_timer0_init(void)
{
	TCCR0 &= ~((1<<CS02)|(1<<CS01)|(1<<CS00));
	TCCR0 |= (1<<CS02)|(0<<CS01)|(0<<CS00);	
	TIMSK |= (1<<TOIE0);
}

void set_time(struct time * time)
{
	static uint8_t buff[4];
	buff[0] = time->hours/10;
	buff[1] = time->hours%10;
	buff[2] = time->minutes/10;
	buff[3] = time->minutes%10;
	display_set(buff, 4);
}

void clock_process(void)
{
	pcf8583_get_time(&g_time);
	analog_clock_set(g_time.seconds);
	set_time(&g_time);
}

int
main(void)
{
	g_state = STATE_CLOCK;
	i2c_init();
	analog_clock_init();
	display_init();
	interrupt_timer0_init();
	sei();
	while(1)
	{
		if(STATE_CLOCK == g_state)
		{
			clock_process();
		}
		else if(STATE_SETTING == g_state)
		{
			g_state = STATE_SETTING_HOURS;
		}
	}
}

ISR(TIMER0_OVF0_vect)
{
	display_process();
	TCNT0 = 255-43;
}

