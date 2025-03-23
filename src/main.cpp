#include <Arduino.h>
#include <ArduinoOTA.h>
#include <Arduino_MQTT_Client.h>
#include <DHT20.h>
#include <HardwareSerial.h>
#include <ThingsBoard.h>
#include <WiFi.h>

constexpr char WIFI_SSID[] = "Harw";
constexpr char WIFI_PASSWORD[] = "baohan1107";
constexpr char TOKEN[] = "5Ap61lYda1GENmE54hla";
constexpr char THINGSBOARD_SERVER[] = "app.coreiot.io";

constexpr uint16_t THINGSBOARD_PORT = 1883U;
constexpr uint32_t MAX_MESSAGE_SIZE = 1024U;
constexpr uint32_t SERIAL_DEBUG_BAUD = 9600UL;

WiFiClient wifiClient;
Arduino_MQTT_Client mqttClient(wifiClient);
ThingsBoard tb(mqttClient, MAX_MESSAGE_SIZE);
DHT20 dht20;

void TaskHelloWorld(void *pvParameters) {
  while (1) {
    Serial.println("Hello World!");
    vTaskDelay(2000);
  }
}

void InitWiFi() {
  Serial.print("Connecting to Wifi ...");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(); Serial.println("Connected to Wifi!");
}

void setup() {
  Serial.begin(SERIAL_DEBUG_BAUD);
  Serial.println();
  InitWiFi();
  Wire.begin(GPIO_NUM_21, GPIO_NUM_22);
  dht20.begin();
  tb.connect(THINGSBOARD_SERVER, TOKEN, THINGSBOARD_PORT);
  xTaskCreate(TaskHelloWorld, "HelloWorld", 2048, NULL, 2, NULL);
}

void loop() {}