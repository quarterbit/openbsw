/**
 * RP2040 Platform Console I/O Functions Implementation
 * UART-based console I/O for OpenBSW
 */

#include "rp2040_registers.h"
#include <cstdint>

extern "C" {

/**
 * Write a byte to stdout (UART0 TX)
 * @param data Byte to transmit
 */
void putByteToStdout(int data) {
    UartRegisters* uart = getUart0Registers();
    
    // Wait for TX FIFO to have space
    while (uart->fr & rp2040::uart_bits::FR_TXFF) {
        // TX FIFO is full, wait
    }
    
    // Write data to transmit FIFO
    uart->dr = static_cast<uint8_t>(data);
}

/**
 * Read a byte from stdin (UART0 RX)
 * @return Received byte or -1 if no data available
 */
int getByteFromStdin() {
    UartRegisters* uart = getUart0Registers();
    
    // Check if RX FIFO has data
    if (uart->fr & rp2040::uart_bits::FR_RXFE) {
        // RX FIFO is empty
        return -1;
    }
    
    // Read data from receive FIFO
    return uart->dr & 0xFF;
}

} // extern "C"