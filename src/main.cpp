/**
 * @file main.cpp
 * @brief Contains the FSM of the SmartFactory Arm
 * 
 * @image html fsm.png width=1000
 * 
 * @author Luca Mazzoleni (luca.mazzoleni@hsr.ch)
 * 
 * @version 1.0 
 * 
 * @date 2019-03-22
 * @copyright Copyright (c) 2019
 * 
 */
#include <Arduino.h>
#include "Configuration.h"
#include "LogConfiguration.h"
#include "MyServo.h"
#include "Network.h"
#include "PositionConfiguration.h"
#include "Sensor.h"

//===Global Variables==========

bool (*funcPoint)() = nullptr;  ///< states function pointer for FSM
int substate = 0;               ///< used for substate of FSM (second level)

//===Generate Objects==========
MyServo servo_center(PIN_SERVO);                                 ///< Object of center servo
Sensor sensorLinks(PIN_LB_SENSOR_LEFT, PIN_LED_SENSOR_LEFT);     ///< Sensor on left side, Servo(int pin, int maxPulse, int minPulse);
Sensor sensorRechts(PIN_LB_SENSOR_RIGHT, PIN_LED_SENSOR_RIGHT);  ///< Sensor on right side, Servo(int pin, int maxPulse, int minPulse);
Network networkObj;                                              ///< Object of network communication
Network::receiveStates currentMessage;                           ///< saves the current received Message, which is in work now

//=========FUNCTION-PROTOTYP=========
/**
 * @brief first state, on boot
 *
 * State I:
 *   - go to rest position to drive without a thing
 *   - emit signal ready
 *
 * @return true if state done and goig to next
 * @return false if in state
 */
bool stat_getToRestPosition();

/**
 * @brief second state, after reached rest position or after unloading
 *
 * State II:
 *   - waiting for signal, depending on signal switch to the needed state
 *
 * @return true if state done and goig to next
 * @return false if in state
 */
bool stat_waitingForSignal();

/**
 * @brief fourth state, after loading package
 *
 * State IV:
 *    - waiting for signal, depending on signal switch to the needed state
 *
 * @return true if state done and goig to next
 * @return false if in state
 */
bool stat_waitingForSignal2();

/**
 * @brief third state, after signal for pickup package
 *
 * State III:
 *   - move arm to load position, thing falls into tray
 *   - sensor reads if thing is in tray
 *   - move thing to drive position
 *   - emit signal ready to drive
 *
 * @return true if state done and goig to next
 * @return false if in state
 */
bool stat_loadThing();

/**
 * @brief error state
 * 
 * @return true - leave state
 * @return false - stay in state
 */
bool stat_error();

/**
 * @brief fifth state, after signal for drop package
 *
 * State V:
 *   - move arm to unload position, thing falls from tray
 *   - sensor reads if thing has fallen from tray
 *   - move arm to rest position
 *   - emit signal ready to drive
 *
 * @return true if state done and goig to next
 * @return false if in state
 */
bool stat_unloadThing();

/**
 * @brief moving arm to resting position, the position at which no package is in the tray and the arm is save for driving
 *
 * @return true if in position
 * @return false if not in position
 */
bool unloadThing_moveToRestPos();

/**
 * @brief moving arm to package loading position
 *
 * @return true if in position
 * @return false if not in position
 */
bool loadThing_moveToLoadPos();

/**
 * @brief moving arm to package loading position
 *
 * @param side Network::receiveStates passed by bluetooth
 * @return true if in position
 * @return false if not in position
 */
bool loadThing_moveToUnloadPos(Network::receiveStates side);

/**
 * @brief moving arm to drive position, position at which the package is in the tray and save for driving
 *
 * @return true if in position
 * @return false if not in position
 */
bool loadThing_moveToDrivePos();

/**
 * @brief testing function for testing components
 *
 * switch statement to select test cases
 * 
 */
bool testing();

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
    // networkObj.init("ZellwegerBettinaglioMazzoleni");

    funcPoint = stat_getToRestPosition;
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
    // funcPoint = testing;
    funcPoint();
    delay(500);
}

