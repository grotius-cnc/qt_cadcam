#include "cw_ccw.h"
#include <core_functions/variables.h>

cw_ccw::cw_ccw()
{
    // formula to find if polygon (contour) is cw or ccw..
    // (x2-x1)*(y2+y1)
    // point[0]=(5,0) edge[0]: (6-5)(4+0) = 4
    // point[1]=(6,4) edge[1]: (4-6)(5+4) = -18
    // point[2]=(4,5) edge[2]: (1-4)(5+5) = -30
    // point[3]=(1,5) edge[3]: (1-1)(0+5) = 0
    // point[4]=(1,0) edge[4]: (5-1)(0+0) = 0
    //                                   _____
    //                                sum = -44
    //if positive, cw..
    //if negative, ccw..
    //lets try this on our array's..


    //the rectangle test was confusing. The rectangle has to be rearranged in cw or ccw first..

    double sum = 0;

    for(int i=0; i<cad_counter; i++){

        if(i < cad_counter-1){
            sum += ( double_cad_array[i+1][0] - double_cad_array[i][0] ) * ( double_cad_array[i+1][1] + double_cad_array[i][1] );
            qDebug() << "point :" << i << " x : " << double_cad_array[i][0] << " y : " << double_cad_array[i][1];
        }

        //last point of the list connected to the first point on the list..
        if(i == cad_counter-1){
            sum += ( double_cad_array[0][0] - double_cad_array[i][0] ) * ( double_cad_array[0][1] + double_cad_array[i][1] );
            qDebug() << "point :" << i << " x : " << double_cad_array[i][0] << " y : " << double_cad_array[i][1];
        }

        //qDebug() << "i :" << i;
    }

    qDebug() << "sum :" << sum;
    mode_define_cw_ccw = 0;
}
