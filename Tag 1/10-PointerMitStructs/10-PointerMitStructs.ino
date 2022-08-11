/*
 * Structs sind sammlungen von Variablen.
 * Es kann als Objekte ohne Funktionen gesehen werden.
 * Pointer sind Zeiger auf ein Objekt, sowas wie die Adresse eines Gebäudes
 * Aufgabe: Lerne Pointer kennen und verstehe "&" "*" "." "->"
 * UND Erstelle eine kopier funktion, womit man eine unabhänige Kopie erhält.
 * 
 * Beispiel von: https://www.tutorialspoint.com/structs-in-arduino-program#
 * 
 * 
 * https://www.arduino.cc/reference/de/language/functions/communication/serial/readstring/
 * https://www.arduino.cc/reference/de/language/functions/communication/serial/parseint/
 */

 struct student{    // Erstelle eine Sammlung von Varablen und gebe ihnen einen neu erstellten Datentypen
   String name;     // Der Datentype student bekommt das Attribut Name vom Type String
   int alter;       // Und alter vom Type int
};

student increaseAge(student *B){  // Diese Funktion bekommt den Pointer eines student und erhöht das alter
   B->alter = B->alter + 1;       // Alter ist = alter +1 (-> wird auf Pointern verwendet)
   return *B;                     // Gibt den Pointer auf den Studenten zurück
}

void setup() {
   Serial.begin(115200);
   Serial.println();
   student A = {"Max Müller", 25};  // Erstelle einen student, schnelle Schreibweise
   Serial.println(A.name);          // komme an die Variable name von student A
   Serial.println(A.alter);
   student *C = &A;           // Erstelle einen Pointer auf einen student C und schreibe in ihn den Pointer von A
    // * ist eine Adresse zu einem Objekt
    // & nimmt die Adresse von einem Objekt
    //increaseAge(A); Dies würde nicht funktionieren, da die Funktion einen Pointer erwartet, es müsste //increaseAge(&A); heißen
   student D = increaseAge(C);  // Erhöht das alter von dem Objekt hinter C und gibt die adresse von C zurück und schreibt sie in D
   Serial.println(A.alter); // das alter in A hat sich mit geändert
   Serial.println(D.alter); // das alter von D (und C) hat sich auch geändert, da alle Pointer auf das selbe Objekt zeigen.
}

void loop() {
   esp_deep_sleep_start();
}
