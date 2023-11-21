#include <WebServer.h>
#include <WiFi.h>
#include "esp_wpa2.h"

#include <ArduinoJson.h>

#include "config.h"

WebServer server(80);

int a0Val;

void handleNotFound() {
  String message = "";
  message += "404!\n";
  message += server.uri();
  message += " NOT FOUND\n\n";
  server.send(404, "text/plain", message);
}

void handleData() {
  StaticJsonDocument<64> resJson;
  JsonObject data = resJson.createNestedObject("data");
  data["A0"] = a0Val;

  String resTxt = "";
  serializeJson(resJson, resTxt);

  server.send(200, "application/json", resTxt);
}

void setup() {
  Serial.begin(9600);
  delay(10);
  Serial.print(F("Connecting to network: "));
  Serial.println(ssid);
  WiFi.disconnect(true);
  WiFi.mode(WIFI_STA);

  WiFi.begin(ssid, ssid_password);

  int trycount = 0;
  while (WiFi.status() != WL_CONNECTED && trycount < 60) {
    delay(500);
    Serial.print(F("."));
    trycount++;
  }

  Serial.println("");
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println(F("WiFi is connected!"));
    Serial.println(F("IP address set: "));
    Serial.println(WiFi.localIP());
  } else {
    Serial.println(F("WiFi is NOT connected! 💩"));
  }

  server.enableCORS();
  server.on("/data", handleData);
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  a0Val = analogRead(A0);
  server.handleClient();
  delay(2);
}
