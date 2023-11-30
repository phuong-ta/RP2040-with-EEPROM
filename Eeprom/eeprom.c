#include "eeprom.h"

void eeprom_init(){
    // Initialize I2C
    i2c_init(I2C_PORT, SPEED);
    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(SDA_PIN);
    gpio_pull_up(SCL_PIN);
}

void eeprom_write(uint16_t address, uint8_t data) {
    uint8_t buffer[3] = {address >> 8, address & 0xFF, data};
    i2c_write_blocking(I2C_PORT, I2C_ADDRESS, buffer, sizeof(buffer), false);
    sleep_ms(10);
}

uint8_t eeprom_read(uint16_t address) {
    uint8_t buffer[2] = {address >> 8, address & 0xFF};
    i2c_write_blocking(I2C_PORT, I2C_ADDRESS, buffer, sizeof(buffer), true);
    sleep_ms(10);
    i2c_read_blocking(I2C_PORT, I2C_ADDRESS, buffer, 1, false);
    return buffer[0];
}
