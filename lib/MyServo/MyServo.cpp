#include "MyServo.h"

MyServo::MyServo(int pin) {
    pinMode(1, OUTPUT);
    attach(pin);
}

MyServo::~MyServo() {
    detach();
}

bool MyServo::moveToPosition(int pos) {
    DBINFO1ln(pos);
    // pos += 90;
    // pos = pos * 180.0 / (2.5 * 360);
    // pos = map(pos, -90.0, 90.0, 0.0, 180.0 / (5 * 360.0));
    // pos = map(pos, 0, 5 * 360, 0.0, 180.0);
    // pos = map(pos, 0, 180, 0, 255);
    DBINFO1("Pos:");
    DBINFO1(pos);
    DBINFO1(" / ");
    // analogWrite(5, pos);
    writeMicroseconds(pos);
    int actualpos = read();
    DBINFO1ln(actualpos);
    if (actualpos == pos) {
        // DBINFO1("Endposition reached");
        return true;
    } else {
        return false;
    }
}