/**
 * @file Servo.h
 * @brief The Sensor Array
 * 
 * @author Luciano Bettinaglio (luciano.bettinaglio@hsr.ch)
 * 
 * @version 1.2 - Refactoring  - Luca Mazzoleni (luca.mazzoleni@hsr.ch)  - 2019-03-20
 * @version 1.1 - Added Doxygen-Documentation  - Luca Mazzoleni (luca.mazzoleni@hsr.ch)  - 2019-03-20
 * @version 1.0 - SA SmartFactroyBox HS 2018
 * 
 * @date 2019-03-20
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef MYSERVO_H
#define MYSERVO_H

#include <Arduino.h>
#include "LogConfiguration.h"
#include "Servo.h"

class MyServo : public Servo {
   public:
    /**
    * @brief Construct a new Servo object
    * 
    */
    MyServo(const int pin);

    /**
     * @brief C-Tor for ServoObject
     * 
     */
    ~MyServo();

    /**
     * @brief move servo to desired position with 1 degree per functioncall
     * 
     * 
     * @param pos - Desired Servo-position; -90deg is left 0deg is Center, 90deg is right
     * @return true  - if servo is in position
     * @return false - if servo is not in position
     * 
     */
    bool moveToPosition(int desiredposDeg);

    /**
     * @brief  Move servo to desired position with choosen stepwidth in degree per functioncall
     * 
     * @param desiredposDeg - Desired Servo-position; -90deg is left 0deg is Center, 90deg is right
     * @param stepwidthDeg - choose stepwidth in degree 0<x
     * @return true - if servo is in position
     * @return false - if servo is not in position
     */
    bool moveToPosition(int desiredposDeg, int stepwidthDeg);

   private:
    const int pPin;
    int pActualposDeg;
};

#endif