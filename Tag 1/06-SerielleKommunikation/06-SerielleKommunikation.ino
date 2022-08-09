/*
  ReadSerial

  Basisprogramm für Serielle Kommunikation
  Quelle: https://www.arduino.cc/reference/de/language/functions/communication/serial/read/
  Angepasst durch Marco Gabrecht

  Bitte passe dieses Programm so an, dass wenn man ein "+" Schreibt
  die LED 10% schneller Blinkt und bei "-" 10% langsamer.
  Bonus: Wenn man eine Zahl schreibt, soll die wartezeit auf diese Zahl gesetzt werden.
  Negative eingaben müssen verhindert werden.
  Hilfreiche Links:
  https://www.arduino.cc/reference/de/language/variables/data-types/int/
  https://www.arduino.cc/reference/de/language/functions/digital-io/pinmode/
  https://www.arduino.cc/reference/en/language/functions/digital-io/digitalread/
  https://www.arduino.cc/reference/de/language/functions/time/delay/
  https://www.arduino.cc/reference/de/language/structure/control-structure/if/
  https://www.arduino.cc/reference/de/language/structure/control-structure/else/
  https://arduinogetstarted.com/de/reference/serial-readstring
  https://www.arduino.cc/reference/de/language/functions/communication/serial/print/
  https://www.arduino.cc/reference/de/language/functions/communication/serial/println/
  https://www.arduino.cc/reference/de/language/variables/data-types/stringobject/
  https://www.arduino.cc/reference/de/language/variables/data-types/string/functions/equals
  https://www.arduino.cc/reference/de/language/variables/data-types/string/functions/startswith
  https://www.arduino.cc/reference/de/language/variables/data-types/string/functions/toint  
  
*/
void setup() {
  Serial.begin(9600); // Öffnet die serielle Schnittstelle und stellt die Datenrate auf 9600 Bit/s ein
  delay(1000);
  Serial.println("Wie ist dein Name?");
}

void loop() {
  // Daten nur senden, wenn Daten erhalten:
  if (Serial.available() > 0) {
    // Lies die eingehenden Bytes:
    String text = Serial.readString();

    // Ausgeben:
    Serial.print("Hallo ");
    Serial.println(text);
  }
}
