// Copyright 2024 Accenture.

#include "tsn/TimeSync.h"

namespace tsn
{

TimeSync::TimeSync()
: _initialized(false)
, _synchronized(false)
, _clockState(GptpClockState::INITIALIZING)
, _masterClockId{}
, _timeAccuracy(TimeAccuracy::ACCURACY_UNKNOWN)
, _syncMessagesSent(0U)
, _syncMessagesReceived(0U)
, _syncErrors(0U)
{
    // Initialize master clock ID to all zeros
    for (int i = 0; i < 8; ++i)
    {
        _masterClockId.id[i] = 0;
    }
}

} // namespace tsn