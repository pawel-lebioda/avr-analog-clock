#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>
#include <i2c.h>
#include <analog_clock.h>
#include <pin.h>
#include <display.h>
#include <pcf8583.h>

void interrupt_timer0_init(void)
{
	TCCR0 &= ~((1<<CS02)|(1<<CS01)|(1<<CS00));
	TCCR0 |= (1<<CS02)|(0<<CS01)|(0<<CS00);	
	TIMSK |= (1<<TOIE0);
}

void rtc_set_time(struct pcf8583_time * time)
{
	static uint8_t buff[4];
	buff[0] = time->hours>>4;
	buff[1] = time->hours&0xf;
	buff[2] = time->minutes>>4;
	buff[3] = time->minutes&0xf;
	display_set(buff, 4);
}

void rtc_process(void)
{
	static struct pcf8583_time time;
	time.hours=0;
	time.minutes=0;
	pcf8583_get_time(&time);
	analog_clock_set(time.seconds);
	rtc_set_time(&time);
}

int
main(void)
{
	i2c_init();
	analog_clock_init();
	display_init();
	interrupt_timer0_init();
	struct pcf8583_time time;
	time.seconds = 30;
	time.hours = 0x12;
	time.minutes = 0x13;
	rtc_set_time(&time);
	sei();
	while(1)
	{
		rtc_process();
	}
}

ISR(TIMER0_OVF0_vect)
{
	static uint8_t counter = 0;
	display_process();
	TCNT0 = 255-43;
}

