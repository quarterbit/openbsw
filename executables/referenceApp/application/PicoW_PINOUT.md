# Raspberry Pi Pico W 2024 Pinout Reference

## Pin Configuration Table

| GPIO | Pin | Pin | GPIO | Primary Function | Secondary Functions | Special Notes |
|------|-----|-----|------|------------------|-------------------|---------------|
| GP0  | 1   | 40  | VBUS | GPIO, UART0 TX, I2C0 SDA, SPI0 RX | PWM0 A | 5V power input from USB |
| GP1  | 2   | 39  | VSYS | GPIO, UART0 RX, I2C0 SCL, SPI0 CSn | PWM0 B | System voltage input |
| GND  | 3   | 38  | GND  | Ground | Ground | Ground connection |
| GP2  | 4   | 37  | 3V3_EN | GPIO, I2C1 SDA, SPI0 SCK | PWM1 A | 3.3V regulator enable |
| GP3  | 5   | 36  | 3V3(OUT) | GPIO, I2C1 SCL, SPI0 TX | PWM1 B | 3.3V power output |
| GP4  | 6   | 35  | ADC_VREF | GPIO, UART1 TX, I2C0 SDA, SPI0 RX | PWM2 A | ADC voltage reference |
| GP5  | 7   | 34  | GP28 | GPIO, UART1 RX, I2C0 SCL, SPI0 CSn | PWM2 B | ADC2 input |
| GND  | 8   | 33  | GND  | Ground | Ground | Ground connection |
| GP6  | 9   | 32  | GP27 | GPIO, UART1 CTS, I2C1 SDA, SPI0 SCK | PWM3 A | ADC1 input |
| GP7  | 10  | 31  | GP26 | GPIO, UART1 RTS, I2C1 SCL, SPI0 TX | PWM3 B | ADC0 input |
| GP8  | 11  | 30  | RUN  | GPIO, UART1 TX, I2C0 SDA, SPI1 RX | PWM4 A | Reset pin (active low) |
| GP9  | 12  | 29  | GP22 | GPIO, UART1 RX, I2C0 SCL, SPI1 CSn | PWM4 B | |
| GND  | 13  | 28  | GND  | Ground | Ground | Ground connection |
| GP10 | 14  | 27  | GP21 | GPIO, UART1 CTS, I2C1 SDA, SPI1 SCK | PWM5 A | |
| GP11 | 15  | 26  | GP20 | GPIO, UART1 RTS, I2C1 SCL, SPI1 TX | PWM5 B | |
| GP12 | 16  | 25  | GP19 | GPIO, UART0 TX, I2C0 SDA, SPI1 RX | PWM6 A | |
| GP13 | 17  | 24  | GP18 | GPIO, UART0 RX, I2C0 SCL, SPI1 CSn | PWM6 B | |
| GND  | 18  | 23  | GND  | Ground | Ground | Ground connection |
| GP14 | 19  | 22  | GP17 | GPIO, UART0 CTS, I2C1 SDA, SPI1 SCK | PWM7 A | |
| GP15 | 20  | 21  | GP16 | GPIO, UART0 RTS, I2C1 SCL, SPI1 TX | PWM7 B | |

## Special Function Pins

### ADC Pins (Analog Input)
- **GP26 (Pin 31)**: ADC0 - Analog input channel 0
- **GP27 (Pin 32)**: ADC1 - Analog input channel 1
- **GP28 (Pin 34)**: ADC2 - Analog input channel 2
- **ADC3**: Internal temperature sensor (not on external pin)

### Power Pins
- **VBUS (Pin 40)**: 5V from USB connector
- **VSYS (Pin 39)**: Main system power input (1.8-5.5V)
- **3V3_EN (Pin 37)**: 3.3V regulator enable (pull low to disable)
- **3V3(OUT) (Pin 36)**: 3.3V regulated output
- **ADC_VREF (Pin 35)**: ADC voltage reference input

### Control Pins
- **RUN (Pin 30)**: Reset pin - pull low to reset the chip
- **GND**: Ground connections on pins 3, 8, 13, 18, 23, 28, 33, 38

## Wi-Fi Module (CYW43439)
The Pico W includes an integrated Wi-Fi module that uses the following internal connections:
- **CYW43_WL_GPIO0**: Connected to GPIO23 (not exposed)
- **CYW43_WL_GPIO1**: Connected to GPIO24 (not exposed)
- **CYW43_WL_GPIO2**: Connected to GPIO25 (not exposed)
- **CYW43_SCLK**: Connected to GPIO29 (not exposed)
- **CYW43_MOSI**: Connected to GPIO30 (not exposed)
- **CYW43_MISO**: Connected to GPIO31 (not exposed)
- **CYW43_CS**: Connected to GPIO32 (not exposed)

