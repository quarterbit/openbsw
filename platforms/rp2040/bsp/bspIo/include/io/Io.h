// Copyright 2024 quarterbit

#pragma once

#include "bsp/Bsp.h"
#include "io/ioPorts.h"
#include "mcu/mcu.h"
#include "platform/estdint.h"

namespace bios
{

class Io
{
public:
    Io();

    enum Level
    {
        LOW,
        HIGH
    };

    enum Direction
    {
        _DISABLED = 0,
        _IN       = (1 << 0),
        _OUT      = (1 << 1),
    };

    using tDirection = Direction;

    // Pin ID type for BSP compatibility
    using PinId = uint16_t;

    enum
    {
        clearISR = (1 << 24)
    };

    enum
    {
        unlock = 0,
        lock   = (1 << 15)
    };

    // RP2040 GPIO function selection (hardware-specific values)
    enum
    {
        GPIO_FUNC_NULL = 31,  // Disabled/null function
        GPIO_FUNC_SIO  = 5,   // SIO (GPIO)
        GPIO_FUNC_SPI  = 1,   // SPI
        GPIO_FUNC_UART = 2,   // UART
        GPIO_FUNC_I2C  = 3,   // I2C
        GPIO_FUNC_PWM  = 4,   // PWM
        GPIO_FUNC_PIO0 = 6,   // PIO0
        GPIO_FUNC_PIO1 = 7,   // PIO1
        GPIO_FUNC_GPCK = 8,   // GPCLK
        GPIO_FUNC_USB  = 9    // USB
    };

    // RP2040 drive strength
    enum
    {
        DRIVE_2MA = 0,
        DRIVE_4MA,
        DRIVE_8MA,
        DRIVE_12MA
    };

    // RP2040 pull-up/down
    enum
    {
        PULL_NONE = 0,
        PULL_UP,
        PULL_DOWN
    };

    static bool const LOW_ACTIVE  = true;
    static bool const HIGH_ACTIVE = false;

    // RP2040 Pin Definitions
    enum
    {
        // Demo application pins
        WS2812B_DATA_PIN     = 2,   // GP2 - WS2812B LED strip data
        HCSR04_TRIGGER_PIN   = 3,   // GP3 - HC-SR04 ultrasonic trigger  
        HCSR04_ECHO_PIN      = 4,   // GP4 - HC-SR04 ultrasonic echo
        
        // Standard board pins
        ONBOARD_LED          = 25,  // GP25 - Built-in LED on Pico boards
        ONBOARD_BUTTON       = 16,  // GP16 - Example button pin (user configurable)
        PORT_UNAVAILABLE     = 255  // Invalid pin marker
    };

    /**
     * \brief port configuration (aligned with S32K1xx)
     */
    struct PinConfiguration
    {
        uint8_t port;
        uint8_t pinNumber;
        uint8_t dir;
        uint8_t pinCfgExt; // reserve
        uint32_t pinCfg;
    };

    static bsp::BspReturnCode setDefaultConfiguration(uint16_t io);
    static bsp::BspReturnCode setConfiguration(uint16_t io, PinConfiguration const& cfg);
    static bsp::BspReturnCode getConfiguration(uint16_t io, PinConfiguration& cfg);
    static bool getPin(uint16_t io);
    static bsp::BspReturnCode setPin(uint16_t io, bool vol);

    static uint32_t getPinNumber(uint16_t io);
    static uint16_t const NUMBER_OF_IOS = NUMBER_OF_INPUTS_AND_OUTPUTS;
    static bsp::BspReturnCode resetConfig(uint16_t io);

    // RP2040 doesn't have separate GPIO and PORT registers like S32K
    // We use direct GPIO functions
    static bool getPinIrq(uint16_t io);

private:
    static uint16_t const MAX_GPIO_NUMBER = 30;  // GP0-GP29

    // Default pin configurations - to be defined in ioConfiguration.h
    static PinConfiguration const fPinConfiguration[NUMBER_OF_IOS];
};

} /* namespace bios */