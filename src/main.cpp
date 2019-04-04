/**
 * @file main.cpp
 * @brief 
 * 
 * @author Luca Mazzoleni (luca.mazzoleni@hsr.ch)
 * 
 * @version 0.1 
 * 
 * @date 2019-03-22
 * @copyright Copyright (c) 2019
 * 
 */
#include <Arduino.h>
#include "Configuration.h"
#include "LogConfiguration.h"
#include "MyServo.h"
#include "PosConf.h"
#include "Sensor.h"

//===Global Variables==========

void (*funcPoint)() = nullptr;  // states function pointer
bool toNextStatus = true;

int substate = 0;  // used for state progress

//===Generate Objects==========
MyServo servo_center(PIN_SERVO);
Sensor sensorLinks(PIN_LB_SENSOR_LEFT, PIN_LED_SENSOR_LEFT);  //     Servo(int pin, int maxPulse, int minPulse);
Sensor sensorRechts(PIN_LB_SENSOR_RIGHT, PIN_LED_SENSOR_RIGHT);

//=========FUNCTION-PROTOTYP=========
// /**
//  * @brief
//  *
//  * State I:
//  *   - go to rest position to drive without a thing
//  *   - emit signal ready
//  *
//  * @return true -
//  * @return false -
//  */
// bool stat_getToRestPosition();

// /**
//  * @brief
//  *
//  * State II &  IV:
//  *   - waiting for signal, depending on signal switch to the needed state
//  *
//  * @return true -
//  * @return false -
//  */
// bool stat_waitingForSignal();

// /**
//  * @brief
//  *
//  * State III:
//  *   - move arm to load position, thing falls into tray
//  *   - sensor reads if thing is in tray
//  *   - move thing to drive position
//  *   - emit signal ready to drive
//  *
//  * @return true -
//  * @return false -
//  */
// bool stat_loadThing();

// /**
//  * @brief
//  *
//  * State V:
//  *   - move arm to unload position, thing falls from tray
//  *   - sensor reads if thing has fallen from tray
//  *   - move arm to rest position
//  *   - emit signal ready to drive
//  *
//  * @return true -
//  * @return false -
//  */
// bool stat_unloadThing();

// /**
//  * @brief
//  *
//  * @return true -
//  * @return false -
//  */
// bool unloadThing_moveToRestPos();

// /**
//  * @brief
//  *
//  * @return true -
//  * @return false -
//  */
// bool loadThing_moveToLoadPos();

// /**
//  * @brief
//  *
//  * move the thing to the unload position
//  *
//  * @param side true if thing needs to be ejected on the left side
//  * @param side false if thing needs to be ejected on the right side
//  * @return true if arm is in unload position
//  * @return false if arm is not in unload position
//  */
// bool loadThing_moveToUnloadPos(bool side);

// /**
//  * @brief
//  *
//  * @return true -
//  * @return false -
//  */
// bool loadThing_moveToDrivePos();

/**
 * @brief 
 * 
 * @return true - 
 * @return false - 
 */
void testing();

//=========================MAIN-FUNCTIONS========================================

/**
 * @brief for initialisation of the Board
 * 
 * Use it to initialize variables, pin modes, start using libraries, etc.
 * The setup() function will only run once,
 * after each powerup or reset of the board
 */
void setup() {
    DBFUNCCALLln("::setup()");
    Serial.begin(9600);
}

/**
 * @brief one loop per cycle (SB full -> transported -> returned empty)
 * 
 * After creating a setup() function, which initializes and sets the initial values,
 * the loop() function does precisely what its name suggests,
 * and loops consecutively, allowing your program to change and respond.
 * Use it to actively control the board.
 */
void loop() {
    DBFUNCCALLln("::loop()");
    // bool toNextStatus = false;
    funcPoint = testing;
    // toNextStatus = true;
    funcPoint();
}

