#include <avr/io.h>
#include <inttypes.h>

#include <i2c.h>
#include <conf.h>
#include <pin.h>

#define NOP() {asm volatile("nop"::);}

#define I2C_nhalf (F_CPU/I2C_SPEED/2)

#if I2C_nhalf < 3
#elif I2C_nhalf < 8
	static void i2c_xdelay(void)
	{
		NOP();
	}
#else
	#define I2C_delayloops (1+(I2C_nhalf-8)/3)
	#if I2C_delayloops > 255
		#error F_CPU too small
	#endif
	static void i2c_xdelay(void)
	{
		asm volatile( \
			"delayus8_loop%=: \n\t"\
			"dec %[ticks] \n\t"\
			"brne delayus8_loop%= \n\t"\
		: :[ticks]"r"(I2C_delayloops) );
	}
#endif //I2C_nhalf >= 3

static void i2c_hdelay(void)
{
#if I2C_nhalf < 1
	return;
#elif I2C_nhalf < 2
	NOP();
#elif I2C_nhalf < 3
	asm volatile(
		"rjmp exit%=\n\t"
		"exit%=:\n\t"::);
#else
	i2c_xdelay();
#endif	
}

static void i2c_set_sda(void)
{
	DDR_CLR(I2C_SDA);
	PIN_SET(I2C_SDA);
}

static void i2c_clr_sda(void)
{
	PIN_CLR(I2C_SDA);
	DDR_SET(I2C_SDA);
}

static uint8_t i2c_get_sda(void)
{
	return PIN(I2C_SDA);
}

static void i2c_set_scl(void)
{
	PIN_SET(I2C_SCL);
}

static void i2c_clr_scl(void)
{
	PIN_CLR(I2C_SCL);
}

void i2c_init(void)
{
	PIN_CONFIGURE(I2C_SCL, PIN_DIR_OUT);
	PIN_CONFIGURE(I2C_SDA, PIN_DIR_OUT);
}

void i2c_start(void)
{
	i2c_set_sda();
	i2c_hdelay();
	i2c_set_scl();
	i2c_hdelay();
	i2c_clr_sda();
	i2c_hdelay();
	i2c_clr_scl();
}

void i2c_stop(void)
{
	i2c_clr_sda();
	i2c_hdelay();
	i2c_set_scl();
	i2c_hdelay();
	i2c_set_sda();
	i2c_hdelay();
}

uint8_t i2c_send(uint8_t data)
{
	uint8_t n;
	
	for(n=8; n>0; --n)
	{
		if(data & 0x80)
			i2c_set_sda();
		else
			i2c_clr_sda();
		data <<= 1;
		i2c_hdelay();
		i2c_set_scl();
		i2c_hdelay();
		i2c_clr_scl();
	}
	i2c_set_sda();
	i2c_hdelay();
	i2c_set_scl();
	i2c_hdelay();
	n = i2c_get_sda();
	i2c_clr_scl();
	
	return n;
}

uint8_t i2c_get(uint8_t ack)
{
	uint8_t n, temp=0;
	
	i2c_set_sda();
	for(n=8; n>0; --n)
	{
		i2c_hdelay();
		i2c_set_scl();
		i2c_hdelay();
		temp<<=1;
		if(i2c_get_sda())
			temp++;
		i2c_clr_scl();
	}
	if(ack == I2C_ACK)
		i2c_clr_sda();
	else
		i2c_set_sda();
	i2c_hdelay();
	i2c_set_scl();
	i2c_hdelay();
	i2c_clr_scl();
	
	return temp;
}

uint8_t i2c_reg_read(uint8_t addr, uint8_t reg_addr, uint8_t * o_val)
{
	i2c_start();
	i2c_send(I2C_ADDR_W(addr));
	i2c_send(reg_addr);
	i2c_start();
	i2c_send(I2C_ADDR_R(addr));
	*o_val = i2c_get(I2C_NACK);
	i2c_stop();

	return 0;
}

uint8_t i2c_reg_write(uint8_t addr, uint8_t reg_addr, uint8_t val)
{
	i2c_start();
	i2c_send(I2C_ADDR_W(addr));
	i2c_send(reg_addr);
	i2c_send(val);
	i2c_stop();

	return 0;
}

