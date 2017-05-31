#include "../include/Lidar.h"

Lidar::Lidar(){
    fileDescriptor = open("/dev/cu.usbserial", O_RDONLY | O_NOCTTY | O_NDELAY);
    if (fileDescriptor < 0) {
        std::cout << "Unable to open UART!" << std::endl;
    } else {
        fcntl(fileDescriptor, F_SETFL, 0);
        std::cout << "connected" << std::endl;

        speed_t baud = B9600;

        struct termios settings;
        tcgetattr(fileDescriptor, &settings);

        cfsetospeed(&settings, baud);
        settings.c_cflag &= ~PARENB;
        settings.c_cflag &= ~CSTOPB;
        settings.c_cflag &= ~CSIZE;

        tcsetattr(fileDescriptor, TCSANOW, &settings);
        tcflush(fileDescriptor, TCOFLUSH);
    }
    std::cout << "fd: " << fileDescriptor << std::endl;
}

 struct LidarData Lidar::getReading() {
     struct LidarData data;

     unsigned char *c = (unsigned char*) calloc(50, 1);
     unsigned char *headerByte = NULL;
     read(this->fileDescriptor, c, 50);
     for(int i = 0; i < 50; i++) {
         if(c[i] == 0xFF ) {
             headerByte = c + i;
             //break;
         }
     }
    if(headerByte != NULL) {
        unsigned char high = *(headerByte + 1);
        unsigned char low = *(headerByte + 2);
        unsigned char steps = *(headerByte + 3);

        int dist = 0;
        dist = binaryConcat(high, low);
        std::cout << dist << std::endl;
    } else {
        std::cout << "null" << std::endl;
    }
     return data;
 }

unsigned int Lidar::binaryConcat(char high, char low) const {
    return (unsigned int) low | ((unsigned int)(high) << 7);
}