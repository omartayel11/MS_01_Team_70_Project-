// led.h

#ifndef LED_H
#define LED_H

#include "pico/stdlib.h"

// Initializes the LED pin as output
void led_init(uint led_pin);

// Turns the LED on
void led_on(uint led_pin);

// Turns the LED off
void led_off(uint led_pin);

// Toggles the LED state
void led_toggle(uint led_pin);

#endif // LED_H