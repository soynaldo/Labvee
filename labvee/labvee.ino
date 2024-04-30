#include "labvee.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  terminalInit();
  keypadInit();
  displayInit();
}

void loop() {
  // put your main code here, to run repeatedly:
  displayWrite(keypadWaitValue());
  delay(1000);
  displayReset();
  for (uint8_t i = 0; i < 10; i++) {
    displayWrite(i);
    delay(500);
  }
}
