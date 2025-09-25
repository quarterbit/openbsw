
# Architecture

## OpenBSW in a nutshell

OpenBSW is a modular, production-proven basic software stack for automotive MCUs. It enables:

- Fast, reliable integration of embedded software components
- Real-time, deterministic operation across platforms
- Modern development workflows (CI/CD, configuration as code)
- Support for both AUTOSAR and non-AUTOSAR projects
- Proven on the road in millions of vehicles

---

### Sweet-Spot ECUs for OpenBSW

- **Body & Gateway ECUs with high integration**
- **Peripheral control ECUs** (Door, Seat, Trunk, …)
- **Zone ECUs with Ethernet/CAN**
- **MCU domain in HPCs** (e.g., ADAS & Infotainment)

---

OpenBSW is architected for **openness and modularity**, contrasting sharply with existing automotive software stacks. Its design enables scalable, production-grade embedded software that bridges the gap between traditional automotive requirements and modern software engineering practices.

## Key Architectural Principles

- <img src="images/puzzle-modular.png" width="24" style="display: inline; vertical-align: middle;"> **Open Architecture:** Built on versatile libraries and properly layered, allowing easy addition of new modules and scaling from very small to very large ECUs.
- <img src="images/code-config.png" width="24" style="display: inline; vertical-align: middle;"> **Code-First Design:** Plain code for most tasks, with textual code generation when needed - no GUI-based modeling tools required.
- <img src="images/chip-mcu.png" width="24" style="display: inline; vertical-align: middle;"> **Async Abstraction:** The `async` module provides a generic interface for executing code in different contexts (e.g., FreeRTOS tasks), enabling portable, concurrent execution across platforms.
- <img src="images/clock-realtime.png" width="24" style="display: inline; vertical-align: middle;"> **Lifecycle & Runlevel System:** The `lifecycle` module organizes application components into run levels, controlling their bring-up and shutdown order with deterministic behavior.
- <img src="images/shield-safety.png" width="24" style="display: inline; vertical-align: middle;"> **Safety-by-Design:** "Safety shell" approach separates ASIL and QM software for ISO26262 functional safety compliance.
- <img src="images/chip-mcu.png" width="24" style="display: inline; vertical-align: middle;"> **Platform Independence:** Built-in mechanisms like OS abstraction enable easy porting to other operating systems (e.g., Zephyr).
- <img src="images/cpp.png" width="24" style="display: inline; vertical-align: middle;"> <img src="images/rust.png" width="24" style="display: inline; vertical-align: middle;"> **Modern Language Support:** C++ implementation with planned Rust support, bringing modern systems programming to automotive.

## Main Architectural Elements

### Core Runtime Components
- **Hardware Abstraction Layer (HAL):** Provides uniform interface to MCU peripherals with direct hardware interaction
- **Async System:** Abstracts task/context management, mapping to RTOS primitives (e.g., FreeRTOS tasks)
- **Lifecycle Manager:** Centralizes startup/shutdown sequencing using run levels for deterministic control
- **Embedded Standard Library ("estd"):** Automotive-specific standard library with resource constraints in mind

### Communication & Networking
- **Automotive Bus Interfaces:** CAN, LIN, Ethernet with specialized message patterns and cyclic sending
- **UDS (Unified Diagnostic Services):** Comprehensive diagnostic protocol support
- **Transport Layer:** Abstraction for various communication protocols
- **Upcoming:** DoIP (Diagnostics over Internet Protocol) and advanced Ethernet support

### Safety & Compliance Framework
- **Safety Shell Architecture:** Three-component approach for ISO26262 compliance:
  - **MPU-based memory protection** mechanism
  - **Program flow monitor** for execution integrity  
  - **Watchdog** for system monitoring
- **ASIL/QM Separation:** Clean separation of safety-critical and quality management software

### System Components
Functional areas implemented as `LifecycleComponent` classes:
- **CAN System:** Bus communication with simple send/receive interfaces
- **UDS System:** Diagnostic services and protocols
- **Transport System:** Protocol abstraction and routing
- **Demo System:** Reference implementation and examples
- **Platform-Specific Systems:** BSP integration and hardware-specific features

## Automotive-Specific Design Patterns

### Real-Time & Embedded Constraints
- **Cyclic Execution Models:** Deterministic timing for safety-critical automotive systems
- **Resource-Constrained Environment:** Direct hardware interaction with strict memory and power limitations
- **No Dynamic Memory Allocation:** C++ usage with automotive safety restrictions
- **Fast Wake-up & Low Power:** Essential power management for automotive applications

### Communication Patterns
- **Specialized Bus Interfaces:** CAN, LIN, Ethernet with predefined message catalogs
- **Cyclic Message Sending:** Automotive-specific communication patterns
- **Code Generation from Catalogs:** Bus messages generated from predefined databases
- **Diagnostic Integration:** UDS protocol with error code generation from diagnostic databases

### Scalability & Modularity
```cpp
// Simple CAN communication - just plain code
can.send(frame_id, data);
can.registerListener(frame_id, [](const auto& frame) {
    // Handle received frame
});
```

**Customizable Stack Scaling:**
- Very small ECUs: Minimal footprint with essential components only
- Large ECUs: Full feature set with advanced networking and diagnostics
- Easy module addition through open architecture

## Typical Stack

- Hardware Abstraction Layer (HAL)
- Board Support Package (BSP)
- Base Software (BSW) modules (async, lifecycle, communication, diagnostics)
- Application integration layer

This architecture enables:
- Deterministic real-time behavior
- Flexible integration of new features
- Portability across MCU platforms
- Modern development workflows (CI/CD, code review, agentic AI)

A detailed architecture diagram will be provided in the future.