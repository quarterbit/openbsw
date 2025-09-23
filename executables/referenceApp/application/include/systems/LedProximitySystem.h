// Copyright 2024 Accenture.

#pragma once

#include <async/Async.h>
#include <async/IRunnable.h>
#include <lifecycle/AsyncLifecycleComponent.h>

namespace systems {

class LedProximitySystem 
    : public ::lifecycle::AsyncLifecycleComponent
    , private ::async::IRunnable
{
public:
    explicit LedProximitySystem(::async::ContextType context);
    
    LedProximitySystem(LedProximitySystem const&) = delete;
    LedProximitySystem& operator=(LedProximitySystem const&) = delete;

    void init() override;
    void run() override;
    void shutdown() override;

private:
    // Implementation of IRunnable::execute()
    void execute() override;
    
    // LED proximity functionality
    void updateLeds();
    int32_t mapDistanceToLeds(int32_t distance_cm);
    void renderLeds(uint32_t leds_on);
    void performSelfTest();
    bool validateConfiguration();
    
    ::async::ContextType _context;
    ::async::TimeoutType _timeout;
    
    // Configuration constants
    static constexpr uint32_t LED_COUNT = 144;
    static constexpr int32_t DIST_MIN_CM = 1;
    static constexpr int32_t DIST_MAX_CM = 100;
    static constexpr uint32_t UPDATE_INTERVAL_MS = 100;
    
    // Enhanced mapping modes
    enum class MappingMode {
        LINEAR = 0,      // Linear distance mapping
        EXPONENTIAL,     // Exponential mapping for better far-range sensitivity
        ZONES           // Zone-based mapping with distinct regions
    };
    
    MappingMode _mapping_mode = MappingMode::LINEAR;
    
    // Smooth transition state
    uint32_t _current_leds_on = 0;  // Current number of LEDs on
    uint32_t _target_leds_on = 0;   // Target number of LEDs on
    uint32_t _transition_step = 0;  // Current step in transition
    
    // Configuration validation state
    bool _configuration_valid = false;
    bool _self_test_passed = false;
    
    // LED strip colors (RGB values scaled to 1000 for integer math)
    struct Color {
        uint32_t r, g, b;
    };
    
    static constexpr Color COLOR_CLOSE = {1000, 0, 0};      // Red for close
    static constexpr Color COLOR_MEDIUM = {1000, 500, 0};   // Orange for medium
    static constexpr Color COLOR_FAR = {0, 1000, 0};        // Green for far
};

} // namespace systems