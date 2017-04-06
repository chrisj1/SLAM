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

#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */


using namespace std;

typedef enum RoombaState {
    OFF,
    SAFE,
    FULL,
    PASSIVE,
    DISCONNECTED
}RoombaState;


class Roomba {

private:
    /*
     * Instance Fields
     */
    int fileDescriptor;
    RoombaState state = DISCONNECTED;
    string portname;

    unsigned char* sensors;
    unsigned char sensorsPolling;

    thread* sensorThread;

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

    /*
     * Sensor packet ids
     */
    const unsigned char BUMP_WHEEL_DROP_SENSOR = 7;
    const unsigned char DISTANCE_SENSOR = 19;
    const unsigned char ANGLE_SENSOR = 20;
    const unsigned char VOLTAGE_SENSOR = 22;
    const unsigned char BATTER_CHARGE_SENSOR = 25;
    const unsigned char BATTERY_CAPACITY_SENSOR = 26;
    const unsigned char LEFT_ENCODER = 43;
    const unsigned char RIGHT_ENCODER = 44;
    const unsigned char WALL_SENSOR = 8;


    //Packet Ids:
    const unsigned char WALL = 8;
    const unsigned char DISTANCE = 19;
    const unsigned char ANGLE = 20;
    const unsigned char VOLTAGE = 22;
    const unsigned char CHARGE = 24;

    const void sendStart();
    const void seekDock();
    const void setSafeMode();
    const void setFullMode();
    const void setPassiveMode();

    const bool bumpWheelDrop();
    const int distanceDriven();
    const int angleTurned();
    const int voltage();
    const int batteryCharge();
    const int batteryCapacity();
    const int leftEncoder();
    const int rightEncoder();

    const void writeChar(const unsigned char command);
    const void openSerialPort(string portname);
    const void writeCharArray(const unsigned char commands[], int length);
    const void signedIntToTwoUnsignedChar(short speed, unsigned char* high, unsigned char* low);

    const void reconnect();
    const void disconnected();

    void sendSensorStream();

    const void monitorSensors();

public:
    Roomba(const string portname);
    void setSensorStream(std::initializer_list<unsigned char> sensors);
    const void stop();
    const void driveDirect(int right, int left);
    const void powerOff();
    const void drive(int velocity, int radius);
    const void requestSensor(unsigned char id);
    const void driveFor(int right, int left, int time);
    ~Roomba();
};

Roomba* roomba = NULL;

void printChar(char c);

#endif //SLAM_ROOMBA_H
