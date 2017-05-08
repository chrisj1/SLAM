#include "Lidar.h"

Lidar::Lidar(){

}
 struct LidarData Lidar::getReading() {
     struct LidarData data;

     fileDescriptor = open("", O_RDWR | O_NOCTTY | O_NDELAY);
     if (fileDescriptor == -1) {
         std::cout << "Unable to open UART!" << std::endl;
     } else {
         fcntl(fileDescriptor, F_SETFL, 0);
         std::cout << "connected" << std::endl;

         speed_t baud = B115200;

         struct termios settings;
         tcgetattr(fileDescriptor, &settings);

         cfsetospeed(&settings, baud);
         settings.c_cflag &= ~PARENB;
         settings.c_cflag &= ~CSTOPB;
         settings.c_cflag &= ~CSIZE;

         tcsetattr(fileDescriptor, TCSANOW, &settings);
         tcflush(fileDescriptor, TCOFLUSH);
     }

     return data;
 }