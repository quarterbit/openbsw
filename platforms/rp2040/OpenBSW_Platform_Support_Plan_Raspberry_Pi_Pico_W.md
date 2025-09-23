# OpenBSW Platform Support Plan: Raspberry Pi Pico W (RP2040)

## Overview

This document outlines the comprehensive plan for adding support for the Raspberry Pi Pico W (based on the RP2040 microcontroller) to the OpenBSW framework. The initial implementation will focus on core BSP functionality required for ultrasonic sensor and LED demonstrations, with wireless connectivity features deferred to future development phases.

## Table of Contents

1. [Platform Specifications](#platform-specifications)
2. [Hardware Architecture](#hardware-architecture)
3. [Memory Layout](#memory-layout)
4. [GPIO Pinout](#gpio-pinout)
5. [Clock System](#clock-system)
6. [Peripherals](#peripherals)
7. [Development Environment](#development-environment)
8. [Implementation Plan](#implementation-plan)
9. [Build System Integration](#build-system-integration)
10. [Testing Strategy](#testing-strategy)
11. [Not to be included in initial BSP](#not-to-be-included-in-initial-bsp)

## Platform Specifications

### Processor
- **Architecture**: Dual-core ARM Cortex-M0+
- **Maximum Frequency**: 133 MHz per core (266 MHz total processing power)
- **Instruction Set**: ARMv6-M (Thumb-2)
- **Floating Point**: None (software emulation only)
- **Memory Protection**: No MPU (Memory Protection Unit)
- **Interrupts**: NVIC with configurable priority levels

### Memory
- **SRAM**: 264 KB total (6 banks × 64 KB each)
- **Flash**: External QSPI flash (up to 16 MB supported)
- **Boot ROM**: 16 KB with USB bootloader
- **Cache**: No data/instruction cache (M0+ limitation)

### Power
- **Operating Voltage**: 3.3V
- **Current Consumption**: ~10-20mA active, <1mA sleep modes
- **Power Management**: Multiple sleep modes, dynamic voltage scaling

### Connectivity
- **WiFi**: 802.11b/g/n (2.4GHz only) via CYW43439
- **Bluetooth**: 5.0 with BLE support
- **USB**: 1.1 Full-Speed (12 Mbps)
- **Debug**: SWD (Serial Wire Debug) interface
- **No Ethernet**: Has no ethernet - therefore lwip is not used 

## Hardware Architecture

### RP2040 Block Diagram
```
┌─────────────────────────────────────────────────────────────┐
│                    RP2040 Microcontroller                    │
│  ┌─────────────────────────────────────────────────────┐    │
│  │                Dual ARM Cortex-M0+                 │    │
│  │  Core 0 ──────────────────┐  Core 1                │    │
│  │                          │                         │    │
│  │  ┌─────────────────────┐ │ ┌─────────────────────┐ │    │
│  │  │    PIO Block 0      │ │ │    PIO Block 1      │ │    │
│  │  │  (8 state machines) │ │ │  (8 state machines) │ │    │
│  │  └─────────────────────┘ │ └─────────────────────┘ │    │
│  └──────────────────────────┼─────────────────────────┘    │
│                             │                              │
│  ┌──────────────────────────┴─────────────────────────┐    │
│  │              Shared Peripherals                    │    │
│  │  • 2× UART • 2× SPI • 2× I2C • 16× PWM • 4× ADC   │    │
│  │  • USB 1.1 • DMA • Temperature Sensor • Timers     │    │
│  └────────────────────────────────────────────────────┘    │
│                                                             │
│  ┌─────────────────────────────────────────────────────┐    │
│  │              External Interfaces                    │    │
│  │  • QSPI Flash (up to 16MB) • WiFi/BT (CYW43439)    │    │
│  │  • USB PHY • Debug (SWD) • 30 GPIO pins            │    │
│  └────────────────────────────────────────────────────┘    │
└─────────────────────────────────────────────────────────────┘
```

### Key Architectural Features
- **Dual-Core SMP**: Symmetric Multi-Processing with FreeRTOS SMP support
- **PIO (Programmable I/O)**: 8 state machines for custom hardware protocols
- **Flexible GPIO**: All pins can be configured for multiple functions
- **DMA Support**: Direct Memory Access for high-speed data transfers
- **Inter-Core FIFOs**: Hardware-assisted communication between cores

## Memory Layout

### Address Space Mapping
```
0x00000000 - 0x00003FFF: Boot ROM (16KB)
0x10000000 - 0x13FFFFFF: External QSPI Flash (up to 16MB)
0x20000000 - 0x2003FFFF: SRAM Bank 0 (64KB)
0x20040000 - 0x2007FFFF: SRAM Bank 1 (64KB)
0x20080000 - 0x200BFFFF: SRAM Bank 2 (64KB)
0x200C0000 - 0x200FFFFF: SRAM Bank 3 (64KB)
0x20100000 - 0x2013FFFF: SRAM Bank 4 (64KB)
0x20140000 - 0x2017FFFF: SRAM Bank 5 (64KB)
0x40000000 - 0x400FFFFF: APB Peripherals
0x50000000 - 0x503FFFFF: AHB Peripherals
```

### Linker Script Configuration
```ld
MEMORY
{
  FLASH : ORIGIN = 0x10000000, LENGTH = 2048K   /* 2MB flash */
  RAM0  : ORIGIN = 0x20000000, LENGTH = 64K     /* SRAM Bank 0 */
  RAM1  : ORIGIN = 0x20040000, LENGTH = 64K     /* SRAM Bank 1 */
  RAM2  : ORIGIN = 0x20080000, LENGTH = 64K     /* SRAM Bank 2 */
  RAM3  : ORIGIN = 0x200C0000, LENGTH = 64K     /* SRAM Bank 3 */
  RAM4  : ORIGIN = 0x20100000, LENGTH = 64K     /* SRAM Bank 4 */
  RAM5  : ORIGIN = 0x20140000, LENGTH = 64K     /* SRAM Bank 5 */
}

SECTIONS
{
  .bootloader : { /* Boot header */ } > FLASH
  .text : { /* Code */ } > FLASH
  .rodata : { /* Read-only data */ } > FLASH
  .data : { /* Initialized data */ } > RAM0 AT> FLASH
  .bss : { /* Uninitialized data */ } > RAM0
  .heap : { /* Dynamic allocation */ } > RAM1
  .stack : { /* Stack */ } > RAM5
}
```

## GPIO Pinout

### Physical Pin Layout (40-pin Header)
```
┌─────────────────────────────────────────────────┐
│ Raspberry Pi Pico W                              │
│                                                 │
│ GP0   (1)  ┌───┐ (21)  GP12                     │
│ GND   (2)  │   │ (22)  GP13                     │
│ GP1   (3)  │   │ (23)  GND                      │
│ GP2   (4)  │   │ (24)  GP14                     │
│ GP3   (5)  │   │ (25)  GP15                     │
│ GP4   (6)  │   │ (26)  GP16                     │
│ GP5   (7)  │   │ (27)  GP17                     │
│ GND   (8)  │   │ (28)  GP18                     │
│ GP6   (9)  │   │ (29)  GP19                     │
│ GP7  (10)  │   │ (30)  GP20                     │
│ GP8  (11)  │   │ (31)  GP21                     │
│ GP9  (12)  │   │ (32)  GP22                     │
│ GND  (13)  │   │ (33)  GP23                     │
│ GP10 (14)  │   │ (34)  GP24                     │
│ GP11 (15)  │   │ (35)  GP25                     │
│ GP12 (16)  │   │ (36)  RUN                      │
│ GP13 (17)  │   │ (37)  GP26                     │
│ GND  (18)  │   │ (38)  GP27                     │
│ GP14 (19)  │   │ (39)  GND                      │
│ GP15 (20)  └───┘ (40)  GP28                     │
│                                                 │
└─────────────────────────────────────────────────┘
```

### GPIO Functions and Special Pins

#### Standard GPIO (GP0-GP22)
- **Digital I/O**: All pins support input/output with programmable pull-ups/downs
- **Interrupt Capability**: All pins can generate interrupts on edge/level changes
- **Drive Strength**: Programmable (2mA, 4mA, 8mA, 12mA)

#### ADC Pins (GP26-GP28)
- **GP26**: ADC0 (12-bit resolution, 0-3.3V range)
- **GP27**: ADC1 (12-bit resolution, 0-3.3V range)
- **GP28**: ADC2 (12-bit resolution, 0-3.3V range)
- **ADC_VREF**: ADC3 (voltage reference input)

#### Special Function Pins
- **GP23**: ADC3 / WL_ON (WiFi power control)
- **GP24**: ADC4
- **GP25**: ADC5 / WL_GPIO1 (WiFi SPI CSn)
- **GP29**: ADC6 (ground reference)

#### WiFi/BT Interface (CYW43439)
- **WL_GPIO0**: SPI0 RX (GP16)
- **WL_GPIO1**: SPI0 CSn (GP17)
- **WL_GPIO2**: SPI0 SCK (GP18)
- **WL_GPIO3**: SPI0 TX (GP19)
- **WL_ON**: Power control (GP23)
- **WL_REG_ON**: Regulator control

#### USB and Debug
- **USB D+**: GP15
- **USB D-**: GP14
- **SWCLK**: GP6 (SWD clock)
- **SWDIO**: GP7 (SWD data I/O)

### Pin Function Multiplexing
Each GPIO pin can be configured for multiple functions:
- **GPIO**: Digital input/output
- **UART**: UART0 TX/RX, UART1 TX/RX
- **SPI**: SPI0/SCK/TX/RX/CSn, SPI1/SCK/TX/RX/CSn
- **I2C**: I2C0 SDA/SCL, I2C1 SDA/SCL
- **PWM**: 16 PWM channels across 8 slices
- **PIO**: Programmable I/O state machines
- **USB**: USB D+/D- signals
- **ADC**: Analog input channels

## Clock System

### Clock Sources
1. **External Crystal Oscillator**
   - Frequency: 12 MHz (typical)
   - Purpose: High-precision reference clock
   - Used for: PLL input, USB clock generation

2. **Ring Oscillator (ROSC)**
   - Frequency: 6.5 MHz nominal (configurable)
   - Purpose: Always-on low-power clock source
   - Used for: Boot-up, low-power modes

3. **Phase-Locked Loop (PLL)**
   - Input: Reference clock (crystal or ROSC)
   - Output: Configurable up to 266 MHz
   - Purpose: Generate high-frequency system clock
   - Configuration: Dividers and multipliers for frequency synthesis

4. **USB PLL**
   - Input: 12 MHz crystal
   - Output: Fixed 48 MHz
   - Purpose: USB peripheral clock

### Clock Domains
- **CLK_REF**: Reference clock (typically 12 MHz)
- **CLK_SYS**: System clock (up to 133 MHz per core)
- **CLK_PERI**: Peripheral clock (up to 133 MHz)
- **CLK_USB**: USB clock (48 MHz)
- **CLK_ADC**: ADC clock (up to 48 MHz)
- **CLK_RTC**: RTC clock (up to 64 kHz)

### Default Configuration
- System clock: 125 MHz (PLL output divided by 2)
- Peripheral clock: 125 MHz
- USB clock: 48 MHz
- ADC clock: 48 MHz

## Peripherals

### UART (Universal Asynchronous Receiver/Transmitter)
- **Quantity**: 2 (UART0, UART1)
- **Features**: 8-bit data, programmable baud rate, parity, stop bits
- **FIFOs**: 32-byte TX/RX buffers
- **Interrupts**: TX/RX ready, FIFO level, errors
- **Pin Mapping**:
  - UART0: TX=GP0, RX=GP1 (default) or GP12/GP13
  - UART1: TX=GP4, RX=GP5 (default) or GP8/GP9

### SPI (Serial Peripheral Interface)
- **Quantity**: 2 (SPI0, SPI1)
- **Features**: Master/slave modes, 8-bit transfers, programmable clock
- **Clock**: Up to system clock frequency
- **Pin Mapping**:
  - SPI0: SCK=GP2, TX=GP3, RX=GP4, CSn=GP5 (default)
  - SPI1: SCK=GP10, TX=GP11, RX=GP12, CSn=GP13 (default)

### I2C (Inter-Integrated Circuit)
- **Quantity**: 2 (I2C0, I2C1)
- **Features**: Master/slave modes, 7/10-bit addressing, clock stretching
- **Clock**: Programmable up to 1 MHz
- **Pin Mapping**:
  - I2C0: SDA=GP0, SCL=GP1 (default) or GP4/GP5
  - I2C1: SDA=GP2, SCL=GP3 (default) or GP6/GP7

### PWM (Pulse Width Modulation)
- **Quantity**: 16 channels across 8 slices
- **Resolution**: 16-bit
- **Frequency**: Up to system clock / 2
- **Features**: Phase-correct PWM, variable frequency
- **Pin Mapping**: Any GPIO pin can be PWM output

### ADC (Analog-to-Digital Converter)
- **Resolution**: 12-bit
- **Channels**: 5 (ADC0-ADC4)
- **Input Range**: 0-3.3V
- **Sample Rate**: Up to 500 kS/s
- **Features**: Temperature sensor input, programmable gain
- **Pin Mapping**: GP26-GP29 (ADC0-ADC3), ADC4 internal

### USB 1.1 Controller
- **Speed**: Full-Speed (12 Mbps)
- **Features**: Device mode, CDC, MSC, HID support
- **Endpoints**: 16 endpoints
- **Pin Mapping**: D+=GP15, D-=GP14

### PIO (Programmable I/O)
- **State Machines**: 8 total (4 per PIO block)
- **Instructions**: 32-instruction programs
- **Clock**: Up to system clock
- **Features**: Custom protocol implementation, precise timing
- **Applications**: WS2812 LED control, DVI output, custom serial protocols

### DMA (Direct Memory Access)
- **Channels**: 12
- **Features**: Memory-to-memory, peripheral-to-memory transfers
- **Triggers**: All peripherals can trigger DMA transfers

## Development Environment

### Required Tools
- **Compiler**: GCC ARM Embedded (arm-none-eabi-gcc)
- **Build System**: CMake 3.22+
- **SDK**: Raspberry Pi Pico SDK
- **Debugger**: OpenOCD or J-Link
- **IDE**: VS Code with Cortex-Debug extension

### Pico SDK Integration
- **Location**: `platforms/rp2040/3rdparty/pico-sdk/`
- **Components**:
  - Hardware abstraction layer
  - CMake build integration
  - FreeRTOS SMP support
  - PIO framework
  - USB stack

### FreeRTOS Configuration
- **Kernel**: Raspberry Pi maintained FreeRTOS
- **SMP Support**: Dual-core symmetric multiprocessing
- **Custom ISR Setup**: `setupApplicationsIsr()` function
- **Memory Management**: Heap regions across SRAM banks

## Implementation Plan

### Phase 1: Core Infrastructure (Weeks 1-3)
1. **Pico SDK Integration**
   - Download and integrate Raspberry Pi Pico SDK
   - Configure CMake toolchain for RP2040
   - Set up basic build environment

2. **FreeRTOS Dual-Core Port**
   - Integrate Raspberry Pi FreeRTOS kernel
   - Configure SMP (Symmetric Multi-Processing)
   - Implement inter-core communication

3. **Basic BSP Framework**
   - Create platform directory structure
   - Implement MCU abstraction layer
   - Set up clock and power management

### Phase 2: Peripheral Implementation (Weeks 4-7)
1. **GPIO and Pin Management**
   - Implement GPIO abstraction using Pico SDK
   - Configure pin multiplexing
   - Add interrupt handling

2. **Communication Peripherals**
   - UART implementation (2 channels)
   - SPI implementation (2 channels)
   - I2C implementation (2 channels)

3. **Analog and Timer Systems**
   - ADC driver (5 channels + temperature)
   - PWM driver (16 channels)
   - Timer and watchdog implementation

### Phase 3: Advanced Features (Weeks 8-9)
1. **PIO Integration**
   - PIO state machine abstraction
   - WS2812 LED driver implementation
   - Custom protocol support

2. **USB Support**
   - USB device driver
   - CDC (serial) support
   - MSC (mass storage) support

### Phase 4: Application Integration (Weeks 10-11)
1. **Board-Specific Configuration**
   - Create Pico W board configuration
   - Implement platform options
   - Configure memory layout

2. **Build System**
   - Complete CMake integration
   - Linker script development
   - Startup code implementation

3. **ISR and Startup**
   - Interrupt vector table
   - Boot sequence implementation
   - Dual-core initialization

### Phase 5: Testing and Validation (Weeks 12-13)
1. **Unit Testing**
   - BSP module testing
   - Peripheral validation
   - FreeRTOS integration testing

2. **Integration Testing**
   - Full system builds
   - Peripheral functionality
   - Ultrasonic sensor and LED demo validation

3. **Performance Validation**
   - Memory usage analysis
   - Power consumption testing
   - Dual-core performance

## Build System Integration

### CMake Configuration
```cmake
# platforms/rp2040/CMakeLists.txt
add_subdirectory(3rdparty/pico-sdk)
add_subdirectory(bsp)
add_subdirectory(hardFaultHandler)
add_subdirectory(lwipSysArch)
```

### Toolchain File
```cmake
# admin/cmake/ArmNoneEabi-rp2040.cmake
set(_C_FLAGS "-mcpu=cortex-m0plus -mfloat-abi=soft")
set(_CXX_FLAGS "-mcpu=cortex-m0plus -mfloat-abi=soft")

# Pico SDK path
set(PICO_SDK_PATH "${CMAKE_CURRENT_SOURCE_DIR}/platforms/rp2040/3rdparty/pico-sdk")
include(${PICO_SDK_PATH}/pico_sdk_init.cmake)

set(_EXE_LINKER_FLAGS "-specs=nano.specs -specs=nosys.specs")
```

### Platform Options
```cmake
# executables/referenceApp/platforms/pico_w/Options.cmake
set(OPENBSW_PLATFORM rp2040)
set(PLATFORM_SUPPORT_IO ON)
set(PLATFORM_SUPPORT_WIFI ON)
set(PLATFORM_SUPPORT_BLUETOOTH ON)
set(PLATFORM_SUPPORT_WATCHDOG ON)
set(PLATFORM_SUPPORT_MPU OFF)  # M0+ has no MPU
set(PLATFORM_SUPPORT_STORAGE ON)
```

## Testing Strategy

### Unit Testing
- **BSP Modules**: Individual peripheral testing
- **Mock Objects**: Hardware abstraction mocking
- **FreeRTOS Integration**: Task scheduling validation
- **Dual-Core**: Inter-core communication testing

### Integration Testing
- **Hardware Validation**: Physical Pico W board testing
- **Peripheral Functionality**: UART, SPI, I2C, ADC, PWM
- **Wireless Testing**: WiFi connectivity and Bluetooth LE
- **Performance**: Memory usage, power consumption, timing

### Automated Testing
- **CI/CD Pipeline**: GitHub Actions for automated builds
- **Cross-Compilation**: Ensure clean builds for RP2040
- **Binary Analysis**: Size and performance metrics
- **Regression Testing**: Prevent functionality breakage

## Migration Path

### From Existing Platforms
1. **Code Reuse**: Leverage existing OpenBSW patterns
2. **BSP Abstraction**: Maintain consistent APIs across platforms
3. **Build System**: Unified CMake configuration
4. **Documentation**: Consistent platform documentation

### Compatibility Considerations
- **API Consistency**: Maintain OpenBSW interface contracts
- **Feature Mapping**: Map RP2040 features to OpenBSW abstractions
- **Performance**: Optimize for M0+ constraints (no FPU, limited memory)
- **Power Management**: Integrate with RP2040 power modes

## Success Metrics

### Technical Metrics
- **Build Success**: Clean compilation for all configurations
- **Binary Size**: < 100KB for minimal LED demo
- **Memory Usage**: < 50KB RAM for basic applications
- **Performance**: > 100MHz effective processing

### Feature Completeness
- **Core BSP**: 100% peripheral coverage
- **FreeRTOS**: SMP dual-core support
- **PIO**: Custom protocol implementation
- **Ultrasonic/LED Demo**: Full functionality

### Quality Assurance
- **Test Coverage**: > 80% code coverage
- **Documentation**: Complete API documentation
- **Stability**: < 1% failure rate in automated tests

## Not to be included in initial BSP

The following features are not required for the initial ultrasonic sensor and LED demo implementation and will be deferred to future development phases:

### WiFi/Bluetooth Integration

#### CYW43439 Wireless Chip
- **WiFi Standards**: 802.11b/g/n (2.4GHz)
- **Bluetooth**: 5.0 with BLE
- **Interface**: SPI (4-wire)
- **Power Control**: Dedicated enable pins

#### Interface Details
- **SPI Configuration**: 4MHz clock, mode 0
- **Control Pins**:
  - WL_ON: Power enable (active high)
  - WL_REG_ON: Regulator enable
  - Interrupt: Dedicated interrupt line
- **Firmware**: Cypress WWD (Wireless Workbench Driver)

#### OpenBSW Integration Points
- **New BSP Module**: `bspWifi` for wireless connectivity
- **Network Stack**: Integration with existing TCP/IP stack
- **Security**: WPA2/3, BLE pairing support
- **Power Management**: WiFi sleep modes coordination

## Conclusion

The Raspberry Pi Pico W represents an excellent addition to the OpenBSW platform portfolio, providing a cost-effective dual-core ARM Cortex-M0+ platform for embedded applications. This implementation plan focuses initially on core BSP functionality required for ultrasonic sensor and LED demonstrations, establishing a solid foundation for future expansion including wireless connectivity features.

The phased approach ensures that essential platform support is implemented first, enabling immediate development of sensor-based applications while maintaining the architectural flexibility to add advanced features like WiFi and Bluetooth in subsequent development cycles.

---

**Document Version**: 1.0  
**Date**: September 23, 2025  
**Authors**: quarterbit, supported by coPilot  
**Platform**: Raspberry Pi Pico W (RP2040)