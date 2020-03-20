#ifndef EXTEND_H
#define EXTEND_H

#include <QMainWindow>

class extend
{
public:
    extend();
    void calculate_midpoint(int i);
    void update_angles(int i);
    QList<double> rotate_point(double cx ,double cy, double angle, double x, double y);

};

#endif // EXTEND_H
