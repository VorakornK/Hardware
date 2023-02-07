#include <Arduino.h>
#include <Bounce2.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

#define BUTTON 27
#define GREEN 33
#define RED 26
#define YELLOW 25
#define Build_IN 5

Bounce debouncer = Bounce();

TaskHandle_t TaskA = NULL;
TaskHandle_t TaskB = NULL;

int count = 0;

const String url = "https://exceed-hardware-stamp465.koyeb.app/question";

const char *ssid = "Qwerty";
const char *password = "12345678";

void Connect_Wifi();

void setup() {
  Serial.begin(115200);
  ledcSetup(0, 5000, 8);
  ledcAttachPin(GREEN, 0);
  ledcAttachPin(YELLOW, 0);
  ledcAttachPin(RED, 0);
  ledcAttachPin(Build_IN, 1);
  pinMode(BUTTON, INPUT_PULLUP);
  debouncer.attach(BUTTON);
  debouncer.interval(25);
  Connect_Wifi();
}

void loop() {
  for (int i = 0; i < 255; i++) {
    ledcWrite(1, i);
    delay(5);
  }
  for (int i = 255; i > 0; i--) {
    ledcWrite(1, i);
    delay(5);
  }
  delay(1000);
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