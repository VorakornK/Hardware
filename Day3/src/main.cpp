#include <Arduino.h>

#define BLUE 5
#define RED 12
TaskHandle_t TaskA = NULL;
TaskHandle_t TaskB = NULL;

void Blink_LED(void *param){
    while(1){
        digitalWrite(RED, 1);
        vTaskDelay(500/portTICK_PERIOD_MS);
        digitalWrite(RED, 0);
        vTaskDelay(500/portTICK_PERIOD_MS);
    }
}

void Lit_LED(void *param){
    while(1){
        digitalWrite(BLUE, 0);
        vTaskDelay(200/portTICK_PERIOD_MS);
        digitalWrite(BLUE, 1);
        vTaskDelay(200/portTICK_PERIOD_MS);
    }
}

void setup(){
    pinMode(BLUE, OUTPUT);
    pinMode(RED, OUTPUT);

    xTaskCreatePinnedToCore(Lit_LED, "Builtin_LED", 1000, NULL, 1, &TaskA, 0);
    xTaskCreatePinnedToCore(Blink_LED, "Blink_LED", 1000, NULL, 1, &TaskB, 1);
}

void loop(){
}

