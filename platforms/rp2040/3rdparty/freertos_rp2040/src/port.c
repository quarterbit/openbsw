// Minimal FreeRTOS port for RP2040 (Cortex-M0+)
// This is a stub implementation - a full port would be needed for production

#include "portmacro.h"

// CMSIS functions for interrupts
#define __disable_irq() __asm volatile ("cpsid i" ::: "memory")
#define __enable_irq()  __asm volatile ("cpsie i" ::: "memory")

// FreeRTOS constants
#define pdTRUE  1

// Basic port implementation
void vPortSetupTimerInterrupt(void) {
    // Setup SysTick for FreeRTOS
}

void vPortEnterCritical(void) {
    __disable_irq();
}

void vPortExitCritical(void) {
    __enable_irq();
}

BaseType_t xPortStartScheduler(void) {
    // Start the scheduler
    return pdTRUE;
}

void vPortEndScheduler(void) {
    // End scheduler
}

// SysTick handler
void xPortSysTickHandler(void) {
    // Handle SysTick
}