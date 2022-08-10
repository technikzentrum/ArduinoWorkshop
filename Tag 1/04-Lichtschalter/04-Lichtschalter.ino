// Bitte lese das Beispiel durch und vesuche es zu verstehen
#define BUTTON_PIN 0
void setup() {
  // Pins setzen aus das was sie sind
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT); // Hardware Pullup, Closed == GND Level (LOW)
}

void loop() {
  if (digitalRead(BUTTON_PIN) == LOW) {// Wenn wir an dem Pin 0 Lesen und das GND Level anliegt, dann machen wir etwas
    digitalWrite(LED_BUILTIN, HIGH);   // LED an
  } else {                             // Wenn die Bedingung oben nicht erfüllt ist
    digitalWrite(LED_BUILTIN, LOW);    // LED aus
  }
}
