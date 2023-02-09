#include <Arduino.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const String UpdateUrl = "https://api-hardware.onrender.com";
const String CheckUrl = "https://api-hardware.onrender.com/all_traffic";

void POST_Update(String id, int Brightness, bool Status, bool Auto) {
    String json;
    HTTPClient http;
    http.begin(UpdateUrl);
    http.addHeader("Content-Type", "application/json");

    DynamicJsonDocument doc(256);
    doc["code"] = "317cwk";
    serializeJson(doc, json);

    int httpCode = http.POST("{\"id\": \"1\", \"traffic\": \"1\"}");
    if (httpCode > 0) {
        String payload = http.getString();
        Serial.println(payload);
    } else {
        Serial.println("Error on HTTP request");
    }
    http.end();
}