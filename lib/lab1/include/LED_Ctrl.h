#ifndef LED_CTRL_H
#define LED_CTRL_H

#include <stdint.h>
#include <device.h>
#include <drivers/gpio.h>

int LED_ToggleMainloop(const struct device *dev, gpio_pin_t pin, int l_state);
int LED_SetupMainloop(const struct device *dev, gpio_pin_t pin, gpio_flags_t flag);

int LED_ToggleThread(const struct device *dev, gpio_pin_t pin, int l_state, int * counter);
int LED_SetupThread(const struct device *dev, gpio_pin_t pin, gpio_flags_t flag, int * counter);

#endif