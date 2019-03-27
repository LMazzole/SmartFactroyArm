/**
 * @file Sensor.cpp
 * @brief 
 * 
 * @author Luca Mazzoleni (luca.mazzoleni@hsr.ch)
 * 
 * @version 1.1 - Description - {author} - {date}
 * 
 * @date 2019-03-27
 * @copyright Copyright (c) 2019
 * 
 */

#include "Sensor.h"

Sensor::Sensor(const int pin)
    : sensorPin(pin), ledPin(LED_BUILTIN) {
    DBFUNCCALLln("Sensor::Sensor()");
    pinMode(sensorPin, INPUT);
    pinMode(ledPin, OUTPUT);  //DO I NEED THIS?
}

Sensor::Sensor(const int pin, const int led)
    : sensorPin(pin), ledPin(led) {
    DBFUNCCALLln("Sensor::Sensor()");
    pinMode(sensorPin, INPUT);
    pinMode(ledPin, OUTPUT);
}

bool Sensor::hasThing() {
    DBFUNCCALLln("Sensor::hasThing()");
    int value = !digitalRead(sensorPin);  // if Object detected PIN = LOW
    DBFUNCCALLln(value);
    if (value) {
        DBINFO1ln("Object detected");
        digitalWrite(ledPin, HIGH);
        return true;
    } else {
        DBINFO1ln("No Object detected");
        digitalWrite(ledPin, LOW);
        return false;
    }
}