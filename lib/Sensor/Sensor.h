/**
 * @file Sensor.h
 * @brief The Seonsor Class
 * 
 * Handles the Lightbarrier-Sensor
 * Digital Distance Interrupter, Seeed Studio
 * http://wiki.seeedstudio.com/Grove-Digital_Distance_Interrupter_0.5_to_5cm-GP2Y0D805Z0F_P/ 
 * 
 * @author Luca Mazzoleni (luca.mazzoleni@hsr.ch)
 * 
 * @version 1.0 - Class-Implementation - Luca Mazzoleni - 2019-03-20
 * 
 * @date 2019-03-20
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>
#include "LogConfiguration.h"

class Sensor {
   public:
    /**
    * @brief Construct a new Sensor object
    * 
    * @param pin - Number of the Pin where the Sensor is connected.
    */
    Sensor(const int pin);

    /**
    * @brief Construct a new Sensor object
    * 
    * @param pin - Number of the Pin where the Sensor is connected.
    * @param led - Number of the Pin where the Statusled is connected.
    */
    Sensor(const int pin, const int led);

    /**
      * @brief Chechks if the Sensor detects an Object and turns on the LED 
      * 
      * If the Sensor detcts an Object the pin will be Low.
      * When the Object is detected, the LED will be HIGH else LOW.
      * 
      * @return true if there is an object in sensor range
      * @return false if there is no object in sensor range
      */
    bool hasThing();

   private:
    const int psensorPin;
    const int pledPin;
};

#endif