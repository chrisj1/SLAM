#include <iostream>
#include "Roomba.h"

int main() {

    Roomba r("/dev/cu.usbserial-DA01NQY7");
    sleep(1);
    r.setSensorStream({BumpsWheelDrops, LeftEncoderCounts, RightEncoderCounts});
    sleep(1);
    while(!r.leftWheelDrop && !r.rightWheelDrop) {
        float right = 10;
        float left = 5;
        while(!r.bumpRight && !r.bumpLeft) {
            right+=.2;
            left +=.1;
            //r.driveDirect((int)right, (int)left);
            usleep(5000);
        }
        r.stop();
        r.beep();
        r.driveDirect(-100, -150);
        sleep(2);
    }

    //r.beep();
    r.setPassiveMode();
    r.~Roomba();
    return 0;
}