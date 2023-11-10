#ifndef PRACTICEREFACTOR_H
#define PRACTICEREFACTOR_H

#include <drivers/gpio.h>

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


void toggle_led(const struct device* dev, gpio_pin_t pin, bool* state);
void toggle_thread_led(const struct device* dev, gpio_pin_t pin, bool* state,
    int* count);

#endif