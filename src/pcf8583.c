#include <pcf8583.h>
#include <utils.h>

#define PCF8583_REG_CTRL	0x00
#define PCF8583_REG_HSECONDS	0x01
#define PCF8583_REG_SECONDS	0x02
#define PCF8583_REG_MINUTES	0x03
#define PCF8583_REG_HOURS	0x04

void pcf8583_init(void)
{

}

void pcf8583_get_time(struct time * time)
{
	uint8_t val = 0;
	
	i2c_reg_read(PCF8583_ADDR, PCF8583_REG_SECONDS, &val);
	time->seconds = bcd2dec(val);

	i2c_reg_read(PCF8583_ADDR, PCF8583_REG_MINUTES, &val);
	time->minutes = bcd2dec(val);
	
	i2c_reg_read(PCF8583_ADDR, PCF8583_REG_HOURS, &val);
	time->hours = bcd2dec(val);
}

void pcf8583_set_time(struct time * time, uint8_t mask)
{
	uint8_t val = 0;

	i2c_reg_write(PCF8583_ADDR, PCF8583_REG_HSECONDS, val);
	
	if(mask&TIME_CLR_SECONDS)
	{
		i2c_reg_write(PCF8583_ADDR, PCF8583_REG_SECONDS, val);
	}

	if(mask&TIME_SET_MINUTES)
	{
		val = dec2bcd(time->minutes);
		i2c_reg_write(PCF8583_ADDR, PCF8583_REG_MINUTES, val);
	}

	if(mask&TIME_SET_HOURS)
	{
		val = dec2bcd(time->hours);
		i2c_reg_write(PCF8583_ADDR, PCF8583_REG_HOURS, val);
	}
}

