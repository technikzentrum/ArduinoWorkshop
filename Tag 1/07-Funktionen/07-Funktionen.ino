/*
  Funktionen

  Basisprogramm für Serielle Kommunikation
  Quelle: https://www.arduino.cc/reference/de/language/functions/communication/serial/read/
  Angepasst durch Marco Gabrecht

  Bitte passe dieses Programm so an, dass man folgende Ausgabe für folgende Eingabe bekommt:
  Test -> "Dies ist ein Test"
  Ping -> "Pong"
  +, -, *, / -> "Du hast * geschrieben" (wobei * für die Eingabe steht)
  Hallo -> "Hallo <NAME>"
  Ich heiße <NAME> -> Speichert den Namen in der Variablen <NAME>
  <INT> -> <INT> + 1 (Also, wenn du eine Zahl schriebst, dann soll die Zahl plus 1 zurückgegeben werden)
  LED AN -> Macht die LED an
  LED AUS -> Macht die LED aus
  Hilfreiche Links:
  https://www.arduino.cc/reference/de/language/variables/data-types/int/
  https://www.arduino.cc/reference/de/language/functions/digital-io/pinmode/
  https://www.arduino.cc/reference/de/language/functions/digital-io/digitalread/
  https://www.arduino.cc/reference/de/language/functions/time/delay/
  https://www.arduino.cc/reference/de/language/structure/control-structure/if/
  https://www.arduino.cc/reference/de/language/structure/control-structure/else/
  https://arduinogetstarted.com/de/reference/serial-readstring/
  https://www.arduino.cc/reference/de/language/functions/communication/serial/print/
  https://www.arduino.cc/reference/de/language/functions/communication/serial/println/
  https://www.arduino.cc/reference/de/language/variables/data-types/stringobject/
  https://www.arduino.cc/reference/de/language/variables/data-types/string/functions/equals/
  https://www.arduino.cc/reference/de/language/variables/data-types/string/functions/startswith/
  https://www.arduino.cc/reference/de/language/variables/data-types/string/functions/toint/  
  https://myhomethings.eu/de/arduino-funktionen/
  https://www.arduino.cc/reference/de/language/variables/data-types/string/functions/substring/
  https://www.arduino.cc/reference/de/language/variables/data-types/string/functions/length/
  
*/
String meinName = "Name";

void rechenzeichen(String eingabe) {
  Serial.println(eingabe.substring(0, 1));
}

void testEingabe() {
  Serial.println("Dies ist ein Test");
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);  // Den LED Pin 25 Setzen wir als Ausgabe Pin
  Serial.begin(9600); // Öffnet die serielle Schnittstelle und stellt die Datenrate auf 9600 Bit/s ein
  delay(1000);
  Serial.println("Ich kann ganz schön viel.");
}

void loop() {
  // Daten nur senden, wenn Daten erhalten:
  if (Serial.available() > 0) {
    // Lies die eingehenden Bytes:
    String text = Serial.readString();
    if (text.equals("Test\n")) {
      testEingabe();
    } else if (text.equals("+\n") || text.equals("-\n") || text.equals("*\n") || text.equals("/\n")) {
      rechenzeichen(text);
    }else {
      Serial.println("Ich habe dich nicht verstanden.");
    }
  }
}
