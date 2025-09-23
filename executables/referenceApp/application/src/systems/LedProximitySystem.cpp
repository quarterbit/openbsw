// Copyright 2024 Accenture.

#include "systems/LedProximitySystem.h"
#include "hcsr04.h"
#include "ws2812b.h"

// Platform-specific pin definitions
#ifdef OPENBSW_PLATFORM_RP2040
    // RP2040 pin definitions
    constexpr uint32_t LED_DATA_PIN = 16;      // GPIO16 for WS2812B data
    constexpr uint32_t HCSR04_TRIGGER_PIN = 2; // GPIO2 for HC-SR04 trigger
    constexpr uint32_t HCSR04_ECHO_PIN = 3;    // GPIO3 for HC-SR04 echo
#elif defined(OPENBSW_PLATFORM_S32K148EVB)
    // S32K148EVB pin definitions
    constexpr uint32_t LED_DATA_PIN = 0;       // PTD0 for WS2812B data
    constexpr uint32_t HCSR04_TRIGGER_PIN = 1; // PTD1 for HC-SR04 trigger
    constexpr uint32_t HCSR04_ECHO_PIN = 2;    // PTD2 for HC-SR04 echo
#else
    // Default pin definitions for unknown platforms
    constexpr uint32_t LED_DATA_PIN = 16;      // Default to RP2040 pins
    constexpr uint32_t HCSR04_TRIGGER_PIN = 2;
    constexpr uint32_t HCSR04_ECHO_PIN = 3;
#endif

