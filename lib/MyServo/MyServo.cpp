#include "MyServo.h"

MyServo::MyServo(int pin) {
    pinMode(1, OUTPUT);
    m1.attach(pin);
}

MyServo::~MyServo() {
    m1.detach();
}

/**
 * @brief 
 * 
 * move servo to given position
 * 
 * @param pos between ??? and ???, position the arm needs to go to
 * @return true if arm is in position
 * @return false if arm is not in position
 */
bool MyServo::moveToPosition(int pos) {
    m1.write(pos);
    int now = m1.read();
    if (now == pos)
        return true;
    else
        return false;
    // TODO: check if position is in the right range
}