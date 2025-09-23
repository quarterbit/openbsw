// Copyright 2024 Accenture.

#pragma once

#include <cstdint>
#include "bsp/Bsp.h"

namespace bios
{

/**
 * ADC configuration for RP2040
 */
class Adc12BitConfiguration
{
public:
    // RP2040 ADC Configuration placeholders
    static constexpr uint16_t RESOLUTION_BITS = 12;
    static constexpr uint16_t MAX_VALUE = (1 << RESOLUTION_BITS) - 1;
    static constexpr uint16_t VREF_MV = 3300; // 3.3V reference
};

/**
 * Analog Input interface for RP2040
 */
class AnalogInput
{
public:
    // RP2040 ADC Channel Definitions
    enum AnalogInputId
    {
        ADC_CHANNEL_0 = 0,  // GPIO26
        ADC_CHANNEL_1 = 1,  // GPIO27
        ADC_CHANNEL_2 = 2,  // GPIO28
        TEMPERATURE_SENSOR = 4,  // Internal temperature sensor
        
        // Alias for demo compatibility
        AiRP2040_ADC0 = ADC_CHANNEL_0,
        PORT_UNAVAILABLE = 255
    };
    
    /**
     * Get analog input value from channel
     */
    static bsp::BspReturnCode get(uint16_t channel, uint16_t& value);
    
    /**
     * Initialize ADC system
     */
    static void init();

private:
    static bool fInitialized;
};

} // namespace bios