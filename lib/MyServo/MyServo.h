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
     * @brief 
     * 
     */
    ~MyServo();

    /**
     * @brief move servo to given position
     * 
     * 
     * @param pos between ??? and ???, position the arm needs to go to
     * @return true if arm is in position
     * @return false if arm is not in position
     * 
     */
    bool moveToPosition(int pos);

    /**
     * @brief  move servo to given position
     * 
     * @param pos - 
     * @param stepwidthDeg - choose stepwidth in degree
     * @return true - if arm is in position
     * @return false - if arm is not in position
     */
    bool moveToPosition(int pos, int stepwidthDeg);

   private:
    const int pPin;
    int pActualposDeg;
};

#endif