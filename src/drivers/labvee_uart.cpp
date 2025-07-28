#include "labvee_uart.h"

SoftwareSerial UART(LABVEE_UART_RX_PIN, LABVEE_UART_TX_PIN);
SoftwareSerial BT(LABVEE_BT_TX_PIN, LABVEE_BT_RX_PIN);