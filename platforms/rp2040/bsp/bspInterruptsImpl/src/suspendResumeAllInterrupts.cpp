// Copyright 2024 quarterbit

#include <interrupts/suspendResumeAllInterrupts.h>

namespace interrupts
{
/**
 * Get the current machine state register value and suspend all interrupts.
 * For RP2040 (no CAN support), this is a no-op that returns 0.
 */
uint32_t getMachineStateRegisterValueAndSuspendAllInterrupts()
{
    return 0;
}

/**
 * Resume all interrupts using the provided machine state register value.
 * For RP2040 (no CAN support), this is a no-op.
 */
void resumeAllInterrupts(uint32_t /* oldValue */)
{
    // No-op for RP2040
}

} /* namespace interrupts */