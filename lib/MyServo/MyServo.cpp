#include "MyServo.h"

MyServo::MyServo(int pin) {
    pinMode(1, OUTPUT);
    attach(pin);
}

MyServo::~MyServo() {
    detach();
}

bool MyServo::moveToPosition(int pos) {
    DBINFO1("Pos:");
    DBINFO1(pos);
    DBINFO1(" / ");
    write(pos);
    int actualpos = read();
    DBINFO1ln(actualpos);
    if (actualpos == pos) {
        // DBINFO1("Endposition reached");
        return true;
    } else {
        return false;
    }
}