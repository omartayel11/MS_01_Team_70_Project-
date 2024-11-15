#include "led.h"
#include "infraRed.h"
#define LED_PIN 1
#define IR_PIN 3

int main() {
    led_init(LED_PIN);
    ir_init(IR_PIN);
    while (true) {

        //led_toggle(LED_PIN);
        //sleep_ms(1000);

        if(ir_read(IR_PIN)){
            led_on(LED_PIN);

        }
        else{
            led_off(LED_PIN);
        }
        sleep_ms(100);
        

    }
}
