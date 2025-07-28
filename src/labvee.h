#pragma once

#include <Arduino.h>

#include "drivers/labvee_i2c.h"
#include "drivers/labvee_pwm.h"
#include "drivers/labvee_digital.h"
#include "drivers/labvee_keypad.h"
#include "drivers/labvee_display.h"
#include "drivers/labvee_mp3.h"
#include "drivers/labvee_digital_scale.h"
#include "drivers/labvee_rfid.h"


#define PA1 A2 ///< Pin analógico PA1.
#define PA2 A3 ///< Pin analógico PA2.
#define PA3 A6 ///< Pin analógico PA3.
#define PA4 A7 ///< Pin analógico PA4.

void labveeBegin();

