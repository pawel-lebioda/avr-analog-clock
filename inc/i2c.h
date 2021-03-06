#ifndef _I2C_H
#define _I2C_H

#include <stdint.h>

#define I2C_ACK 1
#define I2C_NACK 0

#define I2C_ADDR_W(addr)	(addr)
#define I2C_ADDR_R(addr)	(addr|0x01)

void i2c_init(void);
void i2c_start(void);
void i2c_stop(void);
uint8_t i2c_send(uint8_t data);
uint8_t i2c_get(uint8_t ack);
uint8_t i2c_reg_write(uint8_t addr, uint8_t reg_addr, uint8_t val);
uint8_t i2c_reg_read(uint8_t addr, uint8_t reg_addr, uint8_t * o_val);

#endif //I2C_H
