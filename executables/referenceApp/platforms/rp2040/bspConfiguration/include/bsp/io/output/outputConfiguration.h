// Copyright 2024 Accenture.

// IGNORE_INCLUDE_GUARD_CHECK

#if defined(BSPOUTPUTCONFIG) && (BSPOUTPUTCONFIG == 1)

Output::OutputConfig const Output::sfOutputConfigurations[1][Output::NUMBER_OF_INTERNAL_OUTPUTS]
    = {{
        /*  0 */ {Io::ONBOARD_LED, Io::LOW, false},  // isInverted = false for HIGH_ACTIVE
    }};

Output::OutputConfig const* Output::getConfiguration(uint8_t /* hardwareVersion */)
{
    return &sfOutputConfigurations[0][0];
}

#else

enum OutputId
{
    /*  0 */ ONBOARD_LED,

    /* xx */ NUMBER_OF_INTERNAL_OUTPUTS,
    // TODO: dynamic outputs go here
    //       update LAST_DYNAMIC_OUTPUT when adding a new external output
    /* yy */ // MyFirstDynamicOutput,
    LAST_DYNAMIC_OUTPUT         = NUMBER_OF_INTERNAL_OUTPUTS,
    OUTPUT_PORT_UNAVAILABLE,
    
    // Additional calculated constants required by Output manager
    END_EXTERNAL_OUTPUTS = LAST_DYNAMIC_OUTPUT,
    NUMBER_OF_EXTERNAL_OUTPUTS = END_EXTERNAL_OUTPUTS - NUMBER_OF_INTERNAL_OUTPUTS,
    TOTAL_NUMBER_OF_OUTPUTS = NUMBER_OF_INTERNAL_OUTPUTS + NUMBER_OF_EXTERNAL_OUTPUTS
};
#endif /* #if (BSPOUTPUTCONFIG == 1) */