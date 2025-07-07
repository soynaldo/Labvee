#pragma once

#include "SoftwareSerial.h"

#define UART_TX_PIN 10 ///< Pin de transmisión del UART.
#define UART_RX_PIN 11 ///< Pin de recepción del UART.

extern SoftwareSerial UART; ///< Puerto UART utilizado.