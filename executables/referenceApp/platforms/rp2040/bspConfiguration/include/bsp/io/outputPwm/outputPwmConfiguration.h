// Copyright 2024 Accenture.

#pragma once

// All outputs OutputPwm::
enum outputPwm
{
    _pwmStaticStart = 0,
    dummyPwm        = _pwmStaticStart,
    _pwmStaticEnd,
    _pwmDynamicStart = _pwmStaticEnd

    ,
    ONBOARD_LED_PWM = _pwmDynamicStart,

    _pwmDynamicMark,
    _pwmChannelMax   = _pwmDynamicMark,
    PORT_UNAVAILABLE = _pwmChannelMax

}; //*enum