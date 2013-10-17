#ifndef _DISPLAY_H
#define _DISPLAY_H

#include <stdint.h>

#define DISPLAY_DOT1	0x01
#define DISPLAY_DOT2	0x02
#define DISPLAY_DOT3	0x04
#define DISPLAY_DOT4	0x08

void display_init(void);
void display_process(void);
void display_set(uint8_t * buff, uint8_t len);
void display_set_dot(uint8_t mask);
void display_clr_dot(uint8_t mask);

#endif //_DISPLAY_H
