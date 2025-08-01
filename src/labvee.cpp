#include "labvee.h"

void labveeBegin() {
    I2C_Begin();  // Inicializar I2C
    KP.begin();  // Inicializar el teclado
    DISP.begin();  // Inicializar los displays
}

SoftwareSerial UART(LABVEE_UART_RX_PIN, LABVEE_UART_TX_PIN);
SoftwareSerial BT(LABVEE_BT_TX_PIN, LABVEE_BT_RX_PIN);
MFRC522 RFID(LABVEE_RFID_SS_PIN);  // Pin RST, Pin SS

DISPLAY_Class DISP; ///< Instancia de la clase DISPLAY_Class para su uso en el programa.
KEYPAD_Class KP;    ///< Instancia de la clase KEYPAD_Class para su uso en el programa.
DIGITAL_Class DIGITAL; ///< Instancia de la clase DIGITAL_Class para su uso en el programa.

PWM_Class PWM; ///< Instancia de la clase PWM_Class para su uso en el programa.
DS_Class DS; ///< Instancia de la clase DS_Class para su uso en el programa.