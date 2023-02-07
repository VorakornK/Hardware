#include <Arduino.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <string>


// 0 = Green
// 1 = Yellow
// 2 = Red

const char *ssid = "ZodiaX";
const char *password = "poom1234";

const String baseUrl = "https://exceed-hardware-stamp465.koyeb.app";
const String GroupNum = "1";
const String AGurl = "https://exceed-hardware-stamp465.koyeb.app/all_traffic";

const String GroupCode = "317cwk";


const String point = "1";
const int nearby_1 = 2;
const int nearby_2 = 15;


void GET_traffic() {
  Serial.println("Start!!!");
  DynamicJsonDocument doc(65536);
  HTTPClient http;
  http.begin(AGurl);

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

void POST_traffic(String led)
{
  const String url = baseUrl + "/my_traffic?point=" + point;
  String json;
  HTTPClient http;
  http.begin(url);
  http.addHeader("Content-Type", "application/json");

  DynamicJsonDocument doc(2048);
  doc["code"] = "317cwk";
  doc["traffic"] = led;
  serializeJson(doc, json);

  Serial.println("POST " + led);
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

void setup() {
  Serial.begin(115200);
  Connect_Wifi();
  POST_traffic("Yellow");
  GET_traffic();
}

void loop() {
  // put your main code here, to run repeatedly:
}