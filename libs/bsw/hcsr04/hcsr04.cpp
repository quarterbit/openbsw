#include "hcsr04.h"
// Removed <cstdint> to avoid pulling in C++ standard library
#include "bsp/timer/SystemTimer.h"

// Platform-specific includes
#ifndef __linux__
#include "io/Io.h"
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
                cfg.pinCfg = bios::Io::GPIO;
            } else { // INPUT
                cfg.dir = bios::Io::_IN;
                cfg.pinCfg = bios::Io::GPIO;
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
    
    uint32_t gpio_read(uint32_t pin) {
#ifndef __linux__
        // S32K1xx implementation using BSP IO API
        return bios::Io::getPin(pin) ? 1 : 0;
#else
        // POSIX/stub implementation - simulate a changing signal for testing
        (void)pin;
        static uint32_t counter = 0;
        counter++;
        // Simulate HC-SR04 behavior: return 0 initially, then 1 for a period, then 0
        return ((counter / 100) % 3) == 1 ? 1 : 0;
#endif
    }
    
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
}
