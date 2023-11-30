// led.h
#ifndef LED_STATE_H
#define LED_STATE_H

#include "pico/stdlib.h"
#include "hardware/gpio.h"

typedef struct ledstate {
 uint8_t state;
 uint8_t not_state;
} Led_State;

void set_led_state(Led_State *ls, uint8_t value);
bool led_state_is_valid(Led_State *ls);

#endif  // LED_STATE_H
