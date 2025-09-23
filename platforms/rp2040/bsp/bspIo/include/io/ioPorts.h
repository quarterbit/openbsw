// Copyright 2024 quarterbit

#pragma once

#include "platform/estdint.h"

enum IOPort
{
    _PORTA_     = 0,  // RP2040 has only one "port" - all GPIOs
    _PORTS_MAX_ = 1,
    GP0         = 0,
    GP1,
    GP2,
    GP3,
    GP4,
    GP5,
    GP6,
    GP7,
    GP8,
    GP9,
    GP10,
    GP11,
    GP12,
    GP13,
    GP14,
    GP15,
    GP16,
    GP17,
    GP18,
    GP19,
    GP20,
    GP21,
    GP22,
    GP23,
    GP24,
    GP25,
    GP26,
    GP27,
    GP28,
    GP29,
    // Special pins
    GP30 = 30,  // Not a real GPIO, but used for numbering
    GP31 = 31   // Not a real GPIO, but used for numbering
};

#define NUMBER_OF_INPUTS_AND_OUTPUTS 30  // GP0-GP29
#define NUM_PORTS 1  // RP2040 has only one GPIO port