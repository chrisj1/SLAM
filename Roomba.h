//
// Created by Chris Jerrett on 3/13/17.
//

#ifndef SLAM_ROOMBA_H
#define SLAM_ROOMBA_H
#include <iostream>
#include <string>
#include <cstdlib>
#include <initializer_list>
#include <pthread.h>
#include <unistd.h>
#include <thread>
#include <vector>
#include <map>

#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */

#pragma once


using namespace std;


    enum Sensor {
        BumpsWheelDrops = 7,
        Distance = 19,
        Angle = 20,
        LeftEncoderCounts = 43,
        RightEncoderCounts = 44
    };

    const std::map<Sensor, int> DATA_BYTES = {
            {BumpsWheelDrops, 1 },
            {Distance, 2 },
            {Angle, 2},
            {LeftEncoderCounts, 2},
            {RightEncoderCounts, 2}
    };


    class Roomba {

    private:
        /*
         * Instance Fields
         */
        int fileDescriptor;
        string portname;

        thread *sensorThread;

        vector<Sensor> sensors;
        /**
         * Basic roomba opt codes to control
         * power and roomba io.
         */

        const unsigned char START_OPT_CODE = 128;
        const unsigned char SEEK_DOCK_OPT_CODE = 143;
        const unsigned char POWER_DOWN_OPT_CODE = 133;
        const unsigned char DEMO_OPT_CODE = 136;
        const unsigned char COVER_AND_DOCK_DEMO_CODE = 1;

        /*
         * opt codes to set io modes
         */
        const unsigned char SAFE_OPT_CODE = 131;
        const unsigned char FULL_OPT_CODE = 132;
        const unsigned char PASSIVE_OPT_CODE = 128;

        /*
         * Movement opt codes
         */
        const unsigned char DRIVE_OPT_CODE = 137;
        const unsigned char DRIVE_DIRECT_OPT_CODE = 145;

        /*
         * Sensor opt codes
         */
        const unsigned char SENSORS_OPT_CODE = 142;

        const void sendStart();

        const void writeChar(const unsigned char command);

        const void openSerialPort(string portname);

        const void writeCharArray(const unsigned char commands[], int length);

        const void signedIntToTwoUnsignedChar(short speed, unsigned char *high, unsigned char *low);

        const void reconnect();

        const void disconnected();

        void sendSensorStream();

        const void monitorSensors();

        /*
         * Sensor Processing
         */

        void parseBumpAndWheelDrop(unsigned char *byte);

        void parseDistance(unsigned char *elem);
        void parseAngle(const unsigned char* elem);
        void parseLeftEncoderCounts(const unsigned char* elem);
        void parseRightEncoderCounts(const unsigned char* elem);

        unsigned char* findHeader(unsigned char *c) const;
        void parseBytes(const unsigned char *headerByte, unsigned char size);

    public:

        /*
         * Sesnor States
         */
        volatile bool leftWheelDrop = false;
        volatile bool rightWheelDrop = false;
        volatile bool bumpLeft = false;
        volatile bool bumpRight = false;

        Roomba(const string portname);

        void setSensorStream(std::initializer_list<unsigned char> sensors);

        const void stop();

        const void driveDirect(int right, int left);

        const void powerOff();

        const void drive(int velocity, int radius);

        const void requestSensor(unsigned char id);

        const void driveFor(int right, int left, int time);

        const void beep();

        const void seekDock();

        const void setSafeMode();

        const void setFullMode();

        const void setPassiveMode();

        ~Roomba();
    };

    void printChar(char c);

#endif //SLAM_ROOMBA_H
