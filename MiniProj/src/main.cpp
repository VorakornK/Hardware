#include <Arduino.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Bounce2.h>

#define BUTTON 27
#define GREEN 33
#define RED 26
#define YELLOW 25
#define LDR 32

const char *ssid = "Qwerty";
const char *password = "12345678";

void Connect_Wifi();

void setup() {
  Serial.begin(115200);
  Connect_Wifi();
}

void loop() {
  
}

void Connect_Wifi()
{
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.print("OK! IP=");
  Serial.println(WiFi.localIP());
  Serial.println("----------------------------------");
}