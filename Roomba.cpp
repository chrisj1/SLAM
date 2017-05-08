#include "Roomba.h"

Roomba::Roomba(const string portname) : fileDescriptor(-1), portname(portname), sensorThread(NULL) {
    openSerialPort(portname);
    sendStart();
    setFullMode();
    usleep(1000);

    sensorThread = new thread(&Roomba::monitorSensors, this);
    cout << "created roomba" << endl;
}

void Roomba::setSensorStream(std::initializer_list<unsigned char> sensorsArg) {
    sensors = std::vector<Sensor>();
    size_t size = sensorsArg.size();
    unsigned char sensorsArray[size];
    int i = 0;
    for (auto elem : sensorsArg) {
        sensorsArray[i++] = elem;
        //cout << elem << endl;
        sensors.push_back(Sensor(elem));
        i++;
    }
    sendSensorStream();
    cout << "Set sensor stream" << endl;
}

void Roomba::sendSensorStream() {
    unsigned char commandSequence[sensors.size() + 2];
    commandSequence[0] = (unsigned char) 148;
    commandSequence[1] = static_cast<unsigned char>(sensors.size());

    for (int i = 0; i < sensors.size(); i++) {
        commandSequence[i + 2] = sensors[i];
    }
    writeCharArray(commandSequence, sensors.size() + 2);
    sleep(2);
}

/*
 * This command starts the OI. You must always send the Start command before sending any other
 * commands to the OI.
 * Serial sequence: [128].
 * Available in modes: Passive, Safe, or Full
 * Changes mode to: Passive. Roomba beeps once to acknowledge it is starting from “off” mode.
 * This command starts the OI. You must always send the Start command before sending any other
 * commands to the OI.
 * Serial sequence: [128].
 * Available in modes: Passive, Safe, or Full
 * Changes mode to: Passive. Roomba beeps once to acknowledge it is starting from “off” mode.
 */
const void Roomba::sendStart() {
    writeChar(131);
}

/*
 * This command starts the requested built-in demo.
 * Serial sequence: [136][Which-demo]
 * Available in modes: Passive, Safe, or Full
 * Changes mode to: Passive
 * Demo data byte 1: Demo number (-1 - 9)
 *
 * Identical to the Cover demo, with one exception. If Create sees an infrared
 * signal from an iRobot Home Base, it uses that signal to dock
 */
const void Roomba::seekDock() {
    unsigned char command[] = {
            DEMO_OPT_CODE, COVER_AND_DOCK_DEMO_CODE
    };
    writeCharArray(command, 2);
    sleep(1);
}

const void Roomba::powerOff() {
    writeChar(POWER_DOWN_OPT_CODE);
}

const void Roomba::setFullMode() {
    writeChar(FULL_OPT_CODE);
}

const void Roomba::setSafeMode() {
    writeChar(SAFE_OPT_CODE);
}

const void Roomba::setPassiveMode() {
    writeChar(PASSIVE_OPT_CODE);
}

const void Roomba::stop() {
    unsigned char stopArray[] = {
            145, 0, 0, 0, 0
    };

    writeCharArray(stopArray, 5);
}

const void Roomba::driveDirect(int right, int left) {
    unsigned char rHigh;
    unsigned char rLow;
    signedIntToTwoUnsignedChar(right, &rHigh, &rLow);

    unsigned char lHigh;
    unsigned char lLow;
    signedIntToTwoUnsignedChar(left, &lHigh, &lLow);

    unsigned char commands[] = {
            145, rHigh, rLow, lHigh, lLow
    };

    writeCharArray(commands, 5);
}

const void Roomba::drive(int velocity, int radius) {
    unsigned char vHigh;
    unsigned char vLow;
    signedIntToTwoUnsignedChar(velocity, &vHigh, &vLow);

    unsigned char rHigh;
    unsigned char rLow;
    signedIntToTwoUnsignedChar(radius, &rHigh, &rLow);

    unsigned char commands[] = {
            137, vHigh, vLow, rHigh, rLow
    };

    sleep(1);
}

const void Roomba::writeChar(const unsigned char command) {
    int n = write(fileDescriptor, (&command), 1);
    if (n < 0) {
        cerr << "Write failed!" << endl;
        disconnected();
        writeChar(command);
    }

}

const void Roomba::writeCharArray(const unsigned char commands[], int length) {
    for (int i = 0; i < length; i++) {
        writeChar(commands[i]);
    }
}

