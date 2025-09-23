// Copyright 2024 quarterbit

#include <stdint.h>

// Simple hard fault handler for RP2040
extern "C" void HardFault_Handler(void)
{
    // Disable interrupts using inline assembly
    __asm volatile ("cpsid i" ::: "memory");

    // Infinite loop - in a real implementation, this would save state and reset
    while (true) {
        __asm volatile ("nop");
    }
}

// Other fault handlers can be added as needed
extern "C" __attribute__((weak, alias("HardFault_Handler"))) void NMI_Handler(void);
extern "C" __attribute__((weak, alias("HardFault_Handler"))) void MemManage_Handler(void);
extern "C" __attribute__((weak, alias("HardFault_Handler"))) void BusFault_Handler(void);
extern "C" __attribute__((weak, alias("HardFault_Handler"))) void UsageFault_Handler(void);