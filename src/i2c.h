#pragma once

#include "Arduino.h"
#include "Wire.h"

/**
 * @brief Inicializa la comunicación I2C.
 * 
 * Esta función debe ser llamada antes de realizar cualquier operación de lectura o escritura
 * en el bus I2C.
 */
void portI2C_begin();

/**
 * @brief Lee un byte desde una dirección I2C.
 * 
 * @param address La dirección del dispositivo I2C desde donde se leerá el byte.
 * @return El valor leído (byte) del dispositivo I2C.
 */
uint8_t portI2C_read8(const uint8_t address);

/**
 * @brief Escribe un byte en una dirección I2C.
 * 
 * @param address La dirección del dispositivo I2C donde se escribirá el byte.
 * @param value El valor (byte) que será escrito en el dispositivo I2C.
 * @return 0 si la escritura fue exitosa, de lo contrario un código de error.
 */
uint8_t portI2C_write8(const uint8_t address, const uint8_t value);

/**
 * @brief Lee 16 bits desde una dirección I2C.
 * 
 * @param address La dirección del dispositivo I2C desde donde se leerán los 16 bits.
 * @return El valor leído (16 bits) del dispositivo I2C.
 */
uint16_t portI2C_read16(const uint8_t address);

/**
 * @brief Escribe 16 bits en una dirección I2C.
 * 
 * @param address La dirección del dispositivo I2C donde se escribirán los 16 bits.
 * @param value El valor (16 bits) que será escrito en el dispositivo I2C.
 * @return 0 si la escritura fue exitosa, de lo contrario un código de error.
 */
uint8_t portI2C_write16(const uint8_t address, const uint16_t value);

/**
 * @brief Lee múltiples bytes desde una dirección I2C.
 * 
 * @param address La dirección del dispositivo I2C desde donde se leerán los bytes.
 * @param buffer Puntero al buffer donde se almacenarán los bytes leídos.
 * @param len La cantidad de bytes a leer.
 * @return 0 si la lectura fue exitosa, de lo contrario un código de error.
 */
uint8_t portI2C_readBytes(const uint8_t address, uint8_t *buffer, size_t len);

/**
 * @brief Escribe múltiples bytes en una dirección I2C.
 * 
 * @param address La dirección del dispositivo I2C donde se escribirán los bytes.
 * @param value Puntero al array de bytes que será escrito.
 * @param len La cantidad de bytes a escribir.
 * @return 0 si la escritura fue exitosa, de lo contrario un código de error.
 */
uint8_t portI2C_writeBytes(const uint8_t address, const uint8_t *value, size_t len);

/**
 * @brief Escribe múltiples bytes con un prefijo en una dirección I2C.
 * 
 * @param address La dirección del dispositivo I2C donde se escribirán los bytes.
 * @param value Puntero al array de bytes que será escrito.
 * @param len La cantidad de bytes a escribir.
 * @param prefix_value Puntero al array de bytes prefijo que será enviado antes de los datos.
 * @param prefix_len La cantidad de bytes del prefijo a enviar.
 * @return 0 si la escritura fue exitosa, de lo contrario un código de error.
 */
uint8_t portI2C_writeBytes(const uint8_t address, const uint8_t *value, size_t len, uint8_t *prefix_value, size_t prefix_len);
