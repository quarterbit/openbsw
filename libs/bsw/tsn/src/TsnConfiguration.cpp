// Copyright 2024 Accenture.

#include "tsn/TsnConfiguration.h"

namespace tsn
{

TsnErrorCode TsnConfiguration::getDefaultStreamConfig(
    TsnStreamClass streamClass, 
    TsnStreamConfig& config)
{
    config.streamClass = streamClass;
    config.streamId = 0; // Will be assigned by system
    config.useShaping = true;
    config.usePolicing = false;
    config.redundancyLevel = 0;
    
    switch (streamClass)
    {
        case TsnStreamClass::CLASS_A:
            config.vlanId = DEFAULT_VLAN_ID;
            config.priority = CLASS_A_PRIORITY;
            config.bandwidth = 10000000U; // 10 Mbps default
            config.maxLatency = CLASS_A_MAX_LATENCY_US;
            config.frameSize = 1500U;
            break;
            
        case TsnStreamClass::CLASS_B:
            config.vlanId = DEFAULT_VLAN_ID + 1;
            config.priority = CLASS_B_PRIORITY;
            config.bandwidth = 50000000U; // 50 Mbps default
            config.maxLatency = CLASS_B_MAX_LATENCY_US;
            config.frameSize = 1500U;
            break;
            
        case TsnStreamClass::BEST_EFFORT:
            config.vlanId = DEFAULT_VLAN_ID + 2;
            config.priority = TsnPriority::BEST_EFFORT_0;
            config.bandwidth = 1000000U; // 1 Mbps default
            config.maxLatency = 0; // No latency guarantee
            config.frameSize = 1500U;
            config.useShaping = false;
            break;
            
        default:
            return TsnErrorCode::INVALID_STREAM_CLASS;
    }
    
    return TsnErrorCode::OK;
}

TsnErrorCode TsnConfiguration::validateStreamConfig(const TsnStreamConfig& config)
{
    // Validate stream class
    if (config.streamClass != TsnStreamClass::CLASS_A &&
        config.streamClass != TsnStreamClass::CLASS_B &&
        config.streamClass != TsnStreamClass::BEST_EFFORT)
    {
        return TsnErrorCode::INVALID_STREAM_CLASS;
    }
    
    // Validate VLAN ID
    if (config.vlanId == 0 || config.vlanId > 4095)
    {
        return TsnErrorCode::INVALID_VLAN_ID;
    }
    
    // Validate frame size
    if (config.frameSize < MIN_FRAME_SIZE || config.frameSize > MAX_FRAME_SIZE)
    {
        return TsnErrorCode::GENERAL_ERROR;
    }
    
    // Validate class-specific parameters
    switch (config.streamClass)
    {
        case TsnStreamClass::CLASS_A:
            if (config.bandwidth > CLASS_A_MAX_BANDWIDTH_BPS)
            {
                return TsnErrorCode::BANDWIDTH_EXCEEDED;
            }
            if (config.maxLatency > CLASS_A_MAX_LATENCY_US)
            {
                return TsnErrorCode::LATENCY_NOT_ACHIEVABLE;
            }
            break;
            
        case TsnStreamClass::CLASS_B:
            if (config.bandwidth > CLASS_B_MAX_BANDWIDTH_BPS)
            {
                return TsnErrorCode::BANDWIDTH_EXCEEDED;
            }
            if (config.maxLatency > CLASS_B_MAX_LATENCY_US)
            {
                return TsnErrorCode::LATENCY_NOT_ACHIEVABLE;
            }
            break;
            
        case TsnStreamClass::BEST_EFFORT:
            // No specific bandwidth or latency limits for best effort
            break;
    }
    
    return TsnErrorCode::OK;
}

TsnPriority TsnConfiguration::getClassPriority(TsnStreamClass streamClass)
{
    switch (streamClass)
    {
        case TsnStreamClass::CLASS_A:
            return CLASS_A_PRIORITY;
        case TsnStreamClass::CLASS_B:
            return CLASS_B_PRIORITY;
        case TsnStreamClass::BEST_EFFORT:
        default:
            return TsnPriority::BEST_EFFORT_0;
    }
}

LatencyUs TsnConfiguration::getClassMaxLatency(TsnStreamClass streamClass)
{
    switch (streamClass)
    {
        case TsnStreamClass::CLASS_A:
            return CLASS_A_MAX_LATENCY_US;
        case TsnStreamClass::CLASS_B:
            return CLASS_B_MAX_LATENCY_US;
        case TsnStreamClass::BEST_EFFORT:
        default:
            return 0; // No latency guarantee
    }
}

} // namespace tsn