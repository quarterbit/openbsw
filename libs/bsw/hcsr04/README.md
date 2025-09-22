# HC-SR04 Ultrasonic Sensor Component

This component provides an interface for the HC-SR04 ultrasonic distance sensor for use with the OpenBSW stack.

## API

- `void hcsr04_init(uint32_t trigger_pin, uint32_t echo_pin);`
- `int32_t hcsr04_measure_cm(void);`

## Usage

1. Initialize the sensor with the correct GPIO pins.
2. Call `hcsr04_measure_cm()` to get the distance in centimeters.

## Notes
- Requires platform-specific GPIO and timer abstractions.
- Returns -1 on timeout or error.
