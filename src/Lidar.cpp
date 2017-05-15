#include "../include/Lidar.h"

Lidar::Lidar(){
    fileDescriptor = open("/dev/cu.usbserial", O_RDWR | O_NOCTTY | O_NDELAY);
    if (fileDescriptor == -1) {
        std::cout << "Unable to open UART!" << std::endl;
    } else {
        fcntl(fileDescriptor, F_SETFL, 0);
        std::cout << "connected" << std::endl;

        speed_t baud = B57600;

        struct termios settings;
        tcgetattr(fileDescriptor, &settings);

        cfsetospeed(&settings, baud);
        settings.c_cflag &= ~PARENB;
        settings.c_cflag &= ~CSTOPB;
        settings.c_cflag &= ~CSIZE;

        tcsetattr(fileDescriptor, TCSANOW, &settings);
        tcflush(fileDescriptor, TCOFLUSH);
    }
}

 struct LidarData Lidar::getReading() {
     struct LidarData data;

     std::cout << "reading" << std::endl;

     unsigned char c[50];
     unsigned char *headerByte = NULL;
     read(this->fileDescriptor, c, 50);
     std::cout << "read" << std::endl;
     for(int i = 49; i > 4; i--) {
         if(c[i] == 0xFF ) {
             headerByte = c + i;
         }
     }
    if(headerByte != NULL) {
        char low = *headerByte + 1;
        char high = *headerByte + 2;
        char steps = *headerByte + 3;

        int dist = 0;
        dist = binaryConcat(high, low);
        std::cout << dist << std::endl;
    } else {
        std::cout << "null" << std::endl;
    }
     return data;
 }

int Lidar::binaryConcat(char high, char low) const {
    int dist = 0;
    return (dist | low) | ((int)(high) << 7);
}