#include "hcsr04.h"
#include "ws2812b.h"
#include "lifecycle/AsyncLifecycleComponent.h"
#include "async/Async.h"
#include "async/Config.h"  // For TASK_DEMO

namespace {
    constexpr uint32_t LED_COUNT = 144;
    
    // Distance mapping configuration
    constexpr int32_t DIST_MIN_CM = 1;
    constexpr int32_t DIST_MAX_CM = 100;
    constexpr uint32_t UPDATE_INTERVAL_MS = 100;
    
    // Enhanced mapping modes
    enum class MappingMode {
        LINEAR = 0,      // Linear distance mapping
        EXPONENTIAL,     // Exponential mapping for better far-range sensitivity
        ZONES           // Zone-based mapping with distinct regions
    };
    
    constexpr MappingMode CURRENT_MAPPING_MODE = MappingMode::LINEAR;
    
    // Platform-specific pin configurations
#ifdef PLATFORM_S32K148EVB
    // S32K148EVB pin assignments (compatible with existing ioConfiguration.h)
    constexpr uint32_t LED_DATA_PIN = 78;        // PC14 - configured as GPIO output
    constexpr uint32_t HCSR04_TRIGGER_PIN = 37;  // PB5 - configured as GPIO output  
    constexpr uint32_t HCSR04_ECHO_PIN = 36;     // PB4 - configured as GPIO input
#elif defined(PLATFORM_RP2040)
    // RP2040/Pico W pin assignments (standard GPIO pins)
    constexpr uint32_t LED_DATA_PIN = 2;         // GP2 - WS2812B data pin
    constexpr uint32_t HCSR04_TRIGGER_PIN = 3;   // GP3 - HC-SR04 trigger pin
    constexpr uint32_t HCSR04_ECHO_PIN = 4;      // GP4 - HC-SR04 echo pin
#else
    #error "Please define pin assignments for your platform"
#endif

    // Enhanced distance-to-LED mapping functions
    uint32_t mapDistanceToLeds(int32_t distance_cm, MappingMode mode) {
        if (distance_cm < DIST_MIN_CM || distance_cm > DIST_MAX_CM) {
            return 0;  // Out of range
        }
        
        // Normalize distance to 0-1000 range (using integers instead of floats)
        uint32_t normalized = (1000 * (DIST_MAX_CM - distance_cm)) / (DIST_MAX_CM - DIST_MIN_CM);
        
        uint32_t mapped_value = 0;
        
        switch (mode) {
            case MappingMode::LINEAR:
                mapped_value = normalized;
                break;
                
            case MappingMode::EXPONENTIAL:
                // Exponential mapping: more sensitive to far distances  
                mapped_value = (normalized * normalized) / 1000;
                break;
                
            case MappingMode::ZONES:
                // Zone-based mapping with distinct regions
                if (normalized > 800) {
                    mapped_value = 1000;  // Very close: full intensity
                } else if (normalized > 600) {
                    mapped_value = 750;   // Close: 3/4 intensity
                } else if (normalized > 400) {
                    mapped_value = 500;   // Medium: 1/2 intensity
                } else if (normalized > 200) {
                    mapped_value = 250;   // Far: 1/4 intensity
                } else {
                    mapped_value = 100;   // Very far: minimal indication
                }
                break;
        }
        
        // Convert to LED count with bounds checking
        uint32_t led_count = (mapped_value * LED_COUNT) / 1000;
        return (led_count > LED_COUNT) ? LED_COUNT : led_count;
    }

