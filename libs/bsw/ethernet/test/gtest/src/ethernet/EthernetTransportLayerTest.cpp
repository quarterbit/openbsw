// Copyright 2024 Accenture.

#include "ethernet/EthernetTransportLayer.h"

#include <gtest/gtest.h>

namespace ethernet
{

class EthernetTransportLayerTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        // Setup common test environment
    }

    void TearDown() override
    {
        // Cleanup after tests
    }

    static constexpr uint8_t TEST_BUS_ID = 3U; // ETHERNET_0
};

TEST_F(EthernetTransportLayerTest, Constructor_ShouldSetBusId)
{
    EthernetTransportLayer layer(TEST_BUS_ID);
    EXPECT_EQ(TEST_BUS_ID, layer.getBusId());
}

TEST_F(EthernetTransportLayerTest, Init_ShouldSucceed)
{
    EthernetTransportLayer layer(TEST_BUS_ID);
    auto result = layer.init();
    EXPECT_EQ(::transport::AbstractTransportLayer::ErrorCode::TP_OK, result);
}

TEST_F(EthernetTransportLayerTest, Init_CalledTwice_ShouldSucceed)
{
    EthernetTransportLayer layer(TEST_BUS_ID);
    auto result1 = layer.init();
    auto result2 = layer.init();
    
    EXPECT_EQ(::transport::AbstractTransportLayer::ErrorCode::TP_OK, result1);
    EXPECT_EQ(::transport::AbstractTransportLayer::ErrorCode::TP_OK, result2);
}

TEST_F(EthernetTransportLayerTest, Shutdown_WithoutInit_ShouldReturnSyncComplete)
{
    EthernetTransportLayer layer(TEST_BUS_ID);
    
    bool shutdownComplete = layer.shutdown(nullptr);
    EXPECT_TRUE(shutdownComplete);
}

TEST_F(EthernetTransportLayerTest, Shutdown_AfterInit_ShouldReturnSyncComplete)
{
    EthernetTransportLayer layer(TEST_BUS_ID);
    layer.init();
    
    bool shutdownComplete = layer.shutdown(nullptr);
    EXPECT_TRUE(shutdownComplete);
}

TEST_F(EthernetTransportLayerTest, Send_WithoutInit_ShouldReturnError)
{
    EthernetTransportLayer layer(TEST_BUS_ID);
    
    // Create a simple test message
    uint8_t data[] = {0x01, 0x02, 0x03, 0x04};
    ::transport::TransportMessage message(data, sizeof(data), 0x100, 0x200);
    
    auto result = layer.send(message, nullptr);
    EXPECT_EQ(::transport::AbstractTransportLayer::ErrorCode::TP_GENERAL_ERROR, result);
}

TEST_F(EthernetTransportLayerTest, Send_AfterInit_ShouldSucceed)
{
    EthernetTransportLayer layer(TEST_BUS_ID);
    layer.init();
    
    // Create a simple test message
    uint8_t data[] = {0x01, 0x02, 0x03, 0x04};
    ::transport::TransportMessage message(data, sizeof(data), 0x100, 0x200);
    
    auto result = layer.send(message, nullptr);
    EXPECT_EQ(::transport::AbstractTransportLayer::ErrorCode::TP_OK, result);
}

} // namespace ethernet