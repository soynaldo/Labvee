#pragma once

#include "labvee_uart.h"
#include "DFRobotDFPlayerMini.h"

class MP3_CLASS : public DFRobotDFPlayerMini {
public:
    // Constructor: inicializa mysf_serial con los pines RX y TX
    MP3_CLASS() {}

    bool begin() {
        UART.begin(9600);       // Inicializar la comunicación serial
        return DFRobotDFPlayerMini::begin(UART);  // Inicializar el MP3 player correctamente
    }
};

extern MP3_CLASS MP3;
