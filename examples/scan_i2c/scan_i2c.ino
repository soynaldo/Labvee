#include "labvee.h"

void setup() {
    Serial.begin(115200);  // Inicializar UART
    labveeBegin();  // Inicializar Labvee drivers
    I2C_Scan();  // Escanear el bus I2C para detectar dispositivos conectados e Imprimir los resultados
}

void loop(){
    // No se realiza ninguna operación en el loop.
}