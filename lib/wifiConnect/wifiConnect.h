#pragma once
#ifndef WIFICONNECT_H
#define WIFICONNECT_H

#include <iostream>
#include <string>
#include <WiFi.h>

class WifiConnect {


    public:
    WifiConnect(String SSID, String PASSWD);
    void Initialize();
    String get_IP();
    void get_info();
    void set_timeout(unsigned int timeout);
    void matchTrue();


    private:

    String SSID;
    String PASSWD;
    String IP;
    unsigned int timeout = 20000;
    bool connection_state;
    

};

#endif