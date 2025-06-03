#pragma once

#include "Arduino.h"

class LABVEE_Scales {
public:
    /**
     * @brief Inicializa el módulo de balanza con los pines especificados.
     * 
     * @param dout Pin de datos de salida.
     * @param pd_sck Pin de reloj de salida.
     * @param gain Factor de ganancia (128, 64, 32).
     */
    void begin(byte dout, byte pd_sck, byte gain);

    /**
     * @brief Verifica si la balanza está lista para leer datos.
     * 
     * @return true si está lista, false en caso contrario.
     */
    bool is_ready();

    /**
     * @brief Configura el factor de ganancia de la balanza.
     * 
     * @param gain Factor de ganancia (128, 64, 32).
     */
    void set_gain(byte gain);

    /**
     * @brief Lee el valor actual de la balanza.
     * 
     * @return El valor leído por la balanza.
     */
    long read();
}