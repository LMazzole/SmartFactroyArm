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

#define RESTPOSITION -90          // int, where to rest bevore loading
#define LOADPOSITION -18          // int, where to get until thing is loaded (sensor recognizes thing)
#define DRIVEPOSITION 50          // int, where to rest for driving with thing loaded
#define UNLOADPOSITIONLEFT 165    // int, drive until there to eject thing
#define UNLOADPOSITIONRIGHT -165  // int, drive until there to eject thing
#define SERVOSPEED 10
// #define RAMPSIDE true           // true for left, false for right loading ramp

#endif