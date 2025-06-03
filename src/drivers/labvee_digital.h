#pragma once 

#include "Arduino.h"
#include "i2c.h"

/**
 * @brief Lee el estado de un pin digital en un terminal específico.
 * 
 * @param terminal La dirección del terminal.
 * @param pin El pin que se va a leer.
 * @return El estado actual del pin (HIGH o LOW).
 */
uint8_t DIGITAL(uint8_t terminal, uint8_t pin);

/**
 * @brief Configura el estado de un pin digital en un terminal específico.
 * 
 * @param terminal La dirección del terminal.
 * @param pin El pin que se va a configurar.
 * @param state El estado que se desea establecer (HIGH o LOW).
 */
void DIGITAL(uint8_t terminal, uint8_t pin, uint8_t state);

/**
 * @brief Configura el modo de un pin digital (entrada o salida).
 * 
 * @param terminal La dirección del terminal.
 * @param pin El pin que se va a configurar.
 * @param mode El modo del pin (INPUT o OUTPUT).
 */
void DIGITAL_Mode(uint8_t terminal, uint8_t pin, uint8_t mode);