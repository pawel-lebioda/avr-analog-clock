#include <conf.h>
#include <buttons.h>
#include <pin.h>

static struct 
{
	button_callback_t callback;
	uint8_t counter;
	uint8_t state;
	button_state_t last_state;
} buttons = 
{
	0,
	0,
	BUTTONS_RELEASED,
	BUTTON_STATE_NONE
};

void buttons_init(button_callback_t callback)
{
	buttons.callback = callback;
	buttons.counter = 0;
	PINS_CONFIGURE(BUTTONS, PIN_DIR_IN);
	PINS_SET(BUTTONS, 0x3);
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
			buttons.last_state = BUTTON_STATE_HOLD;
			buttons.callback((button_t)buttons.state, BUTTON_STATE_HOLD);
		}
	}
	else
	{
		if(BUTTONS_RELEASED == state)
		{
			if(BUTTON_STATE_NONE == buttons.last_state && buttons.counter > BUTTONS_PRESSED_COUNTER)
			{
				buttons.last_state = BUTTON_STATE_PRESSED;
				buttons.callback((button_t)buttons.state, BUTTON_STATE_PRESSED);
			}
			else
			{
				buttons.last_state = BUTTON_STATE_NONE;
			}
		}
		buttons.counter=0;
	}

	buttons.state = state;
}

