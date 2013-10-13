#ifndef _PCF8583_H
#define _PCF8583_H

#include <conf.h>
#include <i2c.h>

#ifndef PCF8583_A0
#error PCF8583_A0 not defined
#endif

#define PCF8583_ADDR	(0xa0 | (PCF8583_A0&1)<<1)

#define PCF8583_RES_OK	0

struct pcf8583_time
{
	uint8_t seconds;
	uint8_t minutes;
	uint8_t hours;
}

void pcf8583_init(void);
uint8_t pcf8583_get_time(struct pcf8583_time * time);
uint8_t pcf8583_set_time(struct pcf8583_time * time);


#endif //_PCF8583_H
