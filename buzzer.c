// led.c
#include "pico/stdlib.h"
#include "buzzer.h"

// Initializes the LED pin as an output
void buzzer_init(uint buzzer_pin) {
    gpio_init(buzzer_pin);          // Initialize the specified GPIO pin
    gpio_set_dir(buzzer_pin, GPIO_OUT); // Set the GPIO pin as an output
}

// Turns the LED on by setting the pin to HIGH
void buzzer_on(uint buzzer_pin) {
    gpio_put(buzzer_pin, 1);        // Set the GPIO pin to HIGH (turn LED on)
}

// Turns the LED off by setting the pin to LOW
void buzzer_off(uint buzzer_pin) {
    gpio_put(buzzer_pin, 0);        // Set the GPIO pin to LOW (turn LED off)
}
