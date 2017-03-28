#ifndef SLAM_LIDAR_H
#define SLAM_LIDAR_H

class Lidar {
    private:
        int angle;
    public:
        const int getReading();
        const int getAngle();
};


#endif //SLAM_LIDAR_H
