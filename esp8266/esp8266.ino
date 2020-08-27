#include <ESP8266WiFi.h>
#include <ArduinoOTA.h>
#include <ESP8266mDNS.h>
#include <WebSocketsServer.h>

WebSocketsServer webSocket(80);

const char* ssid = "dylonkylie_2.4G@unifi";
const char* password = "Ab670515";

const char* mdnsName = "esp8266";

const char* OTAName = "ESP8266";
const char* OTAPassword = "secretesppassword";

void setup() {
  Serial.begin(115200);
  startWifi();
  startMDNS();
  startWebSocket();
}

void loop() {
  webSocket.loop();
  ArduinoOTA.handle();
  Serial.println("Working...");
  delay(1000);
}

void startWifi() {
  WiFi.begin(ssid, password);
  Serial.print("Connecting to ");
  Serial.print(ssid);
  Serial.println("...");

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.print("Connected to");
  Serial.println(WiFi.SSID());
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void startOTA() {
  ArduinoOTA.setHostname(OTAName);
  ArduinoOTA.setPassword(OTAPassword);

  ArduinoOTA.onStart([]() {
    Serial.println("OTA started");
  });

  ArduinoOTA.onEnd([]() {
    Serial.println("OTA ended");
  });

  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });
  
  ArduinoOTA.begin();
  Serial.println("OTA ready\n");
}

void startMDNS() {
  MDNS.begin(mdnsName);
  Serial.print("mDNS responder listening at http://");
  Serial.print(mdnsName);
  Serial.println(".local");
}

void startWebSocket() {
  webSocket.begin();
  webSocket.onEvent(onEventHandler);
  Serial.println("WebSocket server started");
}

void onEventHandler(uint8_t num, WStype_t type, uint8_t * payload, size_t len) {
  switch (type) {
    case WStype_DISCONNECTED:
      Serial.printf("[%u] Disconnected\n", num);
      break;
    case WStype_CONNECTED: {
      IPAddress ip = webSocket.remoteIP(num);
      Serial.printf("[%u] Connected %d.%d.%d.%d. URL: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);
      }
      break;
    case WStype_TEXT:
      Serial.printf("[%u] sent position: %s\n", num, payload);
      break;
  }   
}
