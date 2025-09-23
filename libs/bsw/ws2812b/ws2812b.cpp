#include "ws2812b.h"
// Removed <cstdint> to avoid pulling in C++ standard library
#include "bsp/timer/SystemTimer.h"

// Platform-specific includes
#ifndef __linux__
#include "io/Io.h"
#endif

namespace {
    constexpr uint32_t WS2812B_MAX_LEDS = 144;
    
    uint32_t ws2812b_data_pin;
    uint32_t ws2812b_led_count;
    uint8_t ws2812b_buffer[WS2812B_MAX_LEDS * 3];
    
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
    
    // Timer delay functions using nanoseconds - improved implementation
    void timer_delay_ns(uint32_t ns) {
        // For WS2812b, precise timing is critical
        // Convert nanoseconds to microseconds for sysDelayUs
        // Note: For production, this may need cycle-accurate timing
        if (ns >= 1000) {
            sysDelayUs(ns / 1000);
        } else {
            // For sub-microsecond delays, we need to be more careful
            // This is a rough approximation - for production use,
            // consider using CPU cycle counting or hardware timers
            volatile uint32_t cycles = ns / 10; // Rough approximation
            for (volatile uint32_t i = 0; i < cycles; i++) {
                // Busy wait - not ideal but necessary for precise timing
            }
        }
    }
    
    constexpr uint32_t GPIO_MODE_OUTPUT = 1;
}

void ws2812b_init(uint32_t data_pin, uint32_t led_count) {
    ws2812b_data_pin = data_pin;
    ws2812b_led_count = (led_count > WS2812B_MAX_LEDS) ? WS2812B_MAX_LEDS : led_count;
    gpio_set_mode(ws2812b_data_pin, GPIO_MODE_OUTPUT);
    ws2812b_clear();
}

void ws2812b_set_led(uint32_t index, uint8_t r, uint8_t g, uint8_t b) {
    if (index >= ws2812b_led_count) return;
    ws2812b_buffer[index * 3 + 0] = g;
    ws2812b_buffer[index * 3 + 1] = r;
    ws2812b_buffer[index * 3 + 2] = b;
}

void ws2812b_clear() {
    for (uint32_t i = 0; i < sizeof(ws2812b_buffer); ++i) {
        ws2812b_buffer[i] = 0;
    }
    ws2812b_show();
}

namespace {
    void ws2812b_send_byte(uint8_t byte) {
        for (int i = 7; i >= 0; i--) {
            if (byte & (1 << i)) {
                // Send '1' bit
                gpio_write(ws2812b_data_pin, 1);
                timer_delay_ns(800);
                gpio_write(ws2812b_data_pin, 0);
                timer_delay_ns(450);
            } else {
                // Send '0' bit
                gpio_write(ws2812b_data_pin, 1);
                timer_delay_ns(400);
                gpio_write(ws2812b_data_pin, 0);
                timer_delay_ns(850);
            }
        }
    }
}

void ws2812b_show() {
    for (uint32_t i = 0; i < ws2812b_led_count * 3; i++) {
        ws2812b_send_byte(ws2812b_buffer[i]);
    }
    // Latch
    sysDelayUs(50);
}
