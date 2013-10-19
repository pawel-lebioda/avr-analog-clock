#ifndef _TIME_H
#define _TIME_H

#include <stdint.h>
#include <utils.h>

#define TIME_CLR_SECONDS	0x01
#define TIME_SET_MINUTES	0x02
#define TIME_SET_HOURS		0x04

struct time
{
	uint8_t hours;
	uint8_t minutes;
	uint8_t seconds;
};

inline void time_inc_hours(struct time * time, uint8_t v)
{
	inc_mod(&time->hours, v, 24);
}

inline void time_dec_hours(struct time * time, uint8_t v)
{
	inc_mod(&time->hours, -(int8_t)v, 24);
}

inline void time_inc_minutes(struct time * time, uint8_t v)
{
	inc_mod(&time->minutes, v, 60);
}

inline void time_dec_minutes(struct time * time, uint8_t v)
{
	inc_mod(&time->minutes, -(int8_t)v, 60);
}

#endif //_TIME_H
