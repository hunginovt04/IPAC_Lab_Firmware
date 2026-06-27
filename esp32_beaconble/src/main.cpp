#include<Arduino.h>
#include <BLEDevice.h>
#include <BLEAdvertising.h>
#include "esp_bt.h"

BLEAdvertising *pAdvertising;

void setup() {
  Serial.begin(115200);

  // Set cong suat phat max +9dbm
  esp_ble_tx_power_set(ESP_BLE_PWR_TYPE_ADV, ESP_PWR_LVL_P9);

  // Khoi tao BLE
  BLEDevice::init("ESP32_RSSI_BEACON_1");

  // Tao advertising
  pAdvertising = BLEDevice::getAdvertising();

  BLEAdvertisementData advData;
  advData.setName("BEACON_1");   // Ten de nhan dien

  // Co the them du lieu tuy y, hoac de trong
  advData.setManufacturerData("ID_01");

  pAdvertising->setAdvertisementData(advData);

  // Tang toc do phat (quan trong)
  pAdvertising->setMinInterval(0x20);
  pAdvertising->setMaxInterval(0x20);

  pAdvertising->start();

  Serial.println("Dang phat BLE...");
}

void loop() {
}