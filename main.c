#include "led.c"

int main() {
    int rc = pico_led_init(); 
    hard_assert(rc == PICO_OK);
    
    while (true) {
        pico_set_led(false, false, true); //all off
        sleep_ms(5000);
        pico_set_led(true, false, true); //oonly red is on (blue is true due to negative logic)
        sleep_ms(1000);
        pico_set_led(false, true, true);// only green is on
        sleep_ms(1000);
        pico_set_led(false, false, false);//only blue is on
        sleep_ms(1000);
        pico_set_led(true, true, false);//all on together
        sleep_ms(2000);
        

    }
}
