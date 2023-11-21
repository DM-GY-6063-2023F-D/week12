#include <ArduinoJson.h>

#include "EasyBLE.h"

String DEVICE_NAME("LDR");
String SERVICE_UUID("250b0d00-1b4f-4f16-9171-f63c733d15ab");

EasyBLE mBLE;

void updateData() {
  StaticJsonDocument<64> resJson;
  JsonObject data = resJson.createNestedObject("data");
  data["A0"] = analogRead(A0);

  String resTxt = "";
  serializeJson(resJson, resTxt);
  mBLE.setValue(resTxt);
}

void setup() {
  Serial.begin(9600);
  while (!Serial) {}

  mBLE.setup(DEVICE_NAME, SERVICE_UUID);
}

void loop() {
  updateData();
  delay(1);
}
