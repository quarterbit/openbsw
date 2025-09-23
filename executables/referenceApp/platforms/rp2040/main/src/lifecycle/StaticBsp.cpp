// Copyright 2024 quarterbit

#include "lifecycle/StaticBsp.h"

#include <stdint.h>

StaticBsp::StaticBsp()
{
    // Initialize basic hardware
    // GPIO, clocks, etc. are handled by bare-metal code
}

void StaticBsp::init()
{
    hwInit();
}

void StaticBsp::hwInit()
{
    // Initialize basic RP2040 hardware
    // For now, we'll implement a minimal version without Pico SDK dependencies
    // stdio_init_all(); // Comment out for now - needs Pico SDK
    
    // TODO: Implement minimal hardware initialization here
    // This should be enough to get the basic system running
}

void StaticBsp::cyclic() 
{
    // Cyclic tasks can be added here
}

StaticBsp staticBsp;