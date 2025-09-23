/**
 * RP2040 AnalogInput Implementation
 * Direct register access ADC implementation for OpenBSW
 */

#include "bsp/adc/AnalogInput.h"
#include "rp2040_registers.h"

namespace bios
{

bool AnalogInput::fInitialized = false;

void AnalogInput::init()
{
    if (fInitialized) {
        return;
    }

    volatile rp2040::AdcRegisters* adc = rp2040::getAdcRegisters();
    
    // Enable ADC
    adc->CS = rp2040::adc_bits::CS_EN;
    
    // Wait for ADC to be ready
    while (!(adc->CS & rp2040::adc_bits::CS_READY)) {
        // Wait
    }
    
    fInitialized = true;
}

bsp::BspReturnCode AnalogInput::get(uint16_t channel, uint16_t& value)
{
    if (!fInitialized) {
        return bsp::BSP_ERROR;
    }
    
    if (channel > 4) { // RP2040 has ADC inputs 0-2 and temp sensor on 4
        return bsp::BSP_ERROR;
    }
    
    volatile rp2040::AdcRegisters* adc = rp2040::getAdcRegisters();
    
    // Select channel and start conversion
    adc->CS = rp2040::adc_bits::CS_EN | rp2040::adc_bits::CS_START_ONCE | (channel & rp2040::adc_bits::CS_AINSEL_MASK);
    
    // Wait for conversion to complete
    while (!(adc->CS & rp2040::adc_bits::CS_READY)) {
        // Wait
    }
    
    // Read result (12-bit value in lower bits)
    value = adc->RESULT & 0xFFF;
    
    return bsp::BSP_OK;
}

} // namespace bios