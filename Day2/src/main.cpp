#include <Arduino.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>

const char *ssid = "vivo 1818";
const char *password = "12345678";

const String baseUrl = "https://jsonplaceholder.typicode.com/";

void GET_post(){
  DynamicJsonDocument doc(2048);
  const String url = baseUrl + "posts/1";
  HTTPClient http;
  http.begin(url);
  int httpResponseCode = http.GET();
  if (httpResponseCode >= 200 && httpResponseCode < 300) {
    Serial.print("HTTP ");
    Serial.println(httpResponseCode);
    String payload = http.getString();
    deserializeJson(doc,payload);
    Serial.println();
    Serial.println((const char*)doc["title"]);
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
}

void GET_comments(String postid ){
  DynamicJsonDocument doc(2048);
  const String url = baseUrl + "comments?postId=" + postid;
  HTTPClient http;
  http.begin(url);
  int httpResponseCode = http.GET();

  if (httpResponseCode >= 200 && httpResponseCode < 300) {
    Serial.print("HTTP ");
    Serial.println(httpResponseCode);
    String payload = http.getString();
    deserializeJson(doc,payload);

    Serial.println();
    Serial.println((const char*)doc[1]["email"]);
    Serial.println((const char*)doc[1]["body"]);
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
}

void POST_post(){
  String json;
  DynamicJsonDocument doc(2048);
  doc["userId"] = 1;
  doc["title"] = "Exceed AHHHHHH";
  doc["body"] = "THIS IS BODY";
  serializeJson(doc,json);

  const String url = baseUrl + "posts";
  HTTPClient http;
  http.begin(url);
  http.addHeader("Content-Type","application/json");

  int httpResponseCode = http.POST(json);
  if (httpResponseCode >= 200 && httpResponseCode < 300) {
    Serial.print("HTTP ");
    Serial.println(httpResponseCode);
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
}

void PUT_post(){
  String json;
  DynamicJsonDocument doc(2048);
  doc["userId"] = 1;
  doc["title"] = "Exceed AHHHHHH 22";
  doc["body"] = "THIS IS BODY XXX";
  doc["id"] = 1;
  serializeJson(doc,json);

  const String url = baseUrl + "posts/1";
  HTTPClient http;
  http.begin(url);
  http.addHeader("Content-Type","application/json");

  int httpResponseCode = http.PUT(json);
  if (httpResponseCode >= 200 && httpResponseCode < 300) {
    Serial.print("HTTP ");
    Serial.println(httpResponseCode);
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
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
}

void loop() {
  // put your main code here, to run repeatedly:
}