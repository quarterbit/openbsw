# OpenBSW POSIX Platform Enhanced Testing Features

## Overview

The POSIX platform build now includes enhanced stubbed functionality for hardware components, allowing for comprehensive testing and demonstration without physical hardware.

## Enhanced Components

### 1. HC-SR04 Distance Sensor (`/libs/bsw/hcsr04/`)

**Stubbed Functionality:**
- Simulates realistic distance measurements cycling through 1-100cm
- Uses a smooth pattern with variations to mimic real sensor behavior
- Includes measurement counter for predictable, reproducible testing

**Implementation:**
```cpp
// POSIX simulation: cycle through 1-100cm for testing
static uint32_t measurement_counter = 0;
measurement_counter++;

// Create a realistic distance pattern that cycles through 1-100cm
uint32_t cycle_position = measurement_counter % 200; // Full cycle every 200 measurements
int32_t distance;

if (cycle_position < 100) {
    // Increasing distance from 1 to 100
    distance = 1 + cycle_position;
} else {
    // Decreasing distance from 100 to 1
    distance = 100 - (cycle_position - 100);
}

// Add some variation to make it more realistic
int32_t variation = ((measurement_counter * 7) % 11) - 5; // -5 to +5 variation
distance += variation;
```

### 2. WS2812B LED Strip (`/libs/bsw/ws2812b/`)

**Stubbed Functionality:**
- ASCII visualization of LED strip using ANSI color codes
- Real-time display of RGB values as colored terminal output
- Visual representation of LED patterns and effects

**Implementation:**
```cpp
// POSIX simulation: output ASCII representation of LED strip
printf("LED Strip: [");

for (uint32_t i = 0; i < ws2812b_led_count; i++) {
    uint8_t r = ws2812b_buffer[i * 3 + 1]; // Red
    uint8_t g = ws2812b_buffer[i * 3 + 0]; // Green
    uint8_t b = ws2812b_buffer[i * 3 + 2]; // Blue
    
    if (r == 0 && g == 0 && b == 0) {
        printf(" "); // Off LED
    } else {
        // Use ANSI color codes for true color representation
        printf("\033[38;2;%d;%d;%dm█\033[0m", r, g, b);
    }
}

printf("]");
```

### 3. LedProximitySystem Enhanced Logging

**Features:**
- Distance measurements logged every 10th update
- LED count and strip visualization
- Clear progress indicators with update counters
- Color gradient visualization in real-time

**Sample Output:**
```
[0001] Distance:   7 cm | LEDs: 135/144 | LED Strip: [████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████...]
[0002] Distance:  21 cm | LEDs: 114/144 | LED Strip: [██████████████████████████████████████████████████████████████████████████████████████████████████████████████████...]
[0003] Distance:  35 cm | LEDs:  94/144 | LED Strip: [████████████████████████████████████████████████████████████████████████████████████████████...]
```

## Testing the Enhanced Features

### Building for POSIX

```bash
cd /workspaces/openbsw/executables/referenceApp
mkdir -p build.posix && cd build.posix
cmake .. -DBUILD_TARGET_PLATFORM=POSIX \
         -DPLATFORM_SUPPORT_UDS=OFF \
         -DPLATFORM_SUPPORT_CAN=OFF \
         -DPLATFORM_SUPPORT_ETHERNET=OFF \
         -DPLATFORM_SUPPORT_IO=OFF \
         -DPLATFORM_SUPPORT_STORAGE=OFF
cmake --build . -j $(nproc)
```

### Running the Test

```bash
# Run for 10 seconds to see the cycling behavior
timeout 10s ./application/app.referenceApp.elf

# Or run indefinitely to observe full cycles
./application/app.referenceApp.elf
```

## Technical Details

### Distance Sensor Simulation
- **Cycle Duration**: 200 measurements for a complete 1→100→1 cycle
- **Update Rate**: 100ms per measurement (configurable)
- **Variation**: ±5cm random variation for realism
- **Range**: 1-100cm as requested

### LED Strip Visualization
- **Colors**: True RGB support via ANSI escape codes
- **Length**: 144 LEDs (configurable)
- **Mapping**: Linear distance-to-LED mapping with color gradient
- **Color Scheme**: Green (far) → Orange (medium) → Red (close)

### Platform Compatibility
- **C++ Standard**: C++14 compatible (no C++17 features)
- **POSIX Systems**: Linux, macOS, WSL
- **Dependencies**: Standard C library (printf, fflush)
- **Terminal Support**: ANSI color codes (most modern terminals)

## Integration with Safety Systems

The enhanced POSIX functionality integrates seamlessly with OpenBSW's safety architecture:

- **SafetyManager**: Monitors component health
- **Lifecycle Management**: Proper initialization and shutdown
- **Async Framework**: Non-blocking operation with FreeRTOS simulation
- **Logging Integration**: Comprehensive logging with configurable levels

## Use Cases

1. **Development Testing**: Rapid iteration without hardware
2. **CI/CD Integration**: Automated testing in containers
3. **Demonstration**: Visual representation of system behavior
4. **Algorithm Validation**: Test proximity algorithms and LED patterns
5. **Safety Testing**: Verify safety mechanisms with predictable inputs

## Future Enhancements

Potential improvements for the POSIX simulation:
- Interactive control (keyboard input to change distances)
- JSON output for automated testing
- Configuration file support for test scenarios
- Integration with external simulation tools
- WebSocket interface for remote monitoring