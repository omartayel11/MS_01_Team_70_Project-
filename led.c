// led.c
#include "pico/stdlib.h"
#include "led.h"

// Initializes the LED pin as an output
void led_init(uint led_pin) {
    gpio_init(led_pin);          // Initialize the specified GPIO pin
    gpio_set_dir(led_pin, GPIO_OUT); // Set the GPIO pin as an output
}

// Turns the LED on by setting the pin to HIGH
void led_on(uint led_pin) {
    gpio_put(led_pin, 1);        // Set the GPIO pin to HIGH (turn LED on)
}

// Turns the LED off by setting the pin to LOW
void led_off(uint led_pin) {
    gpio_put(led_pin, 0);        // Set the GPIO pin to LOW (turn LED off)
}

// Toggles the LED state
void led_toggle(uint led_pin) {
    gpio_put(led_pin, !gpio_get(led_pin)); // Toggle the GPIO pin
}