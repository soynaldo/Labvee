#include "labvee.h"

String celd[16] = {
  "1","2","3","F1",
  "4","5","6","F2",
  "7","8","9","F3",
  "START","0","STOP","F4"
};


void setup() {
    Serial.begin(115200); // Initialize the serial port at 115200 baud rate
    labveeBegin(); // Initialize LabVee library
}

void loop() {
    int value = KP.read(); // Read the pressed key from the keypad
    if (value > 0) { // Check if a key is pressed
        Serial.print("Key pressed: ");
        Serial.println(value); // Print the pressed key value
        String key = celd[value - 1]; // Get the key from the map
        Serial.print("Key value: ");
        Serial.println(key); // Print the key value
    }

    delay(100); // Wait for 100 ms before the next loop iteration
}