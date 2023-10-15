#include "labvee.h"

void teminalInit(){
  labveeIO.begin();
}

void keypadInit(){
  keypad.pinMode(P0, OUTPUT);
  keypad.pinMode(P1, OUTPUT);
  keypad.pinMode(P2, OUTPUT);
  keypad.pinMode(P3, OUTPUT);
  keypad.pinMode(P4, INPUT);
  keypad.pinMode(P5, INPUT);
  keypad.pinMode(P6, INPUT);
  keypad.pinMode(P7, INPUT);

  keypad.begin();
}

uint8_t keypadWaitValue(){
  byte keypadvalue = 0;
  while(!keypadvalue){
    keypadvalue = keypadgetValue();
  }
}

uint8_t keypadgetValue(){
  for (byte pinO = 0; pinO < 4; pinO++){
    keypad.digitalWrite(pinO, HIGH);
    for (byte pinI = 4; pinI < 8; pinI){
      if (keypad.digitalRead(pinI)){
        return (pinI*4) + pinI + 1;
      }
    }
    keypad.digitalWrite(pinO, LOW);
  }
  return 0;
}

void displayInit(uint8_t display){
  if (display == 1){
    display_7seg.pinMode(D1_A, OUTPUT);
    display_7seg.pinMode(D1_B, OUTPUT);
    display_7seg.pinMode(D1_C, OUTPUT);
    display_7seg.pinMode(D1_D, OUTPUT);
    display_7seg.pinMode(D1_E, OUTPUT);
    display_7seg.pinMode(D1_F, OUTPUT);
    display_7seg.pinMode(D1_G, OUTPUT);
    display_7seg.pinMode(D1_DP, OUTPUT);
  }else if(display == 2){
    display_7seg.pinMode(D2_A, OUTPUT);
    display_7seg.pinMode(D2_B, OUTPUT);
    display_7seg.pinMode(D2_C, OUTPUT);
    display_7seg.pinMode(D2_D, OUTPUT);
    display_7seg.pinMode(D2_E, OUTPUT);
    display_7seg.pinMode(D2_F, OUTPUT);
    display_7seg.pinMode(D2_G, OUTPUT);
    display_7seg.pinMode(D2_DP, OUTPUT);
  }
  display_7seg.begin();
}

void displayWrite(uint8_t display, uint8_t value){
  const byte displayvalues[10] = {63, 6, 91, 79, 102, 109, 125, 7, 127, 111};
  if (value < 10){
    byte aux = 0;
    if (display == 1){
      aux = 0;
    }else if(display == 2){
      aux = 8;
    }
    for (byte i = 0; i < 8; i++){
      display_7seg.digitalWrite(i + aux, bitRead(displayvalues[value], i));
    }
  }
}

void displayDP(uint8_t display, uint8_t value){
  if (display == 1){
    display_7seg.digitalWrite(D1_DP, value);
  }else if (display == 2){
    display_7seg.digitalWrite(D2_DP, value);
  }
}

void displayPIN(uint8_t display, uint8_t pin, uint8_t value){
  if (display == 1){
    const byte pins[8] = {D1_A, D1_B, D1_C, D1_D, D1_E, D1_F, D1_G, D1_DP};
    display_7seg.digitalWrite(pins[pin], value);
  }else if (display == 2){
    const byte pins[8] = {D2_A, D2_B, D2_C, D2_D, D2_E, D2_F, D2_G, D2_DP};
    display_7seg.digitalWrite(pins[pin], value);
  }
}
