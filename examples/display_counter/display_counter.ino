#include "labvee.h"

/**
 * @brief Configuración inicial del sistema.
 * 
 * Esta función se ejecuta una vez al inicio del programa. Inicializa la comunicación
 * UART y I2C.
 */
void setup() {
  Serial.begin(115200); ///< Inicializa la comunicación UART a 115200 baudios.
  labveeBegin();  ///< Inicializa los controladores de Labvee.
}

/**
 * @brief Bucle principal del programa.
 * 
 * Esta función se ejecuta en un bucle continuo. Resetea el display y muestra 
 * los números del 0 al 99 en intervalos de un segundo.
 */
void loop() {
  DISP.reset(); ///< Resetea el display antes de mostrar nuevos valores.
    
  // Muestra los números del 0 al 99 en el display, un número por segundo.
  for (int i = 0; i < 100; i++) {  // Corrección: Se cambió la coma (,) por punto y coma (;)
    DISP.write(i);  ///< Escribe el número actual en el display.
    delay(1000);      ///< Espera 1 segundo antes de mostrar el siguiente número.
  }
}
