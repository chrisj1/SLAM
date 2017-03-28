#include "Roomba.h"

Roomba::Roomba(const string portname) :fileDescriptor(-1), portname(portname), sensors(NULL), sensorsPolling(0),sensorThread(NULL) {
    openSerialPort(portname);
    usleep(100);
    sendStart();
    usleep(100);

    setFullMode();

    roomba = this;

    sensorThread = new thread(&Roomba::monitorSensors, this);
}

void Roomba::setSensorStream(std::initializer_list<unsigned char> sensorsArg) {
    int size = sensorsArg.size();
    cout << size << endl;
    sensorsPolling = size;
    unsigned char sensorsArray[size];
    int i = 0;
    for (auto elem : sensorsArg)  {
        sensorsArray[i++] = elem;
        cout << elem << endl;
        i++;
    }
    sensors = sensorsArray;
    sendSensorStream();
}

void Roomba::sendSensorStream() {
    unsigned char commandSequence[sensorsPolling + 2];
    commandSequence[0] = (unsigned char) 149;
    commandSequence[1] = sensorsPolling;

    for(int i = 0; i < sensorsPolling; i++) {
        commandSequence[i + 2] = sensors[i];
    }
    writeCharArray(commandSequence, sensorsPolling + 2);

}

/*
 * This command starts the OI. You must always send the Start command before sending any other
 * commands to the OI.
* Serial sequence: [128].
* Available in modes: Passive, Safe, or Full
* Changes mode to: Passive. Roomba beeps once to acknowledge it is starting from “off” mode.
* This command starts the OI. You must always send the Start command before sending any other
commands to the OI.
* Serial sequence: [128].
* Available in modes: Passive, Safe, or Full
* Changes mode to: Passive. Roomba beeps once to acknowledge it is starting from “off” mode. 
 */
const void Roomba::sendStart() {
    writeChar(131);
}
/**
 * This command starts the requested built-in demo.
 * Serial sequence: [136][Which-demo]
 * Available in modes: Passive, Safe, or Full
 * Changes mode to: Passive
 * Demo data byte 1: Demo number (-1 - 9)
 *
 * Identical to the Cover demo, with one exception. If Create sees an infrared
 * signal from an iRobot Home Base, it uses that signal to dock
 */
const void Roomba::seekDock() {
    unsigned char command[] = {
            DEMO_OPT_CODE, COVER_AND_DOCK_DEMO_CODE
    };
    writeCharArray(command, 2);
    sleep(1);
}

const void Roomba::powerOff() {
    writeChar(POWER_DOWN_OPT_CODE);
}

const void Roomba::setFullMode() {
    writeChar(FULL_OPT_CODE);
}

const void Roomba::setSafeMode() {
    writeChar(SAFE_OPT_CODE);
}

const void Roomba::stop() {
    unsigned char stopArray[] = {
            145, 0, 0, 0, 0
    };

    writeCharArray(stopArray, 5);
}

const void Roomba::driveDirect(int right, int left) {
    unsigned char rHigh;
    unsigned char rLow;
    signedIntToTwoUnsignedChar(right, &rHigh, &rLow);

    unsigned char lHigh;
    unsigned char lLow;
    signedIntToTwoUnsignedChar(left, &lHigh, &lLow);

    unsigned char commands[] = {
            145, rHigh, rLow, lHigh, lLow
    };

    writeCharArray(commands, 5);
    sleep(1);
}

const void Roomba::drive(int velocity, int radius) {
    unsigned char vHigh;
    unsigned char vLow;
    signedIntToTwoUnsignedChar(velocity, &vHigh, &vLow);

    unsigned char rHigh;
    unsigned char rLow;
    signedIntToTwoUnsignedChar(radius, &rHigh, &rLow);

    unsigned char commands[] = {
            137, vHigh, vLow, rHigh, rLow
    };
    cout << commands << endl;

    for(int i = 0; i < 5; i++)  {
        cout << (unsigned int)commands[i] << ", ";
    }
    cout << endl;

    sleep(1);
}

const void Roomba::writeChar(const unsigned char command) {
    cout << (unsigned int) command << endl;
    int n = write(fileDescriptor, (&command) , 1);
    cout << "write" << endl;
    if (n < 0) {
        cout << "Write failed attempting to reconnect" << endl;
    }

}

const void Roomba::writeCharArray(const unsigned char commands[], int length) {
        for(int i = 0; i < length; i++) {
            writeChar(commands[i]);
        }
}

const void Roomba::openSerialPort(string portname) {
    const char* cString = portname.c_str();
    fileDescriptor = open(cString, O_RDWR | O_NOCTTY | O_NDELAY);
    if (fileDescriptor == -1) {
        cout << "open_port: Unable to open port!" << endl;
    } else {
        fcntl(fileDescriptor, F_SETFL, 0);
        cout << "connected" << endl;
    }

    sleep(1);
}

const void Roomba::signedIntToTwoUnsignedChar(short speed, unsigned char* high, unsigned char* low) {
    *low = (unsigned char)(speed & 0xFF);
    *high = (unsigned char)((speed >> 8) & 0xFF);
}

const void Roomba::reconnect() {
    openSerialPort(portname);
}

const void Roomba::disconnected() {
    while(fileDescriptor < 0) {
        cout << "Disconnected from roomba attempting to reconnect" << endl;
        reconnect();
        sleep(1);
    }
    sendStart();
    cout << "Reconnected to create" << endl;

}

const void Roomba::requestSensor(unsigned char id) {
    writeChar(SENSORS_OPT_CODE);
    writeChar(id);
}

const void Roomba::monitorSensors() {
    while(true){}
}

Roomba::~Roomba() {
    sensorThread->join();
}
