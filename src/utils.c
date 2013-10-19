#include <utils.h>

uint8_t dec2bcd(uint8_t val)
{
	return ((val/10)<<4)|((val%10)&0xf);
}

uint8_t bcd2dec(uint8_t val)
{
	return ((val>>4)*10 + (val&0xf));
}

void inc_mod(uint8_t * ptr, int8_t v, uint8_t mod)
{
	*ptr = (*ptr + v)%mod;
}

