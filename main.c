#include <stdio.h>
#include <time.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/i2c.h"
#include "Eeprom/eeprom.h"
#include "BTN/BTN.h"
#include "LED/LED.h"
#include "LED_STATE/LED_STATE.h"

#define EEPROM_SIZE 32768

bool led_state_valid(){
    uint8_t led_states = eeprom_read(0x7FFF);
    uint8_t led_invert_states = eeprom_read(0x7FFE);
    if(led_states == (uint8_t) ~led_invert_states){
        return true;
    }else{
        return false;
    }
}

clock_t clock() {
    return (clock_t) time_us_64() / 10000;
}

int main() {
    clock_t startTime = clock();
    clock_t endTime;
    Button btn1= {7};
    Button btn2= {8};
    Button btn3= {9};
    LED led1 = {20};
    LED led2 = {21};
    LED led3 = {22};
    Led_State led_state1, led_state2, led_state3;

    init_button(&btn1);
    init_button(&btn2);
    init_button(&btn3);
    init_led(&led1);
    init_led(&led2);
    init_led(&led3);

    stdio_init_all();
    eeprom_init();
    uint8_t data = 0b000;

    sleep_ms(4000);
    if (led_state_valid()== true)
    {
        uint8_t led_states = eeprom_read(0x7FFF);
        blink_led(&led1, (led_states >> 0) & 0x01);
        blink_led(&led2, (led_states >> 1) & 0x01);
        blink_led(&led3, (led_states >> 2) & 0x01);
        printf("Init LED states: %d%d%d\n", (led_states >> 2) & 0x01, (led_states >> 1) & 0x01, (led_states >> 0) & 0x01);
        data =(uint8_t) led_states;
        printf("Repeat at %d\n", (clock()-startTime)/CLOCKS_PER_SEC); 
    }else
    {
        blink_led(&led1, 0);
        blink_led(&led2, 1);
        blink_led(&led3, 0);
        data = 0b010;
        eeprom_write(0x7FFF, data);
        eeprom_write(0x7FFE, ~data);
        printf("Repeat at %d\n", (clock()-startTime)/CLOCKS_PER_SEC); 
    }
    while (true) {
        
        if (is_button_clicked(&btn1))
        {            
            if (check_led_state(&led1))
            {
                blink_led(&led1, 0); 
                set_led_state(&led_state1, 0);
                data &= ~(1 << 2);
            }else{
                blink_led(&led1, 1);
                set_led_state(&led_state1, 1);
                data |= (1 << 2);
            }
            eeprom_write(0x7FFF, data);
            uint8_t led_states = eeprom_read(0x7FFF);
            printf("LED states: %d%d%d\n", (led_states >> 2) & 0x01, (led_states >> 1) & 0x01, (led_states >> 0) & 0x01);
            eeprom_write(0x7FFE, ~data);
            uint8_t led_invert_states = eeprom_read(0x7FFE);
            printf("LED invert states: %d%d%d\n", (led_invert_states >> 2) & 0x01, (led_invert_states >> 1) & 0x01, (led_invert_states >> 0) & 0x01);
            printf("Repeat at %d\n", (clock()-startTime)/CLOCKS_PER_SEC); 
        }

        if (is_button_clicked(&btn2))
        {            
            if (check_led_state(&led2))
            {
                blink_led(&led2, 0);
                set_led_state(&led_state2, 0);
                data &= ~(1 << 1);
            }else{
                blink_led(&led2, 1);
                set_led_state(&led_state1, 1);
                data |= (1 << 1);
            }
            eeprom_write(0x7FFF, data);
            uint8_t led_states = eeprom_read(0x7FFF);
            printf("LED states: %d%d%d\n", (led_states >> 2) & 0x01, (led_states >> 1) & 0x01, (led_states >> 0) & 0x01);
            eeprom_write(0x7FFE, ~data);
            uint8_t led_invert_states = eeprom_read(0x7FFE);
            printf("LED invert states: %d%d%d\n", (led_invert_states >> 2) & 0x01, (led_invert_states >> 1) & 0x01, (led_invert_states >> 0) & 0x01);
            printf("Repeat at %d\n", (clock()-startTime)/CLOCKS_PER_SEC); 
        }

        if (is_button_clicked(&btn3))
        {            
            if (check_led_state(&led3))
            {
                blink_led(&led3, 0); 
                set_led_state(&led_state3, 0);
                data &= ~(1 << 0);
            }else{
                blink_led(&led3, 1);
                set_led_state(&led_state3, 1);
                data |= (1 << 0);            
            }
            eeprom_write(0x7FFF, data);
            uint8_t led_states = eeprom_read(0x7FFF);
            printf("LED states: %d%d%d\n", (led_states >> 2) & 0x01, (led_states >> 1) & 0x01, (led_states >> 0) & 0x01);
            eeprom_write(0x7FFE, ~data);
            uint8_t led_invert_states = eeprom_read(0x7FFE);
            printf("LED invert states: %d%d%d\n", (led_invert_states >> 2) & 0x01, (led_invert_states >> 1) & 0x01, (led_invert_states >> 0) & 0x01);
            printf("Repeat at %d\n", (clock()-startTime)/CLOCKS_PER_SEC); 
        }
        sleep_ms(200);
    }
    return 0;
}
