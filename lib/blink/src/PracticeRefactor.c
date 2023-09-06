#include "PracticeRefactor.h"

void toggle_led(const struct device* dev, const gpio_pin_t pin, bool* state) {
    gpio_pin_set(dev, pin, (int)(*state));
    *state = !(*state);
}

void toggle_thread_led(const struct device* dev, const gpio_pin_t pin, bool* state, int* count) {
    *count = *count + 1;
    gpio_pin_set(dev, pin, (int)(*state));
    *state = !(*state);
}