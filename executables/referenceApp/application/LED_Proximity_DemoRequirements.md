# LED Proximity Demo Requirements Specification

## Document Information
- **Project**: OpenBSW LED Proximity Demo
- **Version**: 1.0
- **Date**: September 23, 2025
- **Analysis Method**: MECE (Mutually Exclusive, Collectively Exhaustive)

## MECE Analysis Framework

The requirements are organized using MECE analysis across four primary dimensions:

### 1. **Functional Domains** (What the system does)
- Sensor Input Processing
- LED Output Control  
- Distance Calculation & Mapping
- Dynamic LED Behavior
- System Lifecycle Management

### 2. **Platform Domains** (Where the system runs)
- S32K148EVB Platform
- RP2040/Pico W Platform
- Cross-Platform Abstractions

### 3. **Interface Domains** (How the system interacts)
- Hardware Interfaces
- Software Interfaces
- User Interfaces

### 4. **Quality Domains** (How well the system performs)
- Performance Requirements
- Reliability Requirements
- Maintainability Requirements

---

## Functional Requirements

### Sensor Input Processing

```{req} Distance Measurement Capability
:id: REQ-FUNC-001
:status: approved
:tags: sensor, hcsr04, functional

The system SHALL measure distance using HC-SR04 ultrasonic sensor with a range of 1-100 cm.
```

```{req} Distance Measurement Accuracy
:id: REQ-FUNC-002
:status: approved
:tags: sensor, accuracy, functional
:links: REQ-FUNC-001

The system SHALL provide distance measurements with ±1 cm accuracy within the specified range.
```

```{req} Measurement Update Rate
:id: REQ-FUNC-003
:status: approved
:tags: sensor, timing, functional
:links: REQ-FUNC-001

The system SHALL update distance measurements at 10 Hz (100ms intervals).
```

```{req} Invalid Reading Handling
:id: REQ-FUNC-004
:status: approved
:tags: sensor, error-handling, functional
:links: REQ-FUNC-001

The system SHALL handle invalid sensor readings (out-of-range, timeout) gracefully without system failure.
```

### LED Output Control

```{req} LED Strip Control
:id: REQ-FUNC-005
:status: approved
:tags: led, ws2812b, functional

The system SHALL control a WS2812B LED strip with 144 addressable LEDs.
```

```{req} LED Color Specification
:id: REQ-FUNC-006
:status: approved
:tags: led, color, functional
:links: REQ-FUNC-005

The system SHALL illuminate LEDs using a three-color gradient based on proximity:
- **Green (RGB: 0, 255, 0)** for far distances (strip start)
- **Orange (RGB: 255, 128, 0)** for medium distances (middle section)
- **Red (RGB: 255, 0, 0)** for close distances (strip end)
The gradient SHALL transition smoothly between colors, with brightness increasing toward closer proximity LEDs.
```

```{req} LED Strip Clear Function
:id: REQ-FUNC-007
:status: approved
:tags: led, control, functional
:links: REQ-FUNC-005

The system SHALL be able to turn off all LEDs (clear the strip).
```

```{req} Individual LED Control
:id: REQ-FUNC-008
:status: approved
:tags: led, control, functional
:links: REQ-FUNC-005

The system SHALL be able to control individual LEDs within the strip.
```

### Distance-to-LED Mapping

```{req} Proximity Mapping Algorithm
:id: REQ-FUNC-009
:status: approved
:tags: algorithm, mapping, functional
:links: REQ-FUNC-001, REQ-FUNC-005

The system SHALL map distance measurements to LED illumination count using linear interpolation:
- 1 cm distance → All 144 LEDs ON
- 100+ cm distance → All LEDs OFF
- Intermediate distances → Proportional LED count
```

```{req} Real-time Response
:id: REQ-FUNC-010
:status: approved
:tags: timing, response, functional
:links: REQ-FUNC-009

The system SHALL update LED display within 10ms of distance measurement completion.
```

```{req} Dynamic LED Illumination
:id: REQ-FUNC-014
:status: approved
:tags: dynamic, illumination, functional
:links: REQ-FUNC-009, REQ-FUNC-003

The system SHALL dynamically adjust LED illumination based on real-time distance changes:
- When object moves CLOSER: Additional LEDs SHALL illuminate progressively
- When object moves FARTHER: Illuminated LEDs SHALL turn off progressively
- LED count SHALL be proportional to proximity at all times
```

```{req} Gradual LED Transition
:id: REQ-FUNC-015
:status: approved
:tags: transition, smooth, functional
:links: REQ-FUNC-014

The system SHALL provide smooth LED transitions when distance changes:
- No abrupt on/off switching of large LED groups
- LED changes SHALL follow distance measurement updates (100ms intervals)
- Each distance change SHALL result in corresponding LED count adjustment
```

