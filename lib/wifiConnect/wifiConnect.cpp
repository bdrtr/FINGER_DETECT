#include "wifiConnect.h"
#include <HTTPClient.h>
#include <WiFi.h>

WifiConnect::WifiConnect(String SSID, String PASSWD) {

    this->SSID = SSID;
    this->PASSWD = PASSWD;
}

void WifiConnect::Initialize() {


    connection_state = false;

    WiFi.begin(SSID, PASSWD);
    Serial.print("connection try to be in");

    unsigned int get_current_time = millis();

    while ( WiFi.status() != WL_CONNECTED && (millis() - get_current_time) < timeout) {

        delay(30);
        Serial.print(".");
    }

    connection_state = true;
    IP = WiFi.localIP().toString();

    Serial.print("connection okey");
}

String WifiConnect::get_IP() {

    return WiFi.localIP().toString();
}

void WifiConnect::get_info() {

    Serial.printf("Ip adress : %s,  SSID : %s \n", IP, SSID);
}

void WifiConnect::set_timeout(unsigned int timeout) {

    this->timeout = timeout;
}

void WifiConnect::matchTrue() {

    HTTPClient http;

    String serverIP = "localhost";
    String serverPort = "8080";
    String endpoint = "/endpoint";

}


