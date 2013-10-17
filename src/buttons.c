#include <conf.h>
#include <buttons.h>
#include <pin.h>

static struct 
{
	button_callback_t callback;
	uint8_t counter;
	uint8_t state;
} buttons = 
{
	0,
};

void buttons_init(button_callback_t callback)
{
	buttons.callback = callback;
	PINS_CONFIGURE(BUTTONS, PIN_DIR_IN);
}

void buttons_process(void)
{
}

