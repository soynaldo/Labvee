#include "labvee_keypad.h"


#define KEYPAD_ADDRESS 0x20 ///< Dirección I2C del teclado.

uint8_t keypadWaitValue() {
  uint8_t keypadvalue = 0;
  while (!keypadvalue)
  {
    keypadvalue = keypadGetValue();
  }
  return keypadvalue;
}

uint8_t keypadGetValue() {
  for (uint8_t pinO = 0; pinO < 4; pinO++)
  {
    uint16_t value = 0xFF & ~(1 << pinO);
    I2C_Write16(KEYPAD_ADDRESS, value);
    value = I2C_Read16(KEYPAD_ADDRESS);
    for (uint8_t pinI = 0; pinI < 4; pinI++) {
      if (!bitRead(value, 7 - pinI)) return (4 - pinO) + (pinI * 4);
    }
  }
  return 0;
}

Coords_t keypadGetCoords() {
  Coords_t coord;
  for (coord.x = 0; coord.x < 4; coord.x++)
  {
    uint16_t port_value = 0xFF & ~(1 << coord.x);
    I2C_Write16(KEYPAD_ADDRESS, port_value);
    port_value = I2C_Read16(KEYPAD_ADDRESS);
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
