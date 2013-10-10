#ifndef _PIN_H
#define _PIN_H


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

#define PIN_CONFIGURE(name, mode)	(((mode) == PIN_DIR_IN) ? DDR_CLR(name): DDR_SET(name))
				

#endif //_PIN_H
