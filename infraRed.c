// infraRed.c

#include "infraRed.h"

// Initializes the IR sensor pin as an input
void ir_init(uint ir_pin) {
    gpio_init(ir_pin);              // Initialize the specified GPIO pin
    gpio_set_dir(ir_pin, GPIO_IN);   // Set the GPIO pin as an input
}

// Reads the state of the IR sensor
// Returns 1 if an object is detected, 0 if no object is detected
int ir_read(uint ir_pin) {
    return !gpio_get(ir_pin);         // Read the state of the GPIO pin
}