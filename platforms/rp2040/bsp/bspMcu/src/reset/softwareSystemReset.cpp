// Copyright 2024 quarterbit

#include "reset/softwareSystemReset.h"

#include <stdint.h>

// RP2040 register definitions for reset
#define PPB_BASE        0xE0000000U
#define SCB_AIRCR       (*((volatile uint32_t*)(PPB_BASE + 0xED0C)))
#define SCB_AIRCR_VECTKEY_MASK   (0xFFFFUL << 16)
#define SCB_AIRCR_VECTKEY        (0x05FAUL << 16)
#define SCB_AIRCR_SYSRESETREQ    (1UL << 2)

extern "C"
{
[[noreturn]] void softwareSystemReset(void)
{
    // Trigger system reset using SCB AIRCR register
    SCB_AIRCR = SCB_AIRCR_VECTKEY | SCB_AIRCR_SYSRESETREQ;

    // Wait for reset (should not reach here)
    while (true) { /* Wait for reset */ }
}

void softwareDestructiveReset(void) { softwareSystemReset(); }
}