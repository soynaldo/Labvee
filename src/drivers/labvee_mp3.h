#pragma once

#include "labvee_uart.h"
#include "DFRobotDFPlayerMini.h"

#define MP3_RX_PIN 10  // Define the RX pin for MP3 communication
#define MP3_TX_PIN 11  // Define the TX pin for MP3 communication

class MP3_CLASS : public DFRobotDFPlayerMini {
public:
    // Constructor: inicializa mysf_serial con los pines RX y TX
    MP3_CLASS() {}

    void begin() {
        UART.begin(9600);       // Inicializar la comunicación serial
        DFRobotDFPlayerMini::begin(UART);  // Inicializar el MP3 player correctamente
    }
};

extern MP3_CLASS MP3;
