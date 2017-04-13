#ifndef SLAM_LIDAR_H
#define SLAM_LIDAR_H

#include "StepperMotor.h"

class Lidar {
    private:
        int angle;
        StepperMotor motor;
    public:
        Lidar(StepperMotor stepperMotor);
        const int getReading();
        const int getAngle();
};


#endif //SLAM_LIDAR_H
