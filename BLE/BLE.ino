#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#include <ArduinoJson.h>

String SERVICE_UUID("250b0d00-1b4f-4f16-9171-f63c733d15ab");
String CHARACTERISTIC_UUID("250b0d01-1b4f-4f16-9171-f63c733d15ab");

BLECharacteristic *pCharacteristic;

int a0Val;

void setA0() {
  StaticJsonDocument<64> resJson;
  JsonObject data = resJson.createNestedObject("data");
  data["A0"] = a0Val;

  String resTxt = "";
  serializeJson(resJson, resTxt);
  pCharacteristic->setValue(resTxt.c_str());
}

void setup() {
  Serial.begin(9600);
  while (!Serial) {}

  BLEDevice::init("LDR");
  BLEServer *pServer = BLEDevice::createServer();
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();

  BLEService *pService = pServer->createService(SERVICE_UUID.c_str());
  pCharacteristic = pService->createCharacteristic(CHARACTERISTIC_UUID.c_str(), BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE);

  pService->start();
  pAdvertising->addServiceUUID(SERVICE_UUID.c_str());
  pAdvertising->setScanResponse(true);
  BLEDevice::startAdvertising();
}

void loop() {
  a0Val = analogRead(A0);
  setA0();
  delay(1);
}
