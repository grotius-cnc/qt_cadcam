#ifndef DIMENSION_H
#define DIMENSION_H
#include <QString>

class dimension
{
public:
    dimension();

    QList<double>offset_line_by_points_to_side(double p0x, double p0y, double p1x, double p1y, double offset, double side_px, double side_py);
    QList<double>offset_line_by_id_to_side(int id, double offset, double side_px, double side_py);
    QList<double>draw_3p_arc(double p0x, double p0y, double p1x, double p1y, double p2x, double p2y);
    QList<double>offset_line(double p0x, double p0y, double p1x, double p1y, double offset, double rotate_degrees);
    QList<double>mirror_point(double p0x, double p0y, double p1x, double p1y, double px, double py);
    QList<double>offset_point_on_line(double p0x, double p0y, double p1x, double p1y, double offset);
    QList<double>line_line_intersection_by_points(double p0x, double p0y, double p1x, double p1y, double p2x, double p2y, double p3x, double p3y);
    QList<double>line_line_intersection_by_id(int id1, int id2);
    QList<double>circle_line_intersection_by_points(double cpx, double cpy, double radius, double p0x, double p0y, double p1x, double p1y);
};

#endif // DIMENSION_H
