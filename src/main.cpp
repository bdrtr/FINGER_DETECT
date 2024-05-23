#include <Arduino.h>

#include <wifiConnect.h>
#include <HTTPClient.h>
#include <fProcess.h>
#include <fServer.h>

#include <WebServer.h>  
#include <ArduinoJson.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_Fingerprint.h>


const String SSID = "Kilicarslan";
const String PASSWD = "14531453";


WifiConnect connect(SSID, PASSWD);
fServer server(80);

void setup() {

  Serial.begin(9600);
  connect.Initialize();
  Serial.println(connect.get_IP());
  Serial.println(connect.getIP());
  server.Initialize("/post", HTTP_POST);
  delay(20);

}

void loop() {
  server.listen();
}
