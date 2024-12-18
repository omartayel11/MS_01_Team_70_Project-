#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "lwip/netif.h"
#include "lwip/dhcp.h"
#include "lwip/apps/httpd.h"
#include "lwipopts.h"
#include "ssi.h"
#include "cgi.h"
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
#define SWITCH_PIN 17

#define DIGITAL_PIN 18

bool direction = true;
int currentMillis = 0;
const uint16_t threshold = 1000;
int counter = 0;
bool fireEnded = true;

const char WIFI_SSID[] = "Omar’s iPhone";
const char WIFI_PASSWORD[] = "tayel20033";

void flame_sensor_callback() {

    printf("Interrupt triggered: Flame sensor value exceeded threshold!\n");
    setMillis(SERVO_PIN_ENTRY_GATE, 1250);
    setMillis(SERVO_PIN_EXIT_GATE, 1250);
    led_off(GREEN_LED_PIN_SLOT_1);
    led_off(GREEN_LED_PIN_SLOT_2);
    led_off(GREEN_LED_PIN_SLOT_3);
    led_off(GREEN_LED_PIN_SLOT_4);
    buzzer_on(BUZZER_PIN);

    if (counter < 2){
        led_on(RED_LED_PIN_SLOT_1);
        led_on(RED_LED_PIN_SLOT_2);
        led_on(RED_LED_PIN_SLOT_3);
        led_on(RED_LED_PIN_SLOT_4);
        printf("LED ON\n");
    }
    else{
        if(counter < 4){
            led_off(RED_LED_PIN_SLOT_1);
            led_off(RED_LED_PIN_SLOT_2);
            led_off(RED_LED_PIN_SLOT_3);
            led_off(RED_LED_PIN_SLOT_4);
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

void print_ip_address() {
    struct netif *netif = netif_list; // Access the network interface
    if (netif && netif_is_up(netif)) {
        printf("IP Address: %s\n", ipaddr_ntoa(&netif->ip_addr));
    } else {
        printf("Network interface is down.\n");
    }
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

    gpio_init(SWITCH_PIN); 
    gpio_set_dir(SWITCH_PIN, GPIO_IN);

    gpio_init(DIGITAL_PIN);
    gpio_set_dir(DIGITAL_PIN, GPIO_IN);

    cyw43_arch_init();

    cyw43_arch_enable_sta_mode();

    // Connect to the WiFI network - loop until connected
    while(cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASSWORD, CYW43_AUTH_WPA2_AES_PSK, 30000) != 0){
        printf("Attempting to connect...\n");
    }
    // Print a success message once connected
    printf("Connected! \n");
    
    // Initialise web server
    httpd_init();
    printf("Http server initialised\n");

    // Configure SSI and CGI handler
    ssi_init(); 
    printf("SSI Handler initialised\n");
    cgi_init();
    printf("CGI Handler initialised\n");

    struct repeating_timer timer;
    add_repeating_timer_ms(200, timer_callback, NULL, &timer); // Check every 100 ms

    while (true) {

        //print_ip_address();

        printf("DIGITAL PIN: %d\n", gpio_get(DIGITAL_PIN));


        if(gpio_get(SWITCH_PIN) == 1){
            //led_on(RED_LED_PIN_SLOT_4);
            //led_off(GREEN_LED_PIN_SLOT_4);
            fireEnded = true;
        }
        

        if(fireEnded){

            buzzer_off(BUZZER_PIN);


        //ir entry gate
        if(ir_read(IR_PIN_ENTRY_GATE) == 1 && (ir_read(IR_PIN_SLOT_1) == 0 || ir_read(IR_PIN_SLOT_2) == 0 || ir_read(IR_PIN_SLOT_3) == 0  || ir_read(IR_PIN_SLOT_4) == 0)){
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
        
}
