#ifndef FSERVER_H
#define FSERVER_H

#include <WebServer.h>

class fServer {


    public:
    fServer(int port);
    void Initialize(String subdomain, http_method method);
    void func();
    void listen();
    void selProcess(String message_code);
    void sendReg();
    void sendLog();


    private:
    WebServer server;
    char info[1024];
    uint16_t last_id;
    
};


#endif