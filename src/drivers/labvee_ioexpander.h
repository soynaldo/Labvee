#pragma once

#include <Arduino.h>
#include "labvee_i2c.h"

// PCA9555 REGISTERS
#define PCA9555_REG_INPUT      0
#define PCA9555_REG_OUTPUT     2
#define PCA9555_REG_CONFIG     6

class IOExpander_Class {
public:
    /**
     * @brief Constructor de la clase IOExpander_Class.
     * 
     * Inicializa los valores de los registros de terminal y configuración.
     */
    IOExpander_Class(uint8_t terminal_address) 
        : _terminal_value(0), _terminal_config(0), _address(terminal_address) {
    }

    /**
     * @brief Lee el estado de un pin digital en un terminal específico.
     * 
     * @param terminal La dirección del terminal.
     * @param pin El pin que se va a leer.
     * @return El estado actual del pin (HIGH o LOW).
     */
    uint8_t readPin(uint8_t pin) {
        uint16_t actual_value = readReg(PCA9555_REG_INPUT);
        return (actual_value & (1 << pin));
    }

    uint16_t readAll() {
        return readReg(PCA9555_REG_INPUT);
    }

    /**
     * @brief Configura el estado de un pin digital en un terminal específico.
     * 
     * @param terminal La dirección del terminal.
     * @param pin El pin que se va a configurar.
     * @param state El estado que se desea establecer (HIGH o LOW).
     */
    void writePin(uint8_t pin, uint8_t state) {
        bitWrite(_terminal_value, pin, state);
        writeReg(PCA9555_REG_OUTPUT, _terminal_value);
    }

    void writeAll(uint16_t value) {
        _terminal_value = value;
        writeReg(PCA9555_REG_OUTPUT, _terminal_value);
    }

    /**
     * @brief Configura el modo de un pin digital (entrada o salida).
     * 
     * @param terminal La dirección del terminal.
     * @param pin El pin que se va a configurar.
     * @param mode El modo del pin (INPUT o OUTPUT).
     */
    void modePin(uint8_t pin, uint8_t mode) {
        if (mode == OUTPUT) {
            bitClear(_terminal_config, pin);
        } else {
            bitSet(_terminal_config, pin);
        }
        writeReg(PCA9555_REG_CONFIG, _terminal_config);
    }

    void modeAll(uint16_t config) {
        _terminal_config = config;
        writeReg(PCA9555_REG_CONFIG, _terminal_config);
    }

    uint16_t outValue() {
        return _terminal_value;
    }

private:
    uint16_t _terminal_value;
    uint16_t _terminal_config;
    uint8_t _address;

private:
    void writeReg(uint8_t reg, uint16_t value) {
        uint8_t valueh = value >> 8;
        uint8_t valuel = value;
        uint8_t valueraw[4] = {reg, valuel, (uint8_t)(reg + 1), valueh};
        I2C_WriteBytes(_address, valueraw, 2);
        I2C_WriteBytes(_address, valueraw + 2, 2);
    }

    uint16_t readReg(uint8_t reg) {
        I2C_Write8(_address, reg);
        uint16_t value = I2C_Read8(_address);
        I2C_Write8(_address, reg + 1);
        value |= I2C_Read8(_address) << 8;
        return value;
    }

};
