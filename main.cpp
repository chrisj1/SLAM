#include <iostream>
#include "Roomba.cpp"
#include <unistd.h>


using namespace std;

int main() {

    Roomba r("/dev/cu.usbserial-DA01NQY7");
    sleep(1);
    r.driveDirect(200, 200);

    //usleep(4000);
    r.stop();

    unsigned char distance = 19;
    r.setSensorStream({distance});

    //usleep(30000);

    r.powerOff();
    return 0;
}