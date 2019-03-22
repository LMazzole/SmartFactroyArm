#include "Sensor.h"

Sensor::Sensor(const int pin)
    : sensorPin(pin) {
    DBFUNCCALLln("Sensor::Sensor()");
    pinMode(pin, INPUT);
}

/**
 * @brief 
 * 
 * 
 * checks the sensor for the thing
 * 
 * @return true if there is a thing in the sensor range
 * @return false if there is no thing in the sensor range
 */
bool Sensor::hasThing() {
    DBFUNCCALLln("Sensor::hasThing()");
    int value = !digitalRead(sensorPin);  // if Object detected PIN = LOW
    if (value) {
        return true;
    } else {
        return false;
    }
}