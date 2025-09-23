// Copyright 2024 quarterbit

#pragma once

#include <stdint.h>

typedef uint32_t OldIntEnabledStatusValueType;

#define getMachineStateRegisterValueAndSuspendAllInterrupts \
    getOldIntEnabledStatusValueAndSuspendAllInterrupts

// clang-format off
static inline __attribute__((always_inline))
uint32_t getOldIntEnabledStatusValueAndSuspendAllInterrupts(void)
{
    uint32_t _PRIMASK;
    __asm volatile ("mrs %0, primask\n"
                    "cpsid i\n"
                    : "=r" (_PRIMASK)
                    :
                    : "memory");
    return _PRIMASK;
}

static inline __attribute__((always_inline))
void resumeAllInterrupts(uint32_t const oldIntEnabledStatusValue)
{
    __asm volatile ("msr primask, %[Input]\n"
                    :
                    : [Input] "r" (oldIntEnabledStatusValue)
                    : "memory");
}
// clang-format on