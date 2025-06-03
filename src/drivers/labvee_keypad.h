#pragma once

#include "Arduino.h"
#include "i2c.h"

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

/**
 * @brief Espera un valor del teclado.
 * 
 * Esta función bloquea hasta que se reciba un valor del teclado.
 * 
 * @return El valor del teclado.
 */
uint8_t keypadWaitValue();

/**
 * @brief Obtiene el valor actual del teclado.
 * 
 * @return El valor leído del teclado.
 */
uint8_t keypadGetValue();

/**
 * @brief Obtiene las coordenadas de la última tecla presionada.
 * 
 * @return Un objeto Coords_t con las coordenadas (x, y).
 */
Coords_t keypadGetCoords();