bool testing() {
    DBFUNCCALLln("::testing()");
    switch (7) {
        case 0:
            DBINFO1ln("No Testcase selected");
            delay(10000);
            break;
        case 1:
            DBINFO1ln("-------------Sensortest Lightbarrier-------------");
            sensorLinks.hasThing();
            sensorRechts.hasThing();
            // pinMode(PIN_LED_SENSOR_LEFT, OUTPUT);
            // pinMode(PIN_LED_SENSOR_RIGHT, OUTPUT);
            // DBINFO1("Left: ");
            // if (sensorLinks.hasThing())
            //     // digitalWrite(PIN_LED_SENSOR_LEFT, HIGH);
            // // DBINFO1ln(!digitalRead(PIN_LB_SENSOR_LEFT));
            // delay(2000);
            // DBINFO1("Right: ");
            // // DBINFO1ln(!digitalRead(PIN_LB_SENSOR_RIGHT));
            // if (sensorRechts.hasThing())
            //     // digitalWrite(PIN_LED_SENSOR_RIGHT, HIGH);
            // delay(2000);
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
            DBINFO1ln("---------Servo Test---------");
            int maxstep = 180;
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
            while (!servo_center.moveToPosition(pos, 40)) {
            };
            delay(5000);
            pos = 90;
            while (!servo_center.moveToPosition(pos, 30)) {
            };
            delay(5000);
            pos = -90;
            while (!servo_center.moveToPosition(pos, 40)) {
            };
            delay(5000);
        } break;
        case 6: {
            DBINFO1ln("Network Test");
            // networkObj.printInfo();
            networkObj.sendTestMessage("hoi du luschtige :)\n");
            DBINFO1("received: ");  // + String
            DBINFO1ln(networkObj.decodeReceiveStates(networkObj.receiveAndAnalyse()));
            delay(3000);
        } break;
        case 7: {
            DBINFO1ln("Move Servo to Position Test");
            int speed = 10;
            while (!servo_center.moveToPosition(0, speed))
                ;
            delay(5000);
            // while(!servo_center.moveToPosition(RESTPOSITION,speed));
            // delay(5000);
            // while(!servo_center.moveToPosition(LOADPOSITION,speed));
            // delay(5000);
            // while(!servo_center.moveToPosition(DRIVEPOSITION,speed));
            // delay(5000);
            // while(!servo_center.moveToPosition(UNLOADPOSITIONLEFT,speed));
            // delay(5000);
            // while(!servo_center.moveToPosition(UNLOADPOSITIONRIGHT,speed));
            // delay(5000);
        } break;
        default:
            break;
    }
}

bool stat_getToRestPosition() {
    DBFUNCCALLln("::stat_getToRestPosition()");
    // networkObj.sendMessage(Network::sendStates::dropSuccess);
    if (unloadThing_moveToRestPos()) {
        funcPoint = stat_waitingForSignal;
        return true;
    } else {
        return false;
    }
}

bool stat_waitingForSignal() {
    DBFUNCCALLln("::stat_waitingForSignal()");
    DBSTATUSln("Wait for Signal");
    Network::receiveStates rec = networkObj.receiveAndAnalyse();
    if (rec == Network::receiveStates::nothingReceived)
        return false;
    else if (rec == Network::receiveStates::error) {
        currentMessage = rec;
        DBINFO1("currentMessage: ");
        DBINFO1ln(networkObj.decodeReceiveStates(currentMessage));
        DBERROR("ErrorMsg. received");
        funcPoint = stat_error;
        return true;
    } else {
        currentMessage = rec;
        DBINFO1("currentMessage: ");
        DBINFO1ln(networkObj.decodeReceiveStates(currentMessage));
        funcPoint = stat_loadThing;
        return true;
    }
    // TODO more specific???
}

bool stat_loadThing() {  // must be in rest position!
    DBFUNCCALLln("::stat_loadThing()");
    DBSTATUSln("Load Package");
    DBINFO1("currentMessage: ");
    DBERROR("");
    DBINFO1ln(networkObj.decodeReceiveStates(currentMessage));
    if (!(currentMessage == Network::receiveStates::pickupLeft ||
          currentMessage == Network::receiveStates::pickupRight)) {
        DBERROR("invalid Msg. received");
        funcPoint = stat_waitingForSignal;
    } else if (currentMessage == Network::receiveStates::pickupLeft) {
        DBERROR("wrong side chosen ;)");
        funcPoint = stat_waitingForSignal;
    } else {
        bool hasThingSensed = false;
        switch (substate) {
            case 0:  // 1. move to load position
                if (loadThing_moveToLoadPos())
                    substate = 1;
                break;
            case 1:                                                        // 2. check sensor value
                if (currentMessage == Network::receiveStates::pickupLeft)  // left loading ramp
                {
                    DBERROR("wrong side chosen ;)");
                } else if (currentMessage == Network::receiveStates::pickupRight)  // right loading ramp
                    hasThingSensed = sensorRechts.hasThing();
                else
                    DBINFO1ln("not expected message");  // TODO wrong rampside value

                if (hasThingSensed == true)
                    substate = 2;
                else {
                    networkObj.sendMessage(Network::sendStates::pickupFailure);  // TODO what to do?
                    substate = 0;
                    funcPoint = stat_error;
                }
                break;
            case 2:  //  3. move to drive position
                if (loadThing_moveToDrivePos())
                    substate = 3;
                break;
            case 3:  // 4. emit signal READYNOW
                networkObj.sendMessage(Network::sendStates::pickupSuccess);
                substate = 0;
                funcPoint = stat_waitingForSignal2;
                return true;
                break;
            default:  // wrong substateion
                substate = 0;
                return false;
                break;
        }
    }
}

