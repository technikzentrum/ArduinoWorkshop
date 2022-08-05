/*
   Dieses Beispiel ist von dem Hersteller der Platine und wurde von Marco Gabrecht angepasst.

   Aufgabe: Starte das Display und lasse das Baader Logo für 3 Sekunde anzeigen
   Benutze nicht die UI Libary
   Initialisiere einen Sensor deiner wahl und lese ihn aus.
   Zeige als Text den Sensorwert mit beschreibung 10 Sekunden live an. (Temperatur: 50°C, Luftfeuchtigkeit: 20%, ...)
   Zeige den Wert auf einem Balkendiagramm 10 Sekunden an.
   Zeige den Wert auf einem Tacho 10 Sekunden an.

   Bilder können mit diesem Tool convertiert werden: https://www.online-utility.org/image/convert/to/XBM
   Weiterer hilfreicher Link: https://github.com/ThingPulse/esp8266-oled-ssd1306
   Verwendung von Emums: https://www.programiz.com/c-programming/c-enumeration
   Display enums und Funktionen: https://github.com/ThingPulse/esp8266-oled-ssd1306/blob/master/src/OLEDDisplay.h
   Funktionsbeispiele: https://www.sabulo.com/sb/esp32-development-board/how-to-use-the-heltec-oled-display-on-the-esp32/

*/

#include "Arduino.h"
#include "heltec.h"
#include "oled/OLEDDisplayUi.h"
#include "images.h"

typedef void (*Demo)(void);

extern Heltec_ESP32 Heltec;
int displayTime = 10000;//ms
int frameTime = 250;//ms
int sensorValue = 0;//°C
void msOverlay(OLEDDisplay *display) {
  display->setTextAlignment(TEXT_ALIGN_CENTER);
  display->setFont(ArialMT_Plain_10);
  display->drawString(128, 0, String(millis()));
}

void drawLogo(OLEDDisplay *display, int16_t x, int16_t y) {
  Heltec.display->clear();
  display->drawXbm(x, y, baader_width, baader_height, baader_bits);
  Heltec.display->display();
}

void drawFrame2(OLEDDisplay *display, int16_t x, int16_t y) {
  display->setTextAlignment(TEXT_ALIGN_LEFT);
  display->setFont(ArialMT_Plain_16);
  display->drawString(x, y, "HelTec");
  display->setFont(ArialMT_Plain_10);
  display->drawString(x, y + 25, "HelTec AutoMation");
  display->drawString(x, y + 35, "www.heltec.cn");
}

void writeValueInText() {
  int x, y = 10;
  Heltec.display->clear();
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->drawString(x, y, String("Temperatur: " + String(sensorValue) + "°C"));
  Heltec.display->drawString(x, y + 10, "Luftfeuchtigkeit: 20%");
  Heltec.display->drawString(x, y + 20, "Luftfeuchtigkeit: 20%");
  Heltec.display->display();
}

void writeValueInBalken() {
  int x, y = 0;
  Heltec.display->clear();
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->drawString(x, y, String("Temperatur in °C"));
  Heltec.display->drawString(x, y + 10, String("-10                               110"));
  Heltec.display->drawRect(x + 4 * 5, y + 11, 28 * 3, 9);
  Heltec.display->fillRect(x + 4 * 5, y + 11, map(sensorValue, -10, 110, 0, 28 * 3), 9);
  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->drawString(x, y + 20, String("Luftfeuchtigkeit in %"));
  Heltec.display->drawString(x, y + 30, String("  0                                100"));
  Heltec.display->drawRect(x + 4 * 5, y + 31, 28 * 3, 9);
  Heltec.display->fillRect(x + 4 * 5, y + 31, map(sensorValue, 0, 100, 0, 28 * 3), 9);
  Heltec.display->display();
}

void writeValueInTacho() {
  float x_origo = 128/2;
  float y_origo = 64;
  float arc_lenth = 60;  //second hand length
  float xsec = map(sensorValue, 0, 100, -arc_lenth, arc_lenth);
  float winkelA = map(sensorValue, 0, 100, 0, 180);
  float ysec = 10;
  if (winkelA<=90) {
    ysec = map(winkelA, 0, 90, 0, arc_lenth);
  } else {
    ysec = map(winkelA, 90, 180, arc_lenth, 0);
  }
  Heltec.display->clear();
  Heltec.display->drawCircle(x_origo, y_origo, 60);
  Heltec.display->drawLine(x_origo, y_origo, x_origo + xsec, y_origo - ysec); //Second hand

  /*
    Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
    Heltec.display->setFont(ArialMT_Plain_10);
    Heltec.display->drawString(x, y, String("Temperatur in °C"));
    Heltec.display->drawString(x, y+10, String("-10                               110"));
    Heltec.display->drawRect(x + 4*5, y+11, 28*3, 9);
    Heltec.display->fillRect(x + 4*5, y+11, map(sensorValue, -10,110, 0, 28*3), 9);
    Heltec.display->setFont(ArialMT_Plain_10);
    Heltec.display->drawString(x, y+20, String("Luftfeuchtigkeit in %"));
    Heltec.display->drawString(x, y+30, String("  0                                100"));
    Heltec.display->drawRect(x + 4*5, y+31, 28*3, 9);
    Heltec.display->fillRect(x + 4*5, y+31, map(sensorValue, 0,100, 0, 28*3), 9);*/
  Heltec.display->display();
}

void setup() {
  Heltec.begin(true /*DisplayEnable Enable*/, false /*LoRa Disable*/, true /*Serial Enable*/);
  //Heltec.display->flipScreenVertically();
  drawLogo(Heltec.display, 0, 20);
  Heltec.display->display();
  delay(3000);
}

void loop() {//Zeige als Text den Sensorwert mit beschreibung 10 Sekunden live an. (Temperatur: 50°C, Luftfeuchtigkeit: 20%, ...)
  for (int frames = 0; frames < displayTime / frameTime; frames++) {
    writeValueInText();
    delay(frameTime);
  }
  for (int frames = 0; frames < displayTime / frameTime; frames++) {
    writeValueInBalken();
    delay(frameTime);
  }
  for (int frames = 0; frames < displayTime / frameTime; frames++) {
    writeValueInTacho();
    delay(frameTime);
  }
  sensorValue++;
}
