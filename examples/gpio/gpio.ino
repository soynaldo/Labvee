#include "labvee.h"

/**
 * @brief Ejemplo de lectura y escritura en un pin digital.
 * 
 * Este ejemplo configura el pin 1 del terminal 1 como salida y lo alterna entre HIGH y LOW
 * en intervalos de un segundo. Además, se lee el estado del pin 1 del terminal 2.
 */
void setup() {
  portDIGITAL_mode(1, 1, OUTPUT); ///< Configura el pin 1 del terminal 1 como salida.
  portDIGITAL_mode(2, 1, INPUT);   ///< Configura el pin 1 del terminal 2 como entrada.
}

void loop() {
  uint8_t state = portDIGITAL(1, 7); ///< Lee el estado del pin 1 del terminal 2.
    
  if (state == HIGH) {
    portDIGITAL(1, 1, HIGH); ///< Establece el pin 1 del terminal 1 en HIGH.
  } else {
    portDIGITAL(1, 1, LOW); ///< Establece el pin 1 del terminal 1 en LOW.
  }

  delay(1000); ///< Espera 1 segundo antes de cambiar el estado nuevamente.
}
