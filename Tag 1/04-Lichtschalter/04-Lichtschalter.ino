// the setup function runs once when you press reset or power the board
#define BUTTON_PIN 0
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT); // Hardware Pullup, Closed == GND Level (LOW)
}

// the loop function runs over and over again forever
void loop() {
  if (digitalRead(BUTTON_PIN) == LOW) {// Wenn wir an dem Pin 0 Lesen und das GND Level anliegt, dann machen wir etwas
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  } else {                             // Wenn die Bedinung oben nicht erfüllt ist
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  }
}
