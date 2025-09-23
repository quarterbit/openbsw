// Copyright 2024 Accenture.

// IGNORE_INCLUDE_GUARD_CHECK

#if defined(BSP_INPUT_PIN_CONFIGURATION) && (BSP_INPUT_PIN_CONFIGURATION == 1)
DigitalInput::InputConfiguration const
    DigitalInput::sfDigitalInputConfigurations[][DigitalInput::NUMBER_OF_INTERNAL_DIGITAL_INPUTS]
    = {
        {
            /*  0 */ {Io::ONBOARD_BUTTON, true, 1},  // inverted = true for LOW_ACTIVE
        },
};

DigitalInput::InputConfiguration const*
DigitalInput::getConfiguration(uint8_t /* hardwareVersion */)
{
    return &sfDigitalInputConfigurations[0][0];
}

#else

enum DigitalInputId
{
    /*  0 */ ONBOARD_BUTTON,
    // TODO: other internal inputs go here
    //       update LAST_INTERNAL_DIGITAL_INPUT when adding a new internal input
    LAST_INTERNAL_DIGITAL_INPUT = ONBOARD_BUTTON,
    // TODO: dynamic inputs go here
    //       update LAST_DYNAMIC_DIGITAL_INPUT when adding a new external input
    /* yy */ // MyFirstDynamicInput,
    LAST_DYNAMIC_DIGITAL_INPUT  = LAST_INTERNAL_DIGITAL_INPUT,
    PORT_UNAVAILABLE
};
#endif /* #if (BSP_INPUT_PIN_CONFIGURATION == 1) */