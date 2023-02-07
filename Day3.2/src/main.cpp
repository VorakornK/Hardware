#include <Arduino.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

#define BLED 5

TaskHandle_t TaskA = NULL;
TaskHandle_t TaskB = NULL;

const char *ssid = "Qwerty";
const char *password = "12345678";

int btw = 1000;

const String url = "https://exceed-hardware-stamp465.koyeb.app/leddelay";

void Connect_Wifi();

void GET_Btw(void *param){
  while (1) {
    DynamicJsonDocument doc(512);
    HTTPClient http;
    http.begin(url);
    int httpResponseCode = http.GET();
    if (httpResponseCode >= 200 && httpResponseCode < 300) {
        String payload = http.getString();
        deserializeJson(doc,payload);
        btw = doc["value"].as<int>();
        Serial.println(btw);
    }
    else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
    }
    vTaskDelay(5000);
  }
}

void BLight_Set(void *param) {
  while (1) {
    digitalWrite(BLED, 1);
    vTaskDelay(btw);
    digitalWrite(BLED, 0);
    vTaskDelay(btw);
  }
}

void setup() {
    Serial.begin(115200);
    pinMode(BLED, OUTPUT);
    digitalWrite(BLED, 0);
    Connect_Wifi();

    xTaskCreatePinnedToCore(GET_Btw, "GET_Btw", 10000, NULL, 1, &TaskA, 0);
    xTaskCreatePinnedToCore(BLight_Set, "Builtin_LED", 1000, NULL, 1, &TaskB, 1);
}

void loop() {

}

void Connect_Wifi() {
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }
  Serial.print("OK! IP=");
  Serial.println(WiFi.localIP());
}
