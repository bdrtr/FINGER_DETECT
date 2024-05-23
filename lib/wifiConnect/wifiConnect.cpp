#include "wifiConnect.h"
#include <HTTPClient.h>
#include <WiFi.h>
#include <WebServer.h>  
#include <ArduinoJson.h>

WifiConnect::WifiConnect(String SSID, String PASSWD) {

    this->SSID = SSID;
    this->PASSWD = PASSWD;
}

void WifiConnect::Initialize() {

    /*    
    IPAddress local_IP(192, 168, 1, 146);
    IPAddress gateway (192, 168, 1, 1);
    IPAddress subnet(255, 255, 255, 0);
    IPAddress primaryDNS(192,168, 1, 1);

    connection_state = false;
    if (!WiFi.config(local_IP, gateway, subnet, primaryDNS)) Serial.println("config hata");
    */
    connection_state = false;
    WiFi.begin(SSID, PASSWD);
    Serial.print("connection try to be in");

    unsigned int get_current_time = millis();

    while ( WiFi.status() != WL_CONNECTED && (millis() - get_current_time) < timeout) {

        delay(30);
        Serial.print(".");
    }

     while ( WiFi.status() != WL_CONNECTED) {

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


String WifiConnect::getIP() {
    
    return WiFi.softAPIP().toString();
}


