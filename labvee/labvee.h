#pragma once

#include "PCF8575.h"
#include <Arduino.h>

#define D1_A 0
#define D1_B 1
#define D1_C 2
#define D1_D 3
#define D1_E 4
#define D1_F 5
#define D1_G 6
#define D1_DP 7

#define D2_A 8
#define D2_B 9
#define D2_C 10
#define D2_D 11
#define D2_E 12
#define D2_F 13
#define D2_G 14
#define D2_DP 15

#define ONE 1
#define TWO 2
#define THREE 3
#define FOUR 4

#define UNO 1
#define DOS 2
#define TRES 3
#define CUATRO 4

extern PCF8575 keypad(0x20);
extern PCF8575 labveeIO(0x21);
extern PCF8575 display_7seg(0x22);

#define terminalRead(TERMINAL, PIN) (labveeIO.digitalRead(((TERMINAL-1)*4)+PIN))
#define terminalWrite(TERMINAL, PIN, STATE) (labveeIO.digitalWrite((((TERMINAL-1)*4)+PIN), STATE))
#define terminalMode(TERMINAL, PIN, MODE) (labveeIO.pinMode((((TERMINAL-1)*4)+PIN), MODE))

#define terminalOneRead(PIN) (labveeIO.digitalRead(PIN - 1))
#define terminalOneWrite(PIN, STATE) (labveeIO.digitalWrite(PIN, STATE))
#define terminalOneMode(PIN, MODE) (labveeIO.pinMode(PIN, MODE))

#define terminalTwoRead(PIN) (labveeIO.digitalRead(3 + PIN))
#define terminalTwoWrite(PIN, STATE) (labveeIO.digitalWrite((3 + PIN), STATE))
#define terminalTwoMode(PIN, MODE) (labveeIO.pinMode((3 + PIN), MODE))

#define terminalThreeRead(PIN) (labveeIO.digitalRead(7 + PIN))
#define terminalThreeWrite(PIN, STATE) (labveeIO.digitalWrite((7 + PIN), STATE))
#define terminalThreeMode(PIN, MODE) (labveeIO.pinMode((7 + PIN), MODE))

#define terminalFourRead(PIN) (labveeIO.digitalRead(11 + PIN))
#define terminalFourWrite(PIN, STATE) (labveeIO.digitalWrite((11 + PIN), STATE))
#define terminalFourMode(PIN, MODE) (labveeIO.pinMode((11 + PIN), MODE))

#define teminalInit() labveeIO.begin()

void keypadInit();
uint8_t keypadWaitValue();
uint8_t keypadgetValue();

void displayInit(uint8_t display);
void displayWrite(uint8_t display, uint8_t value);
void displayDP(uint8_t display, uint8_t value);
void displayPIN(uint8_t display, uint8_t pin, uint8_t value);
