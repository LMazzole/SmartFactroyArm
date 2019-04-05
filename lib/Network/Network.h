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

#define FACTORYRESET_ENABLE         1
#define MINIMUM_FIRMWARE_VERSION "0.6.6"

class Network{
public:
   enum receiveStates {
    nothingReceived=-1, // no messages received
	pickupLeft=0,	// pickup(0)
	pickupRight=1,	// pickup(1)
	dropLeft=2,		// drop(0)
	dropRight=3		// drop(1)
	};
	enum sendStates {
	pickupSuccess=0,	// pickupSuccess(1)
	pickupFailure=1,	// pickupSuccess(0)
	dropSuccess=2,		// dropSuccess(1)
	dropFailure=3		// dropSuccess(0)
	};

public:
   Network(String name);
   receiveStates receiveAndAnalyse();
   bool sendMessage(sendStates state);
   bool sendTestMessage(String msg);
   void printInfo();   
   
   private:
    Adafruit_BluefruitLE_SPI *ble;
    bool sendString(String msg);
};


#endif