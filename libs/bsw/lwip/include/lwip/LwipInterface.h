// Copyright 2024 Accenture.

#pragma once

#include <platform/estdint.h>

namespace lwip
{

/**
 * Basic lwIP configuration for automotive embedded systems.
 * This provides minimal lwIP functionality optimized for memory usage.
 */
class LwipConfig
{
public:
    // Memory configuration
    static constexpr uint16_t MAX_PACKET_SIZE = 1500U;
    static constexpr uint8_t NUM_PACKET_BUFFERS = 4U;
    static constexpr uint16_t TCP_MSS = 536U;
    
    // Network configuration
    static constexpr uint8_t MAX_CONNECTIONS = 4U;
    static constexpr uint16_t DEFAULT_PORT = 13400U; // DoIP port
    
    // Timing configuration
    static constexpr uint32_t DHCP_TIMEOUT_MS = 10000U;
    static constexpr uint32_t TCP_TIMEOUT_MS = 5000U;
};

/**
 * lwIP initialization and basic network interface management.
 */
class LwipInterface
{
public:
    enum class ErrorCode : uint8_t
    {
        OK,
        INIT_FAILED,
        NETWORK_DOWN,
        MEMORY_ERROR,
        TIMEOUT_ERROR
    };

    /**
     * Initialize lwIP stack.
     * @return ErrorCode indicating success or failure
     */
    static ErrorCode init();

    /**
     * Shutdown lwIP stack.
     */
    static void shutdown();

    /**
     * Process lwIP stack - should be called periodically.
     */
    static void process();

    /**
     * Check if network interface is up.
     * @return true if network is available
     */
    static bool isNetworkUp();

private:
    static bool _initialized;
    static bool _networkUp;
};

} // namespace lwip