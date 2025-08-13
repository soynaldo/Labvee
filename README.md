# Lavbee

## **`labveeBegin()`**

**Descripción:**
Inicializa todos los módulos principales de la librería para que puedan ser utilizados sin configuración adicional.
Debe llamarse una sola vez, normalmente dentro de la función `setup()` (o su equivalente en tu plataforma), antes de utilizar cualquier otra función de la librería.

**Qué hace internamente:**

* **`I2C_Begin()`** → Configura la comunicación I²C utilizada por algunos periféricos.
* **`KP.begin()`** → Inicializa el teclado matricial (`KP`), ya predeclarado como `extern KEYPAD_Class KP`.
* **`DISP.begin()`** → Inicializa los displays (`DISP`), ya predeclarados como `extern DISPLAY_Class DISP`.

**Instancias disponibles por defecto:**
Al incluir la librería, ya estarán disponibles los siguientes objetos globales para su uso inmediato:

* `UART` → Puerto UART principal (`SoftwareSerial`).
* `BT` → Puerto UART para comunicación Bluetooth (`SoftwareSerial`).
* `RFID` → Lector RFID MFRC522.
* `DISP` → Manejo de los displays.
* `KP` → Manejo del teclado matricial.
* `DIGITAL` → Manejo de salidas y entradas digitales.
* `PWM` → Generación de señales PWM.
* `DS` → Comunicación con el sensor DS (ej. DS18B20).

**Uso recomendado:**

```cpp
#include "Labvee.h"

void setup() {
    labveeBegin();  // Inicializa I2C, teclado y displays
}

void loop() {
    // Código principal usando las instancias globales
    DISP.print("Hola");
}
```

**Notas:**

* No es necesario instanciar manualmente `KP`, `DISP` u otros objetos listados arriba, ya que la librería los declara de forma global.
* No llamar a `labveeBegin()` antes de usar estas instancias puede provocar fallos o comportamientos inesperados.

## **`DIGITAL_Class`**

**Descripción general:**
`DIGITAL_Class` permite leer, escribir y configurar pines digitales conectados a un terminal de expansión I²C.
Es útil para controlar dispositivos externos (LEDs, relés, sensores, etc.) o para leer el estado de entradas (botones, interruptores, etc.) sin ocupar los pines físicos del microcontrolador.

Esta clase ya está preinstanciada en la librería como:

```cpp
extern DIGITAL_Class DIGITAL;
```

Por lo que puedes usar `DIGITAL` directamente sin necesidad de crear un objeto.

---

### **Constructor**

```cpp
DIGITAL_Class();
```

Inicializa internamente la comunicación con el expansor digital usando la dirección I²C definida en `LABVEE_DIGITAL_ADDRESS`.
**Uso:** No es necesario llamarlo manualmente, ya que la librería crea una instancia lista para usar.

---

### **Métodos disponibles**

#### **`read(uint8_t terminal, uint8_t pin)`**

Lee el estado actual de un pin digital.

**Parámetros:**

* `terminal` → Dirección del terminal digital (I²C).
* `pin` → Número de pin que se desea leer.

**Retorno:**

* `HIGH` → El pin está en alto (1).
* `LOW` → El pin está en bajo (0).

**Ejemplo:**

```cpp
uint8_t estado = DIGITAL.read(0x20, 3); // Lee el pin 3 del terminal en dirección 0x20
if (estado == HIGH) {
    // El pin está en alto
}
```

---

#### **`write(uint8_t terminal, uint8_t pin, uint8_t state)`**

Configura el estado de un pin digital como alto o bajo.

**Parámetros:**

* `terminal` → Dirección del terminal digital (I²C).
* `pin` → Número de pin a configurar.
* `state` → `HIGH` o `LOW`.

**Ejemplo:**

```cpp
DIGITAL.write(0x20, 5, HIGH); // Coloca el pin 5 en alto
```

---

#### **`mode(uint8_t terminal, uint8_t pin, uint8_t mode)`**

Configura si un pin será usado como entrada o salida.

**Parámetros:**

* `terminal` → Dirección del terminal digital (I²C).
* `pin` → Número de pin a configurar.
* `mode` → `INPUT` o `OUTPUT`.

**Ejemplo:**

```cpp
DIGITAL.mode(0x20, 5, OUTPUT); // Configura el pin 5 como salida
```

---

**Notas importantes:**

* Asegúrate de que la dirección `terminal` coincida con la dirección I²C real del expansor conectado.
* Antes de usar los pines como salidas, configúralos con `mode()`.
* La clase está diseñada para trabajar con un **IO Expander** que amplía la capacidad de entradas/salidas del sistema.

## **`DISPLAY_Class`**

**Descripción general:**
`DISPLAY_Class` permite controlar uno o dos **displays de 7 segmentos** conectados a través de un expansor I²C.
Con esta clase puedes escribir números, controlar segmentos individuales y encender o apagar el punto decimal.

