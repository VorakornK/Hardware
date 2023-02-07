#include <Arduino.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Bounce2.h>

//0 1 2
//G Y R

const String baseUrl = "https://api-hardware.onrender.com";
//const String baseUrl = "https://exceed-hardware-stamp465.koyeb.app";
//https://api-hardware.onrender.com
const String AGurl = "https://api-hardware.onrender.com/all_traffic";

const String point = "1";
const int nearby_1 = 2;
const int nearby_2 = 15;
const String Color[3] = {"Green", "Yellow", "Red"};

void GET_traffic() {
  Serial.println("Start!!!");
  DynamicJsonDocument doc(65536);
  HTTPClient http;
  http.begin(AGurl);
  http.setTimeout(10000);
  
  Serial.println("Nearby traffic");
  int httpResponseCode = http.GET();
  if (httpResponseCode == 200)
  {
    String payload = http.getString();
    deserializeJson(doc, payload);
    JsonArray all_traffic = doc["all_traffic"].as<JsonArray>();

    Serial.println("Point: " + doc["all_traffic"][0]["point"].as<String>());
    Serial.println("Traffic: " + doc["all_traffic"][0]["traffic"].as<String>());

    Serial.println("Point: " + doc["all_traffic"][nearby_1 - 1]["point"].as<String>());
    Serial.println("Traffic: " + doc["all_traffic"][1][nearby_1 - 1].as<String>());

    Serial.println("Point: " + doc["all_traffic"][nearby_2 - 1]["point"].as<String>());
    Serial.println("Traffic: " + doc["all_traffic"][nearby_2 - 1]["traffic"].as<String>());
  }
  else
  {
    Serial.print("Error ");
    Serial.println(httpResponseCode);
  }

  Serial.println("----------------------------------");
}

void POST_traffic(int led)
{
  const String url = baseUrl + "/my_traffic?point=" + point;
  String json;
  HTTPClient http;
  http.begin(url);
  http.setTimeout(10000);
  http.addHeader("Content-Type", "application/json");

  DynamicJsonDocument doc(2048);
  doc["code"] = "317cwk";
  doc["traffic"] = Color[led];
  serializeJson(doc, json);

  Serial.println("POST " + Color[led]);
  int httpResponseCode = http.POST(json);
  if (httpResponseCode == 200)
  {
    Serial.print("Done");
    Serial.println();
  }
  else
  {
    Serial.print("Error ");
    Serial.println(httpResponseCode);
  }

  Serial.println("----------------------------------");
}
