#include "LED_STATE.h"
void set_led_state(Led_State *ls, uint8_t value)
{
    ls->state = value;
    ls->not_state = ~value;
}
bool led_state_is_valid(Led_State *ls) {
    return ls->state == (uint8_t) ~ls->not_state;
}