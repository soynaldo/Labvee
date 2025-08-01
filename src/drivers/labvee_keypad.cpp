#include "labvee_keypad.h"


void KEYPAD_Class::begin() {
  ioexpander.modeAll(0xFF00); // Configura todos los pines como entrada
  ioexpander.writeAll(0xFFFF); // Configura todos los pines como HIGH
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
  for (coord.x = 0; coord.x < 4; coord.x++) {
    uint16_t port_value = 0xFF & ~(1 << coord.x);
    ioexpander.writeAll(port_value);
    port_value = ioexpander.readAll();
    for (coord.y = 0; coord.y < 4; coord.y++) {
      if (!bitRead(port_value, 7 - coord.y)) {
        coord.x++;
        coord.y++;
        return coord;
      }
    }
  }
  coord.x = 0;
  coord.y = 0;
  return coord;
}

