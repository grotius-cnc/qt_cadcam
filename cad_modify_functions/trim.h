#ifndef TRIM_H
#define TRIM_H

#include <QMainWindow>
#include <QList>

class trim
{
public:
    trim();
    void update_angles(int i);
    int side_d(double x0, double y0, double x1, double y1, double px, double py);
    void calculate_midpoint(int i);
    QList<double> rotate_point(double cx ,double cy, double angle, double x, double y);
    QList<double> line_midpoint(double x0, double y0, double x1, double y1);
};

#endif // TRIM_H
