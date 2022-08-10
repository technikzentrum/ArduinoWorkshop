/*
 * Beim Programmieren lernt man meistens zu erst das "Hello World", wo man sich diesen Text ausgeben lässt, bei µC ist die Textausgabe schon sehr komplex, deshalb beginnen wir mit einer LED, die Blinkt.

Arduino besitzt immer einen Einsprungpunkt(Setup) wo er beginnt Befehle auszuführen.
Danach Springt er immer in einen Dauerschleife(Loop), wo er seine von dir programmierte Aufgabe erfüllt.

Öffnet das Beispiel (03-Blinken.ino)

Geht unter "Werkzeuge"->"Bord: ****" -> "Bordverwalter" und gebt "ESP32" ein.
Installiert "Heltec ESP32 Series DEV-Bords"
Wählt bei "Werkzeuge"->"Bord: ****" -> "WiFi LoRa 32(V2)" aus.

Lest euch das Programm durch und versucht es zu verstehen.

Geht auf "Werkzeuge"->"Port" und schaut euch alle Ports an, die gerade verfügbar sind.
Steckt dann das Bord per USB an und wählt den Port aus, der neu hinzugekommen ist.

Drückt dann auf "->" um das Programm zu kompelieren und hochzuladen.

Nun sollte die weiße LED Blinken.
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Blink
*/

// Die Setup Funktion, hier werden alle Vorbereitungen getroffen
void setup() {
  // Den Pin der LED auf ausgabe setzen.
  pinMode(LED_BUILTIN, OUTPUT);
}

// Die Loop Funktion, dies ist eine Schleife, welche ewig läuft
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   // LED an (HIGH ist, dass Strom fließt, also Strom anliegt)
  delay(1000);                       // ware 1000ms also eine Sekunde
  digitalWrite(LED_BUILTIN, LOW);    // LED aus (LOW ist, dass GND anliegt, also keine Spannung))
  delay(1000);                       // warte eine Sekunde
}
