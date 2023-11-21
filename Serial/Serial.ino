#include <ArduinoJson.h>

int a0Val;

void sendData() {
  StaticJsonDocument<64> resJson;
  JsonObject data = resJson.createNestedObject("data");
  data["A0"] = a0Val;

  String resTxt = "";
  serializeJson(resJson, resTxt);
  Serial.println(resTxt);
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  a0Val = analogRead(A0);

  if (Serial.available() > 0) {
    int byteIn = Serial.read();
    if (byteIn == 0xAB) {
      Serial.flush();
      sendData();
    }
  }

  delay(4);
}
