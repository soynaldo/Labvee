#pragma once

#include "Arduino.h"

#include "labvee_pins.h"
#include "labvee_ioexpander.h"

// Definiciones para los segmentos de los displays
#define segA 0  ///< Segmento A del display.
#define segB 1  ///< Segmento B del display.
#define segC 2  ///< Segmento C del display.
#define segD 3  ///< Segmento D del display.
#define segE 4  ///< Segmento E del display.
#define segF 5  ///< Segmento F del display.
#define segG 6  ///< Segmento G del display.
#define segDP 7 ///< Punto decimal del display.

#define DISPLAY_D 1 ///< Display de unidades.
#define DISPLAY_U 2 ///< Display de decenas.

class DISPLAY_Class {
public:
    /**
     * @brief Constructor de la clase DISPLAY_Class.
     * 
     * Inicializa los valores de los displays y la instancia de DIGITAL_Class.
     */
    DISPLAY_Class() : ioexpander(LABVEE_DISPLAY_ADDRESS) {}

    /**
     * @brief Inicializa el display.
     * 
     * Configura el IO Expander y prepara el display para su uso.
     */
    void begin();

    /**
     * @brief Resetea un display específico.
     * 
     * @param display El número del display a resetear.
     */
    void reset(uint8_t display);

    /**
     * @brief Resetea ambos displays.
     */
    void reset();

    /**
     * @brief Escribe un valor en un display específico.
     * 
     * @param display El número del display donde se escribirá.
     * @param value El valor que se va a escribir.
     */
    void write(uint8_t display, uint8_t value);

    /**
     * @brief Escribe un valor en ambos displays.
     * 
     * @param value El valor que se va a escribir (0-99).
     */
    void write(uint8_t value);

    /**
     * @brief Escribe un valor en un display específico.
     * 
     * @param value El valor que se va a escribir (float).
     */
    void writeF(float value);

    /**
     * @brief Configura el punto decimal de un display específico.
     * 
     * @param display El número del display.
     * @param value El valor del punto decimal (on/off).
     */
    void dp(uint8_t display, uint8_t value);

    /**
     * @brief Configura el valor de un segmento específico en un display.
     * 
     * @param display El número del display.
     * @param segment El segmento que se va a configurar (A-G).
     * @param value El valor del segmento (on/off).
     */
    void segmentU(uint8_t display, uint8_t segment, uint8_t value);

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
    void segmentM(uint8_t display, uint8_t A, uint8_t B, uint8_t C, uint8_t D, uint8_t E, uint8_t F, uint8_t G, uint8_t DP);

    /**
     * @brief Escribe un valor binario en un display específico.
     * 
     * @param display El número del display.
     * @param value El valor binario que se va a escribir.
     */
    void segmentB(uint8_t display, uint8_t value);

private:
    IOExpander_Class ioexpander; ///< Instancia de la clase IOExpander_Class para manejar el IO Expander.
};
