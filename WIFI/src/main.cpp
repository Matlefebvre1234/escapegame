#include <Arduino.h>
#include "WiFi.h"
#include <FastLED.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <WebSocketsClient.h>
#define WIFI_NETWORK "ICI C CHEZ NOUS !!!"
#define WIFI_PASS "8194373549"
#define WIFI_TIMEOUT 20000
#define LED_PIN 26
#define NUM_LEDS 300

CRGB leds[NUM_LEDS];
uint8_t hue = 0;
HTTPClient client;
WebSocketsClient socket;
bool etatled = true;
void webSocketEvent(WStype_t type, uint8_t *payload, size_t stringLenght)
{

  DynamicJsonDocument doc(stringLenght);
  DeserializationError error = deserializeJson(doc, payload);

  if (error)
  {
    Serial.print("deserialization Failed !");
  }
  else
  {

    String etat = doc["etat"];
    if (etat == "true" || etat == "True")
    {
      etatled = true;
    }
    else
    {
      etatled = false;
    }
    Serial.print(etat);
  }
}

void animation3()
{
  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = CHSV(hue + (i * 5), 255, 255);
  }

  EVERY_N_MILLISECONDS(5)
  {
    hue++;
  }
  FastLED.show();
}

void animationEscapeGame()
{
  uint8_t sinbeatRed = beatsin8(7, 0, 27 - 1, 0, 0);
  uint8_t sinbeatBlue = beatsin8(10, 0, 53 - 1, 0, 50);
  uint8_t sinbeatYellow = beatsin8(3, 0, 24 - 1, 0, 100);
  uint16_t sinbeatWhite = beatsin16(10, 0, NUM_LEDS - 1, 0, 150);
  leds[sinbeatRed] = CRGB::Red;
  leds[sinbeatBlue] = CRGB::Blue;
  leds[sinbeatYellow] = CRGB::Yellow;
  leds[sinbeatWhite] = CHSV(hue + (1 * 5), 255, 255);

  fadeToBlackBy(leds, NUM_LEDS, 50);
  EVERY_N_MILLISECONDS(1)
  {
    hue++;
  }
  FastLED.show();
}

void socketConnection()
{
  socket.begin("10.0.0.21", 8080, "/app/socketLed");
  socket.onEvent(webSocketEvent);
  socket.setReconnectInterval(5000);
}
void connectToWifi()
{

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_NETWORK, WIFI_PASS);

  unsigned long attemptime = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - attemptime < WIFI_TIMEOUT)
  {
    Serial.print(" . ");
    delay(100);
  }

  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.print("Connection Failed!!");
  }
  else
  {
    Serial.print("Connection reussi !");
    Serial.println(WiFi.localIP());
  }
}

void setup()
{

  pinMode(LED_PIN, OUTPUT);
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);

  Serial.begin(9600);
  connectToWifi();

  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.print("Connection Failed!!");
  }
  else
  {
    socketConnection();
  }
  // put your setup code here, to run once:
}

void loop()
{

  socket.loop();

  if (etatled)
  {
    animationEscapeGame();
  }
  else
  {
    FastLED.clear(true);
  }

  /*client.begin("http://10.0.0.21:8080/app/escapeGame/getEtatLed");
  int err = client.GET();

  if (err > 0)
  {
    Serial.print("marche");
    String retour = client.getString();
    bool etat = retour;
    Serial.print(etat);
  }
  else
  {
    Serial.print("Erreur http");
  }*/
}