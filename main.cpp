#include <iostream>
#include "Roomba.cpp"


using namespace std;

int randomInt(int min, int max) {
    return (int) (rand() * (max - min)) + min;
}

int main() {

    Roomba r("/dev/cu.usbserial-DA01NQY7");
    sleep(1);
    r.driveDirect(100,100);

    sleep(4);
    r.stop();
    unsigned char distance = 19;
    r.setSensorStream({distance});
    sleep(4);

    r.powerOff();
    r.~Roomba();
    return 0;
}