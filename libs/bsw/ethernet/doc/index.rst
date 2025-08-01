Ethernet Transport Layer
========================

This module provides Ethernet communication support for OpenBSW transport layer.

Features:
- Ethernet transport layer implementation extending AbstractTransportLayer
- UDP and TCP communication support via lwIP
- Integration with existing transport router
- Support for automotive Ethernet protocols

Usage:
- Integrates with TransportRouterSimple for message routing
- Supports both point-to-point and broadcast communication
- Compatible with existing transport message framework