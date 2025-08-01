// Copyright 2024 Accenture.

#include "lwip/LwipInterface.h"

#include <gtest/gtest.h>

namespace lwip
{

class LwipInterfaceTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        // Ensure clean state for each test
        LwipInterface::shutdown();
    }

    void TearDown() override
    {
        // Cleanup after tests
        LwipInterface::shutdown();
    }
};

TEST_F(LwipInterfaceTest, Init_ShouldSucceed)
{
    auto result = LwipInterface::init();
    EXPECT_EQ(LwipInterface::ErrorCode::OK, result);
    EXPECT_TRUE(LwipInterface::isNetworkUp());
}

TEST_F(LwipInterfaceTest, Init_CalledTwice_ShouldSucceed)
{
    auto result1 = LwipInterface::init();
    auto result2 = LwipInterface::init();
    
    EXPECT_EQ(LwipInterface::ErrorCode::OK, result1);
    EXPECT_EQ(LwipInterface::ErrorCode::OK, result2);
    EXPECT_TRUE(LwipInterface::isNetworkUp());
}

TEST_F(LwipInterfaceTest, Shutdown_WithoutInit_ShouldNotCrash)
{
    // Should not crash even if called without init
    EXPECT_NO_THROW(LwipInterface::shutdown());
    EXPECT_FALSE(LwipInterface::isNetworkUp());
}

TEST_F(LwipInterfaceTest, Shutdown_AfterInit_ShouldResetState)
{
    LwipInterface::init();
    EXPECT_TRUE(LwipInterface::isNetworkUp());
    
    LwipInterface::shutdown();
    EXPECT_FALSE(LwipInterface::isNetworkUp());
}

TEST_F(LwipInterfaceTest, Process_WithoutInit_ShouldNotCrash)
{
    // Should not crash even if called without init
    EXPECT_NO_THROW(LwipInterface::process());
}

TEST_F(LwipInterfaceTest, Process_AfterInit_ShouldNotCrash)
{
    LwipInterface::init();
    EXPECT_NO_THROW(LwipInterface::process());
}

TEST_F(LwipInterfaceTest, IsNetworkUp_InitialState_ShouldBeFalse)
{
    EXPECT_FALSE(LwipInterface::isNetworkUp());
}

} // namespace lwip