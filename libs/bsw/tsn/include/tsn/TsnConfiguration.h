// Copyright 2024 Accenture.

#pragma once

#include "tsn/TsnTypes.h"
#include <platform/estdint.h>

namespace tsn
{

/**
 * Configuration structure for a TSN stream.
 */
struct TsnStreamConfig
{
    TsnStreamClass streamClass;
    VlanId vlanId;
    TsnPriority priority;
    BandwidthBps bandwidth;
    LatencyUs maxLatency;
    FrameSizeBytes frameSize;
    
    // Stream identification
    StreamId streamId;
    
    // Advanced configuration
    bool useShaping;
    bool usePolicing;
    uint8_t redundancyLevel;
};

/**
 * TSN Configuration constants and parameters.
 */
class TsnConfiguration
{
public:
    // Class A Stream Parameters (IEEE 802.1Q-2018)
    static constexpr LatencyUs CLASS_A_MAX_LATENCY_US = 2000U;      // 2ms
    static constexpr TsnPriority CLASS_A_PRIORITY = TsnPriority::VOICE;
    static constexpr BandwidthBps CLASS_A_MAX_BANDWIDTH_BPS = 125000000U; // 125 Mbps
    
    // Class B Stream Parameters  
    static constexpr LatencyUs CLASS_B_MAX_LATENCY_US = 50000U;     // 50ms
    static constexpr TsnPriority CLASS_B_PRIORITY = TsnPriority::VIDEO;
    static constexpr BandwidthBps CLASS_B_MAX_BANDWIDTH_BPS = 250000000U; // 250 Mbps
    
    // General TSN Parameters
    static constexpr uint16_t DEFAULT_VLAN_ID = 100U;
    static constexpr FrameSizeBytes MIN_FRAME_SIZE = 64U;
    static constexpr FrameSizeBytes MAX_FRAME_SIZE = 1518U;
    static constexpr uint8_t MAX_STREAMS_PER_CLASS = 16U;
    
    // Memory Configuration for Embedded Systems
    static constexpr uint8_t MAX_TOTAL_STREAMS = 32U;
    static constexpr uint16_t STREAM_BUFFER_SIZE = 2048U;
    static constexpr uint8_t MAX_PENDING_FRAMES = 8U;
    
    // Timing Configuration
    static constexpr uint32_t GUARD_BAND_NS = 12960U;              // Guard band in nanoseconds
    static constexpr uint32_t CYCLE_TIME_US = 125U;                // 125 microseconds
    static constexpr uint16_t OBSERVATION_INTERVAL_MS = 125U;      // 125 milliseconds
    
    /**
     * Get default configuration for a TSN stream class.
     * @param streamClass The TSN stream class
     * @param config Output parameter for the configuration
     * @return TsnErrorCode indicating success or failure
     */
    static TsnErrorCode getDefaultStreamConfig(
        TsnStreamClass streamClass, 
        TsnStreamConfig& config);
    
    /**
     * Validate a TSN stream configuration.
     * @param config The configuration to validate
     * @return TsnErrorCode indicating validation result
     */
    static TsnErrorCode validateStreamConfig(const TsnStreamConfig& config);
    
    /**
     * Get the priority for a given stream class.
     * @param streamClass The TSN stream class
     * @return The corresponding TSN priority
     */
    static TsnPriority getClassPriority(TsnStreamClass streamClass);
    
    /**
     * Get the maximum latency for a given stream class.
     * @param streamClass The TSN stream class
     * @return The maximum latency in microseconds
     */
    static LatencyUs getClassMaxLatency(TsnStreamClass streamClass);

private:
    TsnConfiguration() = delete; // Static class
};

} // namespace tsn