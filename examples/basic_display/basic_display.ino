#include "labvee.h"

/**
 * @brief Ejemplo de uso de un display de 7 segmentos.
 * 
 * Este ejemplo escribe el número "3" en el display de las unidades (DISPLAY_U) utilizando
 * segmentos individuales. También se activa el punto decimal.
 */
void setup() {
  I2C_Begin();
  displayReset(DISPLAY_U); ///< Resetea el display de las unidades.
    
  // Activa los segmentos A, B, C, D y G para formar el número "3".
  displaySegment(DISPLAY_U, 1, 1, 1, 1, 0, 0, 1, 1); ///< Escribe el número "3" con DP encendido.
}

void loop() {
    // No se realiza ninguna operación en el loop.
}
