/*
 * Kein Start, alles muss man selber machen
 * 
 * Schreibe ein Programm, welches:
 * - Alles, was es macht in der Console schriebt
 * - Zum Starten einmal von 0 bis 100 zählt(mittels while)
 * - Und danach einmal von 100 bis 0 zählt(mittels for)
 * - Den Pin einliest und beim drücken anfängt zu zählen, wie lange der Knopf gedrückt ist.
 * - Beim loslassen unter 100 ms Abburch schriebt
 * - Beim los lassen unter 1000ms Die LED an Schaltet
 * - Beim gedrückt halten über 1000ms die LED ausschaltet
 * - Beim los lassen über 5000ms den ESP32 ausschaltet
 * - Beim schnellen hintereinander Drücken (drucklänge unter 300ms pause unter 500ms), resettet er alle Varriablen.
 * - Bei eingabe von Zahlen unter 255 setzt es die LED Helligkeit
 * - Bei eingabe von Zahlen über 255 Sagt es ob diese Zahl größer oder kleiner als die letzte eingegebene Zahl über 255 war. 
 * - Bei eingabe von nicht Zahlen giebt es aus wie lang diese sind und wie oft welcher Buchstabe vor kommt.
 * - Bei eingabe von pause ZAHL, wartet es die angegebe ZAHL in millisekunden.
 * - Bei eingabe von Caesar ZAHL STRING, jedes Zeichen des Strings um ZAHL stellen verschiebt
 * - Bei eingabe von CAESAR ZAHL STRING, das selbe wie Caesar macht, aber für jeden Buchstaben laut hochzählt. 
 *
 * Die Beispiele können dir helfen, eventuell ist Switch Case interessant und millis()
 * https://www.arduino.cc/reference/de/language/variables/data-types/string/functions/charat/
 * https://www.arduino.cc/reference/de/language/functions/time/millis/
 * https://www.arduino.cc/reference/de/language/structure/control-structure/switchcase/
 * https://www.arduino.cc/reference/de/language/functions/math/sq/
 * https://www.arduino.cc/reference/de/language/variables/data-types/array/
 * https://www.arduino.cc/reference/de/language/structure/control-structure/for/
 * https://www.arduino.cc/reference/de/language/structure/control-structure/while/
 * 
 * 
*/