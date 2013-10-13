#ifndef _DISPLAY_H
#define _DISPLAY_H

#include <stdint.h>

void display_init(void);
void display_process(void);
void display_set(uint8_t * buff, uint8_t len);

#endif //_DISPLAY_H
