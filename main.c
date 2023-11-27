

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "Eeprom/eeprom.h"

int main() {
    stdio_init_all();
    eeprom_init();

    eeprom_write(0x0000, 0x01);
    eeprom_write(0x0001, 0x02);
    eeprom_write(0x0002, 0x03);
    eeprom_write(0x0003, 0x04);
    eeprom_write(0x0004, 0x05);

    while (true) {
        for (int i = 0; i < 5; i++) {
            printf("%02x ", eeprom_read(i));
        }
        printf("\n");
        sleep_ms(2000);
    }
    return 0;
}
