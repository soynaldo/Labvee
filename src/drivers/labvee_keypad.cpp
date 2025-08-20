#include "labvee_keypad.h"


void KEYPAD_Class::begin() {
  ioexpander.modeAll(0b11110000); // Configura todos los pines como entrada
  // ioexpander.writeAll(0xFFFF); // Configura todos los pines como HIGH
}

uint8_t KEYPAD_Class::wait() {
  uint8_t keypadvalue = 0;
  while (!keypadvalue) {
    keypadvalue = read();
  }
  return keypadvalue;
}

uint8_t KEYPAD_Class::read() {
  for (uint8_t pinO = 0; pinO < 4; pinO++) {
    uint16_t value = 0xFF & ~(1 << pinO);
    ioexpander.writeAll(value);
    value = ioexpander.readAll();
    for (uint8_t pinI = 0; pinI < 4; pinI++) {
      if (!bitRead(value, 7 - pinI)) return (4 - pinO) + (pinI * 4);
    }
  }
  return 0;
}

Coords_t KEYPAD_Class::coords() {
  Coords_t coord;
  for (coord.column = 0; coord.column < 4; coord.column++) {
    uint16_t port_value = 0xFF & ~(1 << coord.column);
    ioexpander.writeAll(port_value);
    port_value = ioexpander.readAll();
    for (coord.row = 0; coord.row < 4; coord.row++) {
      if (!bitRead(port_value, 7 - coord.row)) {
        coord.column = 4 - coord.column; // Ajusta la columna
        //coord.column++;
        coord.row++;
        return coord;
      }
    }
  }
  coord.column = 0;
  coord.row = 0;
  return coord;
}

