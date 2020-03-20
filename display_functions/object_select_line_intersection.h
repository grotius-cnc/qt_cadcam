#ifndef OBJECT_SELECT_LINE_INTERSECTION_H
#define OBJECT_SELECT_LINE_INTERSECTION_H
#include <QList>

class object_select_line_intersection
{
public:
    object_select_line_intersection();
    QList<int> line_nearest();
    QList<int> arc_nearest();
    QList<double> line_line_intersection_by_id(int id_1, int id_2);
    QList<double> line_arc_intersection_by_id(int id_1, int id_2);
};

#endif // OBJECT_SELECT_LINE_INTERSECTION_H
