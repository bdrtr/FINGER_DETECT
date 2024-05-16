#ifndef FPROCESS_H
#define FPROCESS_H

#include "user.h"

class fProcess{


    public:
    
    fProcess();
    void Initialize();
    void enRoll(User usr);
    uint8_t logIn();
    void showUserList();
    void delDB();
    private:
    String name;

};

#endif