La clase ya está preinstanciada en la librería como:

```cpp
extern DISPLAY_Class DISP;
```

Por lo que puedes usar `DISP` directamente sin necesidad de crear un objeto.

---

### **Constructor**

```cpp
DISPLAY_Class();
```

Inicializa la comunicación con el expansor de pines asociado a los displays, usando la dirección I²C definida en `LABVEE_DISPLAY_ADDRESS`.
**Uso:** No necesitas llamarlo directamente, ya que la instancia global `DISP` está lista para usar.

---

### **Métodos disponibles**

#### **`begin()`**

Inicializa el sistema de displays, configurando el IO Expander y preparando todos los pines para su uso.

**Ejemplo:**

```cpp
DISP.begin();
```

> **Nota:** Este método se ejecuta automáticamente si llamas a `labveeBegin()`.

---

#### **`reset(uint8_t display)`**

Apaga todos los segmentos del display especificado.

**Parámetros:**

* `display` → `DISPLAY_U` (unidades) o `DISPLAY_D` (decenas).

**Ejemplo:**

```cpp
DISP.reset(DISPLAY_U); // Apaga el display de unidades
```

---

#### **`reset()`**

Apaga todos los segmentos de ambos displays.

**Ejemplo:**

```cpp
DISP.reset();
```

---

#### **`write(uint8_t display, uint8_t value)`**

Escribe un valor numérico (0–9) en un display específico.

**Parámetros:**

* `display` → `DISPLAY_U` o `DISPLAY_D`.
* `value` → Número de 0 a 9 que se mostrará.

**Ejemplo:**

```cpp
DISP.write(DISPLAY_U, 7); // Muestra el número 7 en el display de unidades
```

---

#### **`write(uint8_t value)`**

Escribe un valor de **0 a 99** distribuyéndolo automáticamente en ambos displays.

**Parámetros:**

* `value` → Número de 0 a 99.

**Ejemplo:**

```cpp
DISP.write(42); // Muestra 4 en decenas y 2 en unidades
```

---

#### **`dp(uint8_t display, uint8_t value)`**

Enciende o apaga el punto decimal del display indicado.

**Parámetros:**

* `display` → `DISPLAY_U` o `DISPLAY_D`.
* `value` → `HIGH` para encender, `LOW` para apagar.

**Ejemplo:**

```cpp
DISP.dp(DISPLAY_U, HIGH); // Enciende el punto decimal en el display de unidades
```

---

#### **`segment(uint8_t display, uint8_t segment, uint8_t value)`**

Controla un segmento específico del display.

**Parámetros:**

* `display` → `DISPLAY_U` o `DISPLAY_D`.
* `segment` → Segmento (`D1_A` a `D1_DP` para unidades, `D2_A` a `D2_DP` para decenas).
* `value` → `HIGH` para encender, `LOW` para apagar.

**Ejemplo:**

```cpp
DISP.segment(DISPLAY_U, D1_A, HIGH); // Enciende el segmento A del display de unidades
```

---

#### **`segment(uint8_t display, uint8_t A, uint8_t B, uint8_t C, uint8_t D, uint8_t E, uint8_t F, uint8_t G, uint8_t DP)`**

Controla todos los segmentos de un display de forma directa.

**Parámetros:**

* `display` → `DISPLAY_U` o `DISPLAY_D`.
* `A`…`DP` → `HIGH` o `LOW` para cada segmento.

**Ejemplo:**

```cpp
// Enciende A, B, C y apaga los demás segmentos en el display de unidades
DISP.segment(DISPLAY_U, HIGH, HIGH, HIGH, LOW, LOW, LOW, LOW, LOW);
```

---

**Notas importantes:**

* Los valores de `display` están definidos como:

  * `DISPLAY_U` → Unidades
  * `DISPLAY_D` → Decenas
* Para manipulación de segmentos individuales, usa las constantes `D1_A` a `D2_DP`.
* El control de displays se realiza vía I²C, por lo que debes asegurarte de que el expansor esté conectado y con la dirección correcta.


## **`KEYPAD_Class`**

**Descripción general:**
`KEYPAD_Class` permite leer un teclado matricial conectado a través de un expansor I²C.
Esta clase facilita la detección de teclas presionadas y sus coordenadas dentro de la matriz.

Ya está preinstanciada en la librería como:

```cpp
extern KEYPAD_Class KP;
```

Por lo que puedes usar `KP` directamente sin necesidad de crear un objeto.

---

### **Constructor**

```cpp
KEYPAD_Class();
```

Configura internamente la dirección I²C del teclado (`LABVEE_KEYPAD_ADDRESS`).
**Uso:** No necesitas llamarlo, ya que la instancia global `KP` está lista para usarse.

