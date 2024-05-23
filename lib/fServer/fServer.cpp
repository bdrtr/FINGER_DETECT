#include "fServer.h"
#include "WebServer.h"
#include "ArduinoJson.h"
#include "Adafruit_Fingerprint.h"
#include "fProcess.h"

fServer::fServer(int port) : server(port) {

    sprintf(info, "fserver established %s", "okey");    
}


void fServer::func() { 

    if (server.hasArg("plain")) {

        String data = server.arg("plain");
        StaticJsonDocument<1024> document;
        DeserializationError d_err = deserializeJson(document, data);

        if (d_err) sprintf(info, "err occured during deserialization %s\n", d_err.c_str());

        String message = document["message"].as<String>();
        String message_code = document["function_code"].as<String>();
        this->last_id = document["last_id"].as<uint16_t>();

        this->selProcess(message_code);
    }

    return;
}

void fServer::sendReg() {
    
    fProcess fp;
    uint16_t temp_id = this->last_id + 1;
    fp.enRoll(temp_id);

    char RET[20];
    sprintf(RET, "last_id: %u", temp_id);
    server.send(200, "text/plain", RET);

}

void fServer::sendLog() {
    
    fProcess fp;
    char RET[20];
    uint8_t id = fp.logIn();

    if (id != FINGERPRINT_NOTFOUND) {

        sprintf(RET, "current id: %u", id);
        server.send(200, "text/plain", RET);

    } else {

        sprintf(RET, "current id: %d", -1);
        server.send(200, "text/plain", RET);
    }

    return;
}

void fServer::selProcess(String message_code) {

    if (message_code == "1") sendLog();
    else if (message_code == "2") sendReg();

}

void fServer::Initialize(String subdomain, http_method method) {
    
    server.on(subdomain, method, [this]() {this->func();});
    server.begin();
}

void fServer::listen() {
    server.handleClient();
}