// If you want to run in WOKWi
// change pin and wifi
#include <Arduino.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Bounce2.h>
#include "traffic.h"

#define BUTTON 27
#define GREEN 33
#define RED 26
#define YELLOW 25
#define LDR 32

const char *ssid = "Qwerty";
const char *password = "12345678";

int stage = 0;
int lumine = 0;
Bounce debouncer = Bounce();

void Connect_Wifi();

void setup() {
    Serial.begin(115200);
    pinMode(BUTTON, INPUT_PULLUP);
    debouncer.attach(BUTTON);
    debouncer.interval(5);
    pinMode(GREEN, OUTPUT);
    pinMode(YELLOW, OUTPUT);
    pinMode(RED, OUTPUT);
    Connect_Wifi();
    digitalWrite(GREEN, HIGH);
    digitalWrite(YELLOW, LOW);
    digitalWrite(RED, LOW);
    POST_traffic(stage);   
    GET_traffic();
}


void loop(){
    debouncer.update();
    if (debouncer.fell() && stage == 0) { //if button pressed and stage is green
      stage = 1;
      digitalWrite(GREEN, LOW);
      digitalWrite(YELLOW, HIGH);
      digitalWrite(RED, LOW);
      POST_traffic(1);   
      delay(8000);
      digitalWrite(GREEN, LOW);
      digitalWrite(YELLOW, LOW);
      digitalWrite(RED, HIGH);
      POST_traffic(2);
      GET_traffic();
      delay(5000); //wait 5 seconds
      lumine = map(analogRead(LDR),1500,3500,0,255);
      while (lumine >= 100) {
        lumine = map(analogRead(LDR),1500,3500,0,255);
      }
      digitalWrite(GREEN, HIGH);
      digitalWrite(YELLOW, LOW);
      digitalWrite(RED, LOW);
      POST_traffic(0);   
      GET_traffic();
      stage = 0;
    }
    
    //Serial.println(stage); //print stage
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