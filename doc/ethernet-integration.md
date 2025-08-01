# Ethernet Communication Support

This document describes the Ethernet communication support implementation for OpenBSW Release 0.2.

## Overview

The Ethernet communication support provides networking capabilities to complement the existing CAN transport layer. It enables:

- Diagnostics over IP (DoIP) functionality
- Enhanced networking capabilities for automotive applications
- Support for modern automotive communication protocols
- Bridge between CAN and Ethernet networks

## Architecture

### Core Components

1. **lwIP Integration** (`libs/bsw/lwip/`)
   - Provides lightweight IP stack integration
   - Optimized for automotive embedded systems
   - Supports UDP and TCP communication

2. **Ethernet Transport Layer** (`libs/bsw/ethernet/`)
   - Implements `EthernetTransportLayer` extending `AbstractTransportLayer`
   - Provides Ethernet communication using lwIP APIs
   - Handles Ethernet frame processing and routing

3. **BSP Ethernet Driver** (`libs/bsw/bsp/src/ethernet/`)
   - Low-level Ethernet hardware abstraction
   - Foundation for platform-specific implementations

4. **Transport Router Enhancement**
   - Extended `TransportRouterSimple` to support Ethernet bus IDs
   - Enables routing between CAN and Ethernet transport layers

### Bus ID Extension

The bus ID system has been extended to include:
- `SELFDIAG` (1) - Self-diagnostic bus
- `CAN_0` (2) - CAN bus 0
- `ETHERNET_0` (3) - Ethernet bus 0

## Usage

### Basic Ethernet Transport

```cpp
#include <ethernet/EthernetTransportLayer.h>
#include <lwip/LwipInterface.h>

// Initialize lwIP stack
auto lwipResult = lwip::LwipInterface::init();

// Create Ethernet transport layer
ethernet::EthernetTransportLayer ethernetLayer(busid::ETHERNET_0);
auto result = ethernetLayer.init();

// Add to transport router
transportSystem.addTransportLayer(ethernetLayer);
```

### Demo Application

The `EthernetDemoSystem` provides a complete example of Ethernet integration:

```cpp
#include <systems/EthernetDemoSystem.h>

// Create and initialize demo system
demo::EthernetDemoSystem demoSystem(context);
demoSystem.init();

// Process periodic tasks
demoSystem.cyclicTask();
```

### Console Commands

Interactive Ethernet testing is available through console commands:

```
ethernet status  - Show Ethernet status
ethernet stats   - Show network statistics  
ethernet test    - Send test message
```

## Configuration

### lwIP Configuration

Key configuration parameters in `LwipConfig`:
- `MAX_PACKET_SIZE`: 1500 bytes
- `NUM_PACKET_BUFFERS`: 4 buffers
- `TCP_MSS`: 536 bytes
- `DEFAULT_PORT`: 13400 (DoIP port)

### Ethernet Configuration

Key configuration parameters in `EthernetConfiguration`:
- `DEFAULT_UDP_PORT`: 13400 (DoIP port)
- `DEFAULT_TCP_PORT`: 13400 (DoIP port)
- `MAX_MESSAGE_SIZE`: 4095 bytes
- `MAX_PENDING_MESSAGES`: 8 messages

## Integration Points

### Transport Router

The `TransportRouterSimple` now supports routing messages between:
- CAN_0 ↔ SELFDIAG
- ETHERNET_0 ↔ SELFDIAG
- Automatic protocol bridging

### Message Flow

1. Messages received on CAN_0 are forwarded to SELFDIAG
2. Messages received on ETHERNET_0 are forwarded to SELFDIAG  
3. Messages from SELFDIAG are routed back to the originating bus

## Implementation Status

✅ **Completed Features:**
- lwIP integration module with basic interface
- EthernetTransportLayer implementing AbstractTransportLayer
- Bus ID extension for Ethernet support
- Transport router enhancement for Ethernet routing
- BSP Ethernet driver foundation
- Demo application and console commands
- Comprehensive unit tests

🚧 **Future Enhancements:**
- Full lwIP stack integration with actual network drivers
- Hardware-specific Ethernet PHY drivers
- DoIP protocol implementation
- DHCP client support
- Network configuration management

## Testing

Unit tests are provided for all new components:
- `EthernetTransportLayerTest` - Transport layer functionality
- `LwipInterfaceTest` - lwIP interface operations

Run tests with:
```bash
# Build and run tests
python3 .ci/build.py posix gcc 17
```

## Memory Usage

The implementation is designed for minimal memory footprint:
- Static buffer allocation
- Configurable buffer sizes
- Optimized for automotive embedded constraints

## Platform Support

- **POSIX**: Full support for development and testing
- **S32K148**: Foundation provided, hardware drivers needed
- **Extensible**: Architecture supports additional platforms

## Error Handling

Comprehensive error handling with specific error codes:
- `TP_OK`: Operation successful
- `TP_SEND_FAIL`: Send operation failed
- `TP_GENERAL_ERROR`: General error condition
- `TP_NETWORK_DOWN`: Network interface not available