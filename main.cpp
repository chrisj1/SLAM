#include <iostream>
#include "Roomba.h"
#include <QtGui>
#include <QtWidgets>
#include <QPushButton>
#include "PaintArea.h"

void configureRoomba() {
    Roomba *r = new Roomba("/dev/cu.usbserial-DA01NQY7");
    sleep(1);
    r->setSensorStream({BumpsWheelDrops, LeftEncoderCounts, RightEncoderCounts});
    sleep(1);
}

void createWindow(int argc, char* argv[]) {
    QApplication app(argc, argv);
    PaintArea area;
    area.show();
    area.setFixedSize(800, 800);
    app.exec();
}


int main(int argc, char *argv[]) {
    //configureRoomba();
    createWindow(argc, argv);
    return 0;
}