// Copyright 2024 Accenture.

#pragma once

#include "systems/TransportSystem.h"

#include <ethernet/EthernetTransportLayer.h>
#include <lwip/LwipInterface.h>
#include <busid/BusId.h>
#include <lifecycle/ILifecycleComponent.h>
#include <async/Async.h>
#include <etl/singleton.h>

namespace demo
{

/**
 * Ethernet demonstration system.
 * 
 * This system demonstrates Ethernet communication capabilities by:
 * - Initializing the lwIP stack
 * - Creating an Ethernet transport layer
 * - Registering it with the transport router
 * - Providing basic network diagnostics
 */
class EthernetDemoSystem 
: public ::lifecycle::ILifecycleComponent
, public ::etl::singleton<EthernetDemoSystem>
{
public:
    /**
     * Constructor.
     * @param transitionContext Context for lifecycle transitions
     */
    explicit EthernetDemoSystem(::async::ContextType transitionContext);

    // ILifecycleComponent interface
    char const* getName() const override;
    void init() override;
    void run() override;
    void shutdown() override;
    void dump() const override;

    /**
     * Get the Ethernet transport layer instance.
     * @return Reference to the Ethernet transport layer
     */
    ::ethernet::EthernetTransportLayer& getEthernetTransportLayer();

    /**
     * Perform periodic processing of Ethernet operations.
     */
    void cyclicTask();

    /**
     * Get network statistics.
     * @param messagesSent Output parameter for sent message count
     * @param messagesReceived Output parameter for received message count
     */
    void getNetworkStatistics(uint32_t& messagesSent, uint32_t& messagesReceived) const;

private:
    ::ethernet::EthernetTransportLayer _ethernetTransportLayer;
    bool _initialized;
    uint32_t _cyclicTaskCounter;
};

} // namespace demo