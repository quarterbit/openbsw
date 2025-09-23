// Copyright 2024 quarterbit

#pragma once

#include <platform/estdint.h>

class StaticBsp
{
public:
    StaticBsp();

    void init();
    void hwInit();
    void cyclic();

private:
    // Add platform-specific members as needed
};

extern StaticBsp staticBsp;