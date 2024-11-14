#pragma once

#include "i2c.h"
#include "pwm.h"
#include "coordinates.h"
#include <Arduino.h>


// #define GPIO1
// #define GPIO2
// #define GPIO3
// #define GPIO4


// Definiciones para los segmentos de los displays
#define D1_A 0  ///< Segmento A del display 1.
#define D1_B 1  ///< Segmento B del display 1.
#define D1_C 2  ///< Segmento C del display 1.
#define D1_D 3  ///< Segmento D del display 1.
#define D1_E 4  ///< Segmento E del display 1.
#define D1_F 5  ///< Segmento F del display 1.
#define D1_G 6  ///< Segmento G del display 1.
#define D1_DP 7 ///< Punto decimal del display 1.

#define D2_A 8  ///< Segmento A del display 2.
#define D2_B 9  ///< Segmento B del display 2.
#define D2_C 10 ///< Segmento C del display 2.
#define D2_D 11 ///< Segmento D del display 2.
#define D2_E 12 ///< Segmento E del display 2.
#define D2_F 13 ///< Segmento F del display 2.
#define D2_G 14 ///< Segmento G del display 2.
#define D2_DP 15 ///< Punto decimal del display 2.

#define PA1 A2 ///< Pin analógico PA1.
#define PA2 A3 ///< Pin analógico PA2.
#define PA3 A6 ///< Pin analógico PA3.
#define PA4 A7 ///< Pin analógico PA4.

#define DISPLAY_U 1 ///< Display de unidades.
#define DISPLAY_D 2 ///< Display de decenas.

#define UART Serial ///< Puerto UART utilizado.
#define SPI SPI     ///< Puerto SPI utilizado.

/**
 * @brief Inicializa el puerto UART a 115200 baudios.
 */
#define UART_Begin() Serial.begin(115200)

/**
 * @brief Lee un valor analógico desde el pin especificado.
 * 
 * @param pin Pin analógico desde el que se leerá.
 * @return El valor analógico leído.
 */
#define ADC(pin) analogRead(pin)

#define KEYPAD_ADDRESS 0x20 ///< Dirección I2C del teclado.
#define TERMINAL_ADDRESS 0x21 ///< Dirección I2C del terminal.
#define DISPLAY_ADDRESS 0x22 ///< Dirección I2C del display.

/**
 * @brief Lee el estado de un pin digital en un terminal específico.
 * 
 * @param terminal La dirección del terminal.
 * @param pin El pin que se va a leer.
 * @return El estado actual del pin (HIGH o LOW).
 */
uint8_t DIGITAL(uint8_t terminal, uint8_t pin);

/**
 * @brief Configura el estado de un pin digital en un terminal específico.
 * 
 * @param terminal La dirección del terminal.
 * @param pin El pin que se va a configurar.
 * @param state El estado que se desea establecer (HIGH o LOW).
 */
void DIGITAL(uint8_t terminal, uint8_t pin, uint8_t state);

/**
 * @brief Configura el modo de un pin digital (entrada o salida).
 * 
 * @param terminal La dirección del terminal.
 * @param pin El pin que se va a configurar.
 * @param mode El modo del pin (INPUT o OUTPUT).
 */
void DIGITAL_Mode(uint8_t terminal, uint8_t pin, uint8_t mode);

/**
 * @brief Espera un valor del teclado.
 * 
 * Esta función bloquea hasta que se reciba un valor del teclado.
 * 
 * @return El valor del teclado.
 */
uint8_t keypadWaitValue();

/**
 * @brief Obtiene el valor actual del teclado.
 * 
 * @return El valor leído del teclado.
 */
uint8_t keypadGetValue();

/**
 * @brief Obtiene las coordenadas de la última tecla presionada.
 * 
 * @return Un objeto Coords_t con las coordenadas (x, y).
 */
Coords_t keypadGetCoords();

/**
 * @brief Resetea un display específico.
 * 
 * @param display El número del display a resetear.
 */
void displayReset(uint8_t display);

/**
 * @brief Resetea ambos displays.
 */
void displayReset();

/**
 * @brief Escribe un valor en un display específico.
 * 
 * @param display El número del display donde se escribirá.
 * @param value El valor que se va a escribir.
 */
void displayWrite(uint8_t display, uint8_t value);

/**
 * @brief Escribe un valor en ambos displays.
 * 
 * @param value El valor que se va a escribir en ambos displays.
 */
void displayWrite(uint8_t value);

/**
 * @brief Configura el punto decimal de un display específico.
 * 
 * @param display El número del display.
 * @param value El valor del punto decimal (on/off).
 */
void displayDP(uint8_t display, uint8_t value);

/**
 * @brief Configura el valor de un segmento específico en un display.
 * 
 * @param display El número del display.
 * @param segment El segmento que se va a configurar (A-G).
 * @param value El valor del segmento (on/off).
 */
void displaySegment(uint8_t display, uint8_t segment, uint8_t value);

/**
 * @brief Configura los segmentos de un display específico.
 * 
 * @param display El número del display.
 * @param A El valor del segmento A.
 * @param B El valor del segmento B.
 * @param C El valor del segmento C.
 * @param D El valor del segmento D.
 * @param E El valor del segmento E.
 * @param F El valor del segmento F.
 * @param G El valor del segmento G.
 * @param DP El valor del punto decimal.
 */
void displaySegment(uint8_t display, uint8_t A, uint8_t B, uint8_t C, uint8_t D, uint8_t E, uint8_t F, uint8_t G, uint8_t DP);


