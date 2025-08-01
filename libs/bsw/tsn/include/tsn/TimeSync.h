// Copyright 2024 Accenture.

#pragma once

#include "tsn/GptpTypes.h"
#include "tsn/TsnTypes.h"
#include <platform/estdint.h>

namespace tsn
{

/**
 * Interface for time synchronization notifications.
 */
class ITimeSyncListener
{
public:
    virtual ~ITimeSyncListener() = default;
    
    /**
     * Called when time synchronization state changes.
     * @param synchronized True if time is synchronized
     */
    virtual void onTimeSyncStateChanged(bool synchronized) = 0;
    
    /**
     * Called when master clock changes.
     * @param masterClockId The new master clock identity
     */
    virtual void onMasterClockChanged(const ClockIdentity& masterClockId) = 0;
};

/**
 * Time synchronization interface for IEEE 802.1AS gPTP.
 */
class TimeSync
{
public:
    /**
     * Constructor.
     */
    TimeSync();
    
    /**
     * Destructor.
     */
    virtual ~TimeSync() = default;
    
    /**
     * Initialize the time synchronization.
     * @return TsnErrorCode indicating success or failure
     */
    virtual TsnErrorCode init() = 0;
    
    /**
     * Shutdown the time synchronization.
     * @return TsnErrorCode indicating success or failure
     */
    virtual TsnErrorCode shutdown() = 0;
    
    /**
     * Get the current synchronized time.
     * @param timestamp Output parameter for the current time
     * @return TsnErrorCode indicating success or failure
     */
    virtual TsnErrorCode getCurrentTime(GptpTimestamp& timestamp) = 0;
    
    /**
     * Check if time is currently synchronized.
     * @return True if synchronized, false otherwise
     */
    virtual bool isSynchronized() const = 0;
    
    /**
     * Get the current clock state.
     * @return The current gPTP clock state
     */
    virtual GptpClockState getClockState() const = 0;
    
    /**
     * Get the master clock identity.
     * @param masterClockId Output parameter for master clock ID
     * @return TsnErrorCode indicating success or failure
     */
    virtual TsnErrorCode getMasterClockId(ClockIdentity& masterClockId) = 0;
    
    /**
     * Get the time accuracy of the synchronized time.
     * @return The current time accuracy
     */
    virtual TimeAccuracy getTimeAccuracy() const = 0;
    
    /**
     * Register a listener for time synchronization events.
     * @param listener The listener to register
     * @return TsnErrorCode indicating success or failure
     */
    virtual TsnErrorCode registerListener(ITimeSyncListener* listener) = 0;
    
    /**
     * Unregister a time synchronization listener.
     * @param listener The listener to unregister
     * @return TsnErrorCode indicating success or failure
     */
    virtual TsnErrorCode unregisterListener(ITimeSyncListener* listener) = 0;
    
    /**
     * Process periodic time synchronization tasks.
     * Should be called regularly from the main loop.
     */
    virtual void cyclicTask() = 0;

protected:
    bool _initialized;
    bool _synchronized;
    GptpClockState _clockState;
    ClockIdentity _masterClockId;
    TimeAccuracy _timeAccuracy;
    
    // Statistics
    uint32_t _syncMessagesSent;
    uint32_t _syncMessagesReceived;
    uint32_t _syncErrors;
};

} // namespace tsn