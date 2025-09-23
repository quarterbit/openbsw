#pragma once

/**
 * RP2040 Hardware Register Definitions
 * Direct register access for OpenBSW BSP implementation
 */

#include <cstdint>

namespace rp2040 {

// Base addresses
constexpr uint32_t TIMER_BASE = 0x40054000;
constexpr uint32_t SIO_BASE = 0xd0000000;
constexpr uint32_t NVIC_BASE = 0xe000e000;
constexpr uint32_t SCB_BASE = 0xe000ed00;
constexpr uint32_t ADC_BASE = 0x4004c000;
constexpr uint32_t UART0_BASE = 0x40034000;
constexpr uint32_t UART1_BASE = 0x40038000;

// Timer registers
struct TimerRegisters {
    volatile uint32_t TIMEHW;     // 0x00: Timer high word
    volatile uint32_t TIMELW;     // 0x04: Timer low word
    volatile uint32_t TIMEHR;     // 0x08: Timer high word read
    volatile uint32_t TIMELR;     // 0x0C: Timer low word read
    volatile uint32_t ALARM0;     // 0x10: Alarm 0
    volatile uint32_t ALARM1;     // 0x14: Alarm 1
    volatile uint32_t ALARM2;     // 0x18: Alarm 2
    volatile uint32_t ALARM3;     // 0x1C: Alarm 3
    volatile uint32_t ARMED;      // 0x20: Armed alarms
    volatile uint32_t TIMERAWH;   // 0x24: Raw timer high
    volatile uint32_t TIMERAWL;   // 0x28: Raw timer low
    volatile uint32_t DBGPAUSE;   // 0x2C: Debug pause
    volatile uint32_t PAUSE;      // 0x30: Pause
    volatile uint32_t INTR;       // 0x34: Interrupt status
    volatile uint32_t INTE;       // 0x38: Interrupt enable
    volatile uint32_t INTF;       // 0x3C: Interrupt force
    volatile uint32_t INTS;       // 0x40: Interrupt status
};

static_assert(sizeof(TimerRegisters) == 0x44, "TimerRegisters size mismatch");

// ADC registers
struct AdcRegisters {
    volatile uint32_t CS;         // 0x00: Control and Status
    volatile uint32_t RESULT;     // 0x04: Result
    volatile uint32_t FCS;        // 0x08: FIFO Control and Status
    volatile uint32_t FIFO;       // 0x0C: FIFO data
    volatile uint32_t DIV;        // 0x10: Clock divider
    volatile uint32_t INTR;       // 0x14: Interrupt status
    volatile uint32_t INTE;       // 0x18: Interrupt enable
    volatile uint32_t INTF;       // 0x1C: Interrupt force
    volatile uint32_t INTS;       // 0x20: Interrupt status
};

// UART registers
struct UartRegisters {
    volatile uint32_t DR;         // 0x00: Data register
    volatile uint32_t RSR;        // 0x04: Receive status/error clear
    volatile uint32_t reserved1[4];
    volatile uint32_t FR;         // 0x18: Flag register
    volatile uint32_t reserved2;
    volatile uint32_t ILPR;       // 0x20: IrDA low-power counter
    volatile uint32_t IBRD;       // 0x24: Integer baud rate divisor
    volatile uint32_t FBRD;       // 0x28: Fractional baud rate divisor
    volatile uint32_t LCR_H;      // 0x2C: Line control register
    volatile uint32_t CR;         // 0x30: Control register
    volatile uint32_t IFLS;       // 0x34: Interrupt FIFO level select
    volatile uint32_t IMSC;       // 0x38: Interrupt mask set/clear
    volatile uint32_t RIS;        // 0x3C: Raw interrupt status
    volatile uint32_t MIS;        // 0x40: Masked interrupt status
    volatile uint32_t ICR;        // 0x44: Interrupt clear
    volatile uint32_t DMACR;      // 0x48: DMA control
};

// Register bit definitions
namespace timer_bits {
    constexpr uint32_t CS_EN = (1u << 0);          // Timer enable
    constexpr uint32_t CS_READY = (1u << 1);       // Timer ready
}

namespace adc_bits {
    constexpr uint32_t CS_EN = (1u << 0);          // ADC enable
    constexpr uint32_t CS_TS_EN = (1u << 1);       // Temperature sensor enable
    constexpr uint32_t CS_START_ONCE = (1u << 2);  // Start single conversion
    constexpr uint32_t CS_START_MANY = (1u << 3);  // Start continuous conversions
    constexpr uint32_t CS_READY = (1u << 8);       // ADC ready
    constexpr uint32_t CS_ERR = (1u << 9);         // Error flag
    constexpr uint32_t CS_ERR_STICKY = (1u << 10); // Sticky error flag
    constexpr uint32_t CS_AINSEL_SHIFT = 12;       // Channel select shift
    constexpr uint32_t CS_AINSEL_MASK = 0x7;       // Channel select mask
    constexpr uint32_t CS_RROBIN_SHIFT = 16;       // Round robin shift
    constexpr uint32_t CS_RROBIN_MASK = 0x1F;      // Round robin mask
}

namespace uart_bits {
    constexpr uint32_t FR_TXFF = (1u << 5);        // TX FIFO full
    constexpr uint32_t FR_RXFE = (1u << 4);        // RX FIFO empty
    constexpr uint32_t FR_BUSY = (1u << 3);        // UART busy
    constexpr uint32_t CR_UARTEN = (1u << 0);      // UART enable
    constexpr uint32_t CR_TXE = (1u << 8);         // TX enable
    constexpr uint32_t CR_RXE = (1u << 9);         // RX enable
}

// Register accessors
inline volatile TimerRegisters* getTimerRegisters() {
    return reinterpret_cast<volatile TimerRegisters*>(TIMER_BASE);
}

inline volatile AdcRegisters* getAdcRegisters() {
    return reinterpret_cast<volatile AdcRegisters*>(ADC_BASE);
}

inline volatile UartRegisters* getUart0Registers() {
    return reinterpret_cast<volatile UartRegisters*>(UART0_BASE);
}

inline volatile UartRegisters* uart1() {
    return reinterpret_cast<volatile UartRegisters*>(UART1_BASE);
}

} // namespace rp2040