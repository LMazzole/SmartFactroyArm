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

class MyServo {
   public:
    /**
    * @brief Construct a new Servo object
    * 
    */
    MyServo(int pin);

    /**
     * @brief 
     * 
     */
    ~MyServo();

    bool moveToPosition(int pos);

   private:
    Servo m1;
};

#endif