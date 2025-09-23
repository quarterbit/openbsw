// Copyright 2024 quarterbit

#include "io/Io.h"

#include "mcu/mcu.h"

using namespace bsp;

namespace bios
{

// Default pin configurations - RP2040 has 30 GPIO pins
Io::PinConfiguration const Io::fPinConfiguration[NUMBER_OF_IOS] = {
    // GP0-GP29: Default to GPIO input with pull-down
    {0, 0, _IN, 0, GPIO_FUNC_SIO},
    {1, 1, _IN, 0, GPIO_FUNC_SIO},
    {2, 2, _IN, 0, GPIO_FUNC_SIO},
    {3, 3, _IN, 0, GPIO_FUNC_SIO},
    {4, 4, _IN, 0, GPIO_FUNC_SIO},
    {5, 5, _IN, 0, GPIO_FUNC_SIO},
    {6, 6, _IN, 0, GPIO_FUNC_SIO},
    {7, 7, _IN, 0, GPIO_FUNC_SIO},
    {8, 8, _IN, 0, GPIO_FUNC_SIO},
    {9, 9, _IN, 0, GPIO_FUNC_SIO},
    {10, 10, _IN, 0, GPIO_FUNC_SIO},
    {11, 11, _IN, 0, GPIO_FUNC_SIO},
    {12, 12, _IN, 0, GPIO_FUNC_SIO},
    {13, 13, _IN, 0, GPIO_FUNC_SIO},
    {14, 14, _IN, 0, GPIO_FUNC_SIO},
    {15, 15, _IN, 0, GPIO_FUNC_SIO},
    {16, 16, _IN, 0, GPIO_FUNC_SIO},
    {17, 17, _IN, 0, GPIO_FUNC_SIO},
    {18, 18, _IN, 0, GPIO_FUNC_SIO},
    {19, 19, _IN, 0, GPIO_FUNC_SIO},
    {20, 20, _IN, 0, GPIO_FUNC_SIO},
    {21, 21, _IN, 0, GPIO_FUNC_SIO},
    {22, 22, _IN, 0, GPIO_FUNC_SIO},
    {23, 23, _IN, 0, GPIO_FUNC_SIO},
    {24, 24, _IN, 0, GPIO_FUNC_SIO},
    {25, 25, _IN, 0, GPIO_FUNC_SIO},
    {26, 26, _IN, 0, GPIO_FUNC_SIO},
    {27, 27, _IN, 0, GPIO_FUNC_SIO},
    {28, 28, _IN, 0, GPIO_FUNC_SIO},
    {29, 29, _IN, 0, GPIO_FUNC_SIO}
};

Io::Io()
{
    // Initialize GPIO subsystem
    // This would be done in hardware initialization
}

BspReturnCode Io::setDefaultConfiguration(uint16_t io)
{
    if (io < NUMBER_OF_IOS)
    {
        return setConfiguration(io, fPinConfiguration[io]);
    }
    else
    {
        return BSP_NOT_SUPPORTED;
    }
}

BspReturnCode Io::setConfiguration(uint16_t io, PinConfiguration const& cfg)
{
    if (io >= NUMBER_OF_IOS)
    {
        return BSP_NOT_SUPPORTED;
    }

    if (cfg.pinNumber != io)
    {
        // Pin number must match IO number for RP2040
        return BSP_ERROR;
    }

    // Extract function from pinCfg (RP2040 hardware-specific values)
    uint32_t func_select = cfg.pinCfg;

    // Validate function is within RP2040 range (0-31)
    if (func_select > 31)
    {
        return BSP_NOT_SUPPORTED;
    }

    // Set GPIO function in IO_BANK0
    IO_BANK0->IO[io].CTRL = func_select;

    // Configure pad settings in PADS_BANK0
    uint32_t pad_value = 0;

    // Set drive strength (use default for now)
    pad_value |= (1 << 4);  // 4mA default

    // Set pull-up/down (use default for now)
    pad_value |= (1 << 3);  // Pull down default

    // Enable input
    pad_value |= (1 << 6);

    // Apply pad configuration
    PADS_BANK0->GPIO[io] = pad_value;

    // Configure direction if SIO function (GPIO_FUNC_SIO = 5)
    if (func_select == GPIO_FUNC_SIO)
    {
        if (cfg.dir == _OUT)
        {
            // Set as output
            SIO->GPIO_OE_SET = (1 << io);
        }
        else
        {
            // Set as input
            SIO->GPIO_OE_CLR = (1 << io);
        }
    }

    return BSP_OK;
}

BspReturnCode Io::getConfiguration(uint16_t io, PinConfiguration& cfg)
{
    if (io >= NUMBER_OF_IOS)
    {
        return BSP_NOT_SUPPORTED;
    }

    // For now, return the default configuration
    // In a full implementation, this would read current GPIO settings
    cfg = fPinConfiguration[io];
    return BSP_OK;
}

bool Io::getPin(uint16_t io)
{
    if (io >= NUMBER_OF_IOS)
    {
        return false;
    }

    // Read GPIO input value
    return (SIO->GPIO_IN & (1 << io)) != 0;
}

BspReturnCode Io::setPin(uint16_t io, bool vol)
{
    if (io >= NUMBER_OF_IOS)
    {
        return BSP_NOT_SUPPORTED;
    }

    if (vol)
    {
        SIO->GPIO_OUT_SET = (1 << io);
    }
    else
    {
        SIO->GPIO_OUT_CLR = (1 << io);
    }

    return BSP_OK;
}

uint32_t Io::getPinNumber(uint16_t io)
{
    if (io >= NUMBER_OF_IOS)
    {
        return 0xFFFFFFFF;
    }

    return fPinConfiguration[io].pinNumber;
}

BspReturnCode Io::resetConfig(uint16_t io)
{
    return setDefaultConfiguration(io);
}

bool Io::getPinIrq(uint16_t io)
{
    // RP2040 GPIO interrupts are not implemented in this basic version
    // Would need to implement interrupt handling
    (void)io; // Suppress unused parameter warning
    return false;
}

} /* namespace bios */