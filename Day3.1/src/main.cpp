#include <Arduino.h>
#include <bounce2.h>
#define BUTTON 27
#define GREEN 33
#define RED 26
#define YELLOW 25
#define LDR 32

Bounce debouncer = Bounce();

TaskHandle_t TaskA = NULL;
TaskHandle_t TaskB = NULL;

int count = 0;

void LED_bright(void *param){
  while(1){
  for (int i = 0; i < 255; i++) {
    ledcWrite(0, i);
    vTaskDelay(5/portTICK_PERIOD_MS);
  }
  for (int i = 255; i > 0; i--) {
    ledcWrite(0, i);
    vTaskDelay(5/portTICK_PERIOD_MS);
  }
  vTaskDelay(1000/portTICK_PERIOD_MS);
}
}

void count_button(void *param){
  while (1) {
    debouncer.update();
    if (debouncer.fell()) {
      count++;
      Serial.println(count);
    }
  }
}
void setup()
{
  Serial.begin(115200);
  ledcSetup(0, 5000, 8);
  ledcAttachPin(GREEN, 0);
  ledcAttachPin(YELLOW, 0);
  ledcAttachPin(RED, 0);
  pinMode(BUTTON, INPUT_PULLUP);
  debouncer.attach(BUTTON);
  debouncer.interval(25);

  xTaskCreatePinnedToCore(LED_bright, "LED_bright", 1000, NULL, 1, &TaskA, 0);
  xTaskCreatePinnedToCore(count_button, "count_button", 1000, NULL, 1, &TaskB, 1);
}
void loop()
{
}

