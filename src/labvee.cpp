#include "labvee.h"

uint16_t display_value = 0;
uint16_t terminal_value = 0;
uint16_t terminal_config = 0;



// PCA9555 REGISTERS
#define REG_INPUT      0
#define REG_OUTPUT     2
#define REG_CONFIG     6

void portDIGITAL_writeReg(uint8_t reg, uint16_t value) {
  uint8_t valueh = value >> 8;
  uint8_t valuel = value;
  uint8_t valueraw[4] = {reg, valuel, reg + 1, valueh};
  portI2C_writeBytes(TERMINAL_ADDRESS, valueraw, 2);
  portI2C_writeBytes(TERMINAL_ADDRESS, valueraw + 2, 2);
}

uint16_t portDIGITAL_readReg(uint8_t reg) {
  portI2C_write8(TERMINAL_ADDRESS, reg);
  uint16_t value = portI2C_read8(TERMINAL_ADDRESS);
  portI2C_write8(TERMINAL_ADDRESS, reg + 1);
  value |= portI2C_read8(TERMINAL_ADDRESS) << 8;
  return value;
}

uint8_t portDIGITAL(uint8_t terminal, uint8_t pin)
{
  uint16_t actual_value = portDIGITAL_readReg(REG_INPUT);
  uint8_t phisical_pin = ((terminal - 1) * 4) + pin - 1;
  return (actual_value & (1 << phisical_pin));
}

void portDIGITAL(uint8_t terminal, uint8_t pin, uint8_t state)
{
  bitWrite(terminal_value, (((terminal - 1) * 4) + pin - 1), state);
  portDIGITAL_writeReg(REG_OUTPUT, terminal_value);
}

void portDIGITAL_mode(uint8_t terminal, uint8_t pin, uint8_t mode) {
  if (mode == OUTPUT) {
    bitClear(terminal_config, (((terminal - 1) * 4) + pin - 1));
  } else {
    bitSet(terminal_config, (((terminal - 1) * 4) + pin - 1));
  }
  portDIGITAL_writeReg(REG_CONFIG, terminal_config);
}

uint8_t keypadWaitValue()
{
  uint8_t keypadvalue = 0;
  while (!keypadvalue)
  {
    keypadvalue = keypadGetValue();
  }
  return keypadvalue;
}

uint8_t keypadGetValue()
{
  for (uint8_t pinO = 0; pinO < 4; pinO++)
  {
    uint16_t value = 0xFF & ~(1 << pinO);
    portI2C_write16(KEYPAD_ADDRESS, value);
    value = portI2C_read16(KEYPAD_ADDRESS);
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
    portI2C_write16(KEYPAD_ADDRESS, port_value);
    port_value = portI2C_read16(KEYPAD_ADDRESS);
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

void displayReset(uint8_t display)
{
  uint8_t aux = (display == 2) ? 8 : 0;
  display_value &= (0x00FF << aux);
  portI2C_write16(DISPLAY_ADDRESS, display_value);
}

void displayReset()
{
  portI2C_write16(DISPLAY_ADDRESS, 0);
}

void displayWrite(uint8_t display, uint8_t value)
{
  const uint8_t dv[10] = {63, 6, 91, 79, 102, 109, 125, 7, 127, 111};
  if (value < 10)
  {
    uint8_t aux = (display == 2) ? 8 : 0;
    display_value = dv[value] | ((0x00FF << aux) & display_value);
    portI2C_write16(DISPLAY_ADDRESS, display_value);
  }
}

void displayWrite(uint8_t value)
{
  const uint8_t dv[10] = {63, 6, 91, 79, 102, 109, 125, 7, 127, 111};
  if (value < 100)
  {
    uint8_t dec = value % 10;
    uint8_t unit = value / 10;
    display_value = dv[unit] | (dv[dec] << 8);
    portI2C_write16(DISPLAY_ADDRESS, display_value);
  }
}

void displayDP(uint8_t display, uint8_t value)
{
  uint8_t aux = (display == 2) ? D2_DP : D1_DP;
  bitWrite(display_value, aux, value);
  portI2C_write16(DISPLAY_ADDRESS, display_value);
}

void displaySegment(uint8_t display, uint8_t segment, uint8_t value)
{
  uint8_t aux = (display == 2) ? 8 : 0;
  bitWrite(display_value, aux + segment, value);
  portI2C_write16(DISPLAY_ADDRESS, display_value);
}

void displaySegment(uint8_t display, uint8_t A_SEGMENT, uint8_t B_SEGMENT, uint8_t C_SEGMENT, uint8_t D_SEGMENT, uint8_t E_SEGMENT, uint8_t F_SEGMENT,uint8_t G_SEGMENT, uint8_t DP){
  uint8_t aux = (display == 2) ? 8 : 0;
  bitWrite(display_value, 0 + aux, A_SEGMENT);
  bitWrite(display_value, 1 + aux, B_SEGMENT);
  bitWrite(display_value, 2 + aux, C_SEGMENT);
  bitWrite(display_value, 3 + aux, D_SEGMENT);
  bitWrite(display_value, 4 + aux, E_SEGMENT);
  bitWrite(display_value, 5 + aux, F_SEGMENT);
  bitWrite(display_value, 6 + aux, G_SEGMENT);
  bitWrite(display_value, 7 + aux, DP);
  portI2C_write16(DISPLAY_ADDRESS, display_value);
}