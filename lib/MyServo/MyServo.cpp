/**
 * @file MyServo.cpp
 * @brief 
 * 
 * @author Luca Mazzoleni (luca.mazzoleni@hsr.ch)
 * 
 * @version 1.0 - Class-Implementation - Luca Mazzoleni - 2019-03-20
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
    if (!stepwidthDeg) {      //if stepwidthDeg == 0
        stepwidthDeg = 1000;  //set stepwidthDeg to MAX (approx 1000)
    }
    /* Max. Resolution from read is only about 15 degree.
    * This will cause an slight Position-Error in the first Loop.
    *  Edge Cases are not tested. -> Probably undefinde behaviour.
    */
    int actualpos = read();
    if (!attached()) {  //if Servo is not attached read ActualPos and Map it to degree.
        DBFUNCCALLln("First Call");
        attach(pPin);
        pActualposDeg = map(actualpos, 92, 110, 0, 270);  //Values determined by trial
    }

    if (desiredposDeg > pActualposDeg) {
        if (desiredposDeg - pActualposDeg >= stepwidthDeg) {  //use stepwidthDeg as long as possible
            pActualposDeg += stepwidthDeg;
        } else {
            /*switch stepwidth to half the difference+1 when the actual pos
            * is nearer at the target pos than the stepwidth
            */
            //pActualposDeg += 1;
            pActualposDeg += (desiredposDeg - pActualposDeg + 1) / 2;
        }
    } else {
        if (pActualposDeg - desiredposDeg >= stepwidthDeg) {
            pActualposDeg -= stepwidthDeg;
        } else {
            // pActualposDeg -= 1;
            pActualposDeg -= (pActualposDeg - desiredposDeg + 1) / 2;
        }
    }

    int posUsec = map(pActualposDeg, 0, 90, 1500, 1500 + 60);  //Values determined by trial
    posUsec = constrain(posUsec, 700, 2300);
    writeMicroseconds(posUsec);  // More Info: https://www.arduino.cc/en/Reference/ServoWriteMicroseconds
    //delay(1);
    DBINFO1(desiredposDeg);
    DBINFO1(" / ");
    DBINFO1(posUsec);
    DBINFO1(" / ");
    DBINFO1(actualpos);
    DBINFO1(" / ");
    DBINFO1ln(pActualposDeg);

    if (pActualposDeg == desiredposDeg) {  //if endposition is reached detach servo
        DBSTATUS("Endposition reached: ");
        DBSTATUSln(pActualposDeg);
        detach();
        return true;
    } else {
        DBINFO1ln("Endposition not reached");
        return false;
    }
}