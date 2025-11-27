[![Designed by Sitron Labs](https://img.shields.io/badge/Designed_by-Sitron_Labs-FCE477.svg)](https://www.sitronlabs.com/)
[![Join the Discord community](https://img.shields.io/discord/552242187665145866.svg?logo=discord&logoColor=white&label=Discord&color=%237289da)](https://discord.gg/btnVDeWhfW)
[![PayPal Donate](https://img.shields.io/badge/PayPal-Donate-00457C.svg?logo=paypal&logoColor=white)](https://www.paypal.com/donate/?hosted_button_id=QLX8VU9Q3PFFL)
![License](https://img.shields.io/github/license/sitronlabs/SitronLabs_Onsemi_FSUSB43_Arduino_Library.svg)
![Latest Release](https://img.shields.io/github/release/sitronlabs/SitronLabs_Onsemi_FSUSB43_Arduino_Library.svg)
[![Arduino Library Manager](https://www.ardu-badge.com/badge/Sitron%20Labs%20Onsemi%20FSUSB43%20Arduino%20Library.svg)](https://www.ardu-badge.com/Sitron%20Labs%20Onsemi%20FSUSB43%20Arduino%20Library)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/sitronlabs/library/Sitron_Labs_Onsemi_FSUSB43_Arduino_Library.svg)](https://registry.platformio.org/libraries/sitronlabs/Sitron_Labs_Onsemi_FSUSB43_Arduino_Library)

# Sitron Labs Onsemi FSUSB43 Arduino Library

Arduino library for interfacing with the Onsemi FSUSB43 USB switch IC.

## Description

The FSUSB43 is a USB 2.0 high-speed switch IC that allows routing of USB signals between a common input and two selectable outputs. It features low on-resistance, high bandwidth, and ESD protection. This library provides a simple interface to control the switch via GPIO pins, allowing you to select which output is active or disable the switch entirely.

## Installation

### Arduino IDE

Install via the Arduino Library Manager by searching for "Sitron Labs FSUSB43".

Alternatively, install manually:
1. Download or clone this repository
2. Place it in your Arduino `libraries` folder
3. Restart the Arduino IDE

### PlatformIO

Install via the PlatformIO Library Manager by searching for "Sitron Labs FSUSB43".

Alternatively, add the library manually to your `platformio.ini` file:

```ini
lib_deps = 
    https://github.com/sitronlabs/SitronLabs_Onsemi_FSUSB43_Arduino_Library.git
```

## Hardware Connections

Connect the FSUSB43 to your Arduino using GPIO pins:

- VCC → 3.3V (check your board's specifications)
- GND → GND
- SEL → Any digital pin (output selection control)
- OE → Any digital pin (output enable, optional - set to -1 if not used)

The SEL pin controls which output is selected (LOW = OUTPUT_1, HIGH = OUTPUT_2). The OE pin enables/disables the outputs (LOW = enabled, HIGH = disabled). If OE is not connected, it must be set to -1 in the setup function, and OUTPUT_NONE cannot be used.

## Usage

### Basic Output Selection

```cpp
#include <fsusb43.h>

// Create device object
fsusb43 device;

// GPIO pins
const int PIN_SEL = 2;  // Output selection pin
const int PIN_OE = 3;   // Output enable pin (optional, set to -1 if not used)

void setup() {
  Serial.begin(9600);
  
  // Setup the FSUSB43 (selection pin, enable pin)
  if (device.setup(PIN_SEL, PIN_OE) != 0) {
    Serial.println("Failed to setup FSUSB43");
    return;
  }
  
  Serial.println("FSUSB43 initialized");
}

void loop() {
  // Route USB signals to OUTPUT_1
  Serial.println("Selecting OUTPUT_1");
  device.output_select(FSUSB43_OUTPUT_1);
  delay(2000);
  
  // Route USB signals to OUTPUT_2
  Serial.println("Selecting OUTPUT_2");
  device.output_select(FSUSB43_OUTPUT_2);
  delay(2000);
  
  // Disable outputs (requires OE pin)
  Serial.println("Disabling outputs");
  device.output_select(FSUSB43_OUTPUT_NONE);
  delay(2000);
}
```

### Without Output Enable Pin

```cpp
#include <fsusb43.h>

fsusb43 device;
const int PIN_SEL = 2;

void setup() {
  Serial.begin(9600);
  
  // Setup without OE pin (pass -1)
  device.setup(PIN_SEL, -1);
  
  Serial.println("FSUSB43 initialized (no OE pin)");
}

void loop() {
  // Switch between outputs
  device.output_select(FSUSB43_OUTPUT_1);
  delay(1000);
  device.output_select(FSUSB43_OUTPUT_2);
  delay(1000);
  
  // Note: FSUSB43_OUTPUT_NONE cannot be used without OE pin
}
```

## API Reference

### setup(int pin_sel, int pin_oe = -1)

Initializes the FSUSB43 device and configures the GPIO pins.

- `pin_sel`: GPIO pin number connected to the device's SEL (selection) pin
- `pin_oe`: GPIO pin number connected to the device's OE (output enable) pin, or -1 if not used (optional)

Returns 0 on success.

### output_select(enum fsusb43_output output)

Selects which output is active or disables all outputs.

- `output`: Desired output selection
  - `FSUSB43_OUTPUT_NONE`: Disable all outputs (requires OE pin)
  - `FSUSB43_OUTPUT_1`: Route USB signals to OUTPUT_1 (SEL = LOW)
  - `FSUSB43_OUTPUT_2`: Route USB signals to OUTPUT_2 (SEL = HIGH)

Returns 0 on success, or -EINVAL if the device is not initialized, if OUTPUT_NONE is used without an OE pin, or if an invalid output is specified.

## Specifications

- Communication interface: GPIO (digital pins)
- Number of outputs: 2
- Output enable: Optional (OE pin)
- USB standard: USB 2.0 high-speed compatible
- Control method: Direct GPIO control
