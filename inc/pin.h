#ifndef _PIN_H
#define _PIN_H

#include <avr/io.h>

#define PIN_DIR_IN	0
#define PIN_DIR_OUT	1

#define __PORT(name)			(PORT##name)
#define __DDR(name)			(DDR##name)
#define __PIN(name)			(PIN##name)
#define _PORT(name)			__PORT(name)
#define _DDR(name)			__DDR(name)
#define _PIN(name)			__PIN(name)


#define DDR_SET(name)			_DDR(name##_PORT) |= (1<<(name##_PIN))
#define DDR_CLR(name)			_DDR(name##_PORT) &= ~(1<<(name##_PIN))
#define PIN_SET(name)			_PORT(name##_PORT) |= (1<<(name##_PIN))
#define PIN_CLR(name)			_PORT(name##_PORT) &= ~(1<<(name##_PIN))
#define PIN(name)			((_PIN(name##_PORT) & (1<<(name##_PIN)))>>(name##_PIN))

#define PIN_CONFIGURE(name, mode)	if((mode) == PIN_DIR_IN) 	\
					{				\
						DDR_CLR(name); 		\
					}				\
					else				\
					{				\
						DDR_SET(name);		\
					}
				

#define PINS_CONFIGURE(name, mode)	if((mode) == PIN_DIR_IN)					\
					{								\
						_DDR(name##_PORT) &= ~((name##_MASK)<<(name##_SHIFT));	\
					}								\
					else								\
					{								\
						_DDR(name##_PORT) |= ((name##_MASK)<<(name##_SHIFT));	\
					}

#define PINS_SET(name, val)		{								\
						uint8_t _tmp = _PORT(name##_PORT);			\
						_tmp &= ~((name##_MASK)<<(name##_SHIFT));		\
						_tmp |= (((val)&(name##_MASK))<<(name##_SHIFT));	\
						_PORT(name##_PORT) = _tmp;				\
					}

#define PINS_CLR(name, val)		{								\
						uint8_t _tmp = _PORT(name##_PORT);			\
						_tmp |= ((name##_MASK)<<(name##_SHIFT));		\
						_tmp &= ~(((val)&(name##_MASK))<<(name##_SHIFT));	\
						_PORT(name##_PORT) = _tmp;				\
					}

#endif //_PIN_H
