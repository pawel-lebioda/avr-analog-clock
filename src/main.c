#include <avr/io.h>
#include <avr/delay.h>
#include <i2c.h>

int
main(void)
{
	DDRB = 0xff;
	PORTB = 0xf0;
	i2c_start();
	while(1)
	{
		PORTB ^= 0x0f;
		_delay_ms(100);
	}
}