---

### **Métodos disponibles**

#### **`begin()`**

Inicializa el teclado, configurando el IO Expander para permitir la lectura de teclas.

**Ejemplo:**

```cpp
KP.begin();
```

> **Nota:** Si usas `labveeBegin()`, esta inicialización se hace automáticamente.

---

#### **`read()`**

Lee el valor actual del teclado.
Si no hay ninguna tecla presionada, puede devolver `0` o un valor reservado.

**Retorno:**

* Código numérico correspondiente a la tecla presionada.

**Ejemplo:**

```cpp
uint8_t tecla = KP.read();
if (tecla != 0) {
    Serial.print("Tecla presionada: ");
    Serial.println(tecla);
}
```

---

#### **`wait()`**

Espera de forma bloqueante hasta que se presione una tecla y devuelve su valor.
Ideal para casos donde el programa debe detenerse hasta recibir una entrada del usuario.

**Retorno:**

* Código numérico de la tecla presionada.

**Ejemplo:**

```cpp
Serial.println("Presiona una tecla...");
uint8_t tecla = KP.wait();
Serial.print("Tecla recibida: ");
Serial.println(tecla);
```

---

#### **`coords()`**

Devuelve las coordenadas **(x, y)** de la última tecla presionada, usando la clase `Coords_t`.

**Retorno:**

* Un objeto `Coords_t` con:

  * `x` → posición en el eje horizontal.
  * `y` → posición en el eje vertical.

**Ejemplo:**

```cpp
Coords_t pos = KP.coords();
Serial.print("Coordenadas: X=");
Serial.print(pos.x);
Serial.print(", Y=");
Serial.println(pos.y);
```

---

**Notas importantes:**

* El teclado se comunica por I²C, por lo que es necesario que el expansor esté correctamente conectado y con la dirección configurada en `LABVEE_KEYPAD_ADDRESS`.
* Usa `wait()` solo cuando puedas permitir que el flujo del programa se detenga. Si necesitas lectura continua, usa `read()`.

---


## **`PWM_Class`**

**Descripción general:**
`PWM_Class` permite controlar un módulo **PCA9685** para generar múltiples señales PWM con diferentes ciclos útiles y frecuencias.
Es útil para controlar servomotores, iluminación LED, motores DC y otros dispositivos que requieran modulación por ancho de pulso.

Esta clase ya está preinstanciada en la librería como:

```cpp
extern PWM_Class PWM;
```

Por lo que puedes usar `PWM` directamente sin necesidad de crear un objeto.

---

### **Métodos disponibles**

#### **`begin()`**

Inicializa el módulo PWM con configuración por defecto.
Configura el módulo para usar la frecuencia base y estar listo para emitir PWM.

**Ejemplo:**

```cpp
PWM.begin();
```

---

#### **`begin(uint8_t prescale)`**

Inicializa el módulo PWM con un valor de prescaler específico, modificando así la frecuencia base de la señal.

**Parámetros:**

* `prescale` → Valor del prescaler (3–255).

**Ejemplo:**

```cpp
PWM.begin(50); // Inicia el módulo con prescaler 50
```

---

#### **`set(uint8_t pin, uint8_t percent)`**

Configura el ciclo útil (duty cycle) de un canal PWM.

**Parámetros:**

* `pin` → Canal del PCA9685 (0–15).
* `percent` → Ciclo útil en porcentaje (0–100).

**Ejemplo:**

```cpp
PWM.set(0, 75); // Canal 0 con 75% de duty cycle
```

---

#### **`get(uint8_t pin)`**

Obtiene el ciclo útil actual de un canal PWM.

**Parámetros:**

* `pin` → Canal del PCA9685.

**Retorno:**

* Porcentaje del duty cycle (0–100).

**Ejemplo:**

```cpp
uint16_t duty = PWM.get(0);
Serial.println(duty);
```

---

#### **`setFrecuency(float frequency)`**

Configura la frecuencia de salida del PWM en Hz.

**Parámetros:**

* `frequency` → Frecuencia deseada en Hz.

**Ejemplo:**

```cpp
PWM.setFrecuency(1000); // PWM a 1 kHz
```

---

#### **`setOscFreq(uint32_t freq)`**

Configura la frecuencia del oscilador interno del PCA9685.

**Parámetros:**

* `freq` → Frecuencia en Hz.

**Ejemplo:**

```cpp
PWM.setOscFreq(27000000); // Ajusta oscilador a 27 MHz
```

---

#### **`setExtClk(uint8_t prescale)`**

Configura el uso de un reloj externo en lugar del oscilador interno.

**Parámetros:**

* `prescale` → Valor del prescaler para el reloj externo.

**Ejemplo:**

```cpp
PWM.setExtClk(30);
```

---

#### **`reset()`**

