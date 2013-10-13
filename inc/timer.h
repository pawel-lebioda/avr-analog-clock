#ifndef _TIMER_H
#define _TIMER_H

#include <stdint.h>

typedef int8_t timer_t;
typedef void (*timer_callback_t)(timer_t timer,void * arg);

void timer_init(void);
void timer_tick(void);
uint8_t timer_set(timer_t timer,int32_t ms);
uint8_t timer_stop(timer_t timer);
int32_t timer_get_time(timer_t timer);

timer_t timer_alloc(timer_callback_t callback);
void timer_free(timer_t);
uint8_t timer_set_arg(timer_t timer,void * arg);

#endif //_TIMER_H
