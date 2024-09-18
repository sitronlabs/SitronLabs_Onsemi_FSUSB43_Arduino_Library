#ifndef FSUSB43_H
#define FSUSB43_H

/* Arduino libraries */
#include <Arduino.h>

/* C/C++ libraries */
#include <errno.h>
#include <stddef.h>
#include <stdint.h>

/**
 *
 */
enum fsusb43_output {
    FSUSB43_OUTPUT_NONE,
    FSUSB43_OUTPUT_1,
    FSUSB43_OUTPUT_2,
};

/**
 *
 */
class fsusb43 {
   public:
    int setup(const int pin_sel, const int pin_oe = -1);
    int output_select(const enum fsusb43_output output);

   protected:
    int m_pin_oe = -1;
    int m_pin_sel = -1;
};

#endif
