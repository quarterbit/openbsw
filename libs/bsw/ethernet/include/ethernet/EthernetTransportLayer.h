// Copyright 2024 Accenture.

#pragma once

#include "ethernet/EthernetConfiguration.h"
#include <transport/AbstractTransportLayer.h>
#include <transport/TransportMessage.h>
#include <transport/ITransportMessageProcessedListener.h>
#include <lwip/LwipInterface.h>
#include <platform/estdint.h>

namespace ethernet
{

/**
 * Ethernet transport layer implementation.
 * 
 * This class provides Ethernet communication capabilities by extending
 * the AbstractTransportLayer interface and using lwIP for network operations.
 */
class EthernetTransportLayer : public ::transport::AbstractTransportLayer
{
public:
    /**
     * Constructor.
     * @param busId The transport layer's bus identifier
     */
    explicit EthernetTransportLayer(uint8_t busId);

    /**
     * Destructor.
     */
    ~EthernetTransportLayer() override = default;

    /**
     * Initialize the Ethernet transport layer.
     * @return ErrorCode indicating success or failure
     */
    ErrorCode init() override;

    /**
     * Shutdown the Ethernet transport layer.
     * @param delegate Callback for asynchronous shutdown completion
     * @return true if shutdown completed synchronously, false if asynchronous
     */
    bool shutdown(ShutdownDelegate delegate) override;

    /**
     * Send a transport message over Ethernet.
     * @param transportMessage The message to send
     * @param pNotificationListener Optional listener for send completion notification
     * @return ErrorCode indicating the result of the send operation
     */
    ErrorCode send(
        ::transport::TransportMessage& transportMessage,
        ::transport::ITransportMessageProcessedListener* pNotificationListener) override;

    /**
     * Process periodic Ethernet operations.
     * Should be called regularly to handle network operations.
     */
    void cyclicTask();

private:
    /**
     * Internal method to process received messages.
     */
    void processReceivedMessages();

    /**
     * Internal method to handle pending send operations.
     */
    void processPendingSends();

    bool _initialized;
    ShutdownDelegate _shutdownDelegate;
    
    // Statistics and state tracking
    uint32_t _messagesSent;
    uint32_t _messagesReceived;
    uint32_t _sendErrors;
};

} // namespace ethernet