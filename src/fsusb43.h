#ifndef FSUSB43_H
#define FSUSB43_H

/* Arduino libraries */
#include <Arduino.h>

/* C/C++ libraries */
#include <errno.h>
#include <stddef.h>
#include <stdint.h>

/**
 * @brief USB switch output selection
 *
 * Defines which output the USB switch routes signals to, or disables all outputs.
 * The FSUSB43 can route USB signals to one of two outputs or disable routing entirely.
 */
enum fsusb43_output {
    FSUSB43_OUTPUT_NONE,  //!< Disable all outputs (requires OE pin)
    FSUSB43_OUTPUT_1,     //!< Route USB signals to OUTPUT_1 (SEL = LOW)
    FSUSB43_OUTPUT_2,     //!< Route USB signals to OUTPUT_2 (SEL = HIGH)
};

/**
 * @brief FSUSB43 USB switch IC driver class
 *
 * This class provides an interface to the Onsemi FSUSB43 USB 2.0 high-speed switch IC.
 * The device allows routing of USB signals between a common input and two selectable
 * outputs via GPIO control. The switch features low on-resistance, high bandwidth,
 * and ESD protection.
 *
 * The switch is controlled using two GPIO pins:
 * - SEL (selection): Controls which output is active (LOW = OUTPUT_1, HIGH = OUTPUT_2)
 * - OE (output enable): Enables/disables the outputs (LOW = enabled, HIGH = disabled)
 *
 * @note The OE pin is optional. If not used, set pin_oe to -1 in setup().
 * @note FSUSB43_OUTPUT_NONE cannot be used if the OE pin is not connected.
 */
class fsusb43 {
   public:
    /**
     * @brief Initializes the FSUSB43 device
     *
     * Configures the GPIO pins used to control the USB switch. The SEL pin is required,
     * while the OE pin is optional.
     *
     * @param[in] pin_sel GPIO pin number connected to the device's SEL (selection) pin
     * @param[in] pin_oe GPIO pin number connected to the device's OE (output enable) pin,
     *                   or -1 if not used (optional, defaults to -1)
     * @return 0 on success
     */
    int setup(const int pin_sel, const int pin_oe = -1);

    /**
     * @brief Selects which output is active or disables all outputs
     *
     * Controls the USB switch to route signals to the selected output or disable
     * all outputs. The switch state is controlled via the SEL and OE GPIO pins.
     *
     * @param[in] output Desired output selection (OUTPUT_NONE, OUTPUT_1, or OUTPUT_2)
     * @return 0 on success, -EINVAL if device not initialized, if OUTPUT_NONE is used
     *         without an OE pin, or if an invalid output is specified
     */
    int output_select(const enum fsusb43_output output);

   protected:
    int m_pin_oe = -1;   //!< GPIO pin number for output enable (OE), -1 if not used
    int m_pin_sel = -1;  //!< GPIO pin number for output selection (SEL)
};

#endif
