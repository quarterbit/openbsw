// Copyright 2024 Accenture.

#include "systems/EthernetDemoSystem.h"
#include "systems/TransportSystem.h"

#include <transport/TransportLogger.h>

namespace demo
{

EthernetDemoSystem::EthernetDemoSystem(::async::ContextType transitionContext)
: ::etl::singleton_base<EthernetDemoSystem>(*this)
, _ethernetTransportLayer(::busid::ETHERNET_0)
, _initialized(false)
, _cyclicTaskCounter(0U)
{
    // Tell the lifecycle manager in which context to execute init/run/shutdown
    setTransitionContext(transitionContext);
}

char const* EthernetDemoSystem::getName() const
{
    return "EthernetDemo";
}

void EthernetDemoSystem::init()
{
    ::transport::TransportLogger::debug(
        ::busid::ETHERNET_0,
        "EthernetDemoSystem::init() - Initializing Ethernet demo system");

    // Initialize lwIP stack
    auto lwipResult = ::lwip::LwipInterface::init();
    if (lwipResult != ::lwip::LwipInterface::ErrorCode::OK)
    {
        ::transport::TransportLogger::error(
            ::busid::ETHERNET_0,
            "EthernetDemoSystem::init() - Failed to initialize lwIP");
        transitionDone();
        return;
    }

    // Initialize Ethernet transport layer
    auto result = _ethernetTransportLayer.init();
    if (result != ::transport::AbstractTransportLayer::ErrorCode::TP_OK)
    {
        ::transport::TransportLogger::error(
            ::busid::ETHERNET_0,
            "EthernetDemoSystem::init() - Failed to initialize Ethernet transport layer");
        transitionDone();
        return;
    }

    // Add transport layer to the router
    ::transport::TransportSystem::getInstance().addTransportLayer(_ethernetTransportLayer);

    _initialized = true;

    ::transport::TransportLogger::info(
        ::busid::ETHERNET_0,
        "EthernetDemoSystem::init() - Ethernet demo system initialized successfully");

    // Inform the lifecycle manager that the transition has been completed
    transitionDone();
}

void EthernetDemoSystem::run()
{
    ::transport::TransportLogger::debug(
        ::busid::ETHERNET_0,
        "EthernetDemoSystem::run() - Ethernet demo system running");

    // Inform the lifecycle manager that the transition has been completed
    transitionDone();
}

void EthernetDemoSystem::shutdown()
{
    if (_initialized)
    {
        ::transport::TransportLogger::debug(
            ::busid::ETHERNET_0,
            "EthernetDemoSystem::shutdown() - Shutting down Ethernet demo system");

        // Remove transport layer from router
        ::transport::TransportSystem::getInstance().removeTransportLayer(_ethernetTransportLayer);

        // Shutdown transport layer
        _ethernetTransportLayer.shutdown(nullptr);

        // Shutdown lwIP
        ::lwip::LwipInterface::shutdown();

        _initialized = false;

        ::transport::TransportLogger::info(
            ::busid::ETHERNET_0,
            "EthernetDemoSystem::shutdown() - Ethernet demo system shutdown complete");
    }

    // Inform the lifecycle manager that the transition has been completed
    transitionDone();
}

void EthernetDemoSystem::dump() const
{
    ::transport::TransportLogger::info(
        ::busid::ETHERNET_0,
        "EthernetDemoSystem Status:");
    ::transport::TransportLogger::info(
        ::busid::ETHERNET_0,
        "  Initialized: %s", _initialized ? "true" : "false");
    ::transport::TransportLogger::info(
        ::busid::ETHERNET_0,
        "  Network Up: %s", ::lwip::LwipInterface::isNetworkUp() ? "true" : "false");
    ::transport::TransportLogger::info(
        ::busid::ETHERNET_0,
        "  Cyclic Task Counter: %u", static_cast<unsigned>(_cyclicTaskCounter));
}

::ethernet::EthernetTransportLayer& EthernetDemoSystem::getEthernetTransportLayer()
{
    return _ethernetTransportLayer;
}

void EthernetDemoSystem::cyclicTask()
{
    if (!_initialized)
    {
        return;
    }

    // Process Ethernet transport layer
    _ethernetTransportLayer.cyclicTask();

    _cyclicTaskCounter++;

    // Log status every 1000 cycles (for debugging)
    if ((_cyclicTaskCounter % 1000U) == 0U)
    {
        ::transport::TransportLogger::debug(
            ::busid::ETHERNET_0,
            "EthernetDemoSystem::cyclicTask() - Processed %u cycles",
            static_cast<unsigned>(_cyclicTaskCounter));
    }
}

void EthernetDemoSystem::getNetworkStatistics(uint32_t& messagesSent, uint32_t& messagesReceived) const
{
    // In a full implementation, these would come from the transport layer
    // For now, provide placeholder values
    messagesSent = _cyclicTaskCounter / 10U; // Simulate some activity
    messagesReceived = _cyclicTaskCounter / 20U;
}

} // namespace demo