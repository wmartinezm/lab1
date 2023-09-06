#include <zephyr.h>
#include <device.h>
#include <devicetree.h>
#include <drivers/gpio.h>
#include "LED_Ctrl.h"

#define LED0_NODE DT_ALIAS(led0)
#define LED1_NODE DT_ALIAS(led1)

#if DT_NODE_HAS_STATUS(LED1_NODE, okay)
#define LED0	DT_GPIO_LABEL(LED0_NODE, gpios)
#define PIN0	DT_GPIO_PIN(LED0_NODE, gpios)
#define FLAGS0	DT_GPIO_FLAGS(LED0_NODE, gpios)
#define LED1	DT_GPIO_LABEL(LED1_NODE, gpios)
#define PIN1	DT_GPIO_PIN(LED1_NODE, gpios)
#define FLAGS1	DT_GPIO_FLAGS(LED1_NODE, gpios)
#else
/* A build error here means your board isn't set up to blink an LED. */
#error "Unsupported board: led0 devicetree alias is not defined"
#define LED0	""
#define PIN0	0
#define FLAGS0	0
#define LED1	""
#define PIN1	0
#define FLAGS1	0
#endif

#define STACKSIZE 2000

struct k_thread coop_thread;
K_THREAD_STACK_DEFINE(coop_stack, STACKSIZE);	// Define a toplevel array of kernel stack memory region nammed coop_stack w memory size STACKSIZE
int counter;
bool led_is_on;

/**
 * @brief This funtion is dinded to the thred. The first time is called it will intialize the
 * 		  LED1 pin and timer and from that point on will blink the LED any time the thread
 * 		  is running. 
*/
void thread_entry(void)
{
    const struct device *dev;
    dev = device_get_binding(LED1); // If dev is NULL we should handlle that as an error and stop excecution.
    bool led_is_on = true;
	int ret = LED_SetupThread(dev, PIN1, GPIO_OUTPUT_ACTIVE | FLAGS0, &counter);

	struct k_timer t;
	k_timer_init(&t, NULL, NULL);

	while (1) {
		led_is_on = LED_ToggleThread(dev, PIN1, led_is_on, &counter);
		k_timer_start(&t, K_MSEC(2000), K_NO_WAIT);
		k_timer_status_sync(&t);
	}
}

void main(void)
{
	const struct device *dev;
	led_is_on = true;
	int ret;

	dev = device_get_binding(LED0);

	// Create and initialize a thread.
    k_thread_create(&coop_thread,
                    coop_stack,
                    STACKSIZE,
                    (k_thread_entry_t) thread_entry,
                    NULL,
                    NULL,
                    NULL,
                    K_PRIO_COOP(7),
                    0,
                    K_NO_WAIT);

	if (dev == NULL) {
		return;
	}

	ret = LED_SetupMainloop(dev, PIN0, GPIO_OUTPUT_ACTIVE | FLAGS0);
	if (ret < 0) {
		return;
	}

	while (1) { // LED0 toggles every 500 ms
		led_is_on = LED_ToggleMainloop(dev, PIN0, led_is_on);
		k_msleep(500);
	}
}