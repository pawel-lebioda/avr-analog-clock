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
	analog_clock_init();
	display_init();
	interrupt_timer0_init();
	sei();
	while(1)
	{
	}
}

void rtc_process(void)
{
	static struct pcf8583_time time;
	static uint8_t buff[4];
	pcf8583_get_time(&time);
	analog_clock_set(time.seconds);
	buff[0] = time.hours>>4;
	buff[1] = time.hours&0xf;
	buff[2] = time.minutes>>4;
	buff[3] = time.minutes&0xf;
	display_set(buff, 4);
}

ISR(TIMER0_OVF0_vect)
{
	static uint8_t counter = 0;
	TCNT0 = 255-43;
	if(counter == DISPLAY_TIMER_COUNT)
	{
		display_process();
	}
	if(counter == RTC_TIMER_COUNT)
	{
		rtc_process();
	}
	counter = (counter + 1)%TIMER0_COUNTER_MAX;
}

