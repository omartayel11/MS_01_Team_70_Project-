// infraRed.h

#ifndef INFRARED_H
#define INFRARED_H
#include "pico/stdlib.h"

// Initializes the IR sensor pin as input
void ir_init(uint ir_pin);

// Reads the state of the IR sensor
// Returns 1 if an object is detected, 0 otherwise
int ir_read(uint ir_pin);

#endif // INFRARED_H