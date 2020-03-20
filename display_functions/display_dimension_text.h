#ifndef DISPLAY_DIMENSION_TEXT_H
#define DISPLAY_DIMENSION_TEXT_H
#include <QList>

class display_dimension_text
{
public:
    display_dimension_text(int i);
    void text_non_ortho(int i);
    void text_diameter(int i);
    void text_radius(int i);
    void text_angle_2p(int i);
    QList<double>offset_line(double p0x, double p0y, double p1x, double p1y, double offset, double rotate_degrees);
};

#endif // DISPLAY_DIMENSION_TEXT_H
