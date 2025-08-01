#include "labvee.h"

/**
 * @brief Configuración inicial del sistema.
 * 
 * Esta función se ejecuta una vez al inicio del programa. Inicializa la comunicación
 * UART y I2C, y resetea el display para limpiar cualquier visualización anterior.
 */
void setup() {
  Serial.begin(115200);  ///< Inicializa la comunicación UART a 115200 baudios.
  labveeBegin();  ///< Inicializa los controladores de Labvee.
  DISP.reset();    ///< Resetea el display para limpiar la pantalla.
}

/**
 * @brief Bucle principal del programa.
 * 
 * Esta función se ejecuta en un bucle continuo. Lee el valor de un potenciómetro,
 * lo convierte a porcentaje y muestra tanto el valor bruto como el porcentaje 
 * en la salida UART. También actualiza el display con el porcentaje.
 */
void loop() {
  int pot_value = analogRead(PA1);                  ///< Lee el valor del potenciómetro en el pin PA1.
  int percent = map(pot_value, 0, 2047, 0, 99);  ///< Mapea el valor leído a un porcentaje entre 0 y 99.

  // Envía el valor del potenciómetro y el porcentaje a través de UART.
  Serial.print("Potenciometer measure: ");
  Serial.print(pot_value);
  Serial.print(", percent: ");
  Serial.println(percent);

  DISP.write(percent); ///< Muestra el porcentaje en el display.
  delay(50);             ///< Espera 50 ms antes de la próxima lectura.
}
