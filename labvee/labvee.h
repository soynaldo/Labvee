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

uint8_t terminalRead(uint8_t terminal, uint8_t pin);
void terminalWrite(uint8_t terminal, uint8_t pin, uint8_t state);
void terminalInit();

void keypadInit();
uint8_t keypadWaitValue();
uint8_t keypadGetValue();

void displayInit();
void displayReset(uint8_t display);
void displayReset();
void displayWrite(uint8_t display, uint8_t value);
void displayWrite(uint8_t value);
void displayDP(uint8_t display, uint8_t value);
void displayPIN(uint8_t display, uint8_t pin, uint8_t value);
void displayPIN(uint8_t pin, uint8_t value);
