#include <iostream>
#include "Roomba.cpp"


using namespace std;

char randomInt(char min, char max) {
    return (char) (rand() * (max - min)) + min;
}

int main() {

    Roomba r("/dev/cu.usbserial-DA01NQY7");
    sleep(1);
    r.setSensorStream({7});
    while(true) {
        r.driveDirect(randomInt(-100, 100), randomInt(-100, 100));
        sleep(3);
        r.stop();
        r.beep();
    }
    return 0;
}