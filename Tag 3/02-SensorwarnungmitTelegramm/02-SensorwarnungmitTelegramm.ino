/*
 * Nun bist du fit mit dem ESP32.
 * Für ein System gehören jedoch meistens auch andere Komponenten dazu, in diesem Beispiel ein Handy.
 * Du lernst JSON und eine API kennen von Telegramm: https://randomnerdtutorials.com/telegram-control-esp32-esp8266-nodemcu-outputs/
 * 
 * Aufgabe: 
 * 1) Sende beim start eine Nachricht, das du online bist.
 * 2) Wenn irgendein Nutzer /status schreibt sende die aktuellen Messwerte.
 * 3) wenn die Luftfeuchtigkeit über 50% geht sende eine Warnung und wenn er wieder drunter geht eine Entwarnung
 * 4) Setze mit /setThreshold einen neuen Schwellwert für die Luftfeuchtigkeit, speicherre sie in Preferences
 * 
 * Links:
 * API: https://core.telegram.org/bots/api#getupdates
 * Libary: https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot
 * Daten speichern: https://randomnerdtutorials.com/esp32-save-data-permanently-preferences/
 */

 /*
  * Original Credits
  Project created using Brian Lough's Universal Telegram Bot Library: https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot
  Example based on the Universal Arduino Telegram Bot Library: https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot/blob/master/examples/ESP8266/FlashLED/FlashLED.ino
*/

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>   // Universal Telegram Bot Library written by Brian Lough: https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot
#include <Preferences.h>

// Bitte WLAN Zugangsdaten eingeben.
const char* ssid = "REPLACE_WITH_YOUR_SSID";
const char* password = "REPLACE_WITH_YOUR_PASSWORD";
Preferences preferences;

// Telegramm API auf deinen Bot einstellen: 
#define BOTtoken "5555709309:AAEaACmqM6ds_O7Nj6DNdqUgywGP_MZ3Y6Q"  // your Bot Token (Get from Botfather)

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

// Varriablen, um die API anzufragen, bitte nicht ständig (ohne Pause), um die API zu schonen.
int botRequestDelay = 1000;
unsigned long lastTimeBotRan;

// Sensor
int luftfeuchtigkeit = 30;
int schwellwert = 50;
bool isOver = false;


// Funktion um auf eine Nachricht zu reagieren.
void handleNewMessages(int numNewMessages) {// numNewMessages -> Anzahl von Nachrichten

  for (int i=0; i<numNewMessages; i++) {
    // Hole dir die Chattids
    String chat_id = String(bot.messages[i].chat_id);// Objekt vom Bot, davon die nachrichten an der stelle i die chat_id
    
    // Hole den Text
    String text = bot.messages[i].text;
    // Hole den Namen
    String from_name = bot.messages[i].from_name;

    if (text == "/start") {// Wenn ein neuer Nuttzer 
      String welcome = "Welcome, " + from_name + ".\n";
      welcome += "Du kannst folgende Befehle benutzen:\n\n";
      welcome += "/setThreshold setze den neuen Schwellwert \n";
      welcome += "/status bekomme den aktuellen Status \n";
      bot.sendMessage(chat_id, welcome, "");
    }else if (text == "/status") {
      String answer = "Luftfeuchtigkeit:" + luftfeuchtigkeit;
      bot.sendMessage(chat_id, answer, "");
    }else if (text.startsWith("/setThreshold")) {
      int newSchwellwert = text.substring(14, text.length()).toInt();
      if (newSchwellwert != 0) {
        schwellwert = newSchwellwert;
        preferences.putInt("Schwellwert", newSchwellwert);
        String answer = "Schwellwert aktuakisiert auf: " + schwellwert;
        bot.sendMessage(chat_id, answer, "");
      } else {
        bot.sendMessage(chat_id, "Fehler", "");
      }
    } else {
      bot.sendMessage(chat_id, "Ich habe dich nicht verstanden.", "");
    }
    
  }
}

void setup() {
  // Stelle Daten wieder her
  preferences.begin("Telegramm", false);
  schwellwert = preferences.getInt("Schwellwert", schwellwert); 
  // Verbinde mit WLAN
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  client.setCACert(TELEGRAM_CERTIFICATE_ROOT); // Add root certificate for api.telegram.org
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  // Wie ist die interne IP Addresse
  Serial.println(WiFi.localIP());
}

void loop() {
  if (millis() > lastTimeBotRan + botRequestDelay)  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while(numNewMessages) {
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    lastTimeBotRan = millis();
  }
}