    class LedProximityComponent 
    : public ::lifecycle::AsyncLifecycleComponent
    , public ::async::IRunnable {
    public:
        explicit LedProximityComponent(::async::ContextType context)
        : _context(context), _current_leds_on(0), _target_leds_on(0), _transition_step(0), _last_rendered_leds(0) {
            setTransitionContext(context);
        }

    protected:
        void init() override {
            // Platform-specific pin configuration validation
            bool config_valid = validateConfiguration();
            
            if (!config_valid) {
                // Configuration error - indicate with red blinking
                ws2812b_init(LED_DATA_PIN, LED_COUNT);  // Try basic init anyway
                for (int i = 0; i < 5; i++) {
                    ws2812b_clear();
                    ws2812b_set_led(0, 255, 0, 0);  // Red error
                    ws2812b_show();
                    // Note: In a real system, would use proper delay mechanism
                    for (volatile int delay = 0; delay < 100000; delay++) {}
                    ws2812b_clear();
                    ws2812b_show();
                    for (volatile int delay = 0; delay < 100000; delay++) {}
                }
                transitionDone();
                return;
            }
            
            // Initialize hardware components
            hcsr04_init(HCSR04_TRIGGER_PIN, HCSR04_ECHO_PIN);
            ws2812b_init(LED_DATA_PIN, LED_COUNT);
            ws2812b_clear();
            
            // Perform basic functionality test
            performSelfTest();
            
            transitionDone();
        }

        void run() override {
            // Schedule periodic updates using scheduleAtFixedRate
            ::async::scheduleAtFixedRate(
                _context, *this, _timeout, UPDATE_INTERVAL_MS, ::async::TimeUnit::MILLISECONDS);
            transitionDone();
        }

        void shutdown() override {
            ws2812b_clear();
            transitionDone();
        }

    private:
        // Implementation of IRunnable::execute()
        void execute() override {
            updateLeds();
        }

        ::async::ContextType _context;
        ::async::TimeoutType _timeout;
        
        // Smooth transition state
        uint32_t _current_leds_on;  // Current number of LEDs on
        uint32_t _target_leds_on;   // Target number of LEDs on
        uint32_t _transition_step;  // Current step in transition
        uint32_t _last_rendered_leds; // Last actually rendered LED count for optimization

        void updateLeds() {
            static uint32_t error_count = 0;
            static int32_t last_valid_distance = -1;
            static constexpr uint32_t TRANSITION_STEPS = 5;  // Number of steps for smooth transition
            static uint32_t log_counter = 0;  // For periodic logging
            
            int32_t distance = hcsr04_measure_cm();
            
            // Error detection and handling
            bool is_valid_reading = (distance > 0 && distance <= DIST_MAX_CM);
            
            if (!is_valid_reading) {
                error_count++;
                
                // After 3 consecutive errors, show error indication
                if (error_count >= 3) {
                    // Error indication: Red blinking pattern
                    static bool error_blink_state = false;
                    error_blink_state = !error_blink_state;
                    
                    ws2812b_clear();
                    if (error_blink_state) {
                        // Blink first 5 LEDs red to indicate sensor error
                        for (uint32_t i = 0; i < 5 && i < LED_COUNT; i++) {
                            ws2812b_set_led(i, 255, 0, 0); // Red error indication
                        }
                    }
                    ws2812b_show();
                    return;
                }
                
                // For first few errors, use last valid reading if available
                if (last_valid_distance > 0) {
                    distance = last_valid_distance;
                } else {
                    // No valid reading available, clear display
                    ws2812b_clear();
                    ws2812b_show();
                    return;
                }
            } else {
                // Valid reading, reset error count and store as last valid
                error_count = 0;
                last_valid_distance = distance;
                log_counter++;
            }
            
            // Calculate target LED count based on distance using enhanced mapping
            uint32_t new_target_leds_on = 0;
            if (distance >= DIST_MIN_CM && distance <= DIST_MAX_CM) {
                new_target_leds_on = mapDistanceToLeds(distance, CURRENT_MAPPING_MODE);
            }
            
            // Check if we need to start a new transition
            if (new_target_leds_on != _target_leds_on) {
                _target_leds_on = new_target_leds_on;
                _transition_step = 0;  // Reset transition
            }
            
            // Perform smooth transition
            if (_current_leds_on != _target_leds_on) {
                if (_transition_step < TRANSITION_STEPS) {
                    // Calculate intermediate LED count
                    int32_t diff = static_cast<int32_t>(_target_leds_on) - static_cast<int32_t>(_current_leds_on);
                    _current_leds_on += diff * (_transition_step + 1) / TRANSITION_STEPS - diff * _transition_step / TRANSITION_STEPS;
                    _transition_step++;
                } else {
                    // Transition complete
                    _current_leds_on = _target_leds_on;
                }
            }
            
            // Render LEDs with smooth transition effect
            renderLeds(_current_leds_on, _target_leds_on != _current_leds_on);
        }
        
        void renderLeds(uint32_t leds_on, bool transitioning) {
            // Basic LED strip validation
            if (leds_on > LED_COUNT) {
                leds_on = LED_COUNT;  // Clamp to maximum
            }
            
            // Performance optimization: only update if state has changed significantly
            bool needs_full_update = (leds_on != _last_rendered_leds) || transitioning;
            
            if (!needs_full_update) {
                return;  // Skip update if no change needed
            }
            
            // Optimized clearing: only clear LEDs that need to be turned off
            if (leds_on < _last_rendered_leds) {
                // Only clear the LEDs that need to be turned off
                for (uint32_t i = leds_on; i < _last_rendered_leds && i < LED_COUNT; i++) {
                    ws2812b_set_led(i, 0, 0, 0);  // Turn off LED
                }
            } else if (leds_on == 0 && _last_rendered_leds > 0) {
                // Special case: clear all LEDs when going to zero
                ws2812b_clear();
            }
            
            // Set LEDs that need to be on with simplified brightness
            for (uint32_t i = 0; i < leds_on; i++) {
                // Simplified brightness: constant color without complex calculations
                uint8_t red = 161;    // Purple color
                uint8_t green = 0;
                uint8_t blue = 255;
                
                // Optional: Simple gradient effect using integer math
                // LEDs further from base are slightly dimmer
                if (i > LED_COUNT / 2) {
                    // Dim the outer half of the strip by 25%
                    red = (red * 3) / 4;
                    blue = (blue * 3) / 4;
                }
                
                // During transition, add a subtle pulse effect using simple integer math
                if (transitioning) {
                    static uint8_t pulse_phase = 0;
                    pulse_phase = (pulse_phase + 1) % 32;
                    
                    // Simple pulse: vary brightness between 200-255
                    uint8_t pulse_factor = 200 + (55 * pulse_phase) / 32;
                    red = (red * pulse_factor) / 255;
                    blue = (blue * pulse_factor) / 255;
                }
                
                ws2812b_set_led(i, red, green, blue);
            }
            
            // Update the strip only once per render cycle
            ws2812b_show();
            
            // Track last rendered state for optimization
            _last_rendered_leds = leds_on;
        }
        
        bool validateConfiguration() {
            // Platform-specific pin validation
            #ifdef PLATFORM_S32K148EVB
            // Validate S32K148EVB pin assignments
            if (HCSR04_TRIGGER_PIN < 0 || HCSR04_TRIGGER_PIN > 15) return false;
            if (HCSR04_ECHO_PIN < 0 || HCSR04_ECHO_PIN > 15) return false;
            if (LED_DATA_PIN < 0 || LED_DATA_PIN > 15) return false;
            
            // Check for pin conflicts
            if (HCSR04_TRIGGER_PIN == HCSR04_ECHO_PIN) return false;
            if (HCSR04_TRIGGER_PIN == LED_DATA_PIN) return false;
            if (HCSR04_ECHO_PIN == LED_DATA_PIN) return false;
            
            #elif defined(PLATFORM_RP2040)
            // Validate RP2040 pin assignments
            if (HCSR04_TRIGGER_PIN < 0 || HCSR04_TRIGGER_PIN > 29) return false;
            if (HCSR04_ECHO_PIN < 0 || HCSR04_ECHO_PIN > 29) return false;
            if (LED_DATA_PIN < 0 || LED_DATA_PIN > 29) return false;
            
            // Check for pin conflicts
            if (HCSR04_TRIGGER_PIN == HCSR04_ECHO_PIN) return false;
            if (HCSR04_TRIGGER_PIN == LED_DATA_PIN) return false;
            if (HCSR04_ECHO_PIN == LED_DATA_PIN) return false;
            
            // RP2040 specific: avoid conflict with SPI/I2C default pins
            if (LED_DATA_PIN == 16 || LED_DATA_PIN == 17) return false;  // SPI0
            if (LED_DATA_PIN == 4 || LED_DATA_PIN == 5) return false;    // I2C0
            
            #else
            // For unknown platforms, assume basic validation
            if (HCSR04_TRIGGER_PIN == HCSR04_ECHO_PIN) return false;
            if (HCSR04_TRIGGER_PIN == LED_DATA_PIN) return false;
            if (HCSR04_ECHO_PIN == LED_DATA_PIN) return false;
            #endif
            
            // Validate configuration constants
            if (LED_COUNT == 0 || LED_COUNT > 500) return false;  // Reasonable LED count limits
            if (DIST_MIN_CM <= 0 || DIST_MIN_CM >= DIST_MAX_CM) return false;
            if (DIST_MAX_CM <= DIST_MIN_CM || DIST_MAX_CM > 400) return false;  // HC-SR04 max range
            if (UPDATE_INTERVAL_MS < 50 || UPDATE_INTERVAL_MS > 1000) return false;  // Reasonable update rates
            
            return true;
        }
        
        void performSelfTest() {
            // Brief LED self-test sequence
            ws2812b_clear();
            
            // Test pattern: sweep a few LEDs to verify LED strip functionality
            for (uint32_t i = 0; i < 5 && i < LED_COUNT; i++) {
                ws2812b_set_led(i, 0, 255, 0);  // Green test pattern
                ws2812b_show();
                for (volatile int delay = 0; delay < 50000; delay++) {}  // Brief delay
                ws2812b_set_led(i, 0, 0, 0);    // Turn off
            }
            
            ws2812b_clear();
            ws2812b_show();
            
            // Note: HC-SR04 self-test would require actual measurement
            // which might be unreliable during startup, so we skip it here
        }
    };

    // Global instance - this is a simplified integration
    static LedProximityComponent* g_ledProximityComponent = nullptr;
}

extern "C" {
    void app_start() {
        // Create and start the LED proximity component
        // Note: Proper integration would use the lifecycle manager
        if (g_ledProximityComponent == nullptr) {
            g_ledProximityComponent = new LedProximityComponent(TASK_DEMO);
            // The component will start its execution through the scheduleAtFixedRate in run()
        }
    }
}
