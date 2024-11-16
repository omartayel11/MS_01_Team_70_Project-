
#include "servo.h"
#include "pico/stdlib.h"
#include "hardware/pwm.h"

static uint slice_num;  // PWM slice number for the servo
static uint channel;    // PWM channel for the servo

void servo_init(void) {
    // Initialize the GPIO pin as an output for PWM signal
    gpio_set_function(SERVO_PIN, GPIO_FUNC_PWM);

    // Get the PWM slice number for the selected pin
    slice_num = pwm_gpio_to_slice_num(SERVO_PIN);

    // Set the PWM frequency to 50Hz (20ms period)
    pwm_set_clkdiv(slice_num, 125.0f);  // PWM clock divider to achieve 50Hz
    pwm_set_wrap(slice_num, 2000);       // 20ms period for 50Hz

    // Set the initial PWM duty cycle to 0 (servo at 0°)
    pwm_set_chan_level(slice_num, PWM_CHAN_A, 0);

    // Enable the PWM
    pwm_set_enabled(slice_num, true);
}

void servo_set_angle(uint8_t angle) {
    if (angle > 180) {
        angle = 180;  // Limit the angle to 180°
    }

    // Convert the angle to a corresponding PWM duty cycle (1ms to 2ms pulse width)
    uint16_t pulse_width = (uint16_t)(1000 + (angle * 1000 / 180));

    // Set the PWM duty cycle based on the pulse width for the servo
    pwm_set_chan_level(slice_num, PWM_CHAN_A, pulse_width);
}
