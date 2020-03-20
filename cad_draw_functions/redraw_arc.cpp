#include "redraw_arc.h"
#include <core_functions/variables.h>

redraw_arc::redraw_arc(int i) //to get new start and new end angle..
{
    X1 = double_cad_array[i][0];
    Y1 = double_cad_array[i][1];

    X2 = double_cad_array[i][15];
    Y2 = double_cad_array[i][16];

    X3 = double_cad_array[i][3];
    Y3 = double_cad_array[i][4];


    //calculate 3 point circle... calculate xy center and radius..
    // Get the perpendicular bisector of (x1, y1) and (x2, y2).
    double x1 = (X2 + X1) / 2;
    double y1 = (Y2 + Y1) / 2;
    double dy1 = X2 - X1;
    double dx1 = -(Y2 - Y1);

    // Get the perpendicular bisector of (x2, y2) and (x3, y3).
    double x2 = (X3 + X2) / 2;
    double y2 = (Y3 + Y2) / 2;
    double dy2 = X3 - X2;
    double dx2 = -(Y3 - Y2);

    double endpoint_x0 = x1 + dx1;
    double endpoint_y0 = y1 + dy1;
    double endpoint_x1 = x2 + dx2;
    double endpoint_y1 = y2 + dy2;

    //line 1
    double delta_y0 = endpoint_y0 - y1;
    double delta_x0 = x1 - endpoint_x0;
    double c0 = delta_y0 * x1 + delta_x0 * y1;
    //line 2
    double delta_y1 = endpoint_y1 - y2;
    double delta_x1 = x2 - endpoint_x1;
    double c1 = delta_y1 * x2 + delta_x1 * y2;

    double determinant = delta_y0*delta_x1 - delta_y1*delta_x0;
    //qDebug() << "determinant is : " << determinant;

    if (determinant == 0) // The lines are parallel.
    {
        //qDebug() << "the lines are parallel";
    }
    else  {
        double x_center = (delta_x1*c0 - delta_x0*c1)/determinant;
        double y_center = (delta_y0*c1 - delta_y1*c0)/determinant;
        double dx = x_center - X1;
        double dy = y_center - Y1;
        double radius = sqrt(dx * dx + dy * dy);
        //qDebug() << " intersection point is x : " << x_center << " y : " << y_center << " radius : " << radius;

        double_cad_array[i][6] = x_center;
        double_cad_array[i][7] = y_center;
        double_cad_array[i][9] = radius;

        //formula if arc is cw or ccw.. this is nice..
        //To determine which side of the line from A=(x1,y1) to B=(x2,y2) a point P=(x,y) falls on you need to compute the value:-
        //d=(x−x1)(y2−y1)−(y−y1)(x2−x1)
        //If d<0 then the point lies on one side of the line, and if d>0 then it lies on the other side. If d=0 then the point lies exactly line.

        double xp = X3;
        double yp = Y3;
        double x1 = X1;
        double y1 = Y1;
        double x2 = X2;
        double y2 = Y2;

        double d = ((xp-x1)*(y2-y1))-((yp-y1)*(x2-x1));
        //qDebug() << "d :" << d;

        if(d > 0){
            double_cad_array[i][11] = 180/M_PI*atan2(Y3-y_center, X3-x_center);    //start angle G2
            double_cad_array[i][12] = 180/M_PI*atan2(Y1-y_center, X1-x_center);    //end angle G2

            //if(double_cad_array[cad_counter][12]==360){double_cad_array[cad_counter][12]=0;}

            //calculate arc midpoint..
            double radian_start = atan2(Y3-y_center, X3-x_center); //qDebug() << "radian_start : " << radian_start;
            double radian_end = atan2(Y1-y_center, X1-x_center);   //qDebug() << "radian_end : " << radian_end;
            if (radian_end < radian_start){  //this to avoid the start angle is bigger then the end angle value
                radian_end += 2*M_PI;
            }
            double radian_mid = (radian_start+radian_end)/2;       //qDebug() << "radian_mid : " << radian_mid;
            double rotate_x = cos(radian_mid)* radius - sin(radian_mid) * 0;
            double rotate_y = sin(radian_mid)* radius + cos(radian_mid) * 0;
            double_cad_array[i][15] = rotate_x + double_cad_array[i][6];//x_center..
            double_cad_array[i][16] = rotate_y + double_cad_array[i][7];//y_center..
        }

        if(d < 0){
            double_cad_array[i][11] = 180/M_PI*atan2(Y1-y_center, X1-x_center);    //start angle G3
            double_cad_array[i][12] = 180/M_PI*atan2(Y3-y_center, X3-x_center);    //end angle G3

            //if(double_cad_array[cad_counter][12]==360){double_cad_array[cad_counter][12]=0;}

            //calculate arc midpoint..
            double radian_start = atan2(Y1-y_center, X1-x_center); //qDebug() << "radian_start : " << radian_start;
            double radian_end = atan2(Y3-y_center, X3-x_center);   //qDebug() << "radian_end : " << radian_end;
            if (radian_end < radian_start){  //this to avoid the start angle is bigger then the end angle value
                radian_end += 2*M_PI;
            }
            double radian_mid = (radian_start+radian_end)/2;       //qDebug() << "radian_mid : " << radian_mid;
            double rotate_x = cos(radian_mid)* radius - sin(radian_mid) * 0;
            double rotate_y = sin(radian_mid)* radius + cos(radian_mid) * 0;
            double_cad_array[i][15] = rotate_x + double_cad_array[i][6];//x_center..
            double_cad_array[i][16] = rotate_y + double_cad_array[i][7];//y_center..
        }
        if(d == 0){
            //draw a straight line..
        }
    }
}
