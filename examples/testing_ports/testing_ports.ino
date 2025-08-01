#include "labvee.h"
#include <DFRobotDFPlayerMini.h>

DFRobotDFPlayerMini MP3;    ///< Instancia del reproductor MP3.

void setup() {
    Serial.begin(115200); // Initialize the serial port at 115200 baud rate
    Serial.println("Testing Ports Example");
    Serial.println("This example tests the serial ports on the Arduino board.");
    Serial.println("Make sure to connect the serial port to a terminal or serial monitor.");

    labveeBegin(); // Initialize LabVee library

    UART.begin(9600); // Initialize the UART communication
    if (!MP3.begin(UART)) { // Initialize the MP3 player
        Serial.println(F("DFPlayer Mini not found! Please check the connection."));
        while (true); // Stop execution if the MP3 player is not found
    }
}

void loop() {
    Serial.println("Select an option:");
    Serial.println("1. Play MP3 file");
    Serial.println("2. Control PWM");
    Serial.println("3. Display numbers on 7-segment display");
    Serial.println("4. Wait for a keypad input");
    Serial.println("5. Exit");

    while (Serial.available() == 0); // Espera a que el usuario ingrese una opción
    char option = Serial.read(); // Lee la opción ingresada
    Serial.println();
    switch (option) {
        case '1': {
            Serial.println("Playing MP3 file...");
            MP3.play(1); // Reproduce el primer archivo MP3
            break;
        }
        case '2': {
            Serial.println("Controlling PWM...");
            PWM.set(9, 75); // Cambia el ciclo útil del pin 9 al 75%
            delay(1000); // Espera un segundo
            PWM.set(9, 25); // Cambia el ciclo útil del pin 9 al 25%
            break;
        }
        case '3': {
            Serial.println("Displaying numbers on 7-segment display...");
            DISP.reset(); ///< Resetea el display antes de mostrar nuevos valores.
    
            // Muestra los números del 0 al 99 en el display, un número por segundo.
            for (int i = 0; i < 100; i++) {  // Corrección: Se cambió la coma (,) por punto y coma (;)
                DISP.write(i);  ///< Escribe el número actual en el display.
                delay(500);      ///< Espera 1 segundo antes de mostrar el siguiente número.
            }
            break;
        }
        case '4': {
            Serial.println("Waiting for keypad input...");
            uint8_t key = KP.read();
            while (key == 0) {
                // Espera a que se presione una tecla en el teclado
                key = KP.read();
            }
            Serial.print("Key pressed: ");
            Serial.println(key); // Muestra la tecla presionada en el monitor serial
            break;
        }
        case '5': {
            Serial.println("Exiting...");
            return; // Sale del bucle principal
        }
        default: {
            Serial.println("Invalid option. Please try again.");
        }
    }
}