#include "labvee.h"

void labveeBegin() {
    I2C_Begin();  // Inicializar I2C
    KP.begin();  // Inicializar el teclado
    DISP.begin();  // Inicializar los displays
}