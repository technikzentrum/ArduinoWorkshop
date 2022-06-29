/*
  Dies ist das Blink Besispiel aus dem Ersten Programmier Thema
  Bitte erweiterre dieses um die Funktion, dass wenn man den Knopf Drückt,
  die LED 10% langsamer Blinkt und wenn man ihn nicht drückt 10% schneller.
  Bedenke bitte auch Randbedinungen. (min max + Prezisionslimmits)
  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Blink
  Hilfreiche Dokumentation:
  https://www.arduino.cc/reference/de/language/variables/data-types/int/
  https://www.arduino.cc/reference/de/language/functions/digital-io/pinmode/
  https://www.arduino.cc/reference/en/language/functions/digital-io/digitalread/
  https://www.arduino.cc/reference/de/language/functions/time/delay/
  https://www.arduino.cc/reference/de/language/structure/control-structure/if/
  https://www.arduino.cc/reference/de/language/structure/control-structure/else/
*/

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
}