namespace systems {

LedProximitySystem::LedProximitySystem(::async::ContextType context)
    : _context(context)
{
    setTransitionContext(context);
}

void LedProximitySystem::init() {
    // Initialize hardware components
    hcsr04_init(HCSR04_TRIGGER_PIN, HCSR04_ECHO_PIN);
    ws2812b_init(LED_DATA_PIN, LED_COUNT);
    
    // Validate configuration
    _configuration_valid = validateConfiguration();
    if (!_configuration_valid) {
        // Log error but continue - component can still demonstrate basic functionality
        transitionDone();
        return;
    }
    
    // Perform basic functionality test
    performSelfTest();
    
    transitionDone();
}

void LedProximitySystem::run() {
    // Schedule periodic updates using scheduleAtFixedRate
    ::async::scheduleAtFixedRate(
        _context, *this, _timeout, UPDATE_INTERVAL_MS, ::async::TimeUnit::MILLISECONDS);
    transitionDone();
}

void LedProximitySystem::shutdown() {
    _timeout.cancel();
    ws2812b_clear();
    transitionDone();
}

void LedProximitySystem::execute() {
    updateLeds();
}

void LedProximitySystem::updateLeds() {
    // Read distance from HC-SR04 sensor
    int32_t distance_cm = hcsr04_measure_cm();
    
    // Handle sensor errors
    if (distance_cm < 0) {
        // Sensor error - show error pattern (all LEDs dim red)
        for (uint32_t i = 0; i < LED_COUNT; ++i) {
            ws2812b_set_led(i, 100, 0, 0); // Dim red
        }
        ws2812b_show();
        return;
    }
    
    // Map distance to number of LEDs to light up
    int32_t leds_on = mapDistanceToLeds(distance_cm);
    
    // Ensure leds_on is within valid range
    if (leds_on < 0) leds_on = 0;
    if (leds_on > static_cast<int32_t>(LED_COUNT)) leds_on = LED_COUNT;
    
    _target_leds_on = static_cast<uint32_t>(leds_on);
    
    // Render LEDs with current state
    renderLeds(_target_leds_on);
}

int32_t LedProximitySystem::mapDistanceToLeds(int32_t distance_cm) {
    // Clamp distance to valid range
    if (distance_cm < DIST_MIN_CM) distance_cm = DIST_MIN_CM;
    if (distance_cm > DIST_MAX_CM) distance_cm = DIST_MAX_CM;
    
    int32_t leds_on = 0;
    
    switch (_mapping_mode) {
        case MappingMode::LINEAR: {
            // Linear mapping: closer distance = more LEDs
            // Use integer math with scaling to avoid floating point
            int32_t range = DIST_MAX_CM - DIST_MIN_CM;
            int32_t normalized = (DIST_MAX_CM - distance_cm) * 1000 / range; // 0-1000 scale
            leds_on = (normalized * static_cast<int32_t>(LED_COUNT)) / 1000;
            break;
        }
        
        case MappingMode::EXPONENTIAL: {
            // Exponential mapping for better sensitivity at far distances
            int32_t range = DIST_MAX_CM - DIST_MIN_CM;
            int32_t normalized = (DIST_MAX_CM - distance_cm) * 1000 / range; // 0-1000 scale
            
            // Simple exponential approximation using integer math
            // exp_approx = normalized^2 / 1000 (gives exponential-like curve)
            int32_t exp_normalized = (normalized * normalized) / 1000;
            leds_on = (exp_normalized * static_cast<int32_t>(LED_COUNT)) / 1000;
            break;
        }
        
        case MappingMode::ZONES: {
            // Zone-based mapping with distinct regions
            if (distance_cm <= 20) {
                leds_on = LED_COUNT; // Full strip for very close
            } else if (distance_cm <= 40) {
                leds_on = (LED_COUNT * 3) / 4; // 75% for close
            } else if (distance_cm <= 60) {
                leds_on = LED_COUNT / 2; // 50% for medium
            } else if (distance_cm <= 80) {
                leds_on = LED_COUNT / 4; // 25% for far
            } else {
                leds_on = LED_COUNT / 8; // 12.5% for very far
            }
            break;
        }
    }
    
    return leds_on;
}

void LedProximitySystem::renderLeds(uint32_t leds_on) {
    // Clear all LEDs first
    ws2812b_clear();
    
    // Light up the required number of LEDs with gradient effect
    for (uint32_t i = 0; i < leds_on && i < LED_COUNT; ++i) {
        Color color;
        
        // Create gradient effect based on position
        uint32_t position_ratio = (i * 1000) / LED_COUNT; // 0-1000 scale
        
        if (position_ratio < 333) {
            // First third: Green to Orange
            uint32_t blend = (position_ratio * 1000) / 333; // 0-1000 within this third
            color.r = (COLOR_MEDIUM.r * blend) / 1000;
            color.g = COLOR_FAR.g - ((COLOR_FAR.g - COLOR_MEDIUM.g) * blend) / 1000;
            color.b = 0;
        } else if (position_ratio < 666) {
            // Second third: Orange to Red
            uint32_t blend = ((position_ratio - 333) * 1000) / 333; // 0-1000 within this third
            color.r = COLOR_MEDIUM.r + ((COLOR_CLOSE.r - COLOR_MEDIUM.r) * blend) / 1000;
            color.g = COLOR_MEDIUM.g - (COLOR_MEDIUM.g * blend) / 1000;
            color.b = 0;
        } else {
            // Final third: Pure Red
            color = COLOR_CLOSE;
        }
        
        // Apply brightness based on distance (closer = brighter)
        uint32_t brightness = 100 + ((900 * (LED_COUNT - i)) / LED_COUNT); // 100-1000 scale
        
        uint32_t final_r = (color.r * brightness) / 1000;
        uint32_t final_g = (color.g * brightness) / 1000;
        uint32_t final_b = (color.b * brightness) / 1000;
        
        // Scale down to 0-255 range for WS2812B
        ws2812b_set_led(i, 
            (final_r * 255) / 1000,
            (final_g * 255) / 1000,
            (final_b * 255) / 1000);
    }
    
    // Update the LED strip
    ws2812b_show();
}

void LedProximitySystem::performSelfTest() {
    _self_test_passed = true;
    
    // Test 1: LED strip initialization
    ws2812b_clear();
    
    // Test 2: Set a few test LEDs
    for (uint32_t i = 0; i < 5 && i < LED_COUNT; ++i) {
        ws2812b_set_led(i, 50, 50, 50); // Dim white
    }
    ws2812b_show();
    
    // Brief delay for visual confirmation
    // Simple delay loop (not precise, but adequate for demo)
    for (volatile uint32_t i = 0; i < 100000; ++i) {
        // Simple delay
    }
    
    // Test 3: Clear LEDs
    ws2812b_clear();
    
    // Test 4: Basic HC-SR04 sensor test
    int32_t test_distance = hcsr04_measure_cm();
    if (test_distance < 0) {
        _self_test_passed = false;
    }
}

bool LedProximitySystem::validateConfiguration() {
    // Validate LED count
    if (LED_COUNT == 0 || LED_COUNT > 1000) {
        return false;
    }
    
    // Validate distance range
    if (DIST_MIN_CM >= DIST_MAX_CM || DIST_MIN_CM < 0 || DIST_MAX_CM > 500) {
        return false;
    }
    
    // Validate update interval
    if (UPDATE_INTERVAL_MS < 10 || UPDATE_INTERVAL_MS > 10000) {
        return false;
    }
    
    // Platform-specific pin validation
#ifdef OPENBSW_PLATFORM_RP2040
    // RP2040 GPIO pins should be in valid range (0-29)
    if (LED_DATA_PIN > 29 || HCSR04_TRIGGER_PIN > 29 || HCSR04_ECHO_PIN > 29) {
        return false;
    }
    if (HCSR04_TRIGGER_PIN == HCSR04_ECHO_PIN || 
        LED_DATA_PIN == HCSR04_TRIGGER_PIN || 
        LED_DATA_PIN == HCSR04_ECHO_PIN) {
        return false;
    }
#elif defined(OPENBSW_PLATFORM_S32K148EVB)
    // S32K148 specific validation
    // Add specific pin validation for S32K148 if needed
#endif
    
    return true;
}

} // namespace systems