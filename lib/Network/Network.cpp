#include "Network.h"

Network::Network() : ble(BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST) {
}

void Network::init(String name) {
    DBFUNCCALLln("Initialising the Bluefruit LE module: ");
    if (!(ble.begin(VERBOSE_MODE))) {
        DBINFO1ln("Couldn't find Bluefruit, make sure it's in CoMmanD mode & check wiring?");
    }

    if (FACTORYRESET_ENABLE) {
        /* Perform a factory reset to make sure everything is in a known state */
        DBINFO1ln("Performing a factory reset: ");
        if (!ble.factoryReset()) {
            DBERROR("Couldn't factory reset");
        }
        ble.verbose(false);  // debug info is a little annoying after this point!
        while (!ble.isConnected()) {
            DBINFO1ln("connecting to Bluetooth...");
            delay(500);
        }
    }
}

Network::receiveStates Network::receiveAndAnalyse() {
    DBFUNCCALLln("Network::receiveAndAnalyse");
    ble.println("AT+BLEUARTRX");
    ble.readline();
    // DBINFO1ln(ble.buffer);
    if (strcmp(ble.buffer, "OK") == 0) {
        // no data
        return receiveStates::nothingReceived;
    }
    DBINFO1ln(ble.buffer);

    //TODO ask/wait for message
    String msg = ble.buffer;  // received message
    if (msg == "pickup(0)")
        return receiveStates::pickupLeft;
    else if (msg == "pickup(1)")
        return receiveStates::pickupRight;
    else if (msg == "drop(0)")
        return receiveStates::dropLeft;
    else if (msg == "drop(1)")
        return receiveStates::dropRight;
    else {
        DBINFO1ln("unknown message");  // TODO log unknown message received
        return receiveStates::nothingReceived;
    }
}

bool Network::sendMessage(enum Network::sendStates state) {
    DBFUNCCALLln("Network::sendMessage");
    switch (state) {
        case 0:
            sendString("pickupSuccess(1)");
            break;
        case 1:
            sendString("pickupSuccess(0)");
            break;
        case 2:
            sendString("dropSuccess(1)");
            break;
        case 3:
            sendString("dropSuccess(0)");
            break;
        default:
            DBINFO1ln("unknown state");
    }
}

bool Network::sendTestMessage(String msg) {
    sendString(msg);
}

bool Network::sendString(String msg) {
    ble.print("AT+BLEUARTTX=");
    ble.println(msg);

    // check response stastus
    if (!ble.waitForOK()) {
        DBINFO1ln("Failed to send?");
    }
}

void Network::printInfo() {
    /* Disable command echo from Bluefruit */
    ble.echo(false);

    DBINFO1ln("Requesting Bluefruit info:");
    /* Print Bluefruit information */
    ble.info();
}

String Network::decodeReceiveStates(receiveStates states) {
    switch (states) {
        case nothingReceived:
            return "nothingReceived";
            break;
        case pickupLeft:
            return "pickupLeft";
            break;
        case pickupRight:
            return "pickupRight";
            break;
        case dropLeft:
            return "dropLeft";
            break;
        case dropRight:
            return "dropRight";
            break;
        default:
            return "unknown";
            break;
    }
}
String Network::decodeSendStates(sendStates states) {
    switch (states) {
        case pickupSuccess:
            return "pickupSuccess";
            break;
        case pickupFailure:
            return "pickupFailure";
            break;
        case dropSuccess:
            return "dropSuccess";
            break;
        case dropFailure:
            return "dropFailure";
            break;
        default:
            return "unknown";
            break;
    }
}