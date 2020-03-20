#ifndef TRIANGULATION_H
#define TRIANGULATION_H

#include <QMainWindow>
#include <poly2tri.h>
#include <math.h>
#include <stdio.h>
#include <iterator>

class triangulation
{
public:
    triangulation(int id_outside, QVector<int> id_inside, bool outside, bool inside);

    std::vector<p2t::Point*> outside_contour;
    std::vector<p2t::Point*> inside_contour;
    std::vector<p2t::Triangle*> triangles; //one triangle..
    std::list<p2t::Triangle*> map; //array of triangles..
    QVector<int>::iterator it;

};

#endif // TRIANGULATION_H