void testing() {
    DBFUNCCALLln("::testing()");
    switch (0) {
        case 0:
            DBINFO1ln("No Testcase selected");
            delay(10000);
            break;
        case 1:
            DBINFO1ln("Sensortest Lightbarrier");
            DBINFO1("Left: ");
            sensorLinks.hasThing();
            // DBINFO1ln(!digitalRead(PIN_LB_SENSOR_LEFT));
            delay(100);
            DBINFO1("Right: ");
            // DBINFO1ln(!digitalRead(PIN_LB_SENSOR_RIGHT));
            sensorRechts.hasThing();
            delay(100);
            break;
        case 2:
            DBINFO1ln("LED Test");
            DBINFO1ln("Links");
            pinMode(PIN_LED_SENSOR_LEFT, OUTPUT);
            pinMode(PIN_LED_SENSOR_RIGHT, OUTPUT);
            digitalWrite(PIN_LED_SENSOR_LEFT, HIGH);
            delay(1000);
            digitalWrite(PIN_LED_SENSOR_LEFT, LOW);
            DBINFO1ln("Rechts");
            digitalWrite(PIN_LED_SENSOR_RIGHT, HIGH);
            delay(1000);
            digitalWrite(PIN_LED_SENSOR_RIGHT, LOW);
            delay(100);
            break;
        case 3: {
            DBINFO1ln("Servo Test");
            int maxstep = 180;  //=180deg drehrihctung gegenuhrzeiger
            int stepwidth = 10;
            int pauselength = 10;
            servo_center.moveToPosition(0);
            delay(5000);
            for (int pos = 0; pos <= maxstep; pos += stepwidth) {  // goes from 0 degrees to maxstep degrees
                                                                   // in steps of step degree
                servo_center.moveToPosition(pos);                  // tell servo to go to position in variable 'pos'
                delay(pauselength);                                // waits pauselengthms for the servo to reach the position
            }
            delay(2000);
            for (int pos = 0; pos <= 2 * maxstep; pos += stepwidth) {  // goes from maxstep degrees to -maxstep degrees

                servo_center.moveToPosition(maxstep - pos);
                delay(pauselength);
            }
            delay(2000);
            for (int pos = 0; pos <= maxstep; pos += stepwidth) {  // goes from -maxstep degrees to 0 degrees

                servo_center.moveToPosition(-(maxstep - pos));
                delay(pauselength);
            }
            break;
        }
        case 4: {
            DBINFO1ln("Servo TEST /LEFT RIGHT with LB");
            int pos = 0;
            while (sensorLinks.hasThing()) {
                pos += 1;
                servo_center.moveToPosition(pos);
            };
            while (sensorRechts.hasThing()) {
                pos -= 1;
                servo_center.moveToPosition(pos);
            };
            delay(100);
        } break;
        case 5: {
            DBINFO1ln("Servo TEST in Loop");
            int pos = 0;
            while (!servo_center.moveToPosition(pos, 20)) {
            };
            delay(1000);
            pos = 179;
            while (!servo_center.moveToPosition(pos)) {
            };
            delay(1000);
            pos = -179;
            while (!servo_center.moveToPosition(pos, 50)) {
            };
            delay(1000);
        } break;
        default:
            break;
    }
}

// bool stat_getToRestPosition() {
//     DBFUNCCALLln("::stat_getToRestPosition()");
//     return unloadThing_moveToRestPos();
//     // TODO: emit signal READYNOW
// }

// bool stat_waitingForSignal() {
//     DBFUNCCALLln("::stat_waitingForSignal()");
//     // if get signal, return true
//     // network class needed
// }

// bool stat_loadThing() {  // must be in rest position!
//     DBFUNCCALLln("::stat_loadThing()");
//     // switch (substate) {
//     //     case 0:  // 1. move to load position
//     //         if (loadThing_moveToLoadPos())
//     //             substate = 1;
//     //         break;
//     //     case 1:  // 2. check sensor value
//     //         bool hasThingSensed = false;
//     //         if (RAMPSIDE == true)  // left loading ramp
//     //             hasThingSensed = sensLinks.hasThing();
//     //         else if (RAMPSIDE == false)  // right loading ramp
//     //             hasThingSensed = sensRechts.hasThing();
//     //         else
//     //             ;  // TODO wrong rampside value
//     //         if (hasThingSensed == true)
//     //             substate = 2;
//     //         else
//     //             ;  // TODO what to do?
//     //         break;
//     //     case 2:  //  3. move to drive position
//     //         if (loadThing_moveToDrivePos())
//     //             substate = 3;
//     //         break;
//     //     case 3:  // 4. emit signal READYNOW
//     //              // TODO: emit signal READYNOW
//     //         substate = 0;
//     //         return true;
//     //         break;
//     //     default:  // wrong substateion
//     //         substate = 0;
//     //         return false;
//     //         break;
//     // }
// }

// bool stat_unloadThing() {
//     DBFUNCCALLln("::stat_unloadThing()");
//     // bool sside = false;  // get side to unload to, side: true if left, false if right
//     // switch (substate) {
//     //     case 0:  // 1. move to unload position
//     //         if (loadThing_moveToUnloadPos(sside))
//     //             substate = 1;
//     //         break;
//     //     case 1:  // 2. check sensor value
//     //         bool hasThingEjected = false;
//     //         if (sside)  // eject left
//     //             hasThingEjected = !sensLinks.hasThing();
//     //         else if (sside)  // eject right
//     //             hasThingEjected = !sensRechts.hasThing();
//     //         else
//     //             ;  // TODO wrong rampside value
//     //         if (hasThingEjected == true)
//     //             substate = 2;
//     //         else
//     //             ;  // TODO what to do?
//     //         break;
//     //     case 2:  //  3. move to rest position
//     //         if (unloadThing_moveToRestPos())
//     //             substate = 3;
//     //         break;
//     //     case 3:  // 4. emit signal READYNOW
//     //              // TODO: emit signal READYNOW
//     //         substate = 0;
//     //         return true;
//     //         break;
//     //     default:  // wrong substateion
//     //         return false;
//     //         break;
//     // }
// }

// bool unloadThing_moveToRestPos() {
//     return servo_center.moveToPosition(RESTPOSITION);
// }

// bool loadThing_moveToLoadPos() {
//     return servo_center.moveToPosition(LOADPOSITION);
// }

// bool loadThing_moveToUnloadPos(bool side) {  // side: true if left, false if right
//     DBFUNCCALLln("::loadThing_moveToUnloadPos()");
//     if (side)
//         return servo_center.moveToPosition(UNLOADPOSITIONLEFT);
//     else
//         return servo_center.moveToPosition(UNLOADPOSITIONRIGHT);
// }

// bool loadThing_moveToDrivePos() {
//     return servo_center.moveToPosition(DRIVEPOSITION);
// }
