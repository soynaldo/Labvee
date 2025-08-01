#pragma once 

#include "Arduino.h"
#include "labvee_ioexpander.h"
#include "labvee_pins.h"

class DIGITAL_Class {
public:
    /**
     * @brief Constructor de la clase DIGITAL_Class.
     * 
     * Inicializa los valores de los registros de terminal y configuración.
     */
    DIGITAL_Class() : ioexpander(LABVEE_DIGITAL_ADDRESS) {} // Dirección I2C del terminal

    /**
     * @brief Lee el estado de un pin digital en un terminal específico.
     * 
     * @param terminal La dirección del terminal.
     * @param pin El pin que se va a leer.
     * @return El estado actual del pin (HIGH o LOW).
     */
    uint8_t read(uint8_t terminal, uint8_t pin);

    /**
     * @brief Configura el estado de un pin digital en un terminal específico.
     * 
     * @param terminal La dirección del terminal.
     * @param pin El pin que se va a configurar.
     * @param state El estado que se desea establecer (HIGH o LOW).
     */
    void write(uint8_t terminal, uint8_t pin, uint8_t state);

    /**
     * @brief Configura el modo de un pin digital (entrada o salida).
     * 
     * @param terminal La dirección del terminal.
     * @param pin El pin que se va a configurar.
     * @param mode El modo del pin (INPUT o OUTPUT).
     */
    void mode(uint8_t terminal, uint8_t pin, uint8_t mode);

private:
    IOExpander_Class ioexpander; ///< Instancia de la clase IOExpander_Class para manejar el IO Expander.
};
