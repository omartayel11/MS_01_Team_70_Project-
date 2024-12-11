#include "led.h"
#include "infraRed.h"
#include "servo.h"
#include "flameSensor.h"
#include "buzzer.h"
#include "hardware/timer.h"
#include <stdio.h>

//#define LED_PIN 0
#define GREEN_LED_PIN_SLOT_1 0
#define RED_LED_PIN_SLOT_1 1
#define GREEN_LED_PIN_SLOT_2 2
#define RED_LED_PIN_SLOT_2 3
#define GREEN_LED_PIN_SLOT_3 4
#define RED_LED_PIN_SLOT_3 5
#define GREEN_LED_PIN_SLOT_4 6
#define RED_LED_PIN_SLOT_4 7

#define IR_PIN_ENTRY_GATE 8
#define IR_PIN_EXIT_GATE 9

#define FLAME_SENSOR_ADC_PIN 28 

#define SERVO_PIN_ENTRY_GATE 10
#define SERVO_PIN_EXIT_GATE 11

#define IR_PIN_SLOT_1 12
#define IR_PIN_SLOT_2 13
#define IR_PIN_SLOT_3 14
#define IR_PIN_SLOT_4 15

#define BUZZER_PIN 16

bool direction = true;
int currentMillis = 0;
const uint16_t threshold = 1000;

void flame_sensor_callback() {

    printf("Interrupt triggered: Flame sensor value exceeded threshold!\n");
    setMillis(SERVO_PIN_ENTRY_GATE, 1250);
    setMillis(SERVO_PIN_EXIT_GATE, 1250);
    buzzer_on(BUZZER_PIN);
    led_off(GREEN_LED_PIN_SLOT_1);
    led_off(GREEN_LED_PIN_SLOT_2);
    led_off(GREEN_LED_PIN_SLOT_3);
    led_off(GREEN_LED_PIN_SLOT_4);

    while(true) {
    printf("LED ON\n");
    led_on(RED_LED_PIN_SLOT_1);
    sleep_ms(500);
    printf("LED OFF\n");
    led_off(RED_LED_PIN_SLOT_1);
    sleep_ms(500);
    printf("Loop iteration complete\n");
}

}

bool timer_callback(struct repeating_timer *t) {
    uint16_t flame_value = flameSensor_readAnalog();
    
    float voltage = flameSensor_adcToVoltage(flame_value);
    //printf("ADC Value: %u, Voltage: %.2fV\n", flame_value, voltage);

    if (flame_value <= threshold) {
        flame_sensor_callback(); 
        return false;
    }
    return true; 
}

int main() {

    stdio_init_all();

    led_init(GREEN_LED_PIN_SLOT_1);
    led_init(RED_LED_PIN_SLOT_1);
    led_init(GREEN_LED_PIN_SLOT_2);
    led_init(RED_LED_PIN_SLOT_2);
    led_init(GREEN_LED_PIN_SLOT_3);
    led_init(RED_LED_PIN_SLOT_3);
    led_init(GREEN_LED_PIN_SLOT_4);
    led_init(RED_LED_PIN_SLOT_4);

    ir_init(IR_PIN_ENTRY_GATE);
    ir_init(IR_PIN_EXIT_GATE);
    ir_init(IR_PIN_SLOT_1);
    ir_init(IR_PIN_SLOT_2);
    ir_init(IR_PIN_SLOT_3);
    ir_init(IR_PIN_SLOT_4);

    setServo(SERVO_PIN_ENTRY_GATE, currentMillis);
    setServo(SERVO_PIN_EXIT_GATE, currentMillis);

    flameSensor_init(FLAME_SENSOR_ADC_PIN); // Initialize the Flame Sensor

    buzzer_init(BUZZER_PIN);

    struct repeating_timer timer;
    add_repeating_timer_ms(100, timer_callback, NULL, &timer); // Check every 100 ms


    while (true) {


        //ir entry gate
        if(ir_read(IR_PIN_ENTRY_GATE) == 1){
            setMillis(SERVO_PIN_ENTRY_GATE, 1250);
            sleep_ms(2000);
        }
        else{
            setMillis(SERVO_PIN_ENTRY_GATE, 400);
        }


        //ir exity gate
        if(ir_read(IR_PIN_EXIT_GATE) == 1){
            setMillis(SERVO_PIN_EXIT_GATE, 1250);
            sleep_ms(2000);
        }
        else{
            setMillis(SERVO_PIN_EXIT_GATE, 400);
        }

        //----------------------------------------------

        //ir slots
        if(ir_read(IR_PIN_SLOT_1) == 1){
            led_on(RED_LED_PIN_SLOT_1);
            led_off(GREEN_LED_PIN_SLOT_1);
        }
        else{
            led_on(GREEN_LED_PIN_SLOT_1);
            led_off(RED_LED_PIN_SLOT_1);
        }

        if(ir_read(IR_PIN_SLOT_2) == 1){
            led_on(RED_LED_PIN_SLOT_2);
            led_off(GREEN_LED_PIN_SLOT_2);
        }
        else{
            led_on(GREEN_LED_PIN_SLOT_2);
            led_off(RED_LED_PIN_SLOT_2);
        }

        if(ir_read(IR_PIN_SLOT_3) == 1){
            led_on(RED_LED_PIN_SLOT_3);
            led_off(GREEN_LED_PIN_SLOT_3);
        }
        else{
            led_on(GREEN_LED_PIN_SLOT_3);
            led_off(RED_LED_PIN_SLOT_3);
        }

        if(ir_read(IR_PIN_SLOT_4) == 1){
            led_on(RED_LED_PIN_SLOT_4);
            led_off(GREEN_LED_PIN_SLOT_4);
        }
        else{
            led_on(GREEN_LED_PIN_SLOT_4);
            led_off(RED_LED_PIN_SLOT_4);
        }

        //----------------------------------------------

        sleep_ms(100);

    }

}
