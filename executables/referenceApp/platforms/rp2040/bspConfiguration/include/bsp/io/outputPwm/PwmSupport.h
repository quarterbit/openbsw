// Copyright 2024 Accenture.

#pragma once

#include "outputPwm/OutputPwm.h"

namespace bios
{
class PwmSupport : public OutputPwm::IDynamicPwmClient
{
public:
    PwmSupport();
    void init();
    void start();
    void stop();
    void shutdown();
    virtual bsp::BspReturnCode setDuty(uint16_t chan, uint16_t duty, bool immediateUpdate);
    virtual bsp::BspReturnCode setPeriod(uint16_t chan, uint16_t period);

private:
    // RP2040 PWM implementation will go here
    // For now, just a stub implementation
};

} // namespace bios