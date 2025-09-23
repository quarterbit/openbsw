/**
 * RP2040 Platform unsigned long getSystemTicks32Bit() {
    // Convert microseconds to milliseconds (1 tick = 1ms)
    return rp2040::getTimerRegisters()->TIMELR / 1000;
} Functions Implementation
 * Direct register access implementation for OpenBSW
 */

#include "rp2040_registers.h"

extern "C" {

/**
 * Get system time in microseconds (32-bit)
 * Uses RP2040 timer which runs at 1MHz
 */
unsigned long getSystemTimeUs32Bit() {
    // RP2040 timer runs at 1MHz, so TIMELR directly gives us microseconds
    return rp2040::getTimerRegisters()->TIMELR;
}

/**
 * Get system ticks (32-bit)
 * For RP2040, we'll use the same timer but convert to tick units
 * Assuming 1ms tick period (1000 Hz tick rate)
 */
unsigned long getSystemTicks32Bit() {
    // Use RP2040 timer for high resolution clock
    return rp2040::getTimerRegisters()->TIMELR;
}

/**
 * Convert system ticks to microseconds
 * @param ticks Number of system ticks
 * @return Time in microseconds
 */
unsigned long systemTicksToTimeUs(unsigned long ticks) {
    // Convert ticks (ms) to microseconds
    return ticks * 1000;
}

/**
 * ETL high resolution clock implementation
 * Used by ETL chrono library
 */
unsigned long etl_get_high_resolution_clock() {
    // Return high resolution time in microseconds
    return getSystemTimeUs32Bit();
}

} // extern "C"