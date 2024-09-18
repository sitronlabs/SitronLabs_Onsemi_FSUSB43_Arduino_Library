/* Self header */
#include "fsusb43.h"

/**
 *
 * @param[in] pin_sel
 * @param[in] pin_oe Is optional.
 * @return
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
 *
 * @param[in] output
 * @return
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
