#ifndef FLAME_SENSOR_H
#define FLAME_SENSOR_H

#include "pico/stdlib.h"

// Define the pin for the Flame Sensor analog output


/**
 * @brief Initialize the Flame Sensor.
 * This function sets up the ADC for the specified input pin.
 */
void flameSensor_init(uint FLAME_SENSOR_ADC_PIN);

/**
 * @brief Read the analog output from the Flame Sensor.
 * @return A 12-bit ADC value (0-4095).
 */
uint flameSensor_readAnalog();

/**
 * @brief Convert the analog output to voltage.
 * @param adc_value The raw ADC value (0-4095).
 * @return The voltage corresponding to the ADC value.
 */
float flameSensor_adcToVoltage(uint adc_value);

#endif // FLAME_SENSOR_H