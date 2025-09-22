#ifndef WS2812B_H
#define WS2812B_H

#include <cstdint>

/**
 * @brief Initialize the WS2812b LED driver
 * @param data_pin GPIO pin for data
 * @param led_count Number of LEDs in the strip
 */
void ws2812b_init(uint32_t data_pin, uint32_t led_count);

/**
 * @brief Set color of a single LED
 * @param index LED index (0-based)
 * @param r Red value (0-255)
 * @param g Green value (0-255)
 * @param b Blue value (0-255)
 */
void ws2812b_set_led(uint32_t index, uint8_t r, uint8_t g, uint8_t b);

/**
 * @brief Update the LED strip with the current buffer
 */
void ws2812b_show();

/**
 * @brief Clear all LEDs (turn off)
 */
void ws2812b_clear();

#endif // WS2812B_H
