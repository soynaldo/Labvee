#pragma once

#include "drivers/labvee_i2c.h"
#include "drivers/labvee_pwm.h"
#include "drivers/labvee_digital.h"
#include "drivers/labvee_keypad.h"
#include "drivers/labvee_display.h"


// #define GPIO1
// #define GPIO2
// #define GPIO3
// #define GPIO4

#define UART Serial ///< Puerto UART utilizado.
#define SPI SPI     ///< Puerto SPI utilizado.

/**
 * @brief Inicializa el puerto UART a 115200 baudios.
 */
#define UART_Begin() Serial.begin(115200)


#define PA1 A2 ///< Pin analógico PA1.
#define PA2 A3 ///< Pin analógico PA2.
#define PA3 A6 ///< Pin analógico PA3.
#define PA4 A7 ///< Pin analógico PA4.

/**
 * @brief Lee un valor analógico desde el pin especificado.
 * 
 * @param pin Pin analógico desde el que se leerá.
 * @return El valor analógico leído.
 */
#define ADC(pin) analogRead(pin)



