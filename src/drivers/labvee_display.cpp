#include "labvee_display.h"


void DISPLAY_Class::begin() {
  ioexpander.modeAll(0x0000); // Configura todos los pines como salida
  ioexpander.writeAll(0x0000); // Configura todos los pines como LOW
}

void DISPLAY_Class::reset(uint8_t display) {
  uint8_t aux = (display == 2) ? 8 : 0;
  uint16_t display_value = ioexpander.outValue();
  display_value &= (0xFF00 >> aux);
  ioexpander.writeAll(display_value);
}

void DISPLAY_Class::reset() {
  ioexpander.writeAll(0);
}

void DISPLAY_Class::write(uint8_t display, uint8_t value) {
  const uint8_t dv[10] = {63, 6, 91, 79, 102, 109, 125, 7, 127, 111};
  if (value < 10)
  {
    uint8_t aux = (display == 2) ? 8 : 0;
    uint16_t display_value = ioexpander.outValue();
    display_value = dv[value] | ((0xFF00 >> aux) & display_value);
    ioexpander.writeAll(display_value);
  }
}

void DISPLAY_Class::write(uint8_t value) {
  const uint8_t dv[10] = {63, 6, 91, 79, 102, 109, 125, 7, 127, 111};
  if (value < 100)
  {
    uint8_t dec = value % 10;
    uint8_t unit = value / 10;
    uint16_t display_value = ioexpander.outValue();
    display_value = dv[unit] | (dv[dec] << 8);
    ioexpander.writeAll(display_value);
  }
}

void DISPLAY_Class::dp(uint8_t display, uint8_t value) {
  uint8_t aux = (display == 2) ? D2_DP : ((display == 1) ? D1_DP: 0);
  uint16_t display_value = ioexpander.outValue();
  bitWrite(display_value, aux, value);
  ioexpander.writeAll(display_value);
}

void DISPLAY_Class::segment(uint8_t display, uint8_t segment, uint8_t value) {
  uint8_t aux = (display == 2) ? 8 : 0;
  uint16_t display_value = ioexpander.outValue();
  bitWrite(display_value, aux + segment, value);
  ioexpander.writeAll(display_value);
}

void DISPLAY_Class::segment(uint8_t display, uint8_t A_SEGMENT, uint8_t B_SEGMENT, uint8_t C_SEGMENT, uint8_t D_SEGMENT, uint8_t E_SEGMENT, uint8_t F_SEGMENT,uint8_t G_SEGMENT, uint8_t DP){
  uint8_t aux = (display == 2) ? 8 : 0;
  uint16_t display_value = ioexpander.outValue();
  bitWrite(display_value, 0 | aux, A_SEGMENT);
  bitWrite(display_value, 1 | aux, B_SEGMENT);
  bitWrite(display_value, 2 | aux, C_SEGMENT);
  bitWrite(display_value, 3 | aux, D_SEGMENT);
  bitWrite(display_value, 4 | aux, E_SEGMENT);
  bitWrite(display_value, 5 | aux, F_SEGMENT);
  bitWrite(display_value, 6 | aux, G_SEGMENT);
  bitWrite(display_value, 7 | aux, DP);
  ioexpander.writeAll(display_value);
}

DISPLAY_Class DISP; ///< Instancia de la clase DISPLAY_Class para su uso en el programa.