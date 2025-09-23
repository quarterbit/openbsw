# LED Proximity Demo (Multi-Platform OpenBSW)

This demo shows how to use the OpenBSW stack to control a WS2812b LED strip based on distance measured by an HC-SR04 ultrasonic sensor. Supports both S32K148EVB and RP2040/Pico W platforms.

## Features
- 144 addressable WS2812b LEDs (purple: 161, 0, 255)
- HC-SR04 ultrasonic sensor (1–100 cm range)
- LEDs light up stepwise as object approaches (1 cm = all on, >100 cm = all off)
- Modular FreeRTOS task
- **Cross-platform support**: Works on both S32K148EVB and RP2040/Pico W

## Platform-Specific Pin Assignments

### S32K148EVB Board
- **HC-SR04 Trigger**: Pin 37 (PB5) - GPIO output
- **HC-SR04 Echo**: Pin 36 (PB4) - GPIO input  
- **WS2812B Data**: Pin 78 (PC14) - GPIO output with drive strength

### RP2040/Pico W Board
- **HC-SR04 Trigger**: GP3 - GPIO output
- **HC-SR04 Echo**: GP4 - GPIO input
- **WS2812B Data**: GP2 - GPIO output

## Hardware Connections

### S32K148EVB Breadboard Wiring
```
S32K148EVB Board                    Breadboard
┌─────────────────────┐            ┌─────────────────────────────┐
│                     │            │                             │
│  [PB5]─────────────────────────────► Trigger (HC-SR04)        │
│  [PB4]◄────────────────────────────── Echo    (HC-SR04)        │
│  [PC14]────────────────────────────► Data In (WS2812B Strip)  │
│  [GND]─────────────────────────────► GND     (Both Devices)   │
│  [5V]──────────────────────────────► VCC     (Both Devices)   │
│                     │            │                             │
└─────────────────────┘            └─────────────────────────────┘
                                          │                    │
                                   HC-SR04 Sensor    WS2812B LED Strip
                                   ┌──────────────┐   ┌─────────────────┐
                                   │ VCC GND TRIG │   │ 5V GND DIN DOUT │
                                   │ ●   ●   ●    │   │ ●  ●   ●   ●    │
                                   │         ECHO │   │                 │
                                   │         ●    │   │ (144 LEDs)      │
                                   └──────────────┘   └─────────────────┘
```

### RP2040/Pico W Breadboard Wiring  
```
Raspberry Pi Pico W                 Breadboard
┌─────────────────────┐            ┌─────────────────────────────┐
│                     │            │                             │
│ (4) GP3 ──────────────────────────► Trigger (HC-SR04)        │
│ (6) GP4 ◄─────────────────────────── Echo    (HC-SR04)        │
│ (4) GP2 ──────────────────────────► Data In (WS2812B Strip)  │
│(38) GND ──────────────────────────► GND     (Both Devices)   │
│(40) VBUS ─────────────────────────► VCC     (Both Devices)   │
│     (or 3V3)        │            │                             │
└─────────────────────┘            └─────────────────────────────┘
                                          │                    │
                                   HC-SR04 Sensor    WS2812B LED Strip
                                   ┌──────────────┐   ┌─────────────────┐
                                   │ VCC GND TRIG │   │ 5V GND DIN DOUT │
                                   │ ●   ●   ●    │   │ ●  ●   ●   ●    │
                                   │         ECHO │   │                 │
                                   │         ●    │   │ (144 LEDs)      │
                                   └──────────────┘   └─────────────────┘
```

## Usage Instructions

### For S32K148EVB:
1. Wire the HC-SR04 sensor and WS2812B strip according to the diagram above
2. Build with S32K1xx toolchain: `cmake --preset=s32k148evb && make -j4`
3. Flash the firmware to the S32K148EVB board
4. The LED strip will respond to proximity in real time

### For RP2040/Pico W:
1. Wire the HC-SR04 sensor and WS2812B strip according to the diagram above  
2. Build with RP2040 toolchain: `cmake --preset=rp2040 && make -j4`
3. Flash the generated `.uf2` file to the Pico W in bootloader mode
4. The LED strip will respond to proximity in real time

## Power Requirements
- **HC-SR04**: 5V (can work with 3.3V but reduced range)
- **WS2812B Strip**: 5V (144 LEDs at full brightness = ~8.6A max!)
- **Recommendation**: Use external 5V power supply for the LED strip
- **Alternative**: Limit LED count or brightness for USB power

## Integration
- Components: `libs/bsw/hcsr04/`, `libs/bsw/ws2812b/`
- Demo task: `executables/referenceApp/application/led_proximity.cpp`
- Platform configs: Auto-detected via preprocessor macros

## Technical Notes
- Requires precise timer and GPIO implementation for correct WS2812b operation
- Both platforms support microsecond timing needed for WS2812B protocol
- HC-SR04 timing is less critical and works well on both platforms
- Pin assignments are optimized for breadboard prototyping
