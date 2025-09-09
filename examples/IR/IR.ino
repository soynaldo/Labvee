#include <IRremote.h>

#define  IRpin 4 

int IR_DATA, numero_ir=0;
int concatenatedIr=0;

char inputDigits[3] = ""; // Arreglo para almacenar dos dígitos y el terminador nulo
char inputDigitsIr[3] = ""; // Arreglo para almacenar dos dígitos y el terminador nulo

unsigned long lastIRTime = 0;
const unsigned long debounceIRDelay = 400; // Tiempo de antirebote en milisegundos

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  IrReceiver.begin(IRpin);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (IrReceiver.decode()) {
    unsigned long currentTime = millis();

    // Antirebote: ignorar si no ha pasado suficiente tiempo
    if (currentTime - lastIRTime < debounceIRDelay) {
      IrReceiver.resume(); // Preparar para la próxima lectura
      return;
    }

    uint16_t IR_DATA = IrReceiver.decodedIRData.command;

    if (IR_DATA == 0) {
      IrReceiver.resume();
      return;
    }

    lastIRTime = currentTime; // Actualizar el tiempo de la última lectura válida
    //Serial.println(IR_DATA);

    switch (IR_DATA) {
      case 69: numero_ir = 1; break;
      case 70: numero_ir = 2; break;
      case 71: numero_ir = 3; break;
      case 68: numero_ir = 4; break;
      case 64: numero_ir = 5; break;
      case 67: numero_ir = 6; break;
      case 7:  numero_ir = 7; break;
      case 21: numero_ir = 8; break;
      case 9:  numero_ir = 9; break;
      case 25: numero_ir = 0; break;
      case 22: numero_ir = 10; break;
      case 13: numero_ir = 11; break;
      case 24: numero_ir = 12; break;
      case 8:  numero_ir = 13; break;
      case 28: numero_ir = 14; break;
      case 90: numero_ir = 15; break;
      case 82: numero_ir = 16; break;
    }

    Serial.println(numero_ir);
    IrReceiver.resume();
  }
}