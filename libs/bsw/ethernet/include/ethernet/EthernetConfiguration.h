// Copyright 2024 Accenture.

#pragma once

#include <transport/AbstractTransportLayer.h>
#include <lwip/LwipInterface.h>
#include <platform/estdint.h>

namespace ethernet
{

/**
 * Ethernet-specific configuration parameters.
 */
class EthernetConfiguration
{
public:
    // Network configuration
    static constexpr uint16_t DEFAULT_UDP_PORT = 13400U; // DoIP port
    static constexpr uint16_t DEFAULT_TCP_PORT = 13400U; // DoIP port
    static constexpr uint32_t DEFAULT_IP_ADDRESS = 0xC0A80101U; // 192.168.1.1
    static constexpr uint32_t DEFAULT_NETMASK = 0xFFFFFF00U; // 255.255.255.0
    
    // Buffer configuration
    static constexpr uint16_t MAX_MESSAGE_SIZE = 4095U; // Same as DoCanConstants
    static constexpr uint8_t MAX_PENDING_MESSAGES = 8U;
    
    // Timing configuration
    static constexpr uint32_t SEND_TIMEOUT_MS = 1000U;
    static constexpr uint32_t CONNECTION_TIMEOUT_MS = 5000U;
};

} // namespace ethernet