// Copyright 2024 Accenture.

#include "ethernet/console/EthernetDemoCommand.h"
#include "systems/EthernetDemoSystem.h"

#include <lwip/LwipInterface.h>
#include <busid/BusId.h>
#include <transport/TransportMessage.h>
#include <util/stream/ISharedOutputStream.h>

namespace demo
{
namespace console
{

char const* EthernetDemoCommand::getName() const
{
    return "ethernet";
}

char const* EthernetDemoCommand::getDescription() const
{
    return "Ethernet demo commands";
}

void EthernetDemoCommand::execute(
    ::util::stream::ISharedOutputStream& outputStream,
    uint8_t argc,
    char const* const argv[])
{
    if (argc < 2)
    {
        showHelp(outputStream);
        return;
    }

    if (strcmp(argv[1], "status") == 0)
    {
        showStatus(outputStream);
    }
    else if (strcmp(argv[1], "stats") == 0)
    {
        showStatistics(outputStream);
    }
    else if (strcmp(argv[1], "test") == 0)
    {
        testSend(outputStream);
    }
    else
    {
        outputStream.printf("Unknown command: %s\n", argv[1]);
        showHelp(outputStream);
    }
}

void EthernetDemoCommand::showStatus(::util::stream::ISharedOutputStream& outputStream)
{
    outputStream.printf("=== Ethernet Demo Status ===\n");
    
    // Check if lwIP is initialized
    bool networkUp = ::lwip::LwipInterface::isNetworkUp();
    outputStream.printf("Network Status: %s\n", networkUp ? "UP" : "DOWN");
    
    // Check if demo system exists and is initialized
    if (::demo::EthernetDemoSystem::hasInstance())
    {
        auto& demoSystem = ::demo::EthernetDemoSystem::getInstance();
        outputStream.printf("Demo System: ACTIVE\n");
        
        // Show transport layer bus ID
        auto& transportLayer = demoSystem.getEthernetTransportLayer();
        outputStream.printf("Bus ID: %u (ETHERNET_0)\n", 
                          static_cast<unsigned>(transportLayer.getBusId()));
        
        outputStream.printf("Transport Layer: INITIALIZED\n");
    }
    else
    {
        outputStream.printf("Demo System: NOT ACTIVE\n");
    }
    
    outputStream.printf("===========================\n");
}

void EthernetDemoCommand::showStatistics(::util::stream::ISharedOutputStream& outputStream)
{
    outputStream.printf("=== Ethernet Statistics ===\n");
    
    if (::demo::EthernetDemoSystem::hasInstance())
    {
        auto& demoSystem = ::demo::EthernetDemoSystem::getInstance();
        
        uint32_t messagesSent = 0U;
        uint32_t messagesReceived = 0U;
        demoSystem.getNetworkStatistics(messagesSent, messagesReceived);
        
        outputStream.printf("Messages Sent: %u\n", static_cast<unsigned>(messagesSent));
        outputStream.printf("Messages Received: %u\n", static_cast<unsigned>(messagesReceived));
        
        // Show network status
        outputStream.printf("Network Interface: %s\n", 
                          ::lwip::LwipInterface::isNetworkUp() ? "UP" : "DOWN");
    }
    else
    {
        outputStream.printf("Demo system not active\n");
    }
    
    outputStream.printf("============================\n");
}

void EthernetDemoCommand::testSend(::util::stream::ISharedOutputStream& outputStream)
{
    outputStream.printf("=== Ethernet Test Send ===\n");
    
    if (!::demo::EthernetDemoSystem::hasInstance())
    {
        outputStream.printf("Error: Demo system not active\n");
        return;
    }
    
    if (!::lwip::LwipInterface::isNetworkUp())
    {
        outputStream.printf("Error: Network is down\n");
        return;
    }
    
    auto& demoSystem = ::demo::EthernetDemoSystem::getInstance();
    auto& transportLayer = demoSystem.getEthernetTransportLayer();
    
    // Create a test message
    uint8_t testData[] = {'H', 'e', 'l', 'l', 'o', ' ', 'E', 't', 'h', 'e', 'r', 'n', 'e', 't'};
    ::transport::TransportMessage testMessage(testData, sizeof(testData), 0x100, 0x200);
    
    // Send the test message
    auto result = transportLayer.send(testMessage, nullptr);
    
    if (result == ::transport::AbstractTransportLayer::ErrorCode::TP_OK)
    {
        outputStream.printf("Test message sent successfully!\n");
        outputStream.printf("Message: \"Hello Ethernet\"\n");
        outputStream.printf("Size: %u bytes\n", static_cast<unsigned>(sizeof(testData)));
    }
    else
    {
        outputStream.printf("Failed to send test message (error code: %u)\n", 
                          static_cast<unsigned>(result));
    }
    
    outputStream.printf("===========================\n");
}

void EthernetDemoCommand::showHelp(::util::stream::ISharedOutputStream& outputStream)
{
    outputStream.printf("Ethernet Demo Commands:\n");
    outputStream.printf("  ethernet status  - Show Ethernet status\n");
    outputStream.printf("  ethernet stats   - Show network statistics\n");
    outputStream.printf("  ethernet test    - Send test message\n");
}

} // namespace console
} // namespace demo