const void Roomba::openSerialPort(string portname) {
    const char *cString = portname.c_str();
    fileDescriptor = open(cString, O_RDWR | O_NOCTTY | O_NDELAY);
    if (fileDescriptor == -1) {
        cout << "Unable to open port!" << endl;
    } else {
        fcntl(fileDescriptor, F_SETFL, 0);
        cout << "connected" << endl;

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

    sleep(1);
}

const void Roomba::signedIntToTwoUnsignedChar(short speed, unsigned char *high, unsigned char *low) {
    *low = (unsigned char) (speed & 0xFF);
    *high = (unsigned char) ((speed >> 8) & 0xFF);
}

const void Roomba::reconnect() {
    openSerialPort(portname);
}

const void Roomba::disconnected() {
    while (fileDescriptor < 0) {
        cout << "Disconnected from roomba attempting to reconnect" << endl;
        reconnect();
        sleep(1);
    }
    sendStart();
    cout << "Reconnected to create" << endl;

}

const void Roomba::monitorSensors() {
    while (true) {
        unsigned char c[100];
        unsigned char *headerByte = 0;
        read(this->fileDescriptor, c, 100);
        unsigned char size = 0;
        headerByte = findHeader(c);
        if (headerByte == NULL || headerByte == 0) {
            //cerr << "No header" << endl;
            continue;
        }
        size = *(headerByte + 1);
        unsigned char checksum = *(headerByte + size + 2);
        unsigned int total = 0;
        //cout << "size: " << static_cast<int>(size) << endl;
        for (unsigned char *i = headerByte; i < headerByte + size + 2; i++) {
            total += *i;
        }
        total += checksum;

        if ((total & 0xFF)) {
            //cerr << "bad packet" << endl;
            continue;
        }

        if (headerByte != 0) {
            parseBytes(headerByte, size);
        }

        usleep(15000);
    }
}

unsigned char *Roomba::findHeader(unsigned char *c) const {
    unsigned char *headerByte = NULL;
    for (int i = 0; i < 10; i++) {
        if (c[i] == 0x0)
            continue;
        if (c[i] == 0x13) {
            headerByte = c + i;
        }

    }
    return headerByte;
}

void Roomba::parseBytes(const unsigned char *headerByte, unsigned char size) {
    for (unsigned char *elem = const_cast<unsigned char *>(headerByte + 2); elem < headerByte + size;) {
        try {
            //cout << "sensor: " << (int) *elem << endl;
            int databytes = DATA_BYTES.at(Sensor(static_cast<int>(*elem)));
            //cout << "sensor databytes: " << databytes << endl;
            //cout << "Enum: " << static_cast<Sensor>(*elem) << endl;
            switch (static_cast<Sensor>(*elem)) {
                case Distance:
                    //cout << "Distance" << endl;
                    parseDistance(elem + 1);
                    break;
                case Angle:
                    //cout << "Angle" << endl;
                    parseAngle(elem + 1);
                    break;
                case LeftEncoderCounts:
                    //cout << "Left" << endl;
                    parseLeftEncoderCounts(elem + 1);
                    break;
                case RightEncoderCounts:
                    //parseRightEncoderCounts(elem + 1);
                    //cout << "Right" << endl;
                    break;
                case BumpsWheelDrops:
                    //cout << "Bump and Wheel" << endl;
                    parseBumpAndWheelDrop(elem + 1);
                    break;
            }

            elem += databytes + 1;
        } catch (std::out_of_range e) {
            cerr << "Tried to read out of range map value" << endl;
            return;
        }
    }
}

void Roomba::parseDistance(unsigned char *elem) {

}


void Roomba::parseAngle(const unsigned char *elem) {

}


void Roomba::parseLeftEncoderCounts(const unsigned char *elem) {

}


void Roomba::parseRightEncoderCounts(const unsigned char *elem) {

}


Roomba::~Roomba() {
    sensorThread->join();
    delete sensorThread;
}

void printChar(char c) {
    for (int i = 0; i < 8; i++) {
        printf("%d", ((c << i) & 0x80));
    }
}

const void Roomba::driveFor(int right, int left, int time) {
    driveDirect(right, left);
    usleep(time);
    stop();
}

const void Roomba::beep() {
    unsigned char commands[] = {140, 3, 7, 81, 12, 81, 12, 71, 12, 74, 16, 74, 20, 79, 19, 79, 16, 141, 3};
    writeCharArray(commands, 19);
}

void Roomba::parseBumpAndWheelDrop(unsigned char *byte) {

    //printf("0x%x\n", *byte);

    if (*byte >> 4 & 0b1111)
        return;

    bumpRight = static_cast<bool>(*(byte) & 0b0001);
    bumpLeft = static_cast<bool>(*(byte) & 0b0010);
    rightWheelDrop = static_cast<bool>(*(byte) & 0b0100);
    leftWheelDrop = static_cast<bool>(*(byte) & 0b1000);


    cout << "br:" << bumpRight << " bl" << bumpLeft << " rw: " << rightWheelDrop << " lw" << leftWheelDrop << endl;
}
