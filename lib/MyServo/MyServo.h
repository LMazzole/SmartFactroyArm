/**
 * @file MyServo.h
 * @brief The MyServo Class
 * 
 * Modelcraft Standard-Servo RS-22 YMB Digital-Servo
 * 
 * @author Luca Mazzoleni (luca.mazzoleni@hsr.ch)
 * 
 * @version 1.0 - Class-Implementation - Luca Mazzoleni - 2019-03-20
 * 
 * @date 2019-04-12
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
    * @brief Construct a new My Servo object
    * 
    * @param pin - Number of the Pin where the Servo is connected.
    */
    MyServo(const int pin);

    /**
     * @brief C-Tor for ServoObject
     * 
     * Detaches the Servopin
     */
    ~MyServo();

    /**
     * @brief Move servo to desired position with 1 degree per functioncall
     * 
     * Max. Resolution from read() is only about 15 degree.
     * This will cause an slight Position-Error in the first functioncall.
     * The Servo will get detached when the position is reached.
     * 
     * @param pos - Desired Servo-position in degree; -90deg is left 0deg is Center, 90deg is right
     * @return true  - if servo is in position
     * @return false - if servo is not in position
     * 
     */
    bool moveToPosition(int desiredposDeg);

    /**
     * @brief  Move servo to desired position with choosen stepwidth in degree per functioncall
     * 
     * Max. Resolution from read() is only about 15 degree.
     * This will cause an slight Position-Error in the first functioncall.
     * The Servo will get detached when the position is reached.
     * 
     * @param desiredposDeg - Desired Servo-position; -90deg is left 0deg is Center, 90deg is right
     * @param stepwidthDeg - choose stepwidth in degree 0<x
     * @return true - if servo is in position
     * @return false - if servo is not in position
     */
    bool moveToPosition(int desiredposDeg, int stepwidthDeg);

   private:
    const int pPin;     ///< Pin where the Servo is connected.
    int pActualposDeg;  ///< Actual Position in degree: Resolution about 15 deg
};

#endif