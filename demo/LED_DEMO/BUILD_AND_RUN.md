# OpenBSW Build and Run Guide

## Quick Reference for Building and Running OpenBSW Applications

### Directory Structure
- **Main project root**: `/workspaces/openbsw/`
- **Applications**: `/workspaces/openbsw/executables/referenceApp/`
- **Build location**: `/workspaces/openbsw/executables/referenceApp/build/<platform>/`
- **Executable location**: `/workspaces/openbsw/executables/referenceApp/build/<platform>/application/app.referenceApp.elf`

### Supported Platforms
- `POSIX` - Linux simulation (for development/testing)
- `RP2040` - Raspberry Pi Pico
- `S32K148EVB` - NXP S32K148 evaluation board (default)

### Build Commands

#### Configure Build (Required before first build or when changing platforms)
```bash
cd /workspaces/openbsw/executables/referenceApp

# For POSIX simulation (Linux)
cmake -B build/posix -DCMAKE_BUILD_TYPE=Debug -DBUILD_TARGET_PLATFORM=POSIX

# For RP2040 
cmake -B build/rp2040 -DCMAKE_BUILD_TYPE=Debug -DBUILD_TARGET_PLATFORM=RP2040

# For S32K148EVB (default - can omit platform parameter)
cmake -B build/s32k148evb -DCMAKE_BUILD_TYPE=Debug -DBUILD_TARGET_PLATFORM=S32K148EVB
```

#### Build Application
```bash
cd /workspaces/openbsw/executables/referenceApp

# Build for specific platform
cmake --build build/<platform> --target app.referenceApp -j4

# Examples:
cmake --build build/posix --target app.referenceApp -j4
cmake --build build/rp2040 --target app.referenceApp -j4
```

### Run Application

#### POSIX Simulation
```bash
cd /workspaces/openbsw/executables/referenceApp/build/posix/application
./app.referenceApp.elf
```

**Output**: Real-time LED proximity simulation with ASCII LED strip visualization:
```
[0025] Distance:  52 cm | LEDs:  69/144 | LED Strip: [█████████████████████████████████████████████████████████████████████]
```

#### Hardware Platforms
For RP2040 and S32K148EVB, the `.elf` file needs to be flashed to the target hardware using platform-specific tools.

### Key Parameters
- **BUILD_TARGET_PLATFORM**: Must match exactly (`POSIX`, `RP2040`, `S32K148EVB`)
- **Target name**: Always `app.referenceApp` (not `referenceApp`)
- **Executable name**: Always `app.referenceApp.elf`

### Common Mistakes to Avoid
1. ❌ Running cmake from wrong directory (use `/workspaces/openbsw/executables/referenceApp/`)
2. ❌ Using wrong parameter name (`TARGET_PLATFORM` vs `BUILD_TARGET_PLATFORM`)
3. ❌ Looking for executable in build root (it's in `build/<platform>/application/`)
4. ❌ Using lowercase platform names (`posix` vs `POSIX`)

### Quick Development Workflow
```bash
# 1. Configure once
cd /workspaces/openbsw/executables/referenceApp
cmake -B build/posix -DCMAKE_BUILD_TYPE=Debug -DBUILD_TARGET_PLATFORM=POSIX

# 2. Iterative development
cmake --build build/posix --target app.referenceApp -j4 && cd build/posix/application && ./app.referenceApp.elf
```

### Available Build Targets
Use `cmake --build build/<platform> --target help` to see all available targets including individual libraries like `ws2812b`, `hcsr04`, etc.