Restaura el módulo a su estado inicial, apagando las salidas y reiniciando la configuración.

**Ejemplo:**

```cpp
PWM.reset();
```

---

#### **`sleep()`**

Pone el módulo en modo de bajo consumo, deteniendo las señales PWM.

**Ejemplo:**

```cpp
PWM.sleep();
```

---

#### **`wakeup()`**

Reactiva el módulo después de haber estado en suspensión.

**Ejemplo:**

```cpp
PWM.wakeup();
```

---

#### **`readPrescale()`**

Lee el valor actual del prescaler configurado.

**Retorno:**

* Valor del prescaler (3–255).

**Ejemplo:**

```cpp
uint8_t p = PWM.readPrescale();
Serial.println(p);
```

---

#### **`setMode(uint8_t mode, uint8_t value)`**

Configura un modo específico del módulo PWM.

**Parámetros:**

* `mode` → Registro de modo.
* `value` → Valor a asignar.

**Ejemplo:**

```cpp
PWM.setMode(PCA9685_MODE1, MODE1_AI);
```

---

#### **`getMode(uint8_t mode)`**

Obtiene el valor actual de un modo específico.

**Parámetros:**

* `mode` → Registro de modo.

**Retorno:**

* Valor leído del modo.

**Ejemplo:**

```cpp
uint8_t modo = PWM.getMode(PCA9685_MODE1);
```

---

**Notas importantes:**

* El PCA9685 permite controlar **hasta 16 canales PWM** independientes.
* La frecuencia máxima depende del prescaler y de la frecuencia del oscilador.
* Si usas servos, mantén la frecuencia en torno a **50 Hz**.
* Para LED y otros dispositivos, puedes usar frecuencias más altas como **1 kHz** o más.

---


## **Control de reproductor MP3 usando `UART` y `DFRobotDFPlayerMini`**

```cpp
te voy a pasar un ejemplo para que lo hagas mejor:
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
```

**Descripción general:**
La librería permite controlar un módulo MP3 (por ejemplo, **DFRobot DFPlayer Mini**) usando el puerto serial emulado `UART` a través de **SoftwareSerial**.
Se integra con Labvee para inicializar todos los controladores de manera simple mediante `labveeBegin()`.

Se utiliza la instancia:

```cpp
DFRobotDFPlayerMini MP3; ///< Instancia del reproductor MP3
```

---

### **Inicialización**

```cpp
Serial.begin(115200); // Puerto hardware para depuración
labveeBegin();        // Inicializa todos los controladores Labvee
UART.begin(9600);     // Inicializa el puerto SoftwareSerial
MP3.begin(UART);      // Inicializa el reproductor MP3 usando UART
```

**Explicación:**

* `Serial.begin()` se usa para enviar mensajes al monitor serial.
* `labveeBegin()` inicializa los controladores de Labvee (I²C, displays, teclado, etc.).
* `UART.begin()` configura el SoftwareSerial que comunica con la bocina o módulo MP3.
* `MP3.begin(UART)` conecta la instancia del reproductor al puerto UART definido.

---

### **Ejemplo de control en el loop**

```cpp
if (Serial.available()) {
    char c = Serial.read();
    if (c == 'n') MP3.next();         // Reproduce la siguiente pista
    else if (c == 'p') MP3.previous();// Reproduce la pista anterior
    else if (c == 's') MP3.stop();    // Detiene la reproducción
    else if (c == 'v') MP3.volumeUp();// Aumenta volumen
    else if (c == 'V') MP3.volumeDown();// Disminuye volumen
    else if (c == 'r') MP3.reset();   // Resetea el reproductor
}
```

**Explicación:**

* Permite enviar comandos simples desde el monitor serial para controlar la reproducción y volumen.
* Cada tecla corresponde a una acción específica del módulo MP3.

---

### **Gestión de eventos y errores**

```cpp
if (MP3.available()) {
    printDetail(MP3.readType(), MP3.read());
}
```

* `MP3.available()` verifica si hay mensajes de estado o errores del módulo.
* `printDetail()` permite interpretar estos mensajes y mostrarlos en el monitor serial.

**Ejemplo de eventos detectables:**

* `DFPlayerCardInserted` → Tarjeta SD insertada.
* `DFPlayerCardRemoved` → Tarjeta SD removida.
* `DFPlayerPlayFinished` → Fin de la reproducción de una pista.
* `DFPlayerError` → Error de módulo (tarjeta no encontrada, checksum incorrecto, etc.).

---

### **Función de detalle (`printDetail`)**

```cpp
void printDetail(uint8_t type, int value);
```

**Explicación:**

* Esta función imprime información sobre errores y estados del reproductor.
* Cada tipo de mensaje (`TimeOut`, `WrongStack`, `DFPlayerCardInserted`, etc.) se interpreta y se muestra de forma legible para el usuario.

---

