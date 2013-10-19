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
	0,
	BUTTONS_RELEASED,
};

void buttons_init(button_callback_t callback)
{
	buttons.callback = callback;
	buttons.counter = 0;
	PINS_CONFIGURE(BUTTONS, PIN_DIR_IN);
}

button_t buttons_decode(uint8_t state)
{
	switch(state)
	{
	case BUTTONS_PRESSED_LEFT:
		return BUTTON_LEFT;
	case BUTTONS_PRESSED_RIGHT:
		return BUTTON_RIGHT;
	case BUTTONS_PRESSED_BOTH:
		return BUTTON_BOTH;
	default:
		return BUTTON_NONE;
	}
}

void buttons_process(void)
{
	uint8_t state = PINS_VAL(BUTTONS);
	if(state == buttons.state && state != BUTTONS_RELEASED)
	{
		buttons.counter++;
		if(buttons.counter > BUTTONS_HOLD_COUNTER)
		{
			buttons.counter = 0;
			buttons.callback(buttons_decode(buttons.state), BUTTON_STATE_HOLD);
		}
	}
	else
	{
	}

	buttons.state = state;
}

