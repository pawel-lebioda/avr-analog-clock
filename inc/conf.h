#ifndef _CONF_H
#define _CONF_H

#define I2C_SDA_PORT		B	
#define I2C_SDA_PIN		5
#define I2C_SCL_PORT		B
#define I2C_SCL_PIN		4
#define I2C_SPEED		500000


#define PCF8583_A0		0	

#define SR74LS164_AB_PORT	D
#define SR74LS164_AB_PIN	6
#define SR74LS164_CLK_PORT	B
#define SR74LS164_CLK_PIN	6

#define DISPLAY_ANODE_PORT	B
#define DISPLAY_ANODE_MASK	0x0f
#define DISPLAY_ANODE_SHIFT	0
#define DISPLAY_ABCD_PORT	D
#define DISPLAY_ABCD_MASK	0x0f
#define DISPLAY_ABCD_SHIFT	0
#define DISPLAY_SEGMENTS	4
#define DISPLAY_BUFFER		4
#define DISPLAY_TIMER_COUNT	1

#define RTC_TIMER_COUNT		500

#define TIMER0_COUNTER_MAX	1000

#define BUTTONS_PORT		D
#define BUTTONS_MASK		0x3
#define BUTTONS_SHIFT		4
#define BUTTONS_RELEASED	0x3
#define BUTTONS_PRESSED_BOTH	0x0
#define BUTTONS_PRESSED_LEFT	0x1
#define BUTTONS_PRESSED_RIGHT	0x2
#define BUTTONS_PRESSED_COUNTER	5
#define BUTTONS_HOLD_COUNTER	200

#endif //_CONF_H
