# LED Proximity Demo (S32K148 + OpenBSW)

This demo shows how to use the OpenBSW stack to control a WS2812b LED strip based on distance measured by an HC-SR04 ultrasonic sensor on the S32K148EVB board.

## Features
- 144 addressable WS2812b LEDs (purple: 161, 0, 255)
- HC-SR04 ultrasonic sensor (1–100 cm range)
- LEDs light up stepwise as object approaches (1 cm = all on, >100 cm = all off)
- Modular FreeRTOS task

## Usage
1. Connect the HC-SR04 trigger and echo pins to the S32K148EVB (update pin numbers in `led_proximity.c` if needed).
2. Connect the WS2812b data pin to the S32K148EVB (update pin number in `led_proximity.c` if needed).
3. Build and flash the firmware.
4. The LED strip will respond to proximity in real time.

## Integration
- Components: `libs/bsw/hcsr04/`, `libs/bsw/ws2812b/`
- Demo task: `executables/referenceApp/application/led_proximity.c`

## Notes
- Requires precise timer and GPIO implementation for correct WS2812b operation.
- Pin numbers are examples; adjust for your hardware setup.
