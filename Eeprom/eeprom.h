#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

#define I2C_PORT i2c0
#define I2C_ADDRESS 0x50
#define SPEED 1000*100
#define SDA_PIN 16
#define SCL_PIN 17

void eeprom_init();
void eeprom_write(uint16_t address, uint8_t data);

uint8_t eeprom_read(uint16_t address);
