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
    int tmp = stage;
    for (int i = 0; i < 3; i++) {
      ledcWrite(i, tmp%2 * lumine);
      tmp = tmp / 2;
    }
    Serial.println(stage);
}
