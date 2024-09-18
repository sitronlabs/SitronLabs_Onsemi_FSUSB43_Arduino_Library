/* Self header */
#include "fsusb43.h"

/**
 * @brief Initializes the FSUSB43 device
 *
 * Configures the GPIO pins used to control the USB switch. The SEL pin is required
 * and must be connected to a GPIO pin. The OE pin is optional - if not connected
 * to the device, pass -1 for pin_oe.
 *
 * @note Call this from the Arduino setup() function.
 * @note The GPIO pins will be configured as outputs.
 *
 * @param[in] pin_sel GPIO pin number connected to the device's SEL (selection) pin
 * @param[in] pin_oe GPIO pin number connected to the device's OE (output enable) pin,
 *                   or -1 if not used (optional)
 * @return 0 on success
 */
int fsusb43::setup(const int pin_sel, const int pin_oe) {

    /* Store parameters */
    m_pin_sel = pin_sel;
    m_pin_oe = pin_oe;

    /* Configure gpios as outputs */
    pinMode(m_pin_sel, OUTPUT);
    if (pin_oe != -1) {
        pinMode(m_pin_oe, OUTPUT);
    }

    /* Return success */
    return 0;
}

/**
 * @brief Selects which output is active or disables all outputs
 *
 * Controls the USB switch to route signals to the selected output or disable
 * all outputs. The switch state is controlled via the SEL and OE GPIO pins:
 * - OUTPUT_1: Sets SEL to LOW, OE to LOW (if used)
 * - OUTPUT_2: Sets SEL to HIGH, OE to LOW (if used)
 * - OUTPUT_NONE: Sets OE to HIGH (requires OE pin)
 *
 * @param[in] output Desired output selection (OUTPUT_NONE, OUTPUT_1, or OUTPUT_2)
 * @return 0 on success, -EINVAL if device not initialized (setup() not called),
 *         if OUTPUT_NONE is used without an OE pin, or if an invalid output is specified
 */
int fsusb43::output_select(const enum fsusb43_output output) {

    /* Ensure gpios have been configured */
    if (m_pin_sel == -1) {
        return -EINVAL;
    }

    /* Toggle gpios to produce the direct output */
    switch (output) {
        case FSUSB43_OUTPUT_NONE: {
            if (m_pin_oe != -1) {
                digitalWrite(m_pin_oe, 1);
            } else {
                return -EINVAL;
            }
            break;
        }
        case FSUSB43_OUTPUT_1: {
            digitalWrite(m_pin_sel, 0);
            if (m_pin_oe != -1) {
                digitalWrite(m_pin_oe, 0);
            }
            break;
        }
        case FSUSB43_OUTPUT_2: {
            digitalWrite(m_pin_sel, 1);
            if (m_pin_oe != -1) {
                digitalWrite(m_pin_oe, 0);
            }
            break;
        }
        default: {
            return -EINVAL;
        }
    }

    /* Return success */
    return 0;
}
