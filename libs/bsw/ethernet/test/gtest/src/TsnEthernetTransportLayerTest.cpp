// Copyright 2024 Accenture.

#include "ethernet/TsnEthernetTransportLayer.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

namespace ethernet
{

class TsnEthernetTransportLayerTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        tsnLayer = std::make_unique<TsnEthernetTransportLayer>(TEST_BUS_ID);
    }
    
    void TearDown() override
    {
        if (tsnLayer)
        {
            tsnLayer->shutdown(nullptr);
        }
    }
    
    static constexpr uint8_t TEST_BUS_ID = 1U;
    std::unique_ptr<TsnEthernetTransportLayer> tsnLayer;
};

TEST_F(TsnEthernetTransportLayerTest, Constructor_ValidBusId_CreatesInstance)
{
    EXPECT_NE(nullptr, tsnLayer);
}

TEST_F(TsnEthernetTransportLayerTest, Init_FirstCall_ReturnsOK)
{
    auto result = tsnLayer->init();
    
    EXPECT_EQ(::transport::AbstractTransportLayer::ErrorCode::TP_OK, result);
}

TEST_F(TsnEthernetTransportLayerTest, RegisterStream_ClassA_ReturnsOKAndValidStreamId)
{
    tsnLayer->init();
    
    ::tsn::StreamId streamId;
    auto result = tsnLayer->registerStream(
        ::tsn::TsnStreamClass::CLASS_A,
        10000000U, // 10 Mbps
        2000U,     // 2ms latency
        streamId
    );
    
    EXPECT_EQ(::transport::AbstractTransportLayer::ErrorCode::TP_OK, result);
    EXPECT_GT(streamId, 0U);
}

TEST_F(TsnEthernetTransportLayerTest, RegisterStream_ClassB_ReturnsOKAndValidStreamId)
{
    tsnLayer->init();
    
    ::tsn::StreamId streamId;
    auto result = tsnLayer->registerStream(
        ::tsn::TsnStreamClass::CLASS_B,
        50000000U, // 50 Mbps
        50000U,    // 50ms latency
        streamId
    );
    
    EXPECT_EQ(::transport::AbstractTransportLayer::ErrorCode::TP_OK, result);
    EXPECT_GT(streamId, 0U);
}

TEST_F(TsnEthernetTransportLayerTest, RegisterStream_BestEffort_ReturnsOKAndValidStreamId)
{
    tsnLayer->init();
    
    ::tsn::StreamId streamId;
    auto result = tsnLayer->registerStream(
        ::tsn::TsnStreamClass::BEST_EFFORT,
        1000000U,  // 1 Mbps
        0U,        // No latency guarantee
        streamId
    );
    
    EXPECT_EQ(::transport::AbstractTransportLayer::ErrorCode::TP_OK, result);
    EXPECT_GT(streamId, 0U);
}

TEST_F(TsnEthernetTransportLayerTest, UnregisterStream_ValidStreamId_ReturnsOK)
{
    tsnLayer->init();
    
    ::tsn::StreamId streamId;
    tsnLayer->registerStream(
        ::tsn::TsnStreamClass::CLASS_A,
        10000000U,
        2000U,
        streamId
    );
    
    auto result = tsnLayer->unregisterStream(streamId);
    
    EXPECT_EQ(::transport::AbstractTransportLayer::ErrorCode::TP_OK, result);
}

TEST_F(TsnEthernetTransportLayerTest, UnregisterStream_InvalidStreamId_ReturnsError)
{
    tsnLayer->init();
    
    auto result = tsnLayer->unregisterStream(999U); // Non-existent stream ID
    
    EXPECT_EQ(::transport::AbstractTransportLayer::ErrorCode::TP_GENERAL_ERROR, result);
}

TEST_F(TsnEthernetTransportLayerTest, GetStreamStatistics_ValidStreamId_ReturnsOK)
{
    tsnLayer->init();
    
    ::tsn::StreamId streamId;
    tsnLayer->registerStream(
        ::tsn::TsnStreamClass::CLASS_A,
        10000000U,
        2000U,
        streamId
    );
    
    uint32_t messagesSent, messagesDropped;
    auto result = tsnLayer->getStreamStatistics(streamId, messagesSent, messagesDropped);
    
    EXPECT_EQ(::transport::AbstractTransportLayer::ErrorCode::TP_OK, result);
    EXPECT_EQ(0U, messagesSent);    // Initially zero
    EXPECT_EQ(0U, messagesDropped); // Initially zero
}

TEST_F(TsnEthernetTransportLayerTest, GetStreamStatistics_InvalidStreamId_ReturnsError)
{
    tsnLayer->init();
    
    uint32_t messagesSent, messagesDropped;
    auto result = tsnLayer->getStreamStatistics(999U, messagesSent, messagesDropped);
    
    EXPECT_EQ(::transport::AbstractTransportLayer::ErrorCode::TP_GENERAL_ERROR, result);
}

TEST_F(TsnEthernetTransportLayerTest, IsTimeSynchronized_InitialState_ReturnsFalse)
{
    tsnLayer->init();
    
    bool synchronized = tsnLayer->isTimeSynchronized();
    
    EXPECT_FALSE(synchronized);
}

TEST_F(TsnEthernetTransportLayerTest, RegisterMultipleStreams_WithinLimits_AllSucceed)
{
    tsnLayer->init();
    
    // Register multiple streams of different classes
    ::tsn::StreamId streamId1, streamId2, streamId3;
    
    auto result1 = tsnLayer->registerStream(::tsn::TsnStreamClass::CLASS_A, 10000000U, 2000U, streamId1);
    auto result2 = tsnLayer->registerStream(::tsn::TsnStreamClass::CLASS_B, 50000000U, 50000U, streamId2);
    auto result3 = tsnLayer->registerStream(::tsn::TsnStreamClass::BEST_EFFORT, 1000000U, 0U, streamId3);
    
    EXPECT_EQ(::transport::AbstractTransportLayer::ErrorCode::TP_OK, result1);
    EXPECT_EQ(::transport::AbstractTransportLayer::ErrorCode::TP_OK, result2);
    EXPECT_EQ(::transport::AbstractTransportLayer::ErrorCode::TP_OK, result3);
    
    // Verify all stream IDs are unique
    EXPECT_NE(streamId1, streamId2);
    EXPECT_NE(streamId1, streamId3);
    EXPECT_NE(streamId2, streamId3);
}

TEST_F(TsnEthernetTransportLayerTest, Shutdown_AfterInit_CompletesSuccessfully)
{
    tsnLayer->init();
    
    // Register some streams
    ::tsn::StreamId streamId;
    tsnLayer->registerStream(::tsn::TsnStreamClass::CLASS_A, 10000000U, 2000U, streamId);
    
    bool shutdownCompleted = tsnLayer->shutdown(nullptr);
    
    EXPECT_TRUE(shutdownCompleted);
    
    // Verify streams are cleared after shutdown
    uint32_t messagesSent, messagesDropped;
    auto result = tsnLayer->getStreamStatistics(streamId, messagesSent, messagesDropped);
    EXPECT_EQ(::transport::AbstractTransportLayer::ErrorCode::TP_GENERAL_ERROR, result);
}

} // namespace ethernet