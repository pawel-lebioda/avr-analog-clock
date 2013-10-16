#include <conf.h>
#include <buttons.h>


static struct 
{
	button_callback_t callback;
} buttons = 
{
	0,
};

void buttons_init(button_callback_t callback)
{
	buttons.callback = callback;
}

void buttons_process(void)
{
}

