#include "led.h"
#include "infraRed.h"
#include "servo.h"
#include "flameSensor.h"
#include <stdio.h>

//#define LED_PIN 0
#define LED_PIN2 4
#define LED_PIN3 5
#define IR_PIN 3
#define FLAME_SENSOR_ADC_PIN 28 
#define SERVO_PIN 0

bool direction = true;
int currentMillis = 0;

int main() {
    stdio_init_all();
    //led_init(LED_PIN);
    led_init(LED_PIN2);
    //led_init(LED_PIN3);
    //ir_init(IR_PIN);
    setServo(SERVO_PIN, currentMillis);
    flameSensor_init(FLAME_SENSOR_ADC_PIN); // Initialize the Flame Sensor


    while (true) {

        //sleep_ms(60000);

        //led_toggle(LED_PIN);
        //sleep_ms(1000);

        //led_on(LED_PIN);
         //Move the servo to different angles
        // Sweep the servo from 0° to 180°

        
    
        //currentMillis += (direction)?200:-200;
        //if (currentMillis >= 1250) direction = false;
        //if (currentMillis <= 400) direction = true;
        //setMillis(SERVO_PIN, currentMillis);
        //sleep_ms(10);


/*for (uint8_t angle = 0; angle <= 180; angle++) {
    servo_set_angle(angle);
    sleep_ms(1000);  // Delay to allow the servo to reach the position
}

// Sweep the servo back to 0° after completing the first sweep
for (int16_t angle = 180; angle >= 0; angle--) {
    servo_set_angle((uint8_t)angle);  // Cast to uint8_t when calling the function
    sleep_ms(1000);  // Delay to allow the servo to reach the position
}*/


       //servoMotor_set_position(80);

         // Read the analog value
        uint16_t flame_value = flameSensor_readAnalog();

        // Convert to voltage
        float voltage = flameSensor_adcToVoltage(flame_value);

        // Print the raw ADC value and voltage
        printf("ADC Value: %u, Voltage: %.2fV\n", flame_value, voltage);

        if(flame_value<=1000){
            setMillis(SERVO_PIN, 1250);
            led_on(LED_PIN2);
            //sleep_ms(2000);
        }
        else{
            setMillis(SERVO_PIN, 400);
        }

        // Delay for readability
        sleep_ms(100);



        //sleep_ms(3000);

    }

}
