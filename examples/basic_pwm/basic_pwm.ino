#include "labvee.h"

/**
 * @brief Ejemplo de uso básico del módulo PWM.
 * 
 * Este ejemplo inicializa el módulo PWM con un prescaler específico y configura
 * un pin para generar una señal PWM con un ciclo útil del 50%.
 */
void setup() {
    PWM.begin(64);  ///< Inicializa el módulo PWM con un prescaler de 64.
    PWM.set(9, 50);     ///< Configura el pin 9 con un ciclo útil del 50%.
}

void loop() {
    // No se realiza ninguna operación en el loop.
}
