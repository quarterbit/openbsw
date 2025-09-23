// Copyright 2024 quarterbit

#pragma once

#include <stdint.h>

// Minimal CMSIS definitions for Cortex-M0+
#define     __I     volatile const       /*!< Defines 'read only' permissions */
#define     __O     volatile             /*!< Defines 'write only' permissions */
#define     __IO    volatile             /*!< Defines 'read / write' permissions */

// Cortex-M0+ specific defines
#define __CM0PLUS_REV                 0x0000U  /*!< Core revision r0p0 */
#define __MPU_PRESENT                  0U      /*!< MPU present or not */
#define __VTOR_PRESENT                 1U      /*!< VTOR present or not */
#define __NVIC_PRIO_BITS               2U      /*!< Number of Bits used for Priority Levels */
#define __Vendor_SysTickConfig         0U      /*!< Set to 1 if different SysTick Config is used */

// interrupt locking and nvic info used by freertos
#define ENABLE_INTERRUPTS()  __enable_irq()
#define DISABLE_INTERRUPTS() __disable_irq()

#define FEATURE_NVIC_PRIO_BITS (2U)

// RP2040 specific register definitions
#define SIO_BASE        0xD0000000U  // SIO base address
#define IO_BANK0_BASE   0x40014000U  // IO Bank 0 base address
#define PADS_BANK0_BASE 0x4001C000U  // PADS Bank 0 base address
#define PPB_BASE        0xE0000000U  // Private Peripheral Bus base

// GPIO register structures for RP2040
typedef struct {
    volatile uint32_t STATUS;
    volatile uint32_t CTRL;
} GPIO_IO_REGISTERS;

typedef struct {
    GPIO_IO_REGISTERS IO[30];  // 30 GPIO pins
} IO_BANK0_REGISTERS;

typedef struct {
    volatile uint32_t VOLTAGE_SELECT;
    volatile uint32_t GPIO[30];  // GPIO pad controls
} PADS_BANK0_REGISTERS;

typedef struct {
    volatile uint32_t CPUID;
    volatile uint32_t GPIO_IN;
    volatile uint32_t GPIO_HI_IN;
    volatile uint32_t RESERVED1;
    volatile uint32_t GPIO_OUT;
    volatile uint32_t GPIO_OUT_SET;
    volatile uint32_t GPIO_OUT_CLR;
    volatile uint32_t GPIO_OUT_XOR;
    volatile uint32_t GPIO_OE;
    volatile uint32_t GPIO_OE_SET;
    volatile uint32_t GPIO_OE_CLR;
    volatile uint32_t GPIO_OE_XOR;
    volatile uint32_t GPIO_HI_OUT;
    volatile uint32_t GPIO_HI_OUT_SET;
    volatile uint32_t GPIO_HI_OUT_CLR;
    volatile uint32_t GPIO_HI_OUT_XOR;
    volatile uint32_t GPIO_HI_OE;
    volatile uint32_t GPIO_HI_OE_SET;
    volatile uint32_t GPIO_HI_OE_CLR;
    volatile uint32_t GPIO_HI_OE_XOR;
} SIO_REGISTERS;

// Register pointers
#define IO_BANK0 ((IO_BANK0_REGISTERS*)IO_BANK0_BASE)
#define PADS_BANK0 ((PADS_BANK0_REGISTERS*)PADS_BANK0_BASE)
#define SIO ((SIO_REGISTERS*)SIO_BASE)

// Core register access for VTOR
#define CORE0_VTOR   (*((volatile uint32_t*)(PPB_BASE + 0xed08)))
#define CORE1_VTOR   (*((volatile uint32_t*)(PPB_BASE + 0xed08)))  // Same for both cores

// RP2040 doesn't have UART/SPI/I2C/PWM/ADC base defines like S32K
// These would need to be defined if we implement those peripherals
// For now, GPIO is the focus