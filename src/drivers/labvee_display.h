#pragma once

#include "Arduino.h"

#include "labvee_pins.h"
#include "labvee_ioexpander.h"

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

#define DISPLAY_U 1 ///< Display de unidades.
#define DISPLAY_D 2 ///< Display de decenas.

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
    void segment(uint8_t display, uint8_t segment, uint8_t value);

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
    void segment(uint8_t display, uint8_t A, uint8_t B, uint8_t C, uint8_t D, uint8_t E, uint8_t F, uint8_t G, uint8_t DP);

private:
    IOExpander_Class ioexpander; ///< Instancia de la clase IOExpander_Class para manejar el IO Expander.
};

extern DISPLAY_Class DISP; ///< Instancia de la clase DISPLAY_Class para su uso en el programa.