#include "flameSensor.h"
#include "hardware/adc.h"

void flameSensor_init(uint FLAME_SENSOR_ADC_PIN) {
    // Initialize the ADC hardware
    adc_init();
    // Enable the ADC pin
    adc_gpio_init(FLAME_SENSOR_ADC_PIN);
    // Select the ADC channel (0 corresponds to GP26)
    adc_select_input(FLAME_SENSOR_ADC_PIN-26);
}

uint flameSensor_readAnalog() {
    // Read the raw ADC value (12-bit, 0-4095)
    return adc_read();
}

float flameSensor_adcToVoltage(uint adc_value) {
    // Convert the ADC value to a voltage
    // Assuming a reference voltage of 3.3V
    return (adc_value * 3.3f) / 4095.0f;
}