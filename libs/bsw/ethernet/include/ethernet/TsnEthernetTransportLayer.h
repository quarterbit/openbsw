// Copyright 2024 Accenture.

#pragma once

#include "ethernet/EthernetTransportLayer.h"
#include "tsn/TsnConfiguration.h"
#include "tsn/TimeSync.h"
#include <transport/AbstractTransportLayer.h>
#include <transport/TransportMessage.h>
#include <transport/ITransportMessageProcessedListener.h>
#include <platform/estdint.h>

namespace ethernet
{

/**
 * TSN-enhanced Ethernet transport layer implementation.
 * 
 * This class extends the basic EthernetTransportLayer with TSN capabilities
 * including stream classification, priority mapping, and time synchronization.
 */
class TsnEthernetTransportLayer : public EthernetTransportLayer
{
public:
    /**
     * Constructor.
     * @param busId The transport layer's bus identifier
     */
    explicit TsnEthernetTransportLayer(uint8_t busId);

    /**
     * Destructor.
     */
    ~TsnEthernetTransportLayer() override = default;

    /**
     * Initialize the TSN Ethernet transport layer.
     * @return ErrorCode indicating success or failure
     */
    ErrorCode init() override;

    /**
     * Shutdown the TSN Ethernet transport layer.
     * @param delegate Callback for asynchronous shutdown completion
     * @return true if shutdown completed synchronously, false if asynchronous
     */
    bool shutdown(ShutdownDelegate delegate) override;

    /**
     * Send a transport message with TSN stream classification.
     * @param transportMessage The message to send
     * @param pNotificationListener Optional listener for send completion notification
     * @return ErrorCode indicating the result of the send operation
     */
    ErrorCode send(
        ::transport::TransportMessage& transportMessage,
        ::transport::ITransportMessageProcessedListener* pNotificationListener) override;

    /**
     * Register a TSN stream for real-time communication.
     * @param streamClass The TSN stream class (Class A, B, or Best Effort)
     * @param bandwidth Required bandwidth in bits per second
     * @param maxLatency Maximum acceptable latency in microseconds
     * @param streamId Output parameter for the assigned stream ID
     * @return ErrorCode indicating success or failure
     */
    ErrorCode registerStream(
        ::tsn::TsnStreamClass streamClass,
        ::tsn::BandwidthBps bandwidth,
        ::tsn::LatencyUs maxLatency,
        ::tsn::StreamId& streamId);

    /**
     * Unregister a TSN stream.
     * @param streamId The stream ID to unregister
     * @return ErrorCode indicating success or failure
     */
    ErrorCode unregisterStream(::tsn::StreamId streamId);

    /**
     * Send a message on a specific TSN stream.
     * @param streamId The TSN stream ID
     * @param transportMessage The message to send
     * @param pNotificationListener Optional listener for send completion notification
     * @return ErrorCode indicating the result of the send operation
     */
    ErrorCode sendOnStream(
        ::tsn::StreamId streamId,
        ::transport::TransportMessage& transportMessage,
        ::transport::ITransportMessageProcessedListener* pNotificationListener);

    /**
     * Get TSN stream statistics.
     * @param streamId The stream ID
     * @param messagesSent Output parameter for messages sent count
     * @param messagesDropped Output parameter for messages dropped count
     * @return ErrorCode indicating success or failure
     */
    ErrorCode getStreamStatistics(
        ::tsn::StreamId streamId,
        uint32_t& messagesSent,
        uint32_t& messagesDropped);

    /**
     * Get the current time from the TSN time synchronization.
     * @param timestamp Output parameter for the current synchronized time
     * @return ErrorCode indicating success or failure
     */
    ErrorCode getCurrentTime(::tsn::GptpTimestamp& timestamp);

    /**
     * Check if TSN time synchronization is active.
     * @return True if time is synchronized, false otherwise
     */
    bool isTimeSynchronized() const;

private:
    /**
     * Internal structure for TSN stream management.
     */
    struct TsnStream
    {
        ::tsn::StreamId streamId;
        ::tsn::TsnStreamConfig config;
        bool active;
        uint32_t messagesSent;
        uint32_t messagesDropped;
        
        TsnStream() : streamId(0), config{}, active(false), messagesSent(0), messagesDropped(0) {}
    };

    static constexpr uint8_t MAX_TSN_STREAMS = 16U;

    // TSN stream management
    TsnStream _tsnStreams[MAX_TSN_STREAMS];
    uint8_t _streamCount;
    ::tsn::StreamId _nextStreamId;

    // Time synchronization
    ::tsn::TimeSync* _timeSync;
    bool _timeSyncEnabled;

    // Internal helper methods
    ErrorCode classifyMessage(
        const ::transport::TransportMessage& message,
        ::tsn::TsnStreamClass& streamClass,
        ::tsn::TsnPriority& priority);
    
    ErrorCode applyTrafficShaping(
        ::tsn::StreamId streamId,
        const ::transport::TransportMessage& message);
    
    TsnStream* findStreamById(::tsn::StreamId streamId);
    TsnStream* findFreeStream();
    
    ::tsn::TsnPriority mapClassToPriority(::tsn::TsnStreamClass streamClass);
    uint8_t mapPriorityToVlanPcp(::tsn::TsnPriority priority);
};

} // namespace ethernet