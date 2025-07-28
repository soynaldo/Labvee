#pragma once

#define LABVEE_KEYPAD_ADDRESS 0x20 ///< Dirección I2C del teclado.
#define LABVEE_DIGITAL_ADDRESS 0x21 ///< Dirección I2C del terminal de GPIO.
#define LABVEE_DISPLAY_ADDRESS 0x22 ///< Dirección I2C del display.

#define LABVEE_UART_RX_PIN 2 ///< Pin de transmisión del UART.
#define LABVEE_UART_TX_PIN 3 ///< Pin de recepción del UART.

#define LABVEE_BT_TX_PIN A0   ///< Pin de transmisión del Bluetooth.
#define LABVEE_BT_RX_PIN A1   ///< Pin de recepción del Bluetooth.

#define LABVEE_SCALES_DOUT_PIN 5  // Pin de datos de salida del HX711
#define LABVEE_SCALES_SCK_PIN 4   // Pin de reloj de salida del HX711

#define LABVEE_RFID_SS_PIN 10  // Pin Slave Select para el RFID