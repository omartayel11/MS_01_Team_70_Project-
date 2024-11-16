#include "led.h"
#include "infraRed.h"
#include "temperature.h"
#include "servo.h"

#define LED_PIN 1
#define LED_PIN2 4
#define LED_PIN3 5
#define IR_PIN 3

int main() {
    stdio_init_all();
    led_init(LED_PIN);
    led_init(LED_PIN2);
    led_init(LED_PIN3);
    ir_init(IR_PIN);
    servo_init();
    temperature_init();

    while (true) {

        //sleep_ms(60000);

        //led_toggle(LED_PIN);
        //sleep_ms(1000);

        //led_on(LED_PIN);
         //Move the servo to different angles
        for (uint8_t angle = 0; angle <= 180; angle++) {
            servo_set_angle(angle);
            sleep_ms(1000);  // Delay to allow the servo to reach the position
        }

        // Move the servo back to 0° after completing the sweep
        for (uint8_t angle = 180; angle >= 0; angle--) {
            servo_set_angle(angle);
            sleep_ms(1000);  // Delay to allow the servo to reach the position
        }
    
        //sleep_ms(100);
        /*float temp = read_temperature();
        printf("Temperature: %.2f °C\n", temp);
        if(temp >= 20.0f && temp <= 60.0f ){
            led_on(LED_PIN2);
            printf("in ifffffffffffffff \n");
        }
        else{
            printf("in elseeeeeeeeeeeeeeeeeeeeeeeeee \n");
            led_on(LED_PIN3);
        }*/



        //sleep_ms(3000);

    }

}
