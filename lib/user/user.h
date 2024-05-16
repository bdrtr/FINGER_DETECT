#pragma once
#ifndef USER_H
#define USER_H

#include <Arduino.h>

class User {
    
    public:

    User(String name);
    void setID(uint8_t ID);
    uint8_t getID();

    private:

    String name;
    uint8_t ID;


};

#endif