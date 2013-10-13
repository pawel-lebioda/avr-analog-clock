#include <pcf8583.h>


#define PCF8583_REG_CTRL	0x00
#define PCF8583_REG_HSECONDS	0x01
#define PCF8583_REG_SECONDS	0x02
#define PCF8583_REG_MINUTES	0x03
#define PCF8583_REG_HOURS	0x04

void pcf8583_init(void)
{

}

uint8_t pcf8583_get_time(struct pcf8583_time * time)
{
	uint8_t val = 0;
	
	i2c_reg_read(PCF8583_ADDR, PCF8583_REG_SECONDS, &val);
	val = (val>>4)*10 + (val&0x0f);
	time->seconds = val;

	i2c_reg_read(PCF8583_ADDR, PCF8583_REG_MINUTES, &val);
	time->minutes = val;
	
	i2c_reg_read(PCF8583_ADDR, PCF8583_REG_HOURS, &val);
	time->hours = val;
	
	return PCF8583_RES_OK;
}

uint8_t pcf8583_set_time(struct pcf8583_time * time)
{
	return PCF8583_RES_OK;
}

