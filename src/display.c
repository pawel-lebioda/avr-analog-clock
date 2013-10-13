#include <display.h>
#include <pin.h>
#include <conf.h>
#include <string.h>

static struct
{
	uint8_t flicker;
	uint8_t segments[DISPLAY_BUFFER];
	uint8_t first;
} display;

void display_init(void)
{
	PINS_CONFIGURE(DISPLAY_ANODE, PIN_DIR_OUT);
	PINS_CONFIGURE(DISPLAY_ABCD, PIN_DIR_OUT);
	memset(&display, 0, sizeof(display));
	memset(display.segments, 0xff, DISPLAY_BUFFER);
}

void display_process(void)
{
	if(display.first + DISPLAY_SEGMENTS >= DISPLAY_BUFFER)
	{
		display.first = 0;
	}
	PINS_SET(DISPLAY_ANODE, DISPLAY_ANODE_MASK);
	PINS_SET(DISPLAY_ABCD, display.segments[display.first+display.flicker]);
	PINS_CLR(DISPLAY_ANODE, (1<<(DISPLAY_SEGMENTS-1-display.flicker)));
	display.flicker = (display.flicker+1)%DISPLAY_SEGMENTS;
}

void display_set(uint8_t * buff, uint8_t len)
{
	if(display.first + len >= DISPLAY_BUFFER)
	{
		len = DISPLAY_BUFFER - display.first;
	}
	memcpy(&display.segments[display.first], buff, len);
}

void display_set_u8(uint8_t val)
{
	uint8_t * ptr = &display.segments[display.first];
	*(ptr++) = 0xff;
	if(val >= 100)
	{
		*(ptr++) = val/100;
		val %= 100;
	}
	else
	{
		*(ptr++) = 0xff;
	}
	if(val >= 10)
	{
		*(ptr++) = val/10;
		val %= 10;
	}
	else
	{
		*(ptr++) = 0xff;
	}
	*ptr = val;
}

