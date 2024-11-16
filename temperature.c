#include "temperature.h"
#include "hardware/adc.h"

// LM35DZ sensor is connected to ADC0 (GPIO26)
#define LM35_PIN 26

// Function to initialize ADC for LM35
void temperature_init(void) {
    // Initialize ADC
    adc_init();
    
    // Select the ADC pin for the LM35 sensor
    adc_gpio_init(LM35_PIN);
    adc_select_input(0); // ADC0 (GPIO26)
}

// Function to read the temperature value from LM35 sensor
float read_temperature(void) {
    // Read the ADC value (12-bit resolution)
    uint16_t raw_adc = adc_read();

    // Convert ADC reading to voltage (3.3V reference)
    float voltage = raw_adc * (3.3f / 4096);  // 12-bit ADC has a range of 0-4095

    // LM35 gives 10mV per degree Celsius, so the voltage in millivolts equals the temperature
    // Multiply by 100 to convert from volts to millivolts, then divide by 10 for °C
    float temperature = (voltage * 1000) / 10;  // Convert to temperature in °C

    return temperature;
}