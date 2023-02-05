#include <Arduino.h>
#include <Bounce2.h>
#define BUTTON 27
#define GREEN 33
#define RED 26
#define YELLOW 25
#define LDR 32
int stage = 0;
int lumine = 0;
Bounce debouncer = Bounce();

void setup() {
    Serial.begin(115200);
    ledcSetup(0 , 5000, 8);
    ledcSetup(1 , 5000, 8);
    ledcSetup(2 , 5000, 8);
    ledcAttachPin(GREEN, 0);
    ledcAttachPin(YELLOW, 1);
    ledcAttachPin(RED, 2);
    debouncer.attach(BUTTON, INPUT_PULLUP);
    debouncer.interval(25); 
}

void loop() {
    lumine = map(analogRead(LDR),1900,3500,0,255);
    debouncer.update();
    if (debouncer.fell()) { 
      stage++;
      stage = stage%8;
    }
    if (stage == 0) {
      ledcWrite(0, 0);
      ledcWrite(1, 0);
      ledcWrite(2, 0);
    }
    if (stage == 1) {
      ledcWrite(0, lumine);
      ledcWrite(1, 0);
      ledcWrite(2, 0);
    }
    if (stage == 2) {
      ledcWrite(0, 0);
      ledcWrite(1, lumine);
      ledcWrite(2, 0);
    }
    if (stage == 3) {
      ledcWrite(0, lumine);
      ledcWrite(1, lumine);
      ledcWrite(2, 0);
    }
    if (stage == 4) {
      ledcWrite(0, 0);
      ledcWrite(1, 0);
      ledcWrite(2, lumine);
    }
    if (stage == 5) {
      ledcWrite(0, lumine);
      ledcWrite(1, 0);
      ledcWrite(2, lumine);
    }
    if (stage == 6) {
      ledcWrite(0, 0);
      ledcWrite(1, lumine);
      ledcWrite(2, lumine);
    }
    if (stage == 7) {
      ledcWrite(0, lumine);
      ledcWrite(1, lumine);
      ledcWrite(2, lumine);
    }
    Serial.println(stage);
}

// #include <Arduino.h>
// #include <Bounce2.h>
// #define GREEN 33
// #define RED 26
// #define YELLOW 25
// #define BUTTON 27
// Bounce debouncer = Bounce();

// void setup() {
//     Serial.begin(115200);
//     Serial.println("BUTTON");
//     debouncer.attach(BUTTON, INPUT_PULLUP);
//     debouncer.interval(25); 
//     pinMode(RED, OUTPUT);
//     pinMode(GREEN, OUTPUT);
//     pinMode(YELLOW, OUTPUT);
//     digitalWrite(RED,0);
// }

// void loop() {
//     debouncer.update();
//     if ( debouncer.fell() ) { 
//       digitalWrite(RED,1);
//       digitalWrite(GREEN,1);
//       digitalWrite(YELLOW,1);
//       delay(1000);
//     }
//     digitalWrite(RED,0);
//     digitalWrite(GREEN,0);
//     digitalWrite(YELLOW,0);
// }