# Getting Started

Welcome to OpenBSW! You can start exploring right away - no specialized automotive tools required.

## Quick Start: Try the Demo

**Run on any Linux machine** (including WSL):

1. Clone the [OpenBSW GitHub repository](https://github.com/eclipse-openbsw/openbsw)
2. Build the project using standard tools
3. Launch the demo application
4. Explore the **embedded console feature** - it runs as a shell in your terminal

The demo showcases OpenBSW's core capabilities and provides an interactive environment to experiment with commands, display values, and explore the system.

## What You Get Out of the Box

### Platform Support
- <img src="images/chip-mcu.png" width="24" style="display: inline; vertical-align: middle;"> **POSIX platform** - immediate compilation and execution on Linux/WSL
- <img src="images/chip-mcu.png" width="24" style="display: inline; vertical-align: middle;"> **NXP S32K1 microcontroller** - production-ready embedded target

### Core Capabilities
- **Lifecycle management** with component runlevels
- **CAN communication** with simple send/receive interfaces
- **UDS (Unified Diagnostic Services)** for diagnostics
- **Embedded console** for interactive command execution
- **Comprehensive logging** system

## Development Experience

### Familiar Tools
- **VS Code** for development
- **Git** for version control
- **Standard CI/CD pipelines** for automation
- **No GUI-based modeling tools** required

### Code-First Approach
```cpp
// Simple CAN frame sending - just plain code!
can.send(frame_id, data);

// Register for CAN frame reception
can.registerListener(frame_id, callback);
```

## Next Steps

1. **Explore the Documentation** - understand the architecture and concepts
2. **Run Unit Tests** - validate your setup and understanding
3. **Build Your First Application** - start with the demo and extend it
4. **Join the Community** - contribute and collaborate with other developers

### Getting Help

- [GitHub Repository](https://github.com/eclipse-openbsw/openbsw) - source code, issues, discussions
- [Eclipse Project Page](https://projects.eclipse.org/proposals/eclipse-openbsw) - official project information
- [Eclipse SDV Community](https://eclipse.dev/sdv/) - broader automotive software community

---

**Ready to modernize automotive software development?** OpenBSW brings decades of automotive expertise together with modern software engineering practices. Start your journey today!