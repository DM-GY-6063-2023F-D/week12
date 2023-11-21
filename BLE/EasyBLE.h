#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

class EasyBLE {
public:
  EasyBLE() {}

  void setup(String& deviceName, String& serviceUUID) {
    EasyBLE::setupStatic(deviceName, serviceUUID, EasyBLE::CHARACTERISTIC_UUID);
  }

  void setValue(String& value) {
    EasyBLE::pCharacteristic->setValue(value.c_str());
  }

private:
  static BLECharacteristic* pCharacteristic;
  static String CHARACTERISTIC_UUID;

  static void setupStatic(String& deviceName, String& serviceUUID, String& charactUUID) {
    BLEDevice::init(deviceName.c_str());
    BLEServer* pServer = BLEDevice::createServer();
    BLEAdvertising* pAdvertising = BLEDevice::getAdvertising();

    BLEService* pService = pServer->createService(serviceUUID.c_str());
    EasyBLE::pCharacteristic = pService->createCharacteristic(charactUUID.c_str(), BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE);

    pService->start();
    pAdvertising->addServiceUUID(serviceUUID.c_str());
    pAdvertising->setScanResponse(true);
    BLEDevice::startAdvertising();
  }
};

BLECharacteristic* EasyBLE::pCharacteristic;
String EasyBLE::CHARACTERISTIC_UUID("250b0d01-1b4f-4f16-9171-f63c733d15ab");
