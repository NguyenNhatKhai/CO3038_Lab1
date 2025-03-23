#include <Arduino.h>
#include <ArduinoOTA.h>
#include <Arduino_MQTT_Client.h>
#include <DHT20.h>
#include <HardwareSerial.h>
#include <ThingsBoard.h>
#include <WiFi.h>

constexpr uint32_t SERIAL_DEBUG_BAUD = 9600UL;

void TaskHelloWorld(void *pvParameters) {
  while (1) {
    Serial.println("Hello World!");
    vTaskDelay(2000);
  }
}

void setup() {
  Serial.begin(SERIAL_DEBUG_BAUD);
  Serial.println();
  xTaskCreate(TaskHelloWorld, "HelloWorld", 2048, NULL, 2, NULL);
}

void loop() {}