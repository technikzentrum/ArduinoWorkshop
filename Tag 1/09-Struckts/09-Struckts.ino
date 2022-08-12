/*
   Structs sind sammlungen von Variablen.
   Es kann als Objekte ohne Funktionen gesehen werden.
   Aufgabe: Erweitere das Beispiel um Spitzname und Telefonnummer

   Beispiel von: https://www.tutorialspoint.com/structs-in-arduino-program#


   https://www.arduino.cc/reference/de/language/functions/communication/serial/readstring/
   https://www.arduino.cc/reference/de/language/functions/communication/serial/parseint/
*/

 struct student{    // Erstelle eine Sammlung von Variablen und gebe ihnen einen neu erstellten Datentypen
   String name;     // Der Datentyp student bekommt das Atribut Name vom Typ String
   int alter;       // Und alter vom Typ int
};

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    ; // warte auf die Serielleverbindung.
  }
  delay(1000);// warte auf die Serielleverbindung.
  Serial.println();
  student A = {"Max Müller", 25, "Maxi", "+491523498674"};  // Erstelle einen student, schnelle schreibweise
  Serial.println(A.name);          // komme an die Variable name von student A
  Serial.println(A.alter);
  Serial.println("");
}

void loop() {
  student B = {};            // Erstelle einen Studenten
  
  //Name
  Serial.print("Name des Studenten: ");// Frage nach dem namen
  while (Serial.available() == 0) { // Warte auf eine eingabe
    delay(100);
  }
  B.name = Serial.readString();    // Lese die eingabe ein
  B.name = B.name.substring(0, B.name.length() - 1); // Scheinde den Zeilenumbruch weg.
  Serial.println(B.name);// Schreibe den Namen in die Console
  
  //Alter
  Serial.print("Wie alt ist ");// Frage nach dem Alter
  Serial.print(B.name);        // Schreibe den Namen
  Serial.print(": ");
  while (Serial.available() == 0) { // Warte auf die Eingabe
    delay(100);
  }
  B.alter = Serial.parseInt(); // Lese die eingabe als Zahl ein
  Serial.readString();         // Clear everything else
  Serial.println(B.alter);
  
  Serial.println("");
  Serial.print("Name: " );     // Gebe den Studenten aus
  Serial.println(B.name);
  Serial.print("Alter: ");
  Serial.print(B.alter);
  Serial.println(" Jahre");
  Serial.println("");
}