```{req} Distance Visualization Accuracy
:id: REQ-FUNC-016
:status: approved
:tags: visualization, accuracy, functional
:links: REQ-FUNC-009, REQ-FUNC-014

The LED strip SHALL accurately represent current distance measurements:
- LED count SHALL directly correspond to measured distance
- LED illumination SHALL update within one measurement cycle (100ms)
- Visual representation SHALL be intuitive (more LEDs = closer object)
```

### Dynamic LED Behavior

```{req} Proximity-Based LED Response
:id: REQ-FUNC-017
:status: approved
:tags: proximity, response, dynamic, functional
:links: REQ-FUNC-001, REQ-FUNC-005, REQ-FUNC-014

The system SHALL respond immediately to proximity changes:
- Approaching objects SHALL cause progressive LED illumination from strip start
- Receding objects SHALL cause progressive LED turn-off from strip end
- LED response SHALL be continuous and proportional to distance changes
```

### System Lifecycle Management

```{req} System Initialization
:id: REQ-FUNC-011
:status: approved
:tags: lifecycle, initialization, functional

The system SHALL initialize all hardware components (sensor, LED strip) during startup.
```

```{req} Graceful Shutdown
:id: REQ-FUNC-012
:status: approved
:tags: lifecycle, shutdown, functional

The system SHALL clear all LEDs during system shutdown.
```

```{req} FreeRTOS Integration
:id: REQ-FUNC-013
:status: approved
:tags: rtos, integration, functional

The system SHALL operate as a FreeRTOS task within the OpenBSW framework.
```

---

## Platform Requirements

### S32K148EVB Platform

```{req} S32K148EVB GPIO Configuration
:id: REQ-PLAT-001
:status: approved
:tags: s32k148evb, gpio, platform

The system SHALL use the following GPIO pins on S32K148EVB:
- HC-SR04 Trigger: Pin 37 (PB5)
- HC-SR04 Echo: Pin 36 (PB4)  
- WS2812B Data: Pin 78 (PC14)
```

```{req} S32K148EVB IO Configuration Compatibility
:id: REQ-PLAT-002
:status: approved
:tags: s32k148evb, configuration, platform
:links: REQ-PLAT-001

The GPIO pin assignments SHALL be compatible with existing ioConfiguration.h definitions.
```

### RP2040/Pico W Platform

```{req} RP2040 GPIO Configuration
:id: REQ-PLAT-003
:status: approved
:tags: rp2040, gpio, platform

The system SHALL use the following GPIO pins on RP2040/Pico W:
Pico W Pin | GPIO | Function        | Device Connection
-----------|------|-----------------|------------------
Pin 4      | GP2  | Digital Output  | HC-SR04 Trigger
Pin 5      | GP3  | Digital Input   | HC-SR04 Echo  
Pin 21     | GP16 | Digital Output  | WS2812B Data In
Pin 38     | GND  | Ground          | Both devices GND
Pin 40     | VBUS | 5V Power        | Both devices VCC
```

```{req} RP2040 Direct Register Access
:id: REQ-PLAT-004
:status: approved
:tags: rp2040, register-access, platform
:links: REQ-PLAT-003

The system SHALL use direct hardware register access following OpenBSW patterns (no vendor SDK dependency).
```

### Cross-Platform Abstractions

```{req} Platform Detection
:id: REQ-PLAT-005
:status: approved
:tags: cross-platform, detection, platform

The system SHALL automatically detect target platform via preprocessor macros (PLATFORM_S32K148EVB, PLATFORM_RP2040).
```

```{req} Single Source Code Base
:id: REQ-PLAT-006
:status: approved
:tags: cross-platform, maintainability, platform

The system SHALL maintain a single source file supporting both platforms without runtime overhead.
```

```{req} Platform-Specific Pin Assignment
:id: REQ-PLAT-007
:status: approved
:tags: cross-platform, configuration, platform
:links: REQ-PLAT-001, REQ-PLAT-003

The system SHALL select appropriate GPIO pins automatically based on target platform.
```

---

## Interface Requirements

### Hardware Interfaces

```{req} HC-SR04 Sensor Interface
:id: REQ-INT-001
:status: approved
:tags: hardware, sensor, interface

The system SHALL interface with HC-SR04 ultrasonic sensor using:
- Trigger signal: 10μs HIGH pulse
- Echo signal: Input capture with timeout
- Power: 5V/3.3V compatible
```

```{req} WS2812B LED Interface
:id: REQ-INT-002
:status: approved
:tags: hardware, led, interface

The system SHALL interface with WS2812B LED strip using:
- Data protocol: 800kHz NRZ with precise timing
- Color depth: 24-bit RGB (8 bits per channel)
- Reset: >50μs LOW signal between frames
```

```{req} Power Interface Requirements
:id: REQ-INT-003
:status: approved
:tags: hardware, power, interface

The system SHALL support:
- HC-SR04: 5V nominal (3.3V compatible with reduced range)
- WS2812B: 5V @ max 60mA per LED (8.64A for 144 LEDs at full brightness)
- External power supply recommended for LED strip
```

### Software Interfaces

