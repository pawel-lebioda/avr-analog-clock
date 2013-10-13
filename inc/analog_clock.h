#ifndef _ANALOG_CLOCK_H
#define _ANALOG_CLOCK_H

#include <stdint.h>

void analog_clock_init(void);
void analog_clock_clr(void);
void analog_clock_set(uint8_t val);
uint8_t analog_clock_get(void);

#endif //_ANALOG_CLOCK_H
