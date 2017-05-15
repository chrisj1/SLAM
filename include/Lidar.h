#ifndef SLAM_LIDAR_H
#define SLAM_LIDAR_H

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>

struct LidarData {
    float angle;
    int distance;
};

class Lidar {
    private:
        int fileDescriptor = -1;

        int binaryConcat(char high, char low) const;
    public:
        Lidar();
        struct LidarData getReading();
};



#endif //SLAM_LIDAR_H