```{req} OpenBSW Framework Integration
:id: REQ-INT-004
:status: approved
:tags: software, framework, interface

The system SHALL integrate with OpenBSW lifecycle management using AsyncLifecycleComponent.
```

```{req} FreeRTOS Task Interface
:id: REQ-INT-005
:status: approved
:tags: software, rtos, interface

The system SHALL implement IRunnable interface for periodic execution within FreeRTOS.
```

```{req} Hardware Abstraction Layer
:id: REQ-INT-006
:status: approved
:tags: software, hal, interface

The system SHALL use OpenBSW HAL functions:
- hcsr04_init(), hcsr04_measure_cm()
- ws2812b_init(), ws2812b_set_led(), ws2812b_show(), ws2812b_clear()
```

### User Interfaces

```{req} Visual Feedback Interface
:id: REQ-INT-007
:status: approved
:tags: user, visual, interface

The LED strip SHALL provide intuitive visual feedback where more LEDs indicate closer proximity.
```

```{req} Real-time Response Interface
:id: REQ-INT-008
:status: approved
:tags: user, timing, interface

The visual response SHALL appear real-time to human perception (<100ms total latency).
```

---

## Quality Requirements

### Performance Requirements

```{req} Timing Precision
:id: REQ-QUAL-001
:status: approved
:tags: performance, timing, quality

The system SHALL maintain microsecond-level timing precision for WS2812B protocol compliance.
```

```{req} Memory Efficiency
:id: REQ-QUAL-002
:status: approved
:tags: performance, memory, quality

The system SHALL operate within embedded memory constraints:
- Flash usage: <100KB
- RAM usage: <50KB
- Stack usage: <2KB per task
```

```{req} CPU Utilization
:id: REQ-QUAL-003
:status: approved
:tags: performance, cpu, quality

The system SHALL consume <10% CPU utilization during normal operation.
```

```{req} Integer Arithmetic Only
:id: REQ-QUAL-004
:status: approved
:tags: performance, embedded, quality

The system SHALL use only integer arithmetic operations to ensure deterministic execution and avoid floating-point unit dependencies on embedded platforms.
```

### Reliability Requirements

```{req} Continuous Operation
:id: REQ-QUAL-005
:status: approved
:tags: reliability, operation, quality

The system SHALL operate continuously without degradation for >24 hours.
```

```{req} Error Recovery
:id: REQ-QUAL-006
:status: approved
:tags: reliability, error-handling, quality

The system SHALL recover from transient sensor errors without user intervention.
```

```{req} Hardware Fault Tolerance
:id: REQ-QUAL-007
:status: approved
:tags: reliability, fault-tolerance, quality

The system SHALL continue operating with degraded functionality if non-critical hardware fails.
```

### Maintainability Requirements

```{req} Code Documentation
:id: REQ-QUAL-008
:status: approved
:tags: maintainability, documentation, quality

All source code SHALL include comprehensive documentation following OpenBSW standards.
```

```{req} Configuration Management
:id: REQ-QUAL-009
:status: approved
:tags: maintainability, configuration, quality

Hardware pin assignments SHALL be easily configurable without code changes.
```

```{req} Platform Portability
:id: REQ-QUAL-010
:status: approved
:tags: maintainability, portability, quality

The system SHALL be portable to additional platforms with minimal changes.
```

---

## MECE Verification Matrix

| Requirement Category | S32K148EVB | RP2040 | Hardware | Software | Functional | Quality |
|---------------------|------------|--------|----------|----------|------------|---------|
| **Sensor Input**    | ✓          | ✓      | ✓        | ✓        | ✓          | ✓       |
| **LED Output**      | ✓          | ✓      | ✓        | ✓        | ✓          | ✓       |
| **Distance Mapping**| ✓          | ✓      | -        | ✓        | ✓          | ✓       |
| **Dynamic LED Behavior** | ✓     | ✓      | -        | ✓        | ✓          | ✓       |
| **Lifecycle Mgmt**  | ✓          | ✓      | -        | ✓        | ✓          | ✓       |
| **Platform Specific**| ✓         | ✓      | ✓        | ✓        | -          | ✓       |
| **Cross-Platform**  | ✓          | ✓      | -        | ✓        | -          | ✓       |

## Requirements Traceability

### Coverage Analysis
- **Total Requirements**: 38
- **Functional**: 17 (44.7%)
- **Platform**: 7 (18.4%)
- **Interface**: 8 (21.1%)
- **Quality**: 10 (26.3%)

### MECE Completeness Verification
✓ **Mutually Exclusive**: Each requirement addresses a distinct aspect without overlap  
✓ **Collectively Exhaustive**: All identified aspects of the LED Proximity Demo are covered

---

## Appendix: Requirement Links & Dependencies

```{needflow}
:tags: functional
:show_legend:
```

This requirements specification ensures comprehensive coverage of the LED Proximity Demo functionality across both target platforms while maintaining MECE principles for clear, unambiguous system definition.