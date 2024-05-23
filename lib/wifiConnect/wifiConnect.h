#pragma once
#ifndef WIFICONNECT_H
#define WIFICONNECT_H

#include <iostream>
#include <string>
#include <WiFi.h>
#include <HTTPClient.h>

class WifiConnect {


    public:
    WifiConnect(String SSID, String PASSWD);
    void Initialize();
    String get_IP();
    void get_info();
    void set_timeout(unsigned int timeout);
    String getIP();


    private:
    String SSID;
    String PASSWD;
    String IP;
    unsigned int timeout = 20000;
    bool connection_state;
    

};

#endif