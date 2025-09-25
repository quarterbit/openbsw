# LED Proximity Demo Documentation

This directory contains comprehensive documentation for the LED Proximity Demonstration system implemented using OpenBSW framework.

## Overview

The LED proximity demo uses an HC-SR04 ultrasonic sensor to control a WS2812B LED strip (144 LEDs) based on proximity. Objects get closer → more LEDs light up. The system demonstrates real-time embedded development with automotive-grade safety considerations.

Just for fun I have put the assumption that the LED strip is pasrt of a driver monitoring system and check how good coPilot is to generate an initial safety argumentation.

## Documentation Index

### 📋 Core Documentation
- **[LED_Demo_Development_Journey.md](LED_Demo_Development_Journey.md)** - Complete development blog post from GitHub issue #4 to working demo
- **[LED_PROXIMITY_DEMO.md](LED_PROXIMITY_DEMO.md)** - Main demo overview and user guide
- **[LED_Proximity_DemoRequirements.md](LED_Proximity_DemoRequirements.md)** - Comprehensive MECE requirements analysis (48 requirements across 5 domains)

### 🏗️ Architecture & Design
- **[LED-Demo_Architecture_in_OpenBSW.md](LED-Demo_Architecture_in_OpenBSW.md)** - System architecture, task priorities, and OpenBSW integration
- **[LED_PROXIMITY_INTEGRATION_SUMMARY.md](LED_PROXIMITY_INTEGRATION_SUMMARY.md)** - Component integration details and technical summary

### 🔧 Hardware & Platform Support
- **[S32K148_LED_PROXIMITY_PINOUT.md](S32K148_LED_PROXIMITY_PINOUT.md)** - S32K148EVB pin assignments and hardware setup
- **[PicoW_PINOUT.md](PicoW_PINOUT.md)** - Raspberry Pi Pico W pin assignments and GPIO configuration

### 🔍 Quality Assurance
- **[CodeQualityReport.md](CodeQualityReport.md)** - Comprehensive code quality analysis with cppcheck results
- **[RequirementsCheck.md](RequirementsCheck.md)** - Requirements verification and testing documentation

## Quick Start

1. **Read First**: [LED_Demo_Development_Journey.md](LED_Demo_Development_Journey.md) for complete context
2. **Requirements**: [LED_Proximity_DemoRequirements.md](LED_Proximity_DemoRequirements.md) for detailed specifications  
3. **Architecture**: [LED-Demo_Architecture_in_OpenBSW.md](LED-Demo_Architecture_in_OpenBSW.md) for system design
4. **Hardware Setup**: Platform-specific pinout files for your target board
5. **Build & Run**: Refer to main project [BUILD_AND_RUN.md](../../BUILD_AND_RUN.md)

## Features Demonstrated

✅ **Automotive-Grade Development**
- ISO 26262 safety considerations (ASIL B)
- Systematic MECE requirements analysis  
- Comprehensive architecture documentation

✅ **Cross-Platform Embedded**
- S32K148EVB and RP2040 support
- Clean hardware abstraction layers
- POSIX simulation for development

✅ **Real-Time Systems**
- FreeRTOS task integration
- Priority-based scheduling
- 10Hz sensor updates with <10ms LED response

✅ **Professional Quality**
- Static code analysis (cppcheck)
- Memory safety verification
- Production-ready error handling

## GitHub Context

- **Original Issue**: [quarterbit/openbsw#4](https://github.com/quarterbit/openbsw/issues/4)
- **Development Branch**: `copilot/vscode1758643136652`  
- **Repository**: [https://github.com/quarterbit/openbsw](https://github.com/quarterbit/openbsw)

## Development Tools Used

- **OpenBSW Framework**: Automotive-grade embedded development platform
- **GitHub Copilot**: AI-assisted development and documentation
- **CMake**: Cross-platform build system
- **Cppcheck**: Static code analysis
- **FreeRTOS**: Real-time operating system

---

*The LED proximity demo: where automotive safety meets maker creativity, powered by systematic engineering and AI-assisted development.*