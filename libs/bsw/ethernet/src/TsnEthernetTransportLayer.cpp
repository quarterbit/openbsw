// Copyright 2024 Accenture.

#include "ethernet/TsnEthernetTransportLayer.h"
#include "tsn/GptpTypes.h"

namespace ethernet
{

TsnEthernetTransportLayer::TsnEthernetTransportLayer(uint8_t busId)
: EthernetTransportLayer(busId)
, _tsnStreams{}
, _streamCount(0U)
, _nextStreamId(1U)
, _timeSync(nullptr)
, _timeSyncEnabled(false)
{
    // Initialize TSN streams array
    for (uint8_t i = 0; i < MAX_TSN_STREAMS; ++i)
    {
        _tsnStreams[i] = TsnStream{};
    }
}

::transport::AbstractTransportLayer::ErrorCode TsnEthernetTransportLayer::init()
{
    // Call base class initialization first
    auto result = EthernetTransportLayer::init();
    if (result != ErrorCode::TP_OK)
    {
        return result;
    }

    // Initialize TSN-specific components
    // Note: Time synchronization initialization would go here in full implementation
    _timeSyncEnabled = false; // Placeholder for now
    
    return ErrorCode::TP_OK;
}

bool TsnEthernetTransportLayer::shutdown(ShutdownDelegate delegate)
{
    // Shutdown TSN-specific components
    _timeSyncEnabled = false;
    _streamCount = 0U;
    
    // Reset all streams
    for (uint8_t i = 0; i < MAX_TSN_STREAMS; ++i)
    {
        _tsnStreams[i] = TsnStream{};
    }
    
    // Call base class shutdown
    return EthernetTransportLayer::shutdown(delegate);
}

::transport::AbstractTransportLayer::ErrorCode TsnEthernetTransportLayer::send(
    ::transport::TransportMessage& transportMessage,
    ::transport::ITransportMessageProcessedListener* pNotificationListener)
{
    // Classify the message for TSN handling
    ::tsn::TsnStreamClass streamClass;
    ::tsn::TsnPriority priority;
    
    auto classifyResult = classifyMessage(transportMessage, streamClass, priority);
    if (classifyResult != ErrorCode::TP_OK)
    {
        // Fall back to regular Ethernet send if classification fails
        return EthernetTransportLayer::send(transportMessage, pNotificationListener);
    }

    // Apply TSN priority mapping (placeholder implementation)
    uint8_t vlanPcp __attribute__((unused)) = mapPriorityToVlanPcp(priority);
    
    // For now, delegate to base class - in full implementation, this would
    // apply TSN-specific handling including VLAN tagging, traffic shaping, etc.
    return EthernetTransportLayer::send(transportMessage, pNotificationListener);
}

::transport::AbstractTransportLayer::ErrorCode TsnEthernetTransportLayer::registerStream(
    ::tsn::TsnStreamClass streamClass,
    ::tsn::BandwidthBps bandwidth,
    ::tsn::LatencyUs maxLatency,
    ::tsn::StreamId& streamId)
{
    if (_streamCount >= MAX_TSN_STREAMS)
    {
        return ErrorCode::TP_GENERAL_ERROR;
    }

    // Find a free stream slot
    TsnStream* stream = findFreeStream();
    if (stream == nullptr)
    {
        return ErrorCode::TP_GENERAL_ERROR;
    }

    // Create stream configuration
    ::tsn::TsnStreamConfig config;
    auto configResult = ::tsn::TsnConfiguration::getDefaultStreamConfig(streamClass, config);
    if (configResult != ::tsn::TsnErrorCode::OK)
    {
        return ErrorCode::TP_GENERAL_ERROR;
    }

    // Override with provided parameters
    config.bandwidth = bandwidth;
    config.maxLatency = maxLatency;
    
    // Validate configuration
    auto validateResult = ::tsn::TsnConfiguration::validateStreamConfig(config);
    if (validateResult != ::tsn::TsnErrorCode::OK)
    {
        return ErrorCode::TP_GENERAL_ERROR;
    }

    // Assign stream ID and configure stream
    streamId = _nextStreamId++;
    stream->streamId = streamId;
    stream->config = config;
    stream->active = true;
    stream->messagesSent = 0U;
    stream->messagesDropped = 0U;

    ++_streamCount;

    return ErrorCode::TP_OK;
}

::transport::AbstractTransportLayer::ErrorCode TsnEthernetTransportLayer::unregisterStream(
    ::tsn::StreamId streamId)
{
    TsnStream* stream = findStreamById(streamId);
    if (stream == nullptr || !stream->active)
    {
        return ErrorCode::TP_GENERAL_ERROR;
    }

    // Deactivate stream
    stream->active = false;
    stream->streamId = 0;
    --_streamCount;

    return ErrorCode::TP_OK;
}

::transport::AbstractTransportLayer::ErrorCode TsnEthernetTransportLayer::sendOnStream(
    ::tsn::StreamId streamId,
    ::transport::TransportMessage& transportMessage,
    ::transport::ITransportMessageProcessedListener* pNotificationListener)
{
    TsnStream* stream = findStreamById(streamId);
    if (stream == nullptr || !stream->active)
    {
        return ErrorCode::TP_GENERAL_ERROR;
    }

    // Apply traffic shaping for the stream
    auto shapingResult = applyTrafficShaping(streamId, transportMessage);
    if (shapingResult != ErrorCode::TP_OK)
    {
        ++stream->messagesDropped;
        return shapingResult;
    }

    // Send the message using base class functionality
    auto sendResult = EthernetTransportLayer::send(transportMessage, pNotificationListener);
    
    if (sendResult == ErrorCode::TP_OK)
    {
        ++stream->messagesSent;
    }
    else
    {
        ++stream->messagesDropped;
    }

    return sendResult;
}

::transport::AbstractTransportLayer::ErrorCode TsnEthernetTransportLayer::getStreamStatistics(
    ::tsn::StreamId streamId,
    uint32_t& messagesSent,
    uint32_t& messagesDropped)
{
    TsnStream* stream = findStreamById(streamId);
    if (stream == nullptr || !stream->active)
    {
        return ErrorCode::TP_GENERAL_ERROR;
    }

    messagesSent = stream->messagesSent;
    messagesDropped = stream->messagesDropped;

    return ErrorCode::TP_OK;
}

::transport::AbstractTransportLayer::ErrorCode TsnEthernetTransportLayer::getCurrentTime(
    ::tsn::GptpTimestamp& timestamp)
{
    if (!_timeSyncEnabled || _timeSync == nullptr)
    {
        return ErrorCode::TP_GENERAL_ERROR;
    }

    auto result = _timeSync->getCurrentTime(timestamp);
    return (result == ::tsn::TsnErrorCode::OK) ? ErrorCode::TP_OK : ErrorCode::TP_GENERAL_ERROR;
}

bool TsnEthernetTransportLayer::isTimeSynchronized() const
{
    return _timeSyncEnabled && 
           _timeSync != nullptr && 
           _timeSync->isSynchronized();
}

// Private helper methods

::transport::AbstractTransportLayer::ErrorCode TsnEthernetTransportLayer::classifyMessage(
    const ::transport::TransportMessage& message __attribute__((unused)),
    ::tsn::TsnStreamClass& streamClass,
    ::tsn::TsnPriority& priority)
{
    // Placeholder classification logic
    // In a real implementation, this would examine message headers,
    // destination addresses, etc. to determine the appropriate TSN class
    
    // For now, default to best effort
    streamClass = ::tsn::TsnStreamClass::BEST_EFFORT;
    priority = ::tsn::TsnPriority::BEST_EFFORT_0;
    
    return ErrorCode::TP_OK;
}

::transport::AbstractTransportLayer::ErrorCode TsnEthernetTransportLayer::applyTrafficShaping(
    ::tsn::StreamId streamId,
    const ::transport::TransportMessage& message __attribute__((unused)))
{
    TsnStream* stream = findStreamById(streamId);
    if (stream == nullptr)
    {
        return ErrorCode::TP_GENERAL_ERROR;
    }

    // Placeholder for traffic shaping logic
    // In a real implementation, this would:
    // - Check current bandwidth usage
    // - Apply credit-based shaper for AVB streams
    // - Implement time-aware gating for TSN
    // - Queue messages according to priority
    
    return ErrorCode::TP_OK;
}

TsnEthernetTransportLayer::TsnStream* TsnEthernetTransportLayer::findStreamById(
    ::tsn::StreamId streamId)
{
    for (uint8_t i = 0; i < MAX_TSN_STREAMS; ++i)
    {
        if (_tsnStreams[i].active && _tsnStreams[i].streamId == streamId)
        {
            return &_tsnStreams[i];
        }
    }
    return nullptr;
}

TsnEthernetTransportLayer::TsnStream* TsnEthernetTransportLayer::findFreeStream()
{
    for (uint8_t i = 0; i < MAX_TSN_STREAMS; ++i)
    {
        if (!_tsnStreams[i].active)
        {
            return &_tsnStreams[i];
        }
    }
    return nullptr;
}

::tsn::TsnPriority TsnEthernetTransportLayer::mapClassToPriority(::tsn::TsnStreamClass streamClass)
{
    return ::tsn::TsnConfiguration::getClassPriority(streamClass);
}

uint8_t TsnEthernetTransportLayer::mapPriorityToVlanPcp(::tsn::TsnPriority priority)
{
    return static_cast<uint8_t>(priority);
}

} // namespace ethernet