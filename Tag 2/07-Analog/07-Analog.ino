/*
 * Dies ist das Basisbeispiel um analoge Werte einzulesen und in der Console auszugeben.
 * Deine Aufgabe ist es mit dem Datenblatt den Wert auf eine Physikalische größe abzubilden. // WELCHE PHYSIKALISCHE GRÖßE? Was ist der Zielbereich?
 * Benutze gerne die map() funktion.
 * 
 * Wichtigster Link (Datenblatt): https://cdn.shopify.com/s/files/1/1509/1638/files/KY-013_Thermistor_Sensor_Modul_Datenblatt.pdf?9800502722103794008
 * 
  AnalogReadSerial

  Reads an analog input on pin 0, prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/AnalogReadSerial
  https://www.arduino.cc/reference/de/language/functions/math/map/
*/

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // print out the value you read:
  Serial.println(sensorValue);
  delay(1);        // delay in between reads for stability
}
