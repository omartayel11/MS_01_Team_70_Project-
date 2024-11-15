#include "led.h"

#define LED_PIN 1

int main() {
    led_init(LED_PIN);
    
    while (true) {

        led_toggle(LED_PIN);
        sleep_ms(1000);
        

    }
}
