/**
 * @file MyServo.cpp
 * @brief 
 * 
 * @author Luca Mazzoleni (luca.mazzoleni@hsr.ch)
 * 
 * @version 1.1 - Description - {author} - {date}
 * 
 * @date 2019-04-01
 * @copyright Copyright (c) 2019
 * 
 */

#include "MyServo.h"

MyServo::MyServo(const int pin) : pPin(pin) {
    pinMode(pPin, OUTPUT);
}

MyServo::~MyServo() {
    detach();
}

bool MyServo::moveToPosition(int desiredposDeg) {
    DBFUNCCALLln("MyServo::moveToPosition(int pos)");
    return moveToPosition(desiredposDeg, 1);
}

bool MyServo::moveToPosition(int desiredposDeg, int stepwidthDeg) {
    DBFUNCCALLln("MyServo::moveToPosition(int pos, int stepwidthDeg)");
    int actualpos = read();
    if (!attached()) {
        DBFUNCCALLln("First Call");
        attach(pPin);
        pActualposDeg = map(actualpos, 92, 110, 0, 270);
    }

    if (desiredposDeg > pActualposDeg) {
        if (desiredposDeg - pActualposDeg >= stepwidthDeg) {  //use stepwidthDeg as long as possible
            DBINFO1ln("stepwidth");
            pActualposDeg += stepwidthDeg;
        } else {  //switch to stepwidth 1 when the actual pos is nearer at the target pos than the stepwidth
            DBINFO1ln("stepwidth 1");
            pActualposDeg += 1;
            // pActualposDeg += (desiredposDeg - pActualposDeg);
        }
    } else {
        if (pActualposDeg - desiredposDeg >= stepwidthDeg) {
            pActualposDeg -= stepwidthDeg;
        } else {
            pActualposDeg -= 1;
            // pActualposDeg -= (desiredposDeg - pActualposDeg);
        }
    }

    int posUsec = map(pActualposDeg, 0, 90, 1500, 1500 + 60);
    posUsec = constrain(posUsec, 700, 2300);
    writeMicroseconds(posUsec);  //https://www.arduino.cc/en/Reference/ServoWriteMicroseconds
    //delay(1);
    DBINFO1(desiredposDeg);
    DBINFO1(" / ");
    DBINFO1(posUsec);
    DBINFO1(" / ");
    DBINFO1(actualpos);
    DBINFO1(" / ");
    DBINFO1ln(pActualposDeg);

    if (pActualposDeg == desiredposDeg) {
        DBSTATUS("Endposition reached: ");
        DBSTATUSln(pActualposDeg);
        detach();
        return true;
    } else {
        DBINFO1ln("Endposition not reached");
        return false;
    }
}