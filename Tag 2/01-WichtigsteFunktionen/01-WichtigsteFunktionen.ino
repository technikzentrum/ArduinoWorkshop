/*
  Der Inhalt ist aus den Beispielen von Arduino
  Datei -> Beispiele
*/

#define buttonPin 2     // Defines sind Werte, die im Quellcode genau so gesetzt werden, keine Varriablen
const int ledPin =  13; // Constanten sind Varriablen, die nicht mehr geändert werden

int buttonState = 0;    // normale Variablen können verwendet werden und verändert werden.
                        // Variablen die außerhalb von Funktionen gesetzt werden können innerhalb von allen benutzt werden.

void setup() {
  pinMode(ledPin, OUTPUT);// Pins müssen als Ausgabe oder Eingabe definiert werden.
  pinMode(buttonPin, INPUT);// Sie können INPUT, OUTPUT oder INPUT_PULLUP (INPUT_PULLDOWN -> nur ESP32 nur besondere Pins)sein.
                         // Input ist hochohmig, Output ist GND(LOW) oder 40ma 3.3V(HIGH), Pullup istmit 10K bis 100K wiederstand realisiert 
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);       // Über RX und TX (An USB angeschlossen) können Daten gesendet werden.
                        // 9600 ist normal für 8Bit Arduinos, 115200 für ESP32
//ESP32
  ledcSetup(0, 5000, 8);                    // Sage der Hardware, dass der LED Channel 0
                                            // mit einer Frequenz von 5000Hz und einer 8 bit (0-255) Auflösung funktionieren soll.
  ledcAttachPin(LED_BUILTIN, 0);            // Sage der Hardware, das Pin 25 (LED) mit Channel 1 gesteuert werden soll.

}

void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // turn LED on:
    digitalWrite(ledPin, HIGH);
    int fadeValue = random(100, 256); // Variablen innerhalb einer Funktion und innerhalb eines Blocks {..} sind nur da drin aufrufbar und werden danach verworfen.
    analogWrite(LED_BUILTIN, fadeValue);
    ledcWrite(0, fadeValue);                          // Setze den LED Channel 0 auf die aktuelle Zahl
  } else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
  }
  delay(30);
}
