#include "labvee.h"

bool pressed = false; ///< Indica si el sensor táctil está presionado.
int count = 0;       ///< Contador de pulsaciones del sensor táctil.

/**
 * @brief Configuración inicial del sistema.
 * 
 * Esta función se ejecuta una vez al inicio del programa. Inicializa la comunicación
 * UART y I2C, configura el modo de los pines del sensor táctil y los LEDs RGB,
 * y resetea el display.
 */
void setup() {
  Serial.begin(115200); ///< Inicializa la comunicación UART a 115200 baudios.
  labveeBegin();  ///< Inicializa los controladores de Labvee.

  // Configura el pin del sensor táctil como entrada.
  DIGITAL.mode(1, 1, INPUT); ///< Pin 1 del terminal 1 como entrada.  
  
  // Configura los pines del LED RGB como salida.
  DIGITAL.mode(2, 1, OUTPUT); ///< Pin 1 del terminal 2 como salida (Rojo).
  DIGITAL.mode(2, 2, OUTPUT); ///< Pin 2 del terminal 2 como salida (Verde).
  DIGITAL.mode(2, 3, OUTPUT); ///< Pin 3 del terminal 2 como salida (Azul).  
  
  DISP.reset(); ///< Resetea el display para limpiar cualquier visualización anterior.
}

/**
 * @brief Bucle principal del programa.
 * 
 * Esta función se ejecuta en un bucle continuo. Detecta la pulsación del sensor táctil
 * y actualiza el contador y el display. También parpadea los LEDs RGB en respuesta
 * a la pulsación.
 */
void loop() {
  // Verifica si el sensor táctil está presionado y si no se ha registrado una pulsación anterior.
  if (DIGITAL.read(1, 1) && pressed == false) {
    count++;                     ///< Incrementa el contador.
    DISP.write(count);         ///< Muestra el nuevo valor del contador en el display.
    pressed = true;              ///< Marca que se ha registrado una pulsación.  
      
    // Parpadea los LEDs RGB.
    for (int i = 1; i < 4; i++) {
      DIGITAL.write(2, i, HIGH); ///< Enciende el LED.
      delay(50);               ///< Espera 50 ms.
      DIGITAL.write(2, i, LOW);  ///< Apaga el LED.
    }
      
  } else {
    // Resetea la variable pressed si el sensor táctil no está presionado.
    if (DIGITAL.read(1, 1) == 0) {
      pressed = false; ///< Permite registrar una nueva pulsación.
    }
  }
}
