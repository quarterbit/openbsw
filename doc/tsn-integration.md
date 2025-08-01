# TSN (Time-Sensitive Networking) Integration

This document describes the TSN integration in OpenBSW, providing foundational support for IEEE 802.1 AVB/TSN features.

## Overview

The TSN module provides the foundation for automotive Time-Sensitive Networking capabilities, including:

- **Stream Classification**: Support for TSN Stream Classes A, B, and Best Effort
- **Time Synchronization**: IEEE 802.1AS/1588 gPTP foundation 
- **Priority Mapping**: VLAN Priority Code Point (PCP) support
- **Enhanced Ethernet Transport**: TSN-aware transport layer

## Architecture

### Module Structure

```
libs/bsw/tsn/
├── include/tsn/
│   ├── TsnTypes.h           # Basic TSN data types
│   ├── TsnConfiguration.h   # Stream configuration and parameters
│   ├── GptpTypes.h         # IEEE 802.1AS gPTP types
│   └── TimeSync.h          # Time synchronization interface
├── src/
│   ├── TsnConfiguration.cpp
│   └── timesync/
│       ├── TimeSync.cpp
│       └── GptpClock.cpp   # Basic gPTP clock implementation
└── test/gtest/
    └── src/
        └── TsnConfigurationTest.cpp
```

### Enhanced Ethernet Transport

```
libs/bsw/ethernet/
├── include/ethernet/
│   ├── EthernetTransportLayer.h        # Base Ethernet transport
│   └── TsnEthernetTransportLayer.h     # TSN-enhanced transport
└── src/
    ├── EthernetTransportLayer.cpp
    └── TsnEthernetTransportLayer.cpp
```

## TSN Stream Classes

### Class A - High Priority
- **Maximum Latency**: 2ms
- **Priority**: Voice (5)
- **Use Case**: Real-time control, safety-critical communications
- **Bandwidth**: Up to 125 Mbps

### Class B - Medium Priority  
- **Maximum Latency**: 50ms
- **Priority**: Video (4)
- **Use Case**: Multimedia streaming, infotainment
- **Bandwidth**: Up to 250 Mbps

### Best Effort - Standard Priority
- **Maximum Latency**: No guarantee
- **Priority**: Best Effort (0-1)
- **Use Case**: Standard diagnostic, maintenance traffic
- **Bandwidth**: No specific limit

## Usage Examples

### Basic TSN Stream Configuration

```cpp
#include "tsn/TsnConfiguration.h"

// Create a Class A stream for real-time control
tsn::TsnStreamConfig cameraStream;
auto result = tsn::TsnConfiguration::getDefaultStreamConfig(
    tsn::TsnStreamClass::CLASS_A, 
    cameraStream
);

// Customize parameters
cameraStream.bandwidth = 10000000;  // 10 Mbps
cameraStream.maxLatency = 2000;     // 2ms
cameraStream.frameSize = 1500;      // Ethernet frame size

// Validate configuration
result = tsn::TsnConfiguration::validateStreamConfig(cameraStream);
```

### TSN Transport Layer Usage

```cpp
#include "ethernet/TsnEthernetTransportLayer.h"

// Create TSN-enhanced transport layer
ethernet::TsnEthernetTransportLayer tsnLayer(busid::ETHERNET_0);
tsnLayer.init();

// Register a real-time stream
tsn::StreamId streamId;
auto result = tsnLayer.registerStream(
    tsn::TsnStreamClass::CLASS_A,
    10000000,  // 10 Mbps bandwidth
    2000,      // 2ms max latency
    streamId
);

// Send messages on the stream
transport::TransportMessage message;
// ... prepare message ...
tsnLayer.sendOnStream(streamId, message, nullptr);

// Get stream statistics
uint32_t messagesSent, messagesDropped;
tsnLayer.getStreamStatistics(streamId, messagesSent, messagesDropped);
```

### Time Synchronization

```cpp
#include "tsn/TimeSync.h"

// Check if time is synchronized
if (tsnLayer.isTimeSynchronized()) {
    tsn::GptpTimestamp currentTime;
    auto result = tsnLayer.getCurrentTime(currentTime);
    
    if (result == transport::AbstractTransportLayer::ErrorCode::TP_OK) {
        uint64_t timeNs = currentTime.toNanoseconds();
        // Use synchronized time for scheduling
    }
}
```

## Configuration Parameters

### Memory Configuration (Embedded Systems)
- **MAX_TOTAL_STREAMS**: 32 streams maximum
- **MAX_STREAMS_PER_CLASS**: 16 streams per TSN class
- **STREAM_BUFFER_SIZE**: 2048 bytes per stream
- **MAX_PENDING_FRAMES**: 8 frames in queue

### Timing Configuration
- **GUARD_BAND_NS**: 12,960 ns guard band
- **CYCLE_TIME_US**: 125 μs cycle time
- **OBSERVATION_INTERVAL_MS**: 125 ms observation window

## Integration with Existing Systems

### Backward Compatibility
The TSN implementation maintains full backward compatibility with existing Ethernet transport functionality. Applications can continue using the base `EthernetTransportLayer` without modification.

### Build Integration
TSN support is automatically included when building OpenBSW. The module can be excluded by removing the `tsn` subdirectory from the build.

## Testing

### Unit Tests
- **TsnConfigurationTest**: Tests configuration validation and defaults
- **TsnEthernetTransportLayerTest**: Tests stream registration and transport functionality

### Running Tests
```bash
# Build with tests enabled
python3 .ci/build.py posix gcc 17 --enable-tests

# Run TSN-specific tests
cd cmake-build-posix-gcc
ctest -L tsnTest
ctest -L ethernetTsnTest
```

## Future Phases

This Phase 1 implementation provides the foundation for:

### Phase 2 - Core TSN Features
- IEEE 802.1AS time synchronization implementation
- IEEE 802.1Qbv Time-Aware Gating
- IEEE 802.1Qav Credit-Based Shaper

### Phase 3 - Advanced Features  
- IEEE 802.1Qbu Frame Preemption
- IEEE 802.1Qat Stream Reservation Protocol
- IEEE 802.1CB Frame Replication and Elimination

### Phase 4 - Optimization
- Hardware-specific optimizations
- Performance tuning
- Comprehensive validation

## Limitations (Phase 1)

- Time synchronization is placeholder implementation
- Traffic shaping is stubbed
- No actual gPTP message handling
- Stream classification uses default rules
- No hardware TSN feature utilization

These limitations will be addressed in subsequent phases while maintaining API compatibility.

## References

- IEEE 802.1Q-2018: Bridges and Bridged Networks
- IEEE 802.1AS-2020: Timing and Synchronization
- IEEE 1588-2019: Precision Time Protocol
- AUTOSAR Ethernet Integration specification