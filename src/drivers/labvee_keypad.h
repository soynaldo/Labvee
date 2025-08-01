#pragma once

#include "Arduino.h"
#include "labvee_ioexpander.h"
#include "labvee_pins.h"

/**
 * @class Coords_t
 * @brief Clase para almacenar coordenadas en el espacio 2D.
 * 
 * Esta clase representa un punto en un plano 2D con coordenadas enteras (x, y).
 */
class Coords_t {
public:
    /**
     * @brief Coordenada X en el plano.
     * 
     * Representa la posición en el eje horizontal.
     */
    int x = 0;

    /**
     * @brief Coordenada Y en el plano.
     * 
     * Representa la posición en el eje vertical.
     */
    int y = 0;
};


class KEYPAD_Class {
public:
    /**
     * @brief Constructor de la clase KEYPAD_Class.
     * 
     * Inicializa la instancia de IOExpander_Class para manejar el IO Expander del teclado.
     */
    KEYPAD_Class() : ioexpander(LABVEE_KEYPAD_ADDRESS) {} // Dirección I2C del teclado

    /**
     * @brief Inicializa el teclado.
     * 
     * Configura el IO Expander y prepara el teclado para su uso.
     */
    void begin();

    /**
     * @brief Obtiene el valor actual del teclado.
     * 
     * @return El valor leído del teclado.
     */
    uint8_t read();

    /**
     * @brief Espera hasta que se presione una tecla y devuelve su valor.
     * 
     * @return El valor de la tecla presionada.
     */
    uint8_t wait();

    /**
     * @brief Obtiene las coordenadas de la última tecla presionada.
     * 
     * @return Un objeto Coords_t con las coordenadas (x, y).
     */
    Coords_t coords();

private:
    IOExpander_Class ioexpander; ///< Instancia de la clase IOExpander_Class para manejar el IO Expander.
};
