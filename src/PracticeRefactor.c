#include "PracticeRefactor.h"

void toggle_led(const struct device *dev, gpio_pin_t pin, bool* state){
    gpio_pin_set(dev, pin, (int)(*state));
    *state = !(*state);
    k_msleep(500);
}

void toggle_thread_led(const struct device *dev, gpio_pin_t pin, bool* state, struct k_timer *tim, int *count){
    *count = *count + 1;
    gpio_pin_set(dev, pin, (int)(*state));
    *state = !(*state);
    k_timer_start(tim, K_MSEC(2000), K_NO_WAIT);
    k_timer_status_sync(tim);
}