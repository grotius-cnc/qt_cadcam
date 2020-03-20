#include "triangle_array.h"
#include <core_functions/variables.h>
#define myqDebug() qDebug() << fixed << qSetRealNumberPrecision(3)

triangle_array::triangle_array()
{
    myqDebug()  << "\n"
                << "Grotius 2019 Triangle Array Analys\n\n"
                << "- Parallel Multidimensional Arrays\n"
                << "- Data Input External Variables\n"
                << "- Used For Cad Cam Processing\n";

    //out.setRealNumberNotation(QTextStream::FixedNotation);

    for (int i=0 ; i < triangle_counter; i++) {
    myqDebug()  << "\t" << "arrayline           "   << "\t"       << i/3                            <<"\n"
                << "\t" << "dxf integer parameters : "                                              <<"\n"
                << "\t" << "color                 "   << "\t"     << int_triangle_array[i][0]       <<"\n"
                << "\t" << "color                 "   << "\t"     << int_triangle_array[i+1][0]     <<"\n"
                << "\t" << "color                 "   << "\t"     << int_triangle_array[i+2][0]     <<"\n"
                << "\t" << "a.x                   "   << "\t"     << double_triangle_array[i][0]    <<"\n"
                << "\t" << "a.y                   "   << "\t"     << double_triangle_array[i][1]    <<"\n"
                << "\t" << "b.x                   "   << "\t"     << double_triangle_array[i+1][0]  <<"\n"
                << "\t" << "b.y                   "   << "\t"     << double_triangle_array[i+1][1]  <<"\n"
                << "\t" << "c.x                   "   << "\t"     << double_triangle_array[i+2][0]  <<"\n"
                << "\t" << "c.y                   "   << "\t"     << double_triangle_array[i+2][1]  <<"\n";

    }
}
