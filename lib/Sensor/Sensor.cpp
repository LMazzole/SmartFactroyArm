/**
 * @file Sensor.cpp
 * @brief Implemention of the Sensor class
 * 
 * @author Luca Mazzoleni (luca.mazzoleni@hsr.ch)
 * 
 * @version 1.0 - Class-Implementation - Luca Mazzoleni - 2019-03-20
 * 
 * @date 2019-03-27
 * @copyright Copyright (c) 2019
 * 
 */

#include "Sensor.h"

Sensor::Sensor(const int pin)
    : psensorPin(pin), pledPin(LED_BUILTIN) {
    DBFUNCCALLln("Sensor::Sensor()");
    pinMode(psensorPin, INPUT);
    pinMode(pledPin, OUTPUT);
}

Sensor::Sensor(const int pin, const int led)
    : psensorPin(pin), pledPin(led) {
    DBFUNCCALLln("Sensor::Sensor()");
    pinMode(psensorPin, INPUT);
    pinMode(pledPin, OUTPUT);
}

bool Sensor::hasThing() {
    DBFUNCCALLln("Sensor::hasThing()");
    int value = !digitalRead(psensorPin);  // if Object detected PIN = LOW
    // DBINFO1ln(value);
    if (value) {
        DBINFO1ln("Object detected");
        digitalWrite(pledPin, HIGH);
        return true;
    } else {
        DBINFO1ln("No Object detected");
        digitalWrite(pledPin, LOW);
        return false;
    }
}