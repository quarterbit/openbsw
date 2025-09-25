# S32K148 Pinout for LED Stripe and Ultrasonic Sensor

Below is an ASCII-art diagram of the S32K148 QFP-176 package, highlighting example pins for connecting the WS2812b LED strip and the HC-SR04 ultrasonic sensor.

**Legend:**
- `*` = Pin
- `D` = Data pin for WS2812b LED strip (example: PTD5)
- `T` = Trigger pin for HC-SR04 (example: PTC6)
- `E` = Echo pin for HC-SR04 (example: PTC7)

```
      +------------------------------------------------------+
      |                                                      |
      |  S32K148 QFP-176 (Top View)                          |
      |                                                      |
      |  [*].............................................[*] |
      |  [*].............................................[*] |
      |  [*].................D...........................[*] |
      |  [*].............................................[*] |
      |  [*].................T..E.......................[*] |
      |  [*].............................................[*] |
      |  [*].............................................[*] |
      |                                                      |
      +------------------------------------------------------+
```

### Example Pin Mapping
- **WS2812b Data (D):** Pin 78 - PC14 (configured as GPIO output)
- **HC-SR04 Trigger (T):** Pin 37 - PB5 (configured as GPIO output)
- **HC-SR04 Echo (E):** Pin 36 - PB4 (configured as GPIO input)

> **Note:** These pins are already configured in the S32K148EVB ioConfiguration.h. Refer to the S32K148EVB schematic and NXP documentation for physical pin locations on the board.
