#include "labvee.h"

// Base de datos de tarjetas autorizadas (UIDs)
byte tarjetasAutorizadas[][4] = {
  {0x12, 0x34, 0x56, 0x78},  // Tarjeta 1
  {0xAB, 0xCD, 0xEF, 0x12},  // Tarjeta 2
  {0x90, 0x78, 0x56, 0x34}   // Tarjeta 3
};

void setup() {
  Serial.begin(115200);     // Iniciar comunicación serial
  SPI.begin();            // Iniciar bus SPI
  RFID.PCD_Init();     // Iniciar MFRC522
  
  Serial.println("Sistema RFID MFRC522 Iniciado");
  Serial.println("Acercar tarjeta al lector...");
  Serial.println("==================================");
}

void loop() {
  // Verificar si hay una tarjeta presente
  if (!RFID.PICC_IsNewCardPresent()) {
    delay(50);
    return;
  }

  // Leer la tarjeta
  if (!RFID.PICC_ReadCardSerial()) {
    delay(50);
    return;
  }

  // Mostrar información de la tarjeta
  Serial.print("UID de la tarjeta: ");
  mostrarUID(RFID.uid.uidByte, RFID.uid.size);
  Serial.println();

  // Verificar si está autorizada
  if (tarjetaAutorizada(RFID.uid.uidByte, RFID.uid.size)) {
    Serial.println("ACCESO AUTORIZADO ✅");
    Serial.println("Bienvenido al sistema");
    // Aquí puedes activar un relay, LED verde, etc.
  } else {
    Serial.println("ACCESO DENEGADO ❌");
    Serial.println("Tarjeta no reconocida");
    // Aquí puedes activar una alarma, LED rojo, etc.
  }

  Serial.println("==================================");
  
  // Detener comunicación con la tarjeta
  RFID.PICC_HaltA();
  delay(1000);  // Esperar 1 segundo antes de nueva lectura
}

// Función para mostrar el UID de la tarjeta
void mostrarUID(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}

// Función para verificar si la tarjeta está autorizada
bool tarjetaAutorizada(byte *uid, byte uidSize) {
  for (int i = 0; i < sizeof(tarjetasAutorizadas) / sizeof(tarjetasAutorizadas[0]); i++) {
    bool coincide = true;
    for (byte j = 0; j < uidSize; j++) {
      if (uid[j] != tarjetasAutorizadas[i][j]) {
        coincide = false;
        break;
      }
    }
    if (coincide) {
      return true;
    }
  }
  return false;
}

// Función para agregar nueva tarjeta autorizada (opcional)
void agregarTarjetaAutorizada() {
  Serial.println("Modo aprendizaje: Acercar tarjeta a autorizar");
  delay(3000);
  
  if (RFID.PICC_IsNewCardPresent() && RFID.PICC_ReadCardSerial()) {
    Serial.print("Nueva tarjeta agregada: ");
    mostrarUID(RFID.uid.uidByte, RFID.uid.size);
    Serial.println();
    
    // Aquí guardarías en EEPROM o array
  }
}