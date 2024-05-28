#include "labvee.h"

PCF8575 keypad(0x20);
PCF8575 labveeIO(0x21);
PCF8575 display_7seg(0x22);

uint8_t portDIGITAL(uint8_t terminal, uint8_t pin)
{
  return labveeIO.read(((terminal - 1) * 4) + pin);
}

void portDIGITAL(uint8_t terminal, uint8_t pin, uint8_t state)
{
  labveeIO.write((((terminal - 1) * 4) + pin), state);
}

void terminalInit()
{
  labveeIO.begin(0);
}

void keypadInit()
{
  keypad.begin(0);
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
    keypad.write16(1 << pinO);
    uint16_t value = keypad.read16();
    if (value & (1 << 4)) return (pinO * 4) + 1;
    if (value & (1 << 5)) return (pinO * 4) + 2;
    if (value & (1 << 6)) return (pinO * 4) + 3;
    if (value & (1 << 7)) return (pinO * 4) + 4;
  }
  return 0;
}

void displayInit()
{
  display_7seg.begin(0);
}

void displayReset(uint8_t display)
{
  uint8_t aux = (display == 2) ? 8 : 0;
  uint16_t valueo = (0x00FF << aux) & display_7seg.valueOut();
  display_7seg.write16(valueo);
}

void displayReset()
{
  display_7seg.write16(0);
}

void displayWrite(uint8_t display, uint8_t value)
{
  const uint8_t dv[10] = {63, 6, 91, 79, 102, 109, 125, 7, 127, 111};
  if (value < 10)
  {
    uint8_t aux = (display == 2) ? 8 : 0;
    uint16_t valueo = dv[value] | ((0x00FF << aux) & display_7seg.valueOut());
    display_7seg.write16(valueo);
  }
}

void displayWrite(uint8_t value)
{
  const uint8_t dv[10] = {63, 6, 91, 79, 102, 109, 125, 7, 127, 111};
  if (value < 100)
  {
    uint8_t dec = value / 10;
    uint8_t unit = value % 10;
    uint16_t valueo = dv[unit] | (dv[dec] << 8);
    display_7seg.write16(valueo);
  }
}

void displayDP(uint8_t display, uint8_t value)
{
  if (display == 1)
  {
    display_7seg.write(D1_DP, value);
  }
  else if (display == 2)
  {
    display_7seg.write(D2_DP, value);
  }
}

void displaySegment(uint8_t display, uint8_t segment, uint8_t value)
{
  if (display == 1)
  {
    const uint8_t pins[8] = {D1_A, D1_B, D1_C, D1_D, D1_E, D1_F, D1_G, D1_DP};
    display_7seg.write(pins[segment], value);
  }
  else if (display == 2)
  {
    const uint8_t pins[8] = {D2_A, D2_B, D2_C, D2_D, D2_E, D2_F, D2_G, D2_DP};
    display_7seg.write(pins[segment], value);
  }
}

void displaySegment(uint8_t display, uint8_t A, uint8_t B, uint8_t C, uint8_t D, uint8_t E, uint8_t F, uint8_t G, uint8_t DP) {

}