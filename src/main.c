#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>
#include <i2c.h>
#include <analog_clock.h>
#include <pin.h>
#include <display.h>
#include <time.h>
#include <pcf8583.h>
#include <buttons.h>

typedef enum state
{
	STATE_NONE = 0,
	STATE_CLOCK,
	STATE_SETTING,
	STATE_SETTING_HOURS,
	STATE_SETTING_MINUTES
} clock_state_t;

clock_state_t g_state = STATE_CLOCK;

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

void button_callback(button_t button, button_state_t state)
{
	if(STATE_CLOCK == g_state)
	{
		if(BUTTON_STATE_HOLD==state)
		{
			switch(button)
			{
			case BUTTON_LEFT:
				time_inc_hours(&g_time, 1);
				pcf8583_set_time(&g_time, TIME_SET_HOURS);
				break;
			case BUTTON_RIGHT:
				time_dec_hours(&g_time, 1);
				pcf8583_set_time(&g_time, TIME_SET_HOURS);
				break;
			case BUTTON_BOTH:
				g_state=STATE_SETTING;
				analog_clock_set_inv(30);
				break;
			}
		}
	}
	else if(STATE_SETTING_HOURS == g_state)
	{
		if(BUTTON_STATE_PRESSED==state)
		{
			switch(button)
			{
			case BUTTON_LEFT:
				time_inc_hours(&g_time, 1);
				break;
			case BUTTON_RIGHT:
				time_dec_hours(&g_time, 1);
				break;
			case BUTTON_BOTH:
				break;
			}
		}
		else if(BUTTON_STATE_HOLD==state)
		{
			switch(button)
			{
			case BUTTON_LEFT:
				time_inc_hours(&g_time, 10);
				break;
			case BUTTON_RIGHT:
				time_dec_hours(&g_time, 10);
				break;
			case BUTTON_BOTH:
				g_state=STATE_SETTING_MINUTES;
				analog_clock_set(30);
				break;
			}

		}
	}
	else if(STATE_SETTING_MINUTES == g_state)
	{
		if(BUTTON_STATE_PRESSED==state)
		{
			switch(button)
			{
			case BUTTON_LEFT:
				time_inc_minutes(&g_time, 1);
				break;
			case BUTTON_RIGHT:
				time_dec_minutes(&g_time, 1);
				break;
			case BUTTON_BOTH:
				pcf8583_set_time(&g_time, TIME_CLR_SECONDS|TIME_SET_MINUTES|TIME_SET_HOURS);
				g_state = STATE_CLOCK;
				break;
			}
		}
		else if(BUTTON_STATE_HOLD==state)
		{
			switch(button)
			{
			case BUTTON_LEFT:
				time_inc_minutes(&g_time, 10);
				break;
			case BUTTON_RIGHT:
				time_dec_minutes(&g_time, 10);
				break;
			case BUTTON_BOTH:
				pcf8583_set_time(&g_time, TIME_CLR_SECONDS|TIME_SET_MINUTES|TIME_SET_HOURS);
				g_state = STATE_CLOCK;
				break;
			}

		}
	}
}

int
main(void)
{
	g_state = STATE_CLOCK;
	i2c_init();
	analog_clock_init();
	display_init();
	buttons_init(button_callback);
	interrupt_timer0_init();
	sei();
	while(1)
	{
		if(STATE_CLOCK == g_state)
		{
			pcf8583_get_time(&g_time);
			analog_clock_set(g_time.seconds);
		}
		else if(STATE_SETTING == g_state)
		{
			g_state = STATE_SETTING_HOURS;
		}
		else if(STATE_SETTING_HOURS == g_state)
		{

		}
		else if(STATE_SETTING_MINUTES == g_state)
		{

		}
		set_time(&g_time);
	}
}

ISR(TIMER0_OVF0_vect)
{
	static uint8_t counter = 0;
	display_process();
	if(counter++ == 10)
	{
		counter=0;
		buttons_process();
	}
	TCNT0 = 255-43;
}

