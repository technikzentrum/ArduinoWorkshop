/*
 * Structs sind sammlungen von Variablen.
 * Es kann als Objekte ohne Funktionen gesehen werden.
 * Aufgabe: Erweitere das Beispiel um Spitzname und Telefonnummer
 * 
 * Beispiel von: https://www.tutorialspoint.com/structs-in-arduino-program#
 * 
 * 
 * https://www.arduino.cc/reference/de/language/functions/communication/serial/readstring/
 * https://www.arduino.cc/reference/de/language/functions/communication/serial/parseint/
 */

 struct student{    // Erstelle eine Sammlung von Variablen und gebe ihnen einen neu erstellten Datentypen
   String name;     // Der Datentyp student bekommt das Atribut Name vom Typ String
   int alter;       // Und alter vom Typ int
};

void setup() {
   Serial.begin(115200);
   Serial.println();
   student A = {"Max Müller", 25};  // Erstelle einen student, schnelle schreibweise
   Serial.println(A.name);          // komme an die Variable name von student A
   Serial.println(A.alter);
}

void loop() {
   student B = {};
   Serial.print("Name des Studenten: ");
   B.name = Serial.readString();
   Serial.print("Wie alt ist ");
   Serial.print(B.name);
   Serial.print(": ");
   B.alter = Serial.parseInt();
   Serial.print(B.name);
   Serial.print(" (");
   Serial.print(B.alter);
   Serial.println(" Jahre)");
}
