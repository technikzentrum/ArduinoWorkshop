/* Beispiel aus der Bibliothek (angepasst duch Marco Gabrecht)
 *  Dies ist die Lösung von dem RAMP Beispiel.
 *  Bitte passe diese Beispiel so an, dass die LED innerhalb von einer Sekunde auf 100% geht und danach wieder auf 0
 *  UND Schreibe alle 1000ms den aktuellen Wert in die Console.
 *  UND Lese alle 50ms einen Analogen Pin ein (10 Bit, 4 cycles(ESP32 spezifish)) und schreibe das Ergebnis in die Console
 *  Wichtig: Die LED muss weiterhin durchgänig faden.
 *  UND Wenn der button gedrückt wird soll die LED sofort an/aus gehen(Toggleswitch).
 *  
 *  Tipp: delay() sollte nicht verwendet werden, aber du kannst dir merken wie viel Zeit
 *  vergeht indem du millis() aufrufst, dies gibt dir die Millisekunden als long zurück, 
 *  welche das System schon läuft. So kannst du die Wartezeiten realisieren, ohne zu blockieren.
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
 *  
 */
#include <Ramp.h>                             // include library

ramp myRamp;                               // new int ramp object

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);             // LED als ausgabe
  myRamp.go(0);                            // setze anfangswert auf 0
  myRamp.go(255, 1000, LINEAR, BACKANDFORTH);      // gehe in 1000ms auf 255 linear und das in einem Vorwärts- und Rückwärtskreislauf.
  // ESP32 Spezifisch
  ledcSetup(0, 5000, 8);                    // Sage der Hardware, dass der LED Channel 0 ist.
                                            // mit einer Frequenz von 5000Hz und einer 8 bit (0-255) Auflösung funktionieren soll
  ledcAttachPin(LED_BUILTIN, 0);            // Sage der Hardware, das Pin 25 (LED) mit Channel 1 gesteuert werden soll.
  Serial.begin(115200);                     // Schneller und braucht deshalb weniger Zeit
}

void loop() {
  // deine Erweiterrung ...
  byte val = myRamp.update();                  // Hole die aktuelle Zahl
  //analogWrite(LED_BUILTIN, val);            // Arduino Style, nicht ESP32
  ledcWrite(0, val);                          // Setze den LEd Channel 0 auf die aktuelle Zahl
}

// Lösung hat Kompilierungsfehler, läuft nicht.
