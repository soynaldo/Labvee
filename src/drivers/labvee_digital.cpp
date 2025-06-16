#include "labvee_digital.h"


#define TERMINAL_ADDRESS 0x21 ///< Dirección I2C del terminal.

// PCA9555 REGISTERS
#define REG_INPUT      0
#define REG_OUTPUT     2
#define REG_CONFIG     6

uint16_t terminal_value = 0;
uint16_t terminal_config = 0;

void DIGITAL_WriteReg(uint8_t reg, uint16_t value) {
  uint8_t valueh = value >> 8;
  uint8_t valuel = value;
  uint8_t valueraw[4] = {reg, valuel, reg + 1, valueh};
  I2C_WriteBytes(TERMINAL_ADDRESS, valueraw, 2);
  I2C_WriteBytes(TERMINAL_ADDRESS, valueraw + 2, 2);
}

uint16_t DIGITAL_readReg(uint8_t reg) {
  I2C_Write8(TERMINAL_ADDRESS, reg);
  uint16_t value = I2C_Read8(TERMINAL_ADDRESS);
  I2C_Write8(TERMINAL_ADDRESS, reg + 1);
  value |= I2C_Read8(TERMINAL_ADDRESS) << 8;
  return value;
}

uint8_t DIGITAL_Class::read(uint8_t terminal, uint8_t pin) {
  uint16_t actual_value = DIGITAL_readReg(REG_INPUT);
  uint8_t phisical_pin = ((terminal - 1) * 4) + pin - 1;
  return (actual_value & (1 << phisical_pin));
}

void DIGITAL_Class::write(uint8_t terminal, uint8_t pin, uint8_t state) {
  bitWrite(terminal_value, (((terminal - 1) * 4) + pin - 1), state);
  DIGITAL_WriteReg(REG_OUTPUT, terminal_value);
}

void DIGITAL_Class::mode(uint8_t terminal, uint8_t pin, uint8_t mode) {
  if (mode == OUTPUT) {
    bitClear(terminal_config, (((terminal - 1) * 4) + pin - 1));
  } else {
    bitSet(terminal_config, (((terminal - 1) * 4) + pin - 1));
  }
  DIGITAL_WriteReg(REG_CONFIG, terminal_config);
}

DIGITAL_Class DIGITAL; ///< Instancia de la clase DIGITAL_Class para su uso en el programa.