## Interface Summary

### UART Interfaces
- **UART0**: GP0 (TX), GP1 (RX), GP2 (CTS), GP3 (RTS) or GP12 (TX), GP13 (RX), GP14 (CTS), GP15 (RTS)
- **UART1**: GP4 (TX), GP5 (RX), GP6 (CTS), GP7 (RTS) or GP8 (TX), GP9 (RX), GP10 (CTS), GP11 (RTS)

### I2C Interfaces
- **I2C0**: GP0 (SDA), GP1 (SCL) or GP4 (SDA), GP5 (SCL) or GP8 (SDA), GP9 (SCL) or GP12 (SDA), GP13 (SCL) or GP16 (SDA), GP17 (SCL) or GP20 (SDA), GP21 (SCL)
- **I2C1**: GP2 (SDA), GP3 (SCL) or GP6 (SDA), GP7 (SCL) or GP10 (SDA), GP11 (SCL) or GP14 (SDA), GP15 (SCL) or GP18 (SDA), GP19 (SCL) or GP26 (SDA), GP27 (SCL)

### SPI Interfaces
- **SPI0**: GP0 (RX), GP1 (CSn), GP2 (SCK), GP3 (TX) or GP4 (RX), GP5 (CSn), GP6 (SCK), GP7 (TX) or GP16 (RX), GP17 (CSn), GP18 (SCK), GP19 (TX)
- **SPI1**: GP8 (RX), GP9 (CSn), GP10 (SCK), GP11 (TX) or GP12 (RX), GP13 (CSn), GP14 (SCK), GP15 (TX)

### PWM Channels
Each GPIO pin can be configured as PWM output. The PWM channels are organized in slices:
- **PWM0**: GP0 (A), GP1 (B), GP16 (A), GP17 (B)
- **PWM1**: GP2 (A), GP3 (B), GP18 (A), GP19 (B)
- **PWM2**: GP4 (A), GP5 (B), GP20 (A), GP21 (B)
- **PWM3**: GP6 (A), GP7 (B), GP22 (A), GP23 (B)
- **PWM4**: GP8 (A), GP9 (B), GP24 (A), GP25 (B)
- **PWM5**: GP10 (A), GP11 (B), GP26 (A), GP27 (B)
- **PWM6**: GP12 (A), GP13 (B), GP28 (A), GP29 (B)
- **PWM7**: GP14 (A), GP15 (B), GP30 (A), GP31 (B)

## Pin Usage Notes

### Recommended for General GPIO
All GP0-GP28 pins can be used as general purpose I/O, but consider these guidelines:

### Best Practices
- **GP0-GP15**: Excellent for general GPIO, I2C, SPI, UART
- **GP16-GP22**: Good for GPIO and PWM applications
- **GP26-GP28**: Reserve for analog inputs if ADC functionality needed
- **Avoid GP23-GP25**: Used internally by Wi-Fi module on Pico W

### Pin Drive Strength
- All GPIO pins can source/sink up to 12mA
- Total current across all pins should not exceed 50mA
- Use external buffers for high-current loads

### Voltage Levels
- All GPIO pins operate at 3.3V logic levels
- GPIO pins are **NOT** 5V tolerant
- Use voltage dividers or level shifters for 5V devices

## 🎯 **LED Proximity Demo Pin Assignments**

**Verified Pin Assignments for OpenBSW LED Proximity Demo:**
- **WS2812B Data**: GPIO16 → Physical Pin 21 (PWM7B)
- **HC-SR04 Trigger**: GPIO2 → Physical Pin 4 (PWM1A) 
- **HC-SR04 Echo**: GPIO3 → Physical Pin 5 (PWM1B)

**Hardware Connection Summary:**
```
Pico W Pin | GPIO | Function        | Device Connection
-----------|------|-----------------|------------------
Pin 4      | GP2  | Digital Output  | HC-SR04 Trigger
Pin 5      | GP3  | Digital Input   | HC-SR04 Echo  
Pin 21     | GP16 | Digital Output  | WS2812B Data In
Pin 38     | GND  | Ground          | Both devices GND
Pin 40     | VBUS | 5V Power        | Both devices VCC
```

**Pin Selection Rationale:**
- GPIO16: Excellent for WS2812B - PWM capable for precise timing
- GPIO2/GP3: Adjacent GPIOs for clean sensor wiring
- All pins have good drive strength (12mA) and are 3.3V logic
- Avoids GPIO23-25 (used by Wi-Fi module internally)

---
*Generated from https://pico.pinout.xyz/picow.html*
*Last updated: September 24, 2025*