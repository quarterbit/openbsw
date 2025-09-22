# LED Proximity Control - OpenBSW Integration Summary

## Overview
Successfully integrated LED proximity control feature with OpenBSW framework for S32K148 hardware platform.

## Components Implemented

### 1. HC-SR04 Ultrasonic Sensor Component (`libs/bsw/hcsr04/`)
- **Purpose**: Distance measurement using HC-SR04 ultrasonic sensor
- **Implementation**: Platform-conditional compilation
  - S32K1xx: Uses `bios::Io` API for real GPIO control
  - POSIX: Simulation stub for development/testing
- **API**: 
  - `hcsr04_init(trigger_pin, echo_pin)`
  - `hcsr04_measure_cm()` - returns distance in cm

### 2. WS2812b LED Strip Component (`libs/bsw/ws2812b/`)
- **Purpose**: Control addressable LED strips (144 LEDs)
- **Implementation**: Platform-conditional compilation
  - S32K1xx: Uses `bios::Io` API for precise timing control
  - POSIX: Simulation stub for development/testing
- **API**:
  - `ws2812b_init(data_pin, led_count)`
  - `ws2812b_set_color(led_index, r, g, b)`
  - `ws2812b_update()` - sends data to LED strip

### 3. LED Proximity Application (`application/led_proximity.cpp`)
- **Purpose**: Main application integrating sensor and LED control
- **Pattern**: OpenBSW `AsyncLifecycleComponent` with `IRunnable`
- **Behavior**: 
  - Reads distance from HC-SR04 sensor
  - Maps distance (1-100cm) to LED count (0-144 LEDs)
  - Uses purple color (161, 0, 255)
  - Updates at 10Hz using `scheduleAtFixedRate(100ms)`

## Hardware Configuration (S32K148EVB)
- **HC-SR04 Sensor**:
  - Trigger Pin: IO_036 (Port A, Pin 4)
  - Echo Pin: IO_037 (Port A, Pin 5)
- **WS2812b LED Strip**:
  - Data Pin: IO_078 (Port D, Pin 14)
- **Pin assignments**: Documented in `ioConfiguration.h`

## Build System Integration
- **Target Platforms**: 
  - S32K148EVB (real hardware with ARM cross-compilation)
  - POSIX (development/simulation environment)
- **Dependencies**: 
  - S32K1xx builds: Links with `bspIo` for GPIO access
  - POSIX builds: Excludes `bspIo` (not available on POSIX)
- **Conditional Compilation**: Uses `#ifndef __linux__` for platform detection

## Key Features
1. **Real Hardware Support**: Direct S32K1xx BSP integration
2. **Development Support**: POSIX simulation for testing
3. **OpenBSW Patterns**: Proper lifecycle management and async execution
4. **Robust Build**: Platform-conditional linking prevents build errors
5. **Documentation**: Comprehensive pin mapping and integration guides

## Build Status
✅ **POSIX Build**: Successfully compiles `app.referenceApp.elf` (6.4MB)
✅ **S32K1xx Ready**: Code ready for cross-compilation with ARM toolchain
✅ **OpenBSW Compliant**: Follows framework patterns and lifecycle management

## Usage
The application automatically starts when the OpenBSW system boots and runs continuously:
1. HC-SR04 measures distance every 100ms
2. Distance is mapped to number of LEDs to illuminate
3. LEDs display purple gradient based on proximity
4. Closer objects = more LEDs illuminated

## File Structure
```
libs/bsw/
├── hcsr04/
│   ├── CMakeLists.txt
│   ├── README.md
│   ├── hcsr04.h
│   └── hcsr04.cpp
└── ws2812b/
    ├── CMakeLists.txt
    ├── README.md
    ├── ws2812b.h
    └── ws2812b.cpp

executables/referenceApp/application/
├── led_proximity.cpp
└── S32K148_LED_PROXIMITY_PINOUT.md
```