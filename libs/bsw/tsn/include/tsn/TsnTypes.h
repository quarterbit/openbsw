// Copyright 2024 Accenture.

#pragma once

#include <platform/estdint.h>

namespace tsn
{

/**
 * TSN Stream Classes as defined in IEEE 802.1Q.
 */
enum class TsnStreamClass : uint8_t
{
    CLASS_A = 0,     // Class A: Low latency, high priority
    CLASS_B = 1,     // Class B: Medium latency, medium priority  
    BEST_EFFORT = 2  // Best effort: No QoS guarantees
};

/**
 * VLAN Priority Code Point (PCP) values for TSN streams.
 */
enum class TsnPriority : uint8_t
{
    BEST_EFFORT_1 = 1,
    BEST_EFFORT_0 = 0,
    EXCELLENT_EFFORT = 2,
    CRITICAL_APPS = 3,
    VIDEO = 4,
    VOICE = 5,
    INTERNETWORK_CONTROL = 6,
    NETWORK_CONTROL = 7
};

/**
 * TSN Stream ID type.
 */
using StreamId = uint32_t;

/**
 * TSN bandwidth in bits per second.
 */
using BandwidthBps = uint32_t;

/**
 * TSN latency in microseconds.
 */
using LatencyUs = uint32_t;

/**
 * Frame size in bytes.
 */
using FrameSizeBytes = uint16_t;

/**
 * VLAN ID type.
 */
using VlanId = uint16_t;

/**
 * Error codes specific to TSN operations.
 */
enum class TsnErrorCode : uint8_t
{
    OK = 0,
    INVALID_STREAM_CLASS,
    BANDWIDTH_EXCEEDED,
    LATENCY_NOT_ACHIEVABLE,
    INVALID_VLAN_ID,
    STREAM_NOT_FOUND,
    INSUFFICIENT_RESOURCES,
    GENERAL_ERROR
};

} // namespace tsn