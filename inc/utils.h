#ifndef _UTILS_H
#define _UTILS_H

#include <stdint.h>

uint8_t dec2bcd(uint8_t val);
uint8_t bcd2dec(uint8_t val);
void inc_mod(uint8_t * ptr, int8_t v, uint8_t mod);

#endif //_UTILS_H
