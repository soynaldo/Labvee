#include "labvee_i2c.h"

void I2C_Begin()
{
    Wire.begin();
}

void I2C_Scan() {
    Serial.println("Escaneando bus I2C...");
    byte error, address;
    int nDevices = 0;

    for (address = 1; address < 127; address++) {
        Wire.beginTransmission(address);
        error = Wire.endTransmission();

        if (error == 0) {
            Serial.print("Dispositivo encontrado en dirección 0x");
            if (address < 16) Serial.print("0");
            Serial.print(address, HEX);
            Serial.println();
            nDevices++;
        } else if (error == 4) {
            Serial.print("Error desconocido en dirección 0x");
            if (address < 16) Serial.print("0");
            Serial.println(address, HEX);
        }
    }

    if (nDevices == 0) {
        Serial.println("No se encontraron dispositivos I2C.");
    } else {
        Serial.print("Número de dispositivos I2C encontrados: ");
        Serial.println(nDevices);
    }
}

uint8_t I2C_Read8(const uint8_t address)
{
    uint8_t data_in = 0;
    if (Wire.requestFrom(address, (uint8_t)1) != 1)
    {
        return data_in;
    }
    data_in = Wire.read();
    return data_in;
}

uint8_t I2C_Write8(const uint8_t address, const uint8_t value)
{
    Wire.beginTransmission(address);
    Wire.write(value);
    return Wire.endTransmission();
}

uint16_t I2C_Read16(const uint8_t address)
{
    uint16_t data_in = 0;
    if (Wire.requestFrom(address, (uint8_t)2) != 2)
    {
        return data_in;
    }
    data_in = Wire.read();
    data_in |= (Wire.read() << 8);
    return data_in;
}

uint8_t I2C_Write16(const uint8_t address, const uint16_t value)
{
    Wire.beginTransmission(address);
    Wire.write(value & 0xFF);
    Wire.write(value >> 8);
    return Wire.endTransmission();
}

uint8_t I2C_ReadBytes(const uint8_t address, uint8_t *buffer, size_t len)
{
    size_t recv = Wire.requestFrom(address, len);
    if (recv != len)
        return false;
    for (size_t i = 0; i < len; i++)
    {
        buffer[i] = Wire.read();
    }
    return true;
}

uint8_t I2C_WriteBytes(const uint8_t address, const uint8_t *value, size_t len)
{
    Wire.beginTransmission(address);
    Wire.write(value, len);
    return Wire.endTransmission();
}

uint8_t I2C_WriteBytes(const uint8_t address, const uint8_t *value, size_t len,
                           const uint8_t *prefix_value, size_t prefix_len)
{
    Wire.beginTransmission(address);
    Wire.write(value, len);
    Wire.write(prefix_value, prefix_len);
    return Wire.endTransmission();
}