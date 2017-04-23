//
// Created by Chris Jerrett on 4/23/17.
//

#include "PaintArea.h"

PaintArea::PaintArea():QWidget(){
    QPalette pal;
    pal.setColor(QPalette::Background, Qt::black);
    setPalette(pal);
    QTimer *timer = new QTimer(this);
    timer->start(10);
    connect(timer,SIGNAL(timeout()),this,SLOT(update()));
    std::cout << timer << std::endl;
}


void PaintArea::paintEvent(QPaintEvent *event) {
    static std::map<int, int> map;
    QPainter painter(this);
    painter.setPen(QPen(Qt::red, 2, Qt::SolidLine, Qt::FlatCap));
    static int theta = 0;
    double x = 400 + (sin(to_radians(theta)) * 400);
    double y = 400 + (cos(to_radians(theta)) * 400);
    theta += 2;
    theta %= 360;
    painter.drawLine(400, 400, x, y);
    painter.drawEllipse(385, 385 ,30, 30);
    static int r = 300;
    r  += 10 * (-1 + static_cast <double> (rand()) /( static_cast <double> (RAND_MAX/(2))));

    if(map.count(theta)) {
        int oldr = map[theta];
        r = oldr + (2 * (-1 + static_cast <double> (rand()) /( static_cast <double> (RAND_MAX/(2)))));
    } else {
        r += (10 * (-1 + static_cast <double> (rand()) /( static_cast <double> (RAND_MAX/(2)))));
    }
    r = max(50, r);
    map[theta] = r;

    painter.drawText(5, 20, QString(("Magnitude " + std::to_string(r)).c_str()));
    painter.drawText(5, 40, QString(("Theta: " + std::to_string(theta)).c_str()));

    for (auto& dataSample: map) {

        int mag = dataSample.second;
        int t = dataSample.first;
        int p_x;
        int p_y;
        dataToPointOnScreeen(mag, t, p_x, p_y);
        painter.drawEllipse((p_x-3), (p_y-3), 6, 6);

        QPen pen(Qt::blue, 5);
        painter.setPen(pen);
        QBrush brush(Qt::blue);
        painter.setBrush(brush);

        painter.drawEllipse((p_x-3), (p_y-3), 6, 6);


    }
    std::cout << theta << std::endl;

}

void PaintArea::dataToPointOnScreeen(int mag, int t, int &p_x, int &p_y) const {
    p_x= 400 + static_cast<int>((mag * sin(to_radians(t))));
    p_y= 400 + static_cast<int>((mag * cos(to_radians(t))));
}