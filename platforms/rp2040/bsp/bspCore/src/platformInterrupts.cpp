/**
 * RP2040 Platform Interrupt Functions Implementation
 * ARM Cortex-M0+ interrupt management for OpenBSW
 */

#include <cstdint>

extern "C" {

/**
 * Disable interrupts and return previous interrupt state
 * ARM Cortex-M0+ implementation using PRIMASK register
 */
unsigned long getOldIntEnabledStatusValueAndSuspendAllInterrupts() {
    uint32_t primask;
    
    // Read current PRIMASK value
    __asm volatile ("mrs %0, primask" : "=r" (primask) : : "memory");
    
    // Disable interrupts
    __asm volatile ("cpsid i" : : : "memory");
    
    // Return previous state (0 = interrupts enabled, 1 = interrupts disabled)
    return primask;
}

/**
 * Restore interrupts to previous state
 * @param oldStatus Previous interrupt state from getOldIntEnabledStatusValueAndSuspendAllInterrupts
 */
void resumeAllInterrupts(unsigned long oldStatus) {
    if (oldStatus == 0) {
        // Interrupts were enabled, re-enable them
        __asm volatile ("cpsie i" : : : "memory");
    }
    // If oldStatus was 1, interrupts were already disabled, so leave them disabled
}

} // extern "C"