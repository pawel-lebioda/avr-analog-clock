#ifndef _BUTTONS_H
#define _BUTTONS_H

typedef enum 
{
	BUTTON_NONE = 0,
	BUTTON_LEFT,
	BUTTON_RIGHT,
	BUTTON_BOTH
} button_t;

typedef enum
{
	BUTTON_STATE_NONE = 0,
	BUTTON_STATE_PRESSED,
	BUTTON_STATE_HOLD
} button_state_t;

typedef void (*button_callback_t)(button_t button, button_state_t state);

void buttons_init(button_callback_t callback);
void buttons_process(void);

#endif //_BUTTONS_H
