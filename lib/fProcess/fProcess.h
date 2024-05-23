#ifndef FPROCESS_H
#define FPROCESS_H

#include <Arduino.h>

class fProcess{


    public:
    
    fProcess();
    void Initialize();
    void enRoll(uint16_t id);
    uint16_t logIn();
    void showUserList();
    void delDB();
    private:
    String name;

};

#endif