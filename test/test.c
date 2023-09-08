#include <stdint.h>
#include <stdio.h>
#include <unity.h>
#include <zephyr.h>
#include <device.h>
#include <devicetree.h>
#include <drivers/gpio.h>
#include "LED_Ctrl.h"

#define LED0_NODE DT_ALIAS(led0)
#define LED1_NODE DT_ALIAS(led1)

#define LED0	DT_GPIO_LABEL(LED0_NODE, gpios)
#define PIN0	DT_GPIO_PIN(LED0_NODE, gpios)
#define FLAGS0	DT_GPIO_FLAGS(LED0_NODE, gpios)
#define LED1	DT_GPIO_LABEL(LED1_NODE, gpios)
#define PIN1	DT_GPIO_PIN(LED1_NODE, gpios)
#define FLAGS1	DT_GPIO_FLAGS(LED1_NODE, gpios)



void setUp(void) {}

void tearDown(void) {}

void test_main_loop_enable(void)
{
	const struct device *dev = device_get_binding(LED0);
    

	int led_is_on = LED_SetupMainloop(dev, PIN0, GPIO_OUTPUT_ACTIVE | FLAGS0);
    TEST_ASSERT_TRUE_MESSAGE(!led_is_on, "LED0 flag should start toggled off");

    led_is_on = LED_ToggleMainloop(dev, PIN0, led_is_on);
    TEST_ASSERT_TRUE_MESSAGE(led_is_on, "LED0 flag should be toggled on");
}

void test_thread_enable(void)
{
	const struct device *dev = device_get_binding(LED1);
    int counter;

	int led_is_on = LED_SetupThread(dev, PIN1, GPIO_OUTPUT_ACTIVE | FLAGS1, &counter);
    TEST_ASSERT_TRUE_MESSAGE(!led_is_on, "LED1 flag should start toggled off");

    led_is_on = LED_ToggleThread(dev, PIN1, led_is_on, &counter);
    TEST_ASSERT_TRUE_MESSAGE(led_is_on, "LED1 flag should be toggled on");
}

int main (void)
{
    UNITY_BEGIN();
    RUN_TEST(test_main_loop_enable);
    RUN_TEST(test_thread_enable);
    return UNITY_END();
}