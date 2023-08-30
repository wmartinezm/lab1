#include "LED_Ctrl.h"

bool LED_Toggle(const struct device *port, gpio_pin_t pin, bool state)
{
    gpio_pin_set(port, pin, (int)state);
    state = !state;
    return state;
}