/**
 * @file PositionConfiguration.h
 * 
 * @brief Defines all critical Positions for Load and Unloading in degree
 * 
 * @author Luca Mazzoleni (luca.mazzoleni@hsr.ch)
 * 
 * @version 1.0 - Define Positions  - Luca Mazzoleni - 2019-03-20
 * 
 * @date 2019-04-12
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef POSITIONCONFIGURATION_H__
#define POSITIONCONFIGURATION_H__

const int LOADPOSITION = -18;                                    // int, where to get until thing is loaded (sensor recognizes thing)
const int RESTPOSITION = LOADPOSITION - 72;                      // int, where to rest bevore loading
const int DRIVEPOSITION = LOADPOSITION + 88;                     // int, where to rest for driving with thing loaded
const int UNLOADPOSITIONSENSORLEFT = LOADPOSITION + 163;         // 145 int, drive until there to eject thing
const int UNLOADPOSITIONLEFT = UNLOADPOSITIONSENSORLEFT + 20;    // 165 int, drive until there to eject thing
const int UNLOADPOSITIONSENSORRIGHT = LOADPOSITION - 115;        // -145 int, drive until there to eject thing
const int UNLOADPOSITIONRIGHT = UNLOADPOSITIONSENSORRIGHT - 20;  // -165 int, drive until there to eject thing

const int SERVOSPEED = 10;
// const int RAMPSIDE true           // true for left, false for right loading ramp

#endif