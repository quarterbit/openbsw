/**
 * RP2040 Analog Input Configuration
 * Simple ADC implementation for OpenBSW
 */

// IGNORE_INCLUDE_GUARD_CHECK

#if defined(BSP_ANALOGINPUT_PIN_CONFIGURATION) && (BSP_ANALOGINPUT_PIN_CONFIGURATION == 1)
/**
 * Configuration of analog signals
 *
 * Order must be the same as the order of the signal IDs defined below.
 *
 *      <ADC device>, <external input>, <pin>, <conversion channel>
 */
AnalogInput::tAnalogConfiguration const ADChannelCfg[AnalogInput::_AdcChannelMax] = {
    {ADC_0_CH, 0, 0, 0}, // GPIO26 - ADC0 input
    {ADC_0_CH, 1, 1, 1}, // GPIO27 - ADC1 input
    {ADC_0_CH, 2, 2, 2}, // GPIO28 - ADC2 input
};

#else
/**
 * Analog input signal IDs
 */
enum AnalogInputId
{
    AiADC0,  // GPIO26 - ADC channel 0
    AiADC1,  // GPIO27 - ADC channel 1  
    AiADC2,  // GPIO28 - ADC channel 2

    // end marker
    _AdcChannelMax
};

#endif