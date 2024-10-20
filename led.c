#include "pico/stdlib.h"
#include "led.h"


int pico_led_init(void) {
    // Initialize all 3 pins
    gpio_init(LED_GPIO_PINRed);
    gpio_init(LED_GPIO_PINGreen);
    gpio_init(LED_GPIO_PINBlue);

    gpio_set_dir(LED_GPIO_PINRed, GPIO_OUT);
    gpio_set_dir(LED_GPIO_PINGreen, GPIO_OUT);
    gpio_set_dir(LED_GPIO_PINBlue, GPIO_OUT);

    return PICO_OK;
}


void pico_set_led(bool led_on_Red,bool led_on_Green, bool led_on_Blue ) {
    // setting the led to on or off
    gpio_put(LED_GPIO_PINRed, led_on_Red);
    gpio_put(LED_GPIO_PINGreen, led_on_Green);
    gpio_put(LED_GPIO_PINBlue, led_on_Blue);
}
