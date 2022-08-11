/* Beispiel aus der Bibiothek (angepasst duch Marco Gabrecht)
 *  Dies ist die Lösung von dem RAMP Beispiel.
 *  Bitte lese dieses Beispiel durch und verstehe wie, die LED innerhalb von einer Sekunde auf 100% geht und danach wieder auf 0
 *  UND Schreibe alle 1000ms den aktuellen Wert in die Console.
 *  UND Lese alle 50ms einen Analogen Pin ein (10 Bit, 4 cycles(ESP32 spezifish)) und schreibe das Ergebnis in die Console
 *  UND Wenn der button gedrückt wird soll die LED sofort an/aus gehen(Toggleswitch).
 *  
 *  Tipp: delay() kann verwendet werden, besser ist vTaskDelay(50 / portTICK_PERIOD_MS);, was das selbe macht nur mit FreeRTOS
 *  Umsetzung mit FreeRTOS, du kannst Task (sozusagen einzelne Programme) schreiben, 
 *  die vom Betriebssystem verwaltet werden und parallel oder abwechselnd aufgerufen 
 *  werden, somit kannst du für jede Aufgabe ein eigenes einfaches Programm schreiben.
 *  
 *  Links:
 *  https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/freertos.html
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
#include <Ramp.h>                           // include library
#define BUTTONPIN 0
#if CONFIG_FREERTOS_UNICORE
#define ARDUINO_RUNNING_CORE 0
#else
#define ARDUINO_RUNNING_CORE 1
#endif
#define CONSOLE_SMAPLE_TIME 1000
TaskHandle_t tButton;
void TaskFade( void *pvParameters );
void TaskAnalogRead( void *pvParameters );
void TaskConsole( void *pvParameters );
void TaskButton( void *pvParameters );

void IRAM_ATTR buttonIsFalling() {
  BaseType_t xYieldRequired;
  xTaskResumeFromISR(tButton);
  //portYIELD_FROM_ISR( xYieldRequired );
}

ramp myRamp;                               // new int ramp object
boolean toggleswitch = false;

void setup() {
  Serial.begin(115200);                     // Schneler und braucht deshalb weniger Zeit
  Serial.write(configMAX_PRIORITIES);
  // Erstelle einen Fade Task und Priorisiere ihn niedrig, da er keine Wartezeit implementiert hat
  xTaskCreatePinnedToCore(
    TaskFade
    ,  "TaskFade"   // A name just for humans
    ,  1024  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL // Parameter
    ,  1  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  NULL // Handle to Task
    ,  ARDUINO_RUNNING_CORE);
  // Erstelle den Task AnalogRead, der ist höher als der Fade Task und wird diesen also unterbrechen
  xTaskCreatePinnedToCore(
    TaskAnalogRead
    ,  "TaskAnalogRead"   // A name just for humans
    ,  1024  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL // Parameter
    ,  2  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  NULL // Handle to Task
    ,  ARDUINO_RUNNING_CORE);
  // Erstelle den TaskConsole mit selber Priorität der wird Fade unterbrechen und sich mit AnalogRead abwechseln im 1MS takt
  xTaskCreatePinnedToCore(
    TaskConsole
    ,  "TaskConsole"   // A name just for humans
    ,  1024  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL // Parameter
    ,  2  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  NULL // Handle to Task
    ,  ARDUINO_RUNNING_CORE);
  xTaskCreatePinnedToCore(
    TaskButton
    ,  "TaskButton"   // A name just for humans
    ,  1024  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL // Parameter
    ,  2  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  &tButton // Handle to Task (Pointer)
    ,  ARDUINO_RUNNING_CORE);
}

void loop() {
  vTaskDelete(NULL);  // Lösche diesen Task, er wird nicht gebraucht
}

void TaskFade( void *pvParameters ) {
  pinMode(LED_BUILTIN, OUTPUT);             // LED als ausgabe
  myRamp.go(0);                            // setze anfangswert auf 0
  myRamp.go(255, 1000, LINEAR, BACKANDFORTH);      // gehe in 1000ms auf 255 linear und das in einem forwärts und rückwärts Kreislauf.
  // ESP32 Spezifisch
  ledcSetup(0, 5000, 8);                    // Sage der Hardware, dass der LED Channel 0
                                            // mit einer Ferequenz von 5000Hz und einer 8 bit (0-255) auflösung funktionieren soll
  ledcAttachPin(LED_BUILTIN, 0);            // Sage der Hardware, das Pin 25 (LED) mit Channel 1 gesteuert werden soll.
  for (;;) {
    byte val = myRamp.update();                  // Hole die aktuelle Zahl
    //analogWrite(LED_BUILTIN, val);            // Arduino Style, nicht ESP32
    ledcWrite(0, val);                          // Setze den LEd Channel 0 auf die aktuelle Zahl
  }
}
void TaskAnalogRead( void *pvParameters ) {
  int analogPin = 34;
  analogReadResolution(10);
  analogSetCycles(4);
  for (;;) {
    int analogValue = analogRead(analogPin);
    Serial.println(analogValue);
    vTaskDelay(50 / portTICK_PERIOD_MS);// warte 50 ms nachdem du deine aktion gemacht hast
  }
}
void TaskConsole( void *pvParameters ) {
  TickType_t xLastWakeTime;
  xLastWakeTime = xTaskGetTickCount();
  for (;;) {
    vTaskDelayUntil(&xLastWakeTime, CONSOLE_SMAPLE_TIME / portTICK_PERIOD_MS);// Warte die Zeit, bis 1000ms wieder um sind seit diesem letzten aufruf
    Serial.println(myRamp.update());
  }
}
void TaskButton( void *pvParameters ) {
  pinMode(BUTTONPIN, INPUT);
  attachInterrupt(BUTTONPIN, buttonIsFalling, FALLING);
  for (;;) {
    vTaskSuspend( NULL );               // Beende den Task bis er geweckt wird
    toggleswitch = !toggleswitch;      // Wechsle die Varriable
    Serial.println(toggleswitch);     // Schreibe (eigentliche Aufgabe)
  }
}

// LÖSUNG läuft nicht: 'analogSetCycles' was not declared in this scope
