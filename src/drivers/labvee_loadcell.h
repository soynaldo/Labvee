#pragma once

#include "Arduino.h"
#include "HX711.h"

#define SCALES_DOUT_PIN 2  // Pin de datos de salida del HX711
#define SCALES_SCK_PIN 3   // Pin de reloj de salida del HX711

class LOADCELL_Class : public HX711 {
public:
    LOADCELL_Class() : HX711() {}  // Constructor que llama al constructor de la clase base HX711
    /**
     * @brief Inicializa el módulo de balanza.
     * 
     * @param gain Factor de ganancia (128, 64, 32).
     */
    void begin(uint8_t gain = 128) {
        HX711::begin(SCALES_DOUT_PIN, SCALES_SCK_PIN, gain);  // Inicializa el HX711 con los pines y ganancia por defecto
    }
};

extern LOADCELL_Class LOADCELL;  // Declaración de la instancia global de la clase LOADCELL_Class