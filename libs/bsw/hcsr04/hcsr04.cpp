#include "hcsr04.h"
// Removed <cstdint> to avoid pulling in C++ standard library
#include "bsp/timer/SystemTimer.h"

// Platform-specific includes
#ifndef __linux__
#include "io/Io.h"
#endif

// GPIO constant for pinCfg field (compatible with S32K1xx interface)
#ifndef GPIO
#define GPIO (1 << 8)
#endif

namespace {
    uint32_t hcsr04_trigger_pin;
    uint32_t hcsr04_echo_pin;
    constexpr uint32_t TIMEOUT_US = 30000; // 30ms timeout
    
    // GPIO functions with platform-specific implementations
    void gpio_set_mode(uint32_t pin, uint32_t mode) {
#ifndef __linux__
        // S32K1xx implementation using BSP IO API
        bios::Io::PinConfiguration cfg;
        if (bios::Io::getConfiguration(pin, cfg) == bsp::BSP_OK) {
            if (mode == 1) { // OUTPUT
                cfg.dir = bios::Io::_OUT;
                cfg.pinCfg = GPIO;
            } else { // INPUT
                cfg.dir = bios::Io::_IN;
                cfg.pinCfg = GPIO;
            }
            bios::Io::setConfiguration(pin, cfg);
        }
#else
        // POSIX/stub implementation for development/testing
        (void)pin;
        (void)mode;
        // Note: For POSIX simulation, GPIO operations are no-ops
#endif
    }
    
    void gpio_write(uint32_t pin, uint32_t value) {
#ifndef __linux__
        // S32K1xx implementation using BSP IO API
        bios::Io::setPin(pin, value != 0);
#else
        // POSIX/stub implementation for development/testing
        (void)pin;
        (void)value;
        // Note: For POSIX simulation, GPIO operations are no-ops
#endif
    }
    
#ifndef __linux__
    uint32_t gpio_read(uint32_t pin) {
        // S32K1xx implementation using BSP IO API
        return bios::Io::getPin(pin) ? 1 : 0;
    }
#endif
    
    constexpr uint32_t GPIO_MODE_OUTPUT = 1;
    constexpr uint32_t GPIO_MODE_INPUT = 0;
}

void hcsr04_init(uint32_t trigger_pin, uint32_t echo_pin) {
    hcsr04_trigger_pin = trigger_pin;
    hcsr04_echo_pin = echo_pin;
    gpio_set_mode(hcsr04_trigger_pin, GPIO_MODE_OUTPUT);
    gpio_set_mode(hcsr04_echo_pin, GPIO_MODE_INPUT);
    gpio_write(hcsr04_trigger_pin, 0);
}

int32_t hcsr04_measure_cm() {
#ifdef __linux__
    // POSIX simulation: cycle through 1-100cm for testing
    static uint32_t measurement_counter = 0;
    measurement_counter++;
    
    // Create a realistic distance pattern that cycles through 1-100cm
    // Using a combination of sine-like function for smooth transitions
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
    
    // Clamp to valid range
    if (distance < 1) distance = 1;
    if (distance > 100) distance = 100;
    
    return distance;
#else
    // Send 10us trigger pulse
    gpio_write(hcsr04_trigger_pin, 1);
    sysDelayUs(10);
    gpio_write(hcsr04_trigger_pin, 0);

    // Wait for echo to go high
    uint32_t timeout = TIMEOUT_US;
    while (!gpio_read(hcsr04_echo_pin) && timeout--) {
        sysDelayUs(1);
    }
    if (timeout == 0) return -1;

    // Measure echo high time
    uint32_t duration = 0;
    while (gpio_read(hcsr04_echo_pin) && duration < TIMEOUT_US) {
        sysDelayUs(1);
        duration++;
    }
    if (duration == TIMEOUT_US) return -1;

    // Calculate distance in cm: distance = duration(us) / 58
    return static_cast<int32_t>(duration / 58);
#endif
}
