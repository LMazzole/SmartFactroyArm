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

MyServo serv(PIN_SERVO);
Sensor sensLinks(PIN_LB_SENSOR_LEFT);  //     Servo(int pin, int maxPulse, int minPulse);
Sensor sensRechts(PIN_LB_SENSOR_RIGHT);

void (*funcPoint)(bool);  // states function pointer
int opt = 0;              // used for state progress

/**
 * @brief 
 * 
 * @return true - 
 * @return false - 
 */

/**
 * @brief 
 * 
 * @return true - 
 * @return false - 
 */
bool unloadThing_moveToRestPos() {
    return serv.moveToPosition(RESTPOSITION);
}

bool loadThing_moveToLoadPos() {
    return serv.moveToPosition(LOADPOSITION);
}

/**
 * @brief 
 * 
 * move the thing to the unload position
 * 
 * @param side true if thing needs to be ejected on the left side
 * @param side false if thing needs to be ejected on the right side
 * @return true if arm is in unload position
 * @return false if arm is not in unload position
 */
bool loadThing_moveToUnloadPos(bool side) {  // side: true if left, false if right
    DBFUNCCALLln("::loadThing_moveToUnloadPos()");
    if (side)
        return serv.moveToPosition(UNLOADPOSITIONLEFT);
    else
        return serv.moveToPosition(UNLOADPOSITIONRIGHT);
}

bool loadThing_moveToDrivePos() {
    return serv.moveToPosition(DRIVEPOSITION);
}

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
    bool toNext = false;
}

/**
 * @brief 
 * 
 * State I:
 *   - go to rest position to drive without a thing
 *   - emit signal ready
 * 
 * @return true - 
 * @return false - 
 */
bool stat_getToRestPosition() {
    DBFUNCCALLln("::stat_getToRestPosition()");
    return unloadThing_moveToRestPos();
    // TODO: emit signal READYNOW
}

/**
 * @brief 
 * 
 * State II &  IV:
 *   - waiting for signal, depending on signal switch to the needed state
 * 
 * @return true - 
 * @return false - 
 */
bool stat_waitingForSignal() {
    DBFUNCCALLln("::stat_waitingForSignal()");
    // if get signal, return true
    // network class needed
}

/**
 * @brief 
 * 
 * State III:
 *   - move arm to load position, thing falls into tray
 *   - sensor reads if thing is in tray
 *   - move thing to drive position
 *   - emit signal ready to drive
 * 
 * @return true - 
 * @return false - 
 */
bool stat_loadThing() {  // must be in rest position!
    DBFUNCCALLln("::stat_loadThing()");
    // switch (opt) {
    //     case 0:  // 1. move to load position
    //         if (loadThing_moveToLoadPos())
    //             opt = 1;
    //         break;
    //     case 1:  // 2. check sensor value
    //         bool hasThingSensed = false;
    //         if (RAMPSIDE == true)  // left loading ramp
    //             hasThingSensed = sensLinks.hasThing();
    //         else if (RAMPSIDE == false)  // right loading ramp
    //             hasThingSensed = sensRechts.hasThing();
    //         else
    //             ;  // TODO wrong rampside value
    //         if (hasThingSensed == true)
    //             opt = 2;
    //         else
    //             ;  // TODO what to do?
    //         break;
    //     case 2:  //  3. move to drive position
    //         if (loadThing_moveToDrivePos())
    //             opt = 3;
    //         break;
    //     case 3:  // 4. emit signal READYNOW
    //              // TODO: emit signal READYNOW
    //         opt = 0;
    //         return true;
    //         break;
    //     default:  // wrong option
    //         opt = 0;
    //         return false;
    //         break;
    // }
}

/**
 * @brief 
 * 
 * State V:
 *   - move arm to unload position, thing falls from tray
 *   - sensor reads if thing has fallen from tray
 *   - move arm to rest position
 *   - emit signal ready to drive
 * 
 * @return true - 
 * @return false - 
 */
bool stat_unloadThing() {
    DBFUNCCALLln("::stat_unloadThing()");
    // bool sside = false;  // get side to unload to, side: true if left, false if right
    // switch (opt) {
    //     case 0:  // 1. move to unload position
    //         if (loadThing_moveToUnloadPos(sside))
    //             opt = 1;
    //         break;
    //     case 1:  // 2. check sensor value
    //         bool hasThingEjected = false;
    //         if (sside)  // eject left
    //             hasThingEjected = !sensLinks.hasThing();
    //         else if (sside)  // eject right
    //             hasThingEjected = !sensRechts.hasThing();
    //         else
    //             ;  // TODO wrong rampside value
    //         if (hasThingEjected == true)
    //             opt = 2;
    //         else
    //             ;  // TODO what to do?
    //         break;
    //     case 2:  //  3. move to rest position
    //         if (unloadThing_moveToRestPos())
    //             opt = 3;
    //         break;
    //     case 3:  // 4. emit signal READYNOW
    //              // TODO: emit signal READYNOW
    //         opt = 0;
    //         return true;
    //         break;
    //     default:  // wrong option
    //         return false;
    //         break;
    // }
}