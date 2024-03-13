#include "header_global.h"

TaskHandle_t wifi_ota_task_handle;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  xTaskCreate(
    TaskWifi,
    "OTA Sub routine",
    2048,
    NULL,
    1,
    &wifi_ota_task_handle
  );
}

void loop() {
  // put your main code here, to run repeatedly:
  log_i("Stack size : %d", uxTaskGetStackHighWaterMark(NULL));
  delay(1000);
}