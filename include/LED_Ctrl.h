#ifndef LED_CTRL_H
#define LED_CTRL_H

#include <stdint.h>
#include <device.h>
#include <drivers/gpio.h>

bool LED_Toggle(const struct device *port, gpio_pin_t pin, bool state);

#endif