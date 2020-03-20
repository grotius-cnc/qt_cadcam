#include "preview_displacement_arc_stretch.h"
#include <core_functions/variables.h>
#include <display_functions/no_highlight.h>
#include <array_functions/emtpy_current_cad_counter.h>
#include <display_functions/object_select_line_startpoint.h>
#include <display_functions/object_select_line_midpoint.h>
#include <display_functions/object_select_line_endpoint.h>
#include <display_functions/object_select_line_perpendicular.h>
#include <display_functions/object_select_line_nearest.h>
#include <display_functions/object_select_line_tangent_arc.h>
#include <display_functions/object_select_line_tangent_circle.h>
#include <display_functions/object_select_centerpoint.h>
#include <display_functions/object_select_circle_4p_intersection.h>
#include <display_functions/object_select_circle_nearest.h>
#include <display_functions/object_select_arc_nearest.h>
#include <display_functions/color.h>
#include <display_functions/highlight.h>
#include <display_functions/linetype.h>

preview_displacement_arc_stretch::preview_displacement_arc_stretch(int i, bool startpoint, bool midpoint, bool endpoint, double dist_x, double dist_y, double dist_z)
{

    if(startpoint){
        X1 = double_cad_array[i][0] + dist_x;
        Y1 = double_cad_array[i][1] + dist_y;
        Z1 = double_cad_array[i][2] + dist_z;

        X2 = double_cad_array[i][15];
        Y2 = double_cad_array[i][16];
        Z2 = double_cad_array[i][17];

        X3 = double_cad_array[i][3];
        Y3 = double_cad_array[i][4];
        Z3 = double_cad_array[i][5];
    }

    if(midpoint){

    }

    if(endpoint){
        X1 = double_cad_array[i][0];
        Y1 = double_cad_array[i][1];
        Z1 = double_cad_array[i][2];

        X2 = double_cad_array[i][15];
        Y2 = double_cad_array[i][16];
        Z2 = double_cad_array[i][17];

        X3 = double_cad_array[i][3] + dist_x;
        Y3 = double_cad_array[i][4] + dist_y;
        Z3 = double_cad_array[i][5] + dist_z;
    }


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
            double_cad_array[i][11] = 180/M_PI*atan2(Y3-y_center, X3-x_center);    //start angle g2
            double_cad_array[i][12] = 180/M_PI*atan2(Y1-y_center, X1-x_center);    //end angle g2

            //calculate arc midpoint..
            double radian_start = atan2(Y3-y_center, X3-x_center); qDebug() << "radian_start : " << radian_start;
            double radian_end = atan2(Y1-y_center, X1-x_center);   qDebug() << "radian_end : " << radian_end;
            if (radian_end < radian_start){  //this to avoid the start angle is bigger then the end angle value
                radian_end += 2*M_PI;
            }
            double radian_mid = (radian_start+radian_end)/2;       qDebug() << "radian_mid : " << radian_mid;
            double rotate_x = cos(radian_mid)* radius - sin(radian_mid) * 0;
            double rotate_y = sin(radian_mid)* radius + cos(radian_mid) * 0;
            double_cad_array[i][15] = rotate_x + double_cad_array[i][6];//x_center..
            double_cad_array[i][16] = rotate_y + double_cad_array[i][7];//y_center..

        }

        if(d < 0){
            double_cad_array[i][11] = 180/M_PI*atan2(Y1-y_center, X1-x_center);    //start angle g3
            double_cad_array[i][12] = 180/M_PI*atan2(Y3-y_center, X3-x_center);    //end angle g3

            //calculate arc midpoint..
            double radian_start = atan2(Y1-y_center, X1-x_center); qDebug() << "radian_start : " << radian_start;
            double radian_end = atan2(Y3-y_center, X3-x_center);   qDebug() << "radian_end : " << radian_end;
            if (radian_end < radian_start){  //this to avoid the start angle is bigger then the end angle value
                radian_end += 2*M_PI;
            }
            double radian_mid = (radian_start+radian_end)/2;       qDebug() << "radian_mid : " << radian_mid;
            double rotate_x = cos(radian_mid)* radius - sin(radian_mid) * 0;
            double rotate_y = sin(radian_mid)* radius + cos(radian_mid) * 0;
            double_cad_array[i][15] = rotate_x + double_cad_array[i][6];//x_center..
            double_cad_array[i][16] = rotate_y + double_cad_array[i][7];//y_center..

        }
        if(d == 0){
            //draw a straight line..
        }
        //TODO : calculate arc midpoint...
    }
}
