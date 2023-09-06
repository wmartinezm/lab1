#include "LED_Ctrl.h"

int LED_ToggleMainloop(const struct device *dev, gpio_pin_t pin, int l_state)
{
    gpio_pin_set(dev, pin, l_state);
    l_state = !l_state;
    return l_state;
}

int LED_SetupMainloop(const struct device *dev, gpio_pin_t pin, gpio_flags_t flag)
{
    int ret = gpio_pin_configure(dev, pin, flag);
    if(ret == 0) // Setup went ok
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int LED_ToggleThread(const struct device *dev, gpio_pin_t pin, int l_state, int *counter)
{
    *counter = *counter + 1;
    gpio_pin_set(dev, pin, l_state);
    l_state = !l_state;
    return l_state;
}

int LED_SetupThread(const struct device *dev, gpio_pin_t pin, gpio_flags_t flag, int * counter)
{
    *counter = 0;
    int ret = gpio_pin_configure(dev, pin, flag);
    if(ret == 0) // Setup went ok
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
