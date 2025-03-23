#include <Arduino.h>
#include <ArduinoOTA.h>
#include <Arduino_MQTT_Client.h>
#include <DHT20.h>
#include <HardwareSerial.h>
#include <ThingsBoard.h>
#include <WiFi.h>

constexpr uint32_t SERIAL_DEBUG_BAUD = 9600UL;

DHT20 dht20;

void TaskDHT20(void *pvParameters) {
  while(1) {
    dht20.read();
    vTaskDelay(1000);
  }
}

void TaskTemperature(void *pvParameters) {
  while(1) {
    double temperature = dht20.getTemperature();
    Serial.print("Temperature: "); Serial.print(temperature); Serial.println(" *C");
    vTaskDelay(3000);
  }
}

void TaskHumidity(void *pvParameters) {
  while(1) {
    double humidity = dht20.getHumidity();
    Serial.print("Humidity: "); Serial.print(humidity); Serial.println(" %");
    vTaskDelay(2000);
  }
}

void setup() {
  Serial.begin(SERIAL_DEBUG_BAUD);
  Serial.println();
  Wire.begin(GPIO_NUM_21, GPIO_NUM_22);
  dht20.begin();
  xTaskCreate(TaskDHT20, "DHT20", 2048, NULL, 2, NULL);
  xTaskCreate(TaskTemperature, "Temperature", 2048, NULL, 2, NULL);
  xTaskCreate(TaskHumidity, "Humidity", 2048, NULL, 2, NULL);
}

void loop() {}