bool stat_waitingForSignal2() {
    DBFUNCCALLln("::stat_waitingForSignal2()");
    DBSTATUSln("Wait for Signal2");
    DBERROR("");
    Network::receiveStates rec = networkObj.receiveAndAnalyse();
    if (rec == Network::receiveStates::nothingReceived) {
        return false;
    } else if (rec == Network::receiveStates::error) {
        currentMessage = rec;
        DBINFO1("currentMessage: ");
        DBINFO1ln(networkObj.decodeReceiveStates(currentMessage));
        DBERROR("ErrorMsg. received");
        funcPoint = stat_error;
        return true;
    } else {
        currentMessage = rec;
        DBINFO1("currentMessage: ");
        DBINFO1ln(networkObj.decodeReceiveStates(currentMessage));
        funcPoint = stat_unloadThing;
        return true;
    }
    // TODO more specific???
}

bool stat_unloadThing() {
    DBFUNCCALLln("::stat_unloadThing()");
    DBSTATUSln("Unload Package");
    if (!(currentMessage == Network::receiveStates::dropLeft ||
          currentMessage == Network::receiveStates::dropRight)) {
    }  // do nothing
    else {
        // bool sside = false;  // get side to unload to, side: true if left, false if right
        bool hasThingEjected = false;
        switch (substate) {
            case 0:  // 1. move to unload position
                if (loadThing_moveToUnloadPos(currentMessage))
                    substate = 1;
                break;
            case 1:                                                      // 2. check sensor value
                if (currentMessage == Network::receiveStates::dropLeft)  // eject left
                    hasThingEjected = !sensorLinks.hasThing();
                else if (currentMessage == Network::receiveStates::dropRight)  // eject right
                    hasThingEjected = !sensorRechts.hasThing();
                else
                    DBINFO1ln("unexpected 2 message");  // TODO wrong rampside value

                if (hasThingEjected == true)
                    substate = 2;
                else {
                    networkObj.sendMessage(Network::sendStates::dropFailure);  // TODO what to do?
                    substate = 0;
                    funcPoint = stat_error;
                }
                break;
            case 2:  //  3. move to rest position
                if (unloadThing_moveToRestPos())
                    substate = 3;
                break;
            case 3:  // 4. emit signal READYNOW
                networkObj.sendMessage(Network::sendStates::dropSuccess);
                substate = 0;
                funcPoint = stat_waitingForSignal;
                return true;
                break;
            default:  // wrong substateion
                return false;
                break;
        }
    }
}

bool stat_error() {
    DBFUNCCALLln("::stat_error()");
    DBSTATUSln("Wait for Signal");
    Network::receiveStates rec = networkObj.receiveAndAnalyse();
    if (rec == Network::receiveStates::nothingReceived)
        return false;
    else if (rec == Network::receiveStates::resume) {
        currentMessage = rec;
        DBINFO1("currentMessage: ");
        DBINFO1ln(networkObj.decodeReceiveStates(currentMessage));
        funcPoint = stat_getToRestPosition;
        return true;
    } else {
        currentMessage = rec;
        DBINFO1("currentMessage: ");
        DBINFO1ln(networkObj.decodeReceiveStates(currentMessage));
        return false;
    }
}

bool unloadThing_moveToRestPos() {
    return servo_center.moveToPosition(RESTPOSITION, SERVOSPEED);
}

bool loadThing_moveToLoadPos() {
    return servo_center.moveToPosition(LOADPOSITION, SERVOSPEED);
}

bool loadThing_moveToUnloadPos(Network::receiveStates side) {  // side: true if left, false if right
    DBFUNCCALLln("::loadThing_moveToUnloadPos()");
    if (side == Network::receiveStates::dropLeft)
        return servo_center.moveToPosition(UNLOADPOSITIONLEFT, SERVOSPEED);
    else if (side == Network::receiveStates::dropRight)
        return servo_center.moveToPosition(UNLOADPOSITIONRIGHT, SERVOSPEED);
    else
        DBERROR("error unloading");
}

bool loadThing_moveToDrivePos() {
    return servo_center.moveToPosition(DRIVEPOSITION, SERVOSPEED);
}
