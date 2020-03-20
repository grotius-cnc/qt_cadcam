#ifndef POINT_IN_POLYGON_H
#define POINT_IN_POLYGON_H
#include <QVector>

class point_in_polygon
{
public:
    point_in_polygon(int object_id);

   int pip(int n, QVector<QVector<int>> pos, int x, int y);


};

#endif // POINT_IN_POLYGON_H
