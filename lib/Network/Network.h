/**
 * @file Network.h
 * @brief 
 * 
 * @author Luca Mazzoleni (luca.mazzoleni@hsr.ch)
 * 
 * @version 1.1 - Description - {author} - {date}
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
#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_SPI.h"
#include "Adafruit_BluefruitLE_UART.h"

#if SOFTWARE_SERIAL_AVAILABLE
#include <SoftwareSerial.h>
#endif

#define FACTORYRESET_ENABLE 1
#define MINIMUM_FIRMWARE_VERSION "0.6.6"

class Network {
   public:
    /**
    * @brief 
    * 
    */
    enum receiveStates {
        nothingReceived = -1,  ///< no messages received or unknown message received
        pickupLeft = 0,        ///< pickup(0)
        pickupRight = 1,       ///< pickup(1)
        dropLeft = 2,          ///< drop(0)
        dropRight = 3          ///< drop(1)
    };

    /**
     * @brief 
     * 
     */
    enum sendStates {
        pickupSuccess = 0,  ///< pickupSuccess(1)
        pickupFailure = 1,  ///< pickupSuccess(0)
        dropSuccess = 2,    ///< dropSuccess(1)
        dropFailure = 3     ///< dropSuccess(0)
    };

   public:
    /**
    * @brief Construct a new Network object
    * 
    * @param name - 
    */
    Network();

    /**
     * @brief waits until connected to bluetooth
     * 
     * @param name - 
     */
    void init(String name);

    /**
     * @brief 
     * 
     * @return receiveStates - 
     */
    receiveStates receiveAndAnalyse();
    /**
     * @brief 
     * 
     * @param state - 
     * @return true - 
     * @return false - 
     */
    bool sendMessage(sendStates state);

    /**
     * @brief 
     * 
     * @param msg - 
     * @return true - 
     * @return false - 
     */
    bool sendTestMessage(String msg);

    /**
     * @brief 
     * 
     */
    void printInfo();

    /**
     * @brief 
     * 
     * @return String - 
     */
    String decodeReceiveStates(receiveStates);

    /**
     * @brief 
     * 
     * @return String - 
     */
    String decodeSendStates(sendStates);

   private:
    Adafruit_BluefruitLE_SPI ble;  ///<
    bool sendString(String msg);   ///<
};

#endif