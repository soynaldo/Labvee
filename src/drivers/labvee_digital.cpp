#include "labvee_digital.h"


uint8_t DIGITAL_Class::read(uint8_t terminal, uint8_t pin) {
  uint8_t phisical_pin = ((terminal - 1) * 4) + pin - 1;
  return ioexpander.readPin(phisical_pin);
}

void DIGITAL_Class::write(uint8_t terminal, uint8_t pin, uint8_t state) {
  uint8_t phisical_pin = ((terminal - 1) * 4) + pin - 1;
  ioexpander.writePin(phisical_pin, state);
}

void DIGITAL_Class::mode(uint8_t terminal, uint8_t pin, uint8_t mode) {
  uint8_t phisical_pin = ((terminal - 1) * 4) + pin - 1;
  ioexpander.modePin(phisical_pin, mode);
}
