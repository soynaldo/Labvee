#include "labvee.h"

#include "DFRobotDFPlayerMini.h"

DFRobotDFPlayerMini MP3;    ///< Instancia del reproductor MP3.

void setup() {
    Serial.begin(115200);   ///< Inicializa la comunicación UART a 115200 baudios.
    labveeBegin();          ///< Inicializa los controladores de Labvee.
    UART.begin(9600);       // Inicializar la comunicación serial
    MP3.begin(UART);        ///< Inicializa el reproductor MP3.
}

void loop() {
    // // Esperar un segundo antes de la siguiente lectura
    delay(1000);
    if (Serial.available()) {
        char c = Serial.read();
        if (c == 'n') {
            Serial.println(F("Next"));
            MP3.next();  //Play next mp3
        } else if (c == 'p') {
            Serial.println(F("Previous"));
            MP3.previous();  //Play previous mp3
        } else if (c == 's') {
            Serial.println(F("Stop"));
            MP3.stop();  //Stop playing
        } else if (c == 'v') {
            Serial.println(F("Volume Up"));
            MP3.volumeUp();  //Increase volume
        } else if (c == 'V') {
            Serial.println(F("Volume Down"));
            MP3.volumeDown();  //Decrease volume
        } else if (c == 'r') {
            Serial.println(F("Reset"));
            MP3.reset();  //Reset the player
        }
    }
    
    if (MP3.available()) {
        printDetail(MP3.readType(), MP3.read()); //Print the detail message from DFPlayer to handle different errors and states.
    }
}

void printDetail(uint8_t type, int value){
  switch (type) {
    case TimeOut:
      Serial.println(F("Time Out!"));
      break;
    case WrongStack:
      Serial.println(F("Stack Wrong!"));
      break;
    case DFPlayerCardInserted:
      Serial.println(F("Card Inserted!"));
      break;
    case DFPlayerCardRemoved:
      Serial.println(F("Card Removed!"));
      break;
    case DFPlayerCardOnline:
      Serial.println(F("Card Online!"));
      break;
    case DFPlayerUSBInserted:
      Serial.println("USB Inserted!");
      break;
    case DFPlayerUSBRemoved:
      Serial.println("USB Removed!");
      break;
    case DFPlayerPlayFinished:
      Serial.print(F("Number:"));
      Serial.print(value);
      Serial.println(F(" Play Finished!"));
      break;
    case DFPlayerError:
      Serial.print(F("DFPlayerError:"));
      switch (value) {
        case Busy:
          Serial.println(F("Card not found"));
          break;
        case Sleeping:
          Serial.println(F("Sleeping"));
          break;
        case SerialWrongStack:
          Serial.println(F("Get Wrong Stack"));
          break;
        case CheckSumNotMatch:
          Serial.println(F("Check Sum Not Match"));
          break;
        case FileIndexOut:
          Serial.println(F("File Index Out of Bound"));
          break;
        case FileMismatch:
          Serial.println(F("Cannot Find File"));
          break;
        case Advertise:
          Serial.println(F("In Advertise"));
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
  
}