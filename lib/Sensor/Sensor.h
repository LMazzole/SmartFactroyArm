/**
 * @file SensorArray.h
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

#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>
#include "LogConfiguration.h"

class Sensor {
   public:
    /**
    * @brief Construct a new Sensor object
    * 
    */
    Sensor(const int pin);

    /**
    * @brief Construct a new Sensor object
    * 
    */
    Sensor(const int pin, const int led);

    /**
      * @brief 
      * 
      * 
      * checks the sensor for the thing
      * 
      * @return true if there is a thing in the sensor range
      * @return false if there is no thing in the sensor range
      */
    bool hasThing();

   private:
    const int sensorPin;
    const int ledPin;
};

#endif