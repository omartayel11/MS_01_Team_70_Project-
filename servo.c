#include "servo.h"
#include "pico/stdlib.h"
#include "hardware/pwm.h"



void setMillis(uint servoPin , float millis){
    pwm_set_gpio_level(servoPin,(millis/20000.0f)*39062.0f);
}

void setServo(uint servoPin, float startMillis){
    gpio_set_function(servoPin,GPIO_FUNC_PWM);
    uint sliceNum = pwm_gpio_to_slice_num(servoPin);
    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, 64.0f);
    pwm_config_set_wrap(&config, 39062.0f);
    pwm_init(sliceNum, &config , true);
    setMillis(servoPin,startMillis);
}
