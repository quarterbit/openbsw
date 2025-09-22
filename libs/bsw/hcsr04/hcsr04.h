#ifndef HCSR04_H
#define HCSR04_H

#include <cstdint>

/**
 * @brief Initialize the HC-SR04 sensor driver
 * @param trigger_pin GPIO pin for trigger
 * @param echo_pin GPIO pin for echo
 */
void hcsr04_init(uint32_t trigger_pin, uint32_t echo_pin);

/**
 * @brief Measure distance in centimeters
 * @return Distance in cm, or -1 on error
 */
int32_t hcsr04_measure_cm();

#endif // HCSR04_H
