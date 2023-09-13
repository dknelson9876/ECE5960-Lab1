#include <stdint.h>
#include <unity.h>

#include <zephyr.h>
#include <device.h>
#include <devicetree.h>
#include <drivers/gpio.h>
#include "PracticeRefactor.h"


void setUp(void) { }

void tearDown(void) { }

int counter = 0;

void test_toggle_led(void) {
    const struct device* dev;
    dev = device_get_binding(LED0);
    gpio_pin_configure(dev, PIN0, GPIO_OUTPUT_ACTIVE | FLAGS0);
    bool led_is_on = true;
    
    toggle_led(dev, PIN0, &led_is_on);
    
    TEST_ASSERT_TRUE_MESSAGE(led_is_on == false, "LED did not toggle");
    TEST_ASSERT_TRUE_MESSAGE(gpio_pin_get(dev, PIN0), "GPIO was not set");
}

void test_toggle_led_thread_toggle_test(void) {
    const struct device* dev;
    dev = device_get_binding(LED1);
    gpio_pin_configure(dev, PIN1, GPIO_OUTPUT_ACTIVE | FLAGS1);
    
    bool led_is_on = false;
    
    struct k_timer t;
    k_timer_init(&t, NULL, NULL);

    toggle_thread_led(dev, PIN1, &led_is_on, &counter);
    TEST_ASSERT_TRUE_MESSAGE(led_is_on == true, "LED did not toggle");
    TEST_ASSERT_TRUE_MESSAGE(gpio_pin_get(dev, PIN1) == 0, "GPIO was not set");

}

void test_toggle_led_thread_counter_test(void) {
    const struct device* dev;
    dev = device_get_binding(LED1);
    gpio_pin_configure(dev, PIN1, GPIO_OUTPUT_ACTIVE | FLAGS1);

    bool led_is_on = true;
    
    struct k_timer t;
    k_timer_init(&t, NULL, NULL);

    toggle_thread_led(dev, PIN1, &led_is_on, &counter);
    TEST_ASSERT_TRUE_MESSAGE(counter == 2, "LED did not toggle");
    TEST_ASSERT_TRUE_MESSAGE(gpio_pin_get(dev, PIN1), "GPIO was not set");

}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_toggle_led);
    RUN_TEST(test_toggle_led_thread_toggle_test);
    RUN_TEST(test_toggle_led_thread_counter_test);
    return UNITY_END();
}