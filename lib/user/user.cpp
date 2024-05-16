#include "user.h"
#include "WString.h"

User::User(String name) {
    this->name = name;
}

void User::setID(uint8_t ID) {

    this->ID = ID;
}

uint8_t User::getID() {

    return ID;
}