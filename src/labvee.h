#pragma once

#include <Arduino.h>
#include "SoftwareSerial.h"
#include <SPI.h>
#include <MFRC522.h>

#include "drivers/labvee_pins.h"
#include "drivers/labvee_i2c.h"
#include "drivers/labvee_pwm.h"
#include "drivers/labvee_digital.h"
#include "drivers/labvee_keypad.h"
#include "drivers/labvee_display.h"
#include "drivers/labvee_digital_scale.h"

#define PA1 A2 ///< Pin analógico PA1.
#define PA2 A3 ///< Pin analógico PA2.
#define PA3 A6 ///< Pin analógico PA3.
#define PA4 A7 ///< Pin analógico PA4.

extern SoftwareSerial UART; ///< Puerto UART utilizado.
extern SoftwareSerial BT; ///< Puerto UART utilizado para Bluetooth.
extern MFRC522 RFID;  ///< Instancia del lector RFID MFRC522.

extern DISPLAY_Class DISP; ///< Instancia de la clase DISPLAY_Class para su uso en el programa.
extern KEYPAD_Class KP;    ///< Instancia de la clase KEYPAD_Class para su uso en el programa.
extern DIGITAL_Class DIGITAL; ///< Instancia de la clase DIGITAL_Class para su uso en el programa.
extern PWM_Class PWM; ///< Instancia de la clase PWM_Class para su uso en el programa.
extern DS_Class DS; ///< Instancia de la clase DS_Class para su uso en el programa.

void labveeBegin();