#pragma once

#include <Arduino.h>
#include "SoftwareSerial.h"

#include "labvee_pins.h"

extern SoftwareSerial UART; ///< Puerto UART utilizado.
extern SoftwareSerial BT; ///< Puerto UART utilizado para Bluetooth.