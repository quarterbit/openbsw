// Copyright 2024 Accenture.

#include "tsn/TsnConfiguration.h"
#include <gtest/gtest.h>

namespace tsn
{

class TsnConfigurationTest : public ::testing::Test
{
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TsnConfigurationTest, GetDefaultStreamConfig_ClassA_SetsCorrectValues)
{
    TsnStreamConfig config;
    
    auto result = TsnConfiguration::getDefaultStreamConfig(TsnStreamClass::CLASS_A, config);
    
    EXPECT_EQ(TsnErrorCode::OK, result);
    EXPECT_EQ(TsnStreamClass::CLASS_A, config.streamClass);
    EXPECT_EQ(TsnConfiguration::CLASS_A_PRIORITY, config.priority);
    EXPECT_EQ(TsnConfiguration::CLASS_A_MAX_LATENCY_US, config.maxLatency);
    EXPECT_EQ(10000000U, config.bandwidth);
    EXPECT_EQ(TsnConfiguration::DEFAULT_VLAN_ID, config.vlanId);
    EXPECT_TRUE(config.useShaping);
    EXPECT_FALSE(config.usePolicing);
}

TEST_F(TsnConfigurationTest, GetDefaultStreamConfig_ClassB_SetsCorrectValues)
{
    TsnStreamConfig config;
    
    auto result = TsnConfiguration::getDefaultStreamConfig(TsnStreamClass::CLASS_B, config);
    
    EXPECT_EQ(TsnErrorCode::OK, result);
    EXPECT_EQ(TsnStreamClass::CLASS_B, config.streamClass);
    EXPECT_EQ(TsnConfiguration::CLASS_B_PRIORITY, config.priority);
    EXPECT_EQ(TsnConfiguration::CLASS_B_MAX_LATENCY_US, config.maxLatency);
    EXPECT_EQ(50000000U, config.bandwidth);
    EXPECT_EQ(TsnConfiguration::DEFAULT_VLAN_ID + 1, config.vlanId);
    EXPECT_TRUE(config.useShaping);
    EXPECT_FALSE(config.usePolicing);
}

TEST_F(TsnConfigurationTest, GetDefaultStreamConfig_BestEffort_SetsCorrectValues)
{
    TsnStreamConfig config;
    
    auto result = TsnConfiguration::getDefaultStreamConfig(TsnStreamClass::BEST_EFFORT, config);
    
    EXPECT_EQ(TsnErrorCode::OK, result);
    EXPECT_EQ(TsnStreamClass::BEST_EFFORT, config.streamClass);
    EXPECT_EQ(TsnPriority::BEST_EFFORT_0, config.priority);
    EXPECT_EQ(0U, config.maxLatency);
    EXPECT_EQ(1000000U, config.bandwidth);
    EXPECT_EQ(TsnConfiguration::DEFAULT_VLAN_ID + 2, config.vlanId);
    EXPECT_FALSE(config.useShaping);
    EXPECT_FALSE(config.usePolicing);
}

TEST_F(TsnConfigurationTest, ValidateStreamConfig_ValidClassA_ReturnsOK)
{
    TsnStreamConfig config;
    TsnConfiguration::getDefaultStreamConfig(TsnStreamClass::CLASS_A, config);
    
    auto result = TsnConfiguration::validateStreamConfig(config);
    
    EXPECT_EQ(TsnErrorCode::OK, result);
}

TEST_F(TsnConfigurationTest, ValidateStreamConfig_InvalidVlanId_ReturnsError)
{
    TsnStreamConfig config;
    TsnConfiguration::getDefaultStreamConfig(TsnStreamClass::CLASS_A, config);
    config.vlanId = 0; // Invalid VLAN ID
    
    auto result = TsnConfiguration::validateStreamConfig(config);
    
    EXPECT_EQ(TsnErrorCode::INVALID_VLAN_ID, result);
}

TEST_F(TsnConfigurationTest, ValidateStreamConfig_ExcessiveBandwidthClassA_ReturnsError)
{
    TsnStreamConfig config;
    TsnConfiguration::getDefaultStreamConfig(TsnStreamClass::CLASS_A, config);
    config.bandwidth = TsnConfiguration::CLASS_A_MAX_BANDWIDTH_BPS + 1;
    
    auto result = TsnConfiguration::validateStreamConfig(config);
    
    EXPECT_EQ(TsnErrorCode::BANDWIDTH_EXCEEDED, result);
}

TEST_F(TsnConfigurationTest, ValidateStreamConfig_ExcessiveLatencyClassA_ReturnsError)
{
    TsnStreamConfig config;
    TsnConfiguration::getDefaultStreamConfig(TsnStreamClass::CLASS_A, config);
    config.maxLatency = TsnConfiguration::CLASS_A_MAX_LATENCY_US + 1;
    
    auto result = TsnConfiguration::validateStreamConfig(config);
    
    EXPECT_EQ(TsnErrorCode::LATENCY_NOT_ACHIEVABLE, result);
}

TEST_F(TsnConfigurationTest, GetClassPriority_ClassA_ReturnsVoice)
{
    auto priority = TsnConfiguration::getClassPriority(TsnStreamClass::CLASS_A);
    
    EXPECT_EQ(TsnPriority::VOICE, priority);
}

TEST_F(TsnConfigurationTest, GetClassPriority_ClassB_ReturnsVideo)
{
    auto priority = TsnConfiguration::getClassPriority(TsnStreamClass::CLASS_B);
    
    EXPECT_EQ(TsnPriority::VIDEO, priority);
}

TEST_F(TsnConfigurationTest, GetClassPriority_BestEffort_ReturnsBestEffort)
{
    auto priority = TsnConfiguration::getClassPriority(TsnStreamClass::BEST_EFFORT);
    
    EXPECT_EQ(TsnPriority::BEST_EFFORT_0, priority);
}

TEST_F(TsnConfigurationTest, GetClassMaxLatency_ClassA_ReturnsCorrectValue)
{
    auto latency = TsnConfiguration::getClassMaxLatency(TsnStreamClass::CLASS_A);
    
    EXPECT_EQ(TsnConfiguration::CLASS_A_MAX_LATENCY_US, latency);
}

TEST_F(TsnConfigurationTest, GetClassMaxLatency_ClassB_ReturnsCorrectValue)
{
    auto latency = TsnConfiguration::getClassMaxLatency(TsnStreamClass::CLASS_B);
    
    EXPECT_EQ(TsnConfiguration::CLASS_B_MAX_LATENCY_US, latency);
}

TEST_F(TsnConfigurationTest, GetClassMaxLatency_BestEffort_ReturnsZero)
{
    auto latency = TsnConfiguration::getClassMaxLatency(TsnStreamClass::BEST_EFFORT);
    
    EXPECT_EQ(0U, latency);
}

} // namespace tsn