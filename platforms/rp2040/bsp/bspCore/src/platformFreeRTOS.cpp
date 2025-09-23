/**
 * RP2040 FreeRTOS Port Functions
 * ARM Cortex-M0+ specific FreeRTOS integration
 */

#include "FreeRTOS.h"
#include "task.h"

extern "C" {

/**
 * Initialize the stack for a new task
 * This sets up the ARM Cortex-M0+ stack frame for task switching
 */
StackType_t* pxPortInitialiseStack(StackType_t* pxTopOfStack, TaskFunction_t pxCode, void* pvParameters)
{
    /* Simulate the stack frame as it would be created by a context switch
       interrupt on ARM Cortex-M0+. */
    
    /* Offset added to account for the way the MCU uses the stack on entry/exit
       of interrupts, and to ensure alignment. */
    pxTopOfStack--;

    *pxTopOfStack = 0x01000000; /* xPSR */
    pxTopOfStack--;
    *pxTopOfStack = ((StackType_t)pxCode) & 0xfffffffeUL; /* PC */
    pxTopOfStack--;
    *pxTopOfStack = 0xFFFFFFFD; /* LR */
    
    /* Save code space by skipping register initialisation. */
    pxTopOfStack -= 5; /* R12, R3, R2 and R1. */
    *pxTopOfStack = (StackType_t)pvParameters; /* R0 */

    /* A save method is being used that requires each task to maintain its
       own exec return value. */
    pxTopOfStack--;
    *pxTopOfStack = 0xFFFFFFFD; /* portINITIAL_EXEC_RETURN */

    pxTopOfStack -= 8; /* R11, R10, R9, R8, R7, R6, R5 and R4. */

    return pxTopOfStack;
}

/**
 * Disable interrupts for critical sections
 * Uses the PRIMASK register to disable all interrupts
 */
void portDISABLE_INTERRUPTS(void)
{
    __asm volatile ("cpsid i" : : : "memory");
}

} // extern "C"