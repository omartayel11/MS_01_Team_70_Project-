#ifndef SERVO_H
#define SERVO_H

#include "pico/stdlib.h"

// Pin connected to the PWM signal of the servo motor
#define SERVO_PIN 0  // You can choose a different pin if needed

// Function prototypes
void servo_init(void);
void servo_set_angle(uint8_t angle); // Set the servo position (0° to 180°)

#endif // SERVO_H
