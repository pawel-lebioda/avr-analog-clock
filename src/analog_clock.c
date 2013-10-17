#include <analog_clock.h>
#include <conf.h>
#include <pin.h>

static uint8_t analog_clock_val = 0;

static inline void analog_clock_delay(void)
{
}

static uint8_t analog_clock_get_ticks(uint8_t val)
{
	return val + (val/7);
}

static void analog_clock_gen_ticks(uint8_t ticks)
{
	while(ticks--)
	{
		PIN_SET(SR74LS164_CLK);
		analog_clock_delay();

		PIN_CLR(SR74LS164_CLK);
		analog_clock_delay();
	}
}

void analog_clock_init(void)
{
	PIN_CONFIGURE(SR74LS164_CLK, PIN_DIR_OUT);
	PIN_CONFIGURE(SR74LS164_AB,  PIN_DIR_OUT);

	PIN_CLR(SR74LS164_CLK);
	PIN_CLR(SR74LS164_AB);

	analog_clock_clr();
}

void analog_clock_set(uint8_t val)
{
	uint8_t ticks = 0;
	
	analog_clock_clr();
	
	PIN_CLR(SR74LS164_AB);
	
	ticks = analog_clock_get_ticks(val);
	analog_clock_gen_ticks(ticks);
}

void analog_clock_clr(void)
{
	uint8_t ticks = 0;
	
	PIN_SET(SR74LS164_AB);
	
	ticks = analog_clock_get_ticks(60);
	analog_clock_gen_ticks(ticks);
}

uint8_t analog_clock_get(void)
{
	return analog_clock_val;
}

