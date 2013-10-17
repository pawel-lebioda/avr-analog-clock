#ifndef _PCF8583_H
#define _PCF8583_H

#include <stdint.h>
#include <conf.h>
#include <i2c.h>
#include <time.h>

#ifndef PCF8583_A0
#error PCF8583_A0 not defined
#endif

#define PCF8583_ADDR	(0xa0 | (PCF8583_A0&1)<<1)

#define PCF8583_RES_OK	0

void pcf8583_init(void);
void pcf8583_get_time(struct time * time);
void pcf8583_set_time(struct time * time, uint8_t mask);


#endif //_PCF8583_H
