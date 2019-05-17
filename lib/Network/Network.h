/**
 * @file Network.h
 * @brief handles network connections over bluetooth and signals passed by the Raspberry Pi
 * 
 * @author Luca Mazzoleni (luca.mazzoleni@hsr.ch)
 * 
 * 
 * @date 2019-04-12
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef NETWORK_H
#define NETWORK_H

#include <Arduino.h>
#include "LogConfiguration.h"
#include "NetworkConfiguration.h"

#include <SPI.h>
// #include "Adafruit_BLE.h"
// #include "Adafruit_BluefruitLE_SPI.h"
// #include "Adafruit_BluefruitLE_UART.h"

#if SOFTWARE_SERIAL_AVAILABLE
#include <SoftwareSerial.h>
#endif

#define FACTORYRESET_ENABLE 1
#define MINIMUM_FIRMWARE_VERSION "0.6.6"

class Network {
   public:
    /**
    * @brief enumerates the message which may be received
    * 
	* it is somehow a representation of states in the FSM
    */
    enum receiveStates {
        nothingReceived = -1,  ///< no messages received or unknown message received
        pickupLeft = 0,        ///< signal: pickup(0)
        pickupRight = 1,       ///< signal: pickup(1)
        dropLeft = 2,          ///< signal: drop(0)
        dropRight = 3,         ///< signal: drop(0)
        error = 4,             ///< signal: error
        resume = 5             ///< signal: resume
    };

    /**
     * @brief enumerates messages which must be sent
     * 
	 * it is somehow a representation of states in the FSM
     */
    enum sendStates {
        pickupSuccess = 0,  ///< signal: pickupSuccess(1)
        pickupFailure = 1,  ///< signal: pickupSuccess(0)
        dropSuccess = 2,    ///< signal: dropSuccess(1)
        dropFailure = 3     ///< signal: dropSuccess(0)
    };

   public:
    /**
    * @brief Construct a new Network object
    * 
    */
    Network();

    /**
     * @brief waits until connected to bluetooth, makes the connection
     *
     * @param name the name of the board (in Bluetooth), is obolete, since not used
     */
    void init(String name);

    /**
     * @brief return the enum of the message which is received
     * 
     * @return receiveStates the state which is received
     */
    receiveStates receiveAndAnalyse();
    /**
     * @brief sends messages based on the enum value
     * 
     * @param state the state which will be sent
     * @return true if the message is sent
     * @return false if the message is not sent
     */
    bool sendMessage(sendStates state);

    /**
     * @brief is used for debuging purposes, can pass strings to be sent
     * 
     * @param msg the string to send over bluetooth
     * @return true if the string is sent
     * @return false if the string is not sent
     */
    bool sendTestMessage(String msg);

    // /**
    //  * @brief can print information concerning bluetooth and connection
    //  *
    //  */
    // void printInfo();

    /**
     * @brief used to decode the enum values for receiveStates to human readable strings
     * 
	 * @param receiveStates the enum to be passed
     * @return String the decoded message, human intepretable
     */
    String decodeReceiveStates(receiveStates);

    /**
     * @brief used to decode the enum values for sendStates to human readable strings
     * 
	 * @param sendStates the enum to be passed
     * @return String the decoded message, human intepretable 
     */
    String decodeSendStates(sendStates);

   private:
    // Adafruit_BluefruitLE_SPI ble;  ///< the connection element

    /**
     * @brief the function, that actually sends the message, used as helper function for sendMessage, etc.
     * 
	 * @param msg the message, which will be sent
     * @return true if the message is sent
	 * @return false if the message is not sent
     */
    bool sendString(String msg);
};

#endif