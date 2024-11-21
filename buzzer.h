
#ifndef BUZZER_H
#define BUZZER_H

#include "pico/stdlib.h"

// Initializes the LED pin as output
void buzzer_init(uint buzzer_pin);

// Turns the LED on
void buzzer_on(uint buzzer_pin);

// Turns the LED off
void buzzer_off(uint buzzer_pin);


#endif // LED_H