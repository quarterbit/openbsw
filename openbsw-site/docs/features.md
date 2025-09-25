# Features

OpenBSW delivers a comprehensive set of features designed specifically for automotive microcontroller development, addressing the unique challenges of embedded automotive environments.

## Core Automotive Requirements

- <img src="images/clock-realtime.png" width="24" style="display: inline; vertical-align: middle;"> **Real-time performance and deterministic behavior** - Cyclic execution models for safety-critical systems
- <img src="images/shield-safety.png" width="24" style="display: inline; vertical-align: middle;"> **Safety and reliability for automotive standards** - ISO26262 functional safety through "safety shell" approach
- <img src="images/power-lowpower.png" width="24" style="display: inline; vertical-align: middle;"> **Low power operation and fast wakeup** - Essential for automotive power management
- <img src="images/chip-mcu.png" width="24" style="display: inline; vertical-align: middle;"> **Specialized automotive communication** - CAN, LIN, Ethernet with predefined message catalogs
- <img src="images/chip-mcu.png" width="24" style="display: inline; vertical-align: middle;"> **Resource-constrained embedded environment** - Direct hardware interaction with strict limitations

## Modern Development Experience

### Code-First Philosophy
Unlike traditional automotive software that relies heavily on GUI-based modeling tools, OpenBSW embraces a code-centric approach:
- <img src="images/code-config.png" width="24" style="display: inline; vertical-align: middle;"> **Plain code** is sufficient for most typical tasks
- <img src="images/code-config.png" width="24" style="display: inline; vertical-align: middle;"> **Textual languages** for code generation when needed
- <img src="images/code-config.png" width="24" style="display: inline; vertical-align: middle;"> **No specialized automotive tools** required for daily development

### Developer-Friendly Toolchain
- <img src="images/flow-ci.png" width="24" style="display: inline; vertical-align: middle;"> **Use familiar tools:** VS Code, Git, standard CI/CD pipelines
- <img src="images/cpp.png" width="24" style="display: inline; vertical-align: middle;"> **Modern C++** implementation with safety restrictions (no dynamic allocation, no exceptions)
- <img src="images/rust.png" width="24" style="display: inline; vertical-align: middle;"> **Planned Rust support** for next-generation automotive development
- <img src="images/code-config.png" width="24" style="display: inline; vertical-align: middle;"> **Local tool availability** - all needed tools accessible to every developer

## Scalable & Modular Architecture

- <img src="images/puzzle-modular.png" width="24" style="display: inline; vertical-align: middle;"> **Customizable stack** that scales from very small to very large ECU projects
- <img src="images/puzzle-modular.png" width="24" style="display: inline; vertical-align: middle;"> **Open architecture** allows easy addition of new modules
- <img src="images/puzzle-modular.png" width="24" style="display: inline; vertical-align: middle;"> **Versatile libraries** and proper layering
- <img src="images/chip-mcu.png" width="24" style="display: inline; vertical-align: middle;"> **Built-in OS abstraction** ("async") for easy porting to other operating systems

## Safety & Compliance

### Functional Safety (ISO26262)
OpenBSW addresses functional safety requirements through a **"safety shell" approach**:
- **Separation of ASIL and QM software** using safety shell around ASIL components
- **Localized safety-related code** to simplify the rest of the codebase
- **Non-safety-qualified OS support** through proper isolation

### Safety Shell Components
- **MPU-based memory protection** mechanism
- **Program flow monitor** for execution integrity
- **Watchdog** for system monitoring

## Current Capabilities (Version 0.1+)

### Platform Support
- **NXP S32K1 microcontroller** - production-ready embedded target
- **POSIX platform** - compile and run on Linux/WSL development PCs

### Core Features
- **Lifecycle management** with runlevel-based component control
- **Comprehensive logging** system
- **Embedded standard library** ("estd")
- **CAN communication** with simple send/receive interfaces
- **UDS (Unified Diagnostic Services)** support
- **Embedded console** - shell on POSIX, serial console on embedded devices

## Coming Soon

### Network & Diagnostics
- **Ethernet support** for modern automotive networks
- **DoIP (Diagnostics over Internet Protocol)** 
- **UDS-based flashing** capabilities

### Communication & Integration
- **Simple COM module** for signal-based communication
- **Safety modules preview** with documentation and examples
- **Lightweight ICC1 AUTOSAR Layer** for existing application integration

### Platform Expansion
- <img src="images/zephyr.png" width="24" style="display: inline; vertical-align: middle;"> **Zephyr RTOS integration** (preview release planned)
- <img src="images/chip-mcu.png" width="24" style="display: inline; vertical-align: middle;"> **Extended MCU support** through Zephyr's 800+ device compatibility

---

OpenBSW enables next-generation automotive software development by combining proven automotive expertise with modern software engineering practices.