# WS2812b LED Strip Component

This component provides an interface for controlling a WS2812b addressable LED strip (up to 144 LEDs) for use with the OpenBSW stack.

## API

- `void ws2812b_init(uint32_t data_pin, uint32_t led_count);`
- `void ws2812b_set_led(uint32_t index, uint8_t r, uint8_t g, uint8_t b);`
- `void ws2812b_show(void);`
- `void ws2812b_clear(void);`

## Usage

1. Initialize the driver with the correct data pin and number of LEDs.
2. Set the color of each LED as needed.
3. Call `ws2812b_show()` to update the strip.

## Notes
- Requires platform-specific GPIO and timer abstractions.
- Timing is critical for WS2812b; ensure timer functions are precise.
