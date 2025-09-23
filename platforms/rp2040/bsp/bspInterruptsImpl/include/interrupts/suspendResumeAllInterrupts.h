// Copyright 2024 quarterbit

#pragma once

#include <stdint.h>

typedef uint32_t OldIntEnabledStatusValueType;

#define getMachineStateRegisterValueAndSuspendAllInterrupts \
    getOldIntEnabledStatusValueAndSuspendAllInterrupts

OldIntEnabledStatusValueType getOldIntEnabledStatusValueAndSuspendAllInterrupts(void);

void resumeAllInterrupts(OldIntEnabledStatusValueType const oldIntEnabledStatusValue);