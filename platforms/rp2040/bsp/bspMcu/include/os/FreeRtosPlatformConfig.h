// Copyright 2024 quarterbit

#pragma once

// RP2040 specific FreeRTOS configuration
// This can be expanded with platform-specific settings as needed

// Ensure the following are defined in the toolchain or project settings:
// - configCPU_CLOCK_HZ
// - configTICK_RATE_HZ

// Example of a platform-specific setting
#define configNUM_CORES 2
#define configUSE_CORE_AFFINITY 1
