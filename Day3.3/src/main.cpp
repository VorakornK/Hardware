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

const String gurl = "https://exceed-hardware-stamp465.koyeb.app/question";
const String surl = "https://exceed-hardware-stamp465.koyeb.app/answer";

const char *ssid = "Qwerty";
const char *password = "12345678";

void Connect_Wifi();

void task3(void *param);

void LED_bright(void *param){
  while(1){
    for (int i = 0; i < 255; i++) {
      ledcWrite(1, i);
      vTaskDelay(5/portTICK_PERIOD_MS);
    }
    for (int i = 255; i > 0; i--) {
      ledcWrite(1, i);
      vTaskDelay(5/portTICK_PERIOD_MS);
    }
    vTaskDelay(1000/portTICK_PERIOD_MS);
  }
}

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

  xTaskCreatePinnedToCore(LED_bright, "LED_bright", 1000, NULL, 2, &TaskB, 1);
  xTaskCreatePinnedToCore(task3, "task3", 100000, NULL, 1, &TaskA, 0);
}

void loop()
{
  debouncer.update();
    if(debouncer.fell()){
      ledcWrite(0, 255);
      unsigned long start = millis();
      while (millis() - start < 5000)
      {
        debouncer.update();
        if(debouncer.fell()){
          ledcWrite(0, 0);
          break;
        }
      }
      ledcWrite(0, 0);
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

void task3(void *param) {
  int a, b, result;
  String op, Id;
  while (1) {
    DynamicJsonDocument doc(512);
    HTTPClient http;
    http.begin(gurl);
    int httpResponseCode = http.GET();
    if (httpResponseCode >= 200 && httpResponseCode < 300) {
        String payload = http.getString();
        deserializeJson(doc, payload);
        a = doc["a"].as<int>();
        b = doc["b"].as<int>();
        op = doc["op"].as<String>();
        Id = doc["questionId"].as<String>();
    }
    else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
        vTaskDelay(5000);
        continue;
    }
    Serial.print("a = ");
    Serial.println(a);
    Serial.print("b = ");
    Serial.println(b);
    Serial.print("op = ");
    Serial.println(op);
    Serial.print("questionId = ");
    Serial.println(Id);

    if (op == "+") {
      result = a + b;
    }
    else if (op == "-") {
      result = a - b;
    }
    else if (op == "*") {
      result = a * b;
    }

    Serial.print("result = ");
    Serial.println(result);
    Serial.print("questionId = ");
    Serial.println(Id);

    // time to send back
    String json;
    DynamicJsonDocument doc2(512);
    doc2["questionId"] = Id;
    doc2["result"] = result;
    serializeJson(doc2, json);

    http.begin(surl);
    http.addHeader("Content-Type","application/json");

    httpResponseCode = http.POST(json);
    if (httpResponseCode >= 200 && httpResponseCode < 300) {
      String payload = http.getString();
      deserializeJson(doc, payload);
      Serial.print("{message: ");
      Serial.print(doc["message"].as<String>());
      Serial.println("}");
    }
    else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
    }
    vTaskDelay(5000);
  }
}
