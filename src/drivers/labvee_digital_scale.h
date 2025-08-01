#pragma once

#include "Arduino.h"
#include "HX711.h"
#include "labvee_pins.h"

class DS_Class : public HX711 {
public:
    DS_Class() : HX711() {}  // Constructor que llama al constructor de la clase base HX711
    /**
     * @brief Inicializa el módulo de balanza.
     * 
     * @param gain Factor de ganancia (128, 64, 32).
     */
    void begin(uint8_t gain = 128) {
        HX711::begin(LABVEE_SCALES_DOUT_PIN, LABVEE_SCALES_SCK_PIN, gain);  // Inicializa el HX711 con los pines y ganancia por defecto
    }
};
