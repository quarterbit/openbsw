// Copyright 2024 Accenture.

#pragma once

#include <platform/estdint.h>

namespace tsn
{

/**
 * IEEE 802.1AS Precision Time Protocol (gPTP) types and constants.
 */

/**
 * Time interval type for gPTP (in nanoseconds).
 */
using TimeInterval = int64_t;

/**
 * Timestamp type for gPTP.
 */
struct GptpTimestamp
{
    uint64_t secondsField;
    uint32_t nanosecondsField;
    
    /**
     * Convert to nanoseconds since epoch.
     */
    uint64_t toNanoseconds() const
    {
        return (secondsField * 1000000000ULL) + nanosecondsField;
    }
    
    /**
     * Create from nanoseconds since epoch.
     */
    static GptpTimestamp fromNanoseconds(uint64_t nanoseconds)
    {
        GptpTimestamp ts;
        ts.secondsField = nanoseconds / 1000000000ULL;
        ts.nanosecondsField = static_cast<uint32_t>(nanoseconds % 1000000000ULL);
        return ts;
    }
};

/**
 * Clock Identity type (8 bytes).
 */
struct ClockIdentity
{
    uint8_t id[8];
    
    bool operator==(const ClockIdentity& other) const
    {
        for (int i = 0; i < 8; ++i)
        {
            if (id[i] != other.id[i]) return false;
        }
        return true;
    }
};

/**
 * Port Identity type.
 */
struct PortIdentity
{
    ClockIdentity clockIdentity;
    uint16_t portNumber;
    
    bool operator==(const PortIdentity& other) const
    {
        return (clockIdentity == other.clockIdentity) && 
               (portNumber == other.portNumber);
    }
};

/**
 * gPTP message types.
 */
enum class GptpMessageType : uint8_t
{
    SYNC = 0x0,
    DELAY_REQ = 0x1,
    PDELAY_REQ = 0x2,
    PDELAY_RESP = 0x3,
    FOLLOW_UP = 0x8,
    DELAY_RESP = 0x9,
    PDELAY_RESP_FOLLOW_UP = 0xA,
    ANNOUNCE = 0xB,
    SIGNALING = 0xC,
    MANAGEMENT = 0xD
};

/**
 * gPTP clock state.
 */
enum class GptpClockState : uint8_t
{
    INITIALIZING = 0,
    FAULTY = 1,
    DISABLED = 2,
    LISTENING = 3,
    PRE_MASTER = 4,
    MASTER = 5,
    PASSIVE = 6,
    UNCALIBRATED = 7,
    SLAVE = 8
};

/**
 * Time synchronization accuracy.
 */
enum class TimeAccuracy : uint8_t
{
    ACCURATE_TO_25NS = 0x20,
    ACCURATE_TO_100NS = 0x21,
    ACCURATE_TO_250NS = 0x22,
    ACCURATE_TO_1US = 0x23,
    ACCURATE_TO_2_5US = 0x24,
    ACCURATE_TO_10US = 0x25,
    ACCURATE_TO_25US = 0x26,
    ACCURATE_TO_100US = 0x27,
    ACCURATE_TO_250US = 0x28,
    ACCURATE_TO_1MS = 0x29,
    ACCURATE_TO_2_5MS = 0x2A,
    ACCURATE_TO_10MS = 0x2B,
    ACCURATE_TO_25MS = 0x2C,
    ACCURATE_TO_100MS = 0x2D,
    ACCURATE_TO_250MS = 0x2E,
    ACCURATE_TO_1S = 0x2F,
    ACCURATE_TO_10S = 0x30,
    ACCURACY_UNKNOWN = 0xFE
};

/**
 * gPTP Configuration Constants.
 */
class GptpConstants
{
public:
    // Timing intervals
    static constexpr TimeInterval SYNC_INTERVAL_NS = 125000000LL;      // 125ms
    static constexpr TimeInterval PDELAY_INTERVAL_NS = 1000000000LL;   // 1s
    static constexpr TimeInterval ANNOUNCE_INTERVAL_NS = 1000000000LL; // 1s
    
    // Message limits
    static constexpr uint8_t MAX_HOPS = 255U;
    static constexpr uint16_t SEQUENCE_ID_WRAP = 65536U;
    
    // Default values
    static constexpr uint8_t DEFAULT_DOMAIN_NUMBER = 0U;
    static constexpr int8_t DEFAULT_LOG_SYNC_INTERVAL = -3; // 125ms
    static constexpr int8_t DEFAULT_LOG_PDELAY_REQ_INTERVAL = 0; // 1s
    
    // Ethernet specific
    static constexpr uint16_t GPTP_ETHERTYPE = 0x88F7U;
    static constexpr uint8_t GPTP_MULTICAST_MAC[6] = {0x01, 0x80, 0xC2, 0x00, 0x00, 0x0E};

private:
    GptpConstants() = delete; // Static class
};

} // namespace tsn