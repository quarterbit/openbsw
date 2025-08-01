// Copyright 2024 Accenture.

#include "ethernet/EthernetTransportLayer.h"
#include <transport/TransportLogger.h>

namespace ethernet
{

EthernetTransportLayer::EthernetTransportLayer(uint8_t busId)
: AbstractTransportLayer(busId)
, _initialized(false)
, _shutdownDelegate()
, _messagesSent(0U)
, _messagesReceived(0U)
, _sendErrors(0U)
{
}

::transport::AbstractTransportLayer::ErrorCode EthernetTransportLayer::init()
{
    if (_initialized)
    {
        return ErrorCode::TP_OK;
    }

    // Initialize lwIP if not already done
    auto lwipResult = ::lwip::LwipInterface::init();
    if (lwipResult != ::lwip::LwipInterface::ErrorCode::OK)
    {
        ::transport::TransportLogger::error(
            getBusId(), 
            "EthernetTransportLayer::init() - lwIP initialization failed");
        return ErrorCode::TP_GENERAL_ERROR;
    }

    // Call base class initialization
    auto result = AbstractTransportLayer::init();
    if (result != ErrorCode::TP_OK)
    {
        return result;
    }

    _initialized = true;
    
    ::transport::TransportLogger::debug(
        getBusId(), 
        "EthernetTransportLayer::init() - Ethernet transport layer initialized");
    
    return ErrorCode::TP_OK;
}

bool EthernetTransportLayer::shutdown(ShutdownDelegate delegate)
{
    if (!_initialized)
    {
        return SYNC_SHUTDOWN_COMPLETE;
    }

    _shutdownDelegate = delegate;
    _initialized = false;

    ::transport::TransportLogger::debug(
        getBusId(), 
        "EthernetTransportLayer::shutdown() - Ethernet transport layer shutdown");

    // For now, we perform synchronous shutdown
    // In a full implementation, this might involve closing network connections asynchronously
    
    // Notify delegate that shutdown is complete
    if (_shutdownDelegate)
    {
        _shutdownDelegate(*this);
    }

    return SYNC_SHUTDOWN_COMPLETE;
}

::transport::AbstractTransportLayer::ErrorCode EthernetTransportLayer::send(
    ::transport::TransportMessage& transportMessage,
    ::transport::ITransportMessageProcessedListener* pNotificationListener)
{
    if (!_initialized)
    {
        ::transport::TransportLogger::error(
            getBusId(), 
            "EthernetTransportLayer::send() - Transport layer not initialized");
        return ErrorCode::TP_GENERAL_ERROR;
    }

    if (!::lwip::LwipInterface::isNetworkUp())
    {
        ::transport::TransportLogger::error(
            getBusId(), 
            "EthernetTransportLayer::send() - Network is down");
        _sendErrors++;
        return ErrorCode::TP_SEND_FAIL;
    }

    // Basic validation
    if (transportMessage.getSize() == 0U)
    {
        ::transport::TransportLogger::error(
            getBusId(), 
            "EthernetTransportLayer::send() - Empty message");
        return ErrorCode::TP_MESSAGE_INCOMPLETE;
    }

    if (transportMessage.getSize() > EthernetConfiguration::MAX_MESSAGE_SIZE)
    {
        ::transport::TransportLogger::error(
            getBusId(), 
            "EthernetTransportLayer::send() - Message too large");
        return ErrorCode::TP_MESSAGE_INCOMPLETE;
    }

    // TODO: Implement actual Ethernet/UDP/TCP sending
    // For now, simulate successful send
    
    ::transport::TransportLogger::debug(
        getBusId(), 
        "EthernetTransportLayer::send() - Sending message of size %u", 
        static_cast<unsigned>(transportMessage.getSize()));

    _messagesSent++;

    // Simulate immediate successful completion
    if (pNotificationListener != nullptr)
    {
        pNotificationListener->transportMessageProcessed(
            transportMessage, 
            ::transport::ITransportMessageProcessedListener::ProcessingResult::PROCESSED_OK);
    }

    return ErrorCode::TP_OK;
}

void EthernetTransportLayer::cyclicTask()
{
    if (!_initialized)
    {
        return;
    }

    // Process lwIP stack
    ::lwip::LwipInterface::process();

    // Process received messages
    processReceivedMessages();

    // Process pending send operations
    processPendingSends();
}

void EthernetTransportLayer::processReceivedMessages()
{
    // TODO: Implement message reception from Ethernet/UDP/TCP
    // This would involve:
    // 1. Checking for received packets in lwIP
    // 2. Parsing transport messages from received data
    // 3. Calling getProvidingListenerHelper().messageReceived()
}

void EthernetTransportLayer::processPendingSends()
{
    // TODO: Implement processing of pending send operations
    // This would involve:
    // 1. Checking status of ongoing send operations
    // 2. Handling timeouts and retransmissions
    // 3. Notifying listeners of completion
}

} // namespace ethernet