/*
  Dies ist das Blink Besispiel aus dem Ersten Programmier Thema
  Bitte erweiterre dieses um die Funktion, dass immer wenn man den Knopf Drückt,
  die LED 10% langsamer Blinkt, als vorher und wenn man ihn nicht drückt bei jedem durchlauf 10% schneller.
  Bedenke bitte auch Randbedinungen. (min max + Prezisionslimmits)
  Du wirst eine Varriable benutzen müssen.
  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Blink
  Hilfreiche Dokumentation:
  https://www.arduino.cc/reference/de/language/variables/data-types/int/
  https://www.arduino.cc/reference/de/language/functions/digital-io/pinmode/
  https://www.arduino.cc/reference/en/language/functions/digital-io/digitalread/
  https://www.arduino.cc/reference/de/language/functions/time/delay/
  https://www.arduino.cc/reference/de/language/structure/control-structure/if/
  https://www.arduino.cc/reference/de/language/structure/control-structure/else/
*/
int wartezeit = 1000;
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  // deine Erweiterrung
}


void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(wartezeit);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(wartezeit);                       // wait for a second
}
