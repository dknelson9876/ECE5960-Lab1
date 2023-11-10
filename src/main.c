#include <zephyr.h>
#include <device.h>
#include <devicetree.h>
//#include <drivers/gpio.h>

#include <PracticeRefactor.h>

struct k_thread coop_thread;
K_THREAD_STACK_DEFINE(coop_stack, STACKSIZE);
int counter;
bool led_is_on;

void thread_entry(void) {
	const struct device* dev;
	dev = device_get_binding(LED1);
	bool led_is_on = true;
	int ret = gpio_pin_configure(dev, PIN1, GPIO_OUTPUT_ACTIVE | FLAGS1);

	struct k_timer t;
	k_timer_init(&t, NULL, NULL);

	//in an infinite loop, toggle LED1 then hold until the timer goes off again
	while (1) {
		toggle_thread_led(dev, PIN1, &led_is_on, &counter);
		k_timer_start(&t, K_MSEC(2000), K_NO_WAIT);
		k_timer_status_sync(&t);
	}
}

void main(void) {
	const struct device* dev;
	led_is_on = true;
	int ret;

	dev = device_get_binding(LED0);

	// starts a new thread and points it to the thread_entry function above
	k_thread_create(&coop_thread,
		coop_stack,
		STACKSIZE,
		(k_thread_entry_t)thread_entry,
		NULL,
		NULL,
		NULL,
		K_PRIO_COOP(7),
		0,
		K_NO_WAIT);

	if (dev == NULL) {
		return;
	}

	ret = gpio_pin_configure(dev, PIN0, GPIO_OUTPUT_ACTIVE | FLAGS0);
	if (ret < 0) {
		return;
	}

	// in an infinite loop, toggle LED0 then wait 500ms
	while (1) {
		toggle_led(dev, PIN0, &led_is_on);
		k_msleep(500);
	}
}