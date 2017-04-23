//
// Created by Chris Jerrett on 4/23/17.
//

#ifndef SLAM_PAINTAREA_H
#define SLAM_PAINTAREA_H

#include <QWidget>
#include <QPainter>
#include <iostream>
#include <cmath>
#include <QTimer>
#include <map>

#include "Calculations.cpp"

class PaintArea: public QWidget {

public:
    PaintArea();
protected:
    void paintEvent(QPaintEvent *event);

private slots:
    void dataToPointOnScreeen(int mag, int t, int &p_x, int &p_y) const;
};


#endif //SLAM_PAINTAREA_H
