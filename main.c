#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/i2c.h"
#include "Eeprom/eeprom.h"
#include "BTN/BTN.h"
#include "LED/LED.h"

int main() {
    Button btn1= {7};
    Button btn2= {8};
    Button btn3= {9};
    LED led1 = {20};
    LED led2 = {21};
    LED led3 = {22};
    init_button(&btn1);
    init_button(&btn2);
    init_button(&btn3);
    init_led(&led1);
    init_led(&led2);
    init_led(&led3);

    stdio_init_all();
    /*
    eeprom_init();
    eeprom_write(0x0000, 0x01);
    eeprom_write(0x0001, 0x02);
    eeprom_write(0x0002, 0x03);
    eeprom_write(0x0003, 0x04);
    eeprom_write(0x0004, 0x05);
    */
    while (true) {
        if (is_button_clicked(&btn2))
        {
            if (check_led_state(&led2))
            {
                blink_led(&led2, 0);
            }else{
                blink_led(&led2, 1);
            }
        }
        /*
        for (int i = 0; i < 5; i++) {
            printf("%02x ", eeprom_read(i));
        }
        */
        sleep_ms(200);
    }
    return 0;
}
