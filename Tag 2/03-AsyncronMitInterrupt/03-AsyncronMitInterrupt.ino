/* Beispiel aus der Bibiothek (angepasst duch Marco Gabrecht)
 *  Dies ist die Lösung von dem RAMP Beispiel.
 *  Bitte passe diese Beispiel so an, dass die LED innerhalb von 5 Sekunde auf 100% geht und danach wieder auf 0
 *  UND Schreibe alle 1000ms den aktuellen Wert in die Console.
 *  UND Lese alle 50ms einen Analogen Pin ein (10 Bit) und schreibe das Ergebnis in die Console
 *  Wichtig: Die LED muss weiterhin durchgänig faden.
 *  UND Wenn der button gedrückt wird soll in der Seriellenausgabe sofort an/aus stehen(Toggleswitch).
 *  
 *  Tipp: delay() sollte nicht verwendet werden.
 *  Verwende Interrpts, aber mache in der ISR (Interrupt Service Routine) nicht die Aufgaben. ISR müssen kurz sein.
 *  Mit Hilfe von booleschen Variablen, die du in einem Interrupt setzt,
 *  kannst du in dem Loop Aktionen einmalig ausführen lassen, wie in dem Beispiel.
 *  Die Funktionen sind auch schon geschrieben, verstehe sie und baue die fehlenden
 *  Aufrufe.
 *  
 *  Links:
 *  https://www.arduino.cc/reference/en/libraries/ramp/
 *  https://github.com/siteswapjuggler/RAMP
 *  https://randomnerdtutorials.com/esp32-pwm-arduino-ide/
 *  https://www.arduino.cc/reference/de/language/functions/time/millis/
 *  https://www.arduino.cc/reference/de/language/functions/communication/serial/begin/
 *  https://www.arduino.cc/reference/de/language/structure/arithmetic-operators/modulo/
 *  https://www.arduino.cc/reference/de/language/structure/control-structure/else/
 *  https://randomnerdtutorials.com/esp32-adc-analog-read-arduino-ide/
 *  https://lastminuteengineers.com/handling-esp32-gpio-interrupts-tutorial/
 *  https://www.arduino.cc/reference/de/language/variables/variable-scope-qualifiers/volatile/
 *  https://techtutorialsx.com/2017/10/07/esp32-arduino-timer-interrupts/
 *  
 */
#include <Ramp.h>                             // include library
#define BUTTONPIN 0

ramp myRamp;                               // new int ramp object
int analogPin = 34;
volatile boolean onOff = false;
volatile boolean triggerColsole = false;
volatile boolean trigerAnalogRead = false;
volatile boolean triggerButton = false;
hw_timer_t * timer = NULL;

void IRAM_ATTR buttonIsFalling() {
  triggerButton = true;
  onOff = !onOff;
}

void IRAM_ATTR startAnalogReading() {
  trigerAnalogRead = true;
}

void IRAM_ATTR startConsoleWriting() {
  triggerColsole = true;
}



void setup() {
  analogReadResolution(10);
  pinMode(LED_BUILTIN, OUTPUT);             // LED als ausgabe
  myRamp.go(0);                            // setze anfangswert auf 0
  myRamp.go(255, 5000, LINEAR, BACKANDFORTH);      // gehe in 5000ms auf 255 linear und das in einem forwärts und rückwärts Kreislauf.
  // ESP32 Spezifisch
  ledcSetup(0, 5000, 8);                    // Sage der Hardware, dass der LED Channel 0
                                            // mit einer Ferequenz von 5000Hz und einer 8 bit (0-255) auflösung funktionieren soll
  ledcAttachPin(LED_BUILTIN, 0);            // Sage der Hardware, das Pin 25 (LED) mit Channel 1 gesteuert werden soll.
  Serial.begin(115200);                     // Schneler und braucht deshalb weniger Zeit
  pinMode(BUTTONPIN, INPUT);
  attachInterrupt(BUTTONPIN, buttonIsFalling, FALLING);
  timer = timerBegin(0, 80, true);// Timer mit index 0 von 4 mit einem prescaler von 80 hochzählend
  // Der ESP32 hat 80 MHz auf seiner clock mit dem Prescaler 80 wir reduzieren unseren Timer auf 1MHz
  // 1 000 000 mal die Sekunde, alsoe jede Microsekund
  timerAttachInterrupt(timer, &startAnalogReading, true);
  // Dem Timer wird der Pointer zu unserer ISR übergeben
  timerAlarmWrite(timer, 50000, true);
  // Wir sagen die Funktion sol alle 50000 microsekunden, also alle 50 ms aufgerufen werden.
  timerAlarmEnable(timer); // Wir aktiviren alles
  // Benutze gerne Timer 1,2,3 für deine anderen Aufgaben.
  // Optional benutze nur Timer 0 und multiplexe den Interrupt
}

void loop() {
  if (triggerColsole) {
    triggerColsole = false;
    Serial.println(myRamp.update());
  }
  if (trigerAnalogRead) {
    trigerAnalogRead = false;
    int analogValue = analogRead(analogPin);
    Serial.println(analogValue);
  }
  if (triggerButton) {
    triggerButton = false;
    Serial.println(onOff?"An":"Aus");
  }
  byte val = myRamp.update();                  // Hole die aktuelle Zahl
  //analogWrite(LED_BUILTIN, val);            // Arduino Style, nicht ESP32
  ledcWrite(0, val);                          // Setze den LED Channel 0 auf die aktuelle Zahl
}
