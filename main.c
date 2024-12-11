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
int counter = 0;
bool fireEnded = true;

void flame_sensor_callback() {

    printf("Interrupt triggered: Flame sensor value exceeded threshold!\n");
    setMillis(SERVO_PIN_ENTRY_GATE, 1250);
    setMillis(SERVO_PIN_EXIT_GATE, 1250);
    led_off(GREEN_LED_PIN_SLOT_1);
    led_off(GREEN_LED_PIN_SLOT_2);
    led_off(GREEN_LED_PIN_SLOT_3);
    led_off(GREEN_LED_PIN_SLOT_4);

    if (counter < 2){
        led_on(RED_LED_PIN_SLOT_4);
        buzzer_on(BUZZER_PIN);
        printf("LED ON\n");
    }
    else{
        if(counter < 4){
            led_off(RED_LED_PIN_SLOT_4);
            buzzer_off(BUZZER_PIN);
            printf("LED OFF\n");
        }
        else
            counter = 0;
    }
    printf("Counter : %d", counter);
    counter++;
}

bool timer_callback(struct repeating_timer *t) {
    uint16_t flame_value = flameSensor_readAnalog();
    
    float voltage = flameSensor_adcToVoltage(flame_value);
    //printf("ADC Value: %u, Voltage: %.2fV\n", flame_value, voltage);

    if (flame_value <= threshold || !fireEnded) {
        fireEnded = false;
        flame_sensor_callback(); 
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
    add_repeating_timer_ms(200, timer_callback, NULL, &timer); // Check every 100 ms


    while (true) {

        if(ir_read(IR_PIN_SLOT_4) == 1){
            //led_on(RED_LED_PIN_SLOT_4);
            //led_off(GREEN_LED_PIN_SLOT_4);
            fireEnded = true;
        }
        

        if(fireEnded){

            buzzer_off(BUZZER_PIN);


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

        /*if(ir_read(IR_PIN_SLOT_4) == 1){
            //led_on(RED_LED_PIN_SLOT_4);
            //led_off(GREEN_LED_PIN_SLOT_4);

        }
        else{
            led_on(GREEN_LED_PIN_SLOT_4);
            led_off(RED_LED_PIN_SLOT_4);
        }*/

        //----------------------------------------------

        sleep_ms(100);

    }


        }
        
}
