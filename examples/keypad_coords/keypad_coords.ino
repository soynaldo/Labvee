#include "labvee.h"

String position[4][4] = {
  {"1","2","3","F1"},
  {"4","5","6","F2"},
  {"7","8","9","F3"},
  {"START","0","STOP","F4"}
};

void setup() {
    Serial.begin(115200); // Initialize the serial port at 115200 baud rate
    labveeBegin(); // Initialize LabVee library
}

void loop() {
    Coords_t coord = KP.coords(); // Get the coordinates of the pressed keyn
    Serial.println("looping");
    if (coord.row > 0 && coord.column > 0) { // Check if
        Serial.print("Key pressed at: ");
        Serial.print(coord.row);
        Serial.print(", ");
        Serial.println(coord.column);

        String key = position[coord.row - 1][coord.column - 1]; // Get the key from the map
        Serial.print("Key value: ");
        Serial.println(key);      
    }

    delay(100); // Wait for 100 ms before the next loop iteration
}