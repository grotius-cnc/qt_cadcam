#include "arc.h"
#include <core_functions/variables.h>
#include <array_functions/emtpy_current_cad_counter.h>
#include <display_functions/no_selection.h>
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
#include <display_functions/object_select_ellipse_nearest.h>
#include <display_functions/object_select_hermite_spline_nearest.h>
#include <display_functions/object_select_bezier_curve_nearest.h>
#include <array_functions/restore_undo_array.h>
#include <cad_draw_functions/keyboard_startpoint.h>
#include <cad_draw_functions/keyboard_endpoint.h>
#include <display_functions/object_select_line_intersection.h>

arc::arc()
{
    //initialiation..
    snap_cad_pos_x = mouse_cad_pos_x;
    snap_cad_pos_y = mouse_cad_pos_y;
    snap_cad_pos_z = 0;

    //overwrite initialisation if we spot a snap somewhere..
    if(mode_snap_intersection){
        object_select_line_intersection();
    }
    if(mode_endpoint){
        object_select_line_startpoint();
        object_select_line_endpoint();
    }
    if(mode_midpoint){
        object_select_line_midpoint();
    }
    if(mode_centerpoint){
        object_select_centerpoint();
    }
    if(mode_perpendicular){
        object_select_line_perpendicular();
    }
    if(mode_snap_circle_4p){
        object_select_circle_4p_intersection();
    }
    if(mode_tangent){
        object_select_line_tangent_arc();
        object_select_line_tangent_circle();
    }
    if(mode_nearest){
        object_select_line_nearest(1);
        object_select_arc_nearest(1);
        object_select_circle_nearest(1);
        object_select_ellipse_nearest(1);
        object_select_hermite_spline_nearest(1);
        object_select_bezier_curve_nearest(1);
    }

    if(click == 0){
        messagebox_text = "<b><i>mode arc </i></b> click first arc point";
    }

    if(click == 1){
        messagebox_text = "<b><i>mode arc </i></b> click second arc point";
        //start as line preview....
        int_cad_array[cad_counter][0] = 3; //id arc
        double_cad_array[cad_counter][56] = current_gui_color_red_gl;
        double_cad_array[cad_counter][57] = current_gui_color_green_gl;
        double_cad_array[cad_counter][58] = current_gui_color_blue_gl;
        double_cad_array[cad_counter][59] = current_gui_color_alpha_gl;

        int_cad_array[cad_counter][5] = current_linetype;
        double_cad_array[cad_counter][18] = current_linetype_scale;
        double_cad_array[cad_counter][19] = current_linewidth;

        double_cad_array[cad_counter][0] = snap_cad_pos_x;
        double_cad_array[cad_counter][1] = snap_cad_pos_y;
        double_cad_array[cad_counter][2] = 0;
        double_cad_array[cad_counter][3] = snap_cad_pos_x;
        double_cad_array[cad_counter][4] = snap_cad_pos_y;
        double_cad_array[cad_counter][5] = 0;

        X1 = snap_cad_pos_x;
        Y1 = snap_cad_pos_y;
        click = 2;
    }

    if(click == 2){
        //temponairy line preview endpoint..
        double_cad_array[cad_counter][3] = snap_cad_pos_x;
        double_cad_array[cad_counter][4] = snap_cad_pos_y;

        //temponairy line preview.
        glBegin(GL_LINES);
        glVertex3d(double_cad_array[cad_counter][0], double_cad_array[cad_counter][1], double_cad_array[cad_counter][2]);  //xyz start
        glVertex3d(double_cad_array[cad_counter][3], double_cad_array[cad_counter][4], double_cad_array[cad_counter][5]);  //xyz end
        glEnd();

        X2 = snap_cad_pos_x;
        Y2 = snap_cad_pos_y;
    }

    if(click == 3){

        messagebox_text = "<b><i>mode arc </i></b> click last arc point";
        X3 = snap_cad_pos_x;
        Y3 = snap_cad_pos_y;
        //qDebug() << "thirth point x : " << mouse_cad_pos_x << " y : " << mouse_cad_pos_y;

        //write final arc endpoint..
        double_cad_array[cad_counter][3] = X3;
        double_cad_array[cad_counter][4] = Y3;
        //double_cad_array[cad_counter][5] = Z3;

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

            double_cad_array[cad_counter][6] = x_center;
            double_cad_array[cad_counter][7] = y_center;
            double_cad_array[cad_counter][9] = radius;

            //formula if arc is cw or ccw.. this is nice..
            //To determine which side of the line from A=(x1,y1) to B=(x2,y2) a point P=(x,y) falls on you need to compute the value:-
            //d=(x−x1)(y2−y1)−(y−y1)(x2−x1)
            //If d<0 then the point lies on one side of the line, and if d>0 then it lies on the other side. If d=0 then the point lies exactly line.

            double xp = snap_cad_pos_x;
            double yp = snap_cad_pos_y;
            double x1 = X1;
            double y1 = Y1;
            double x2 = X2;
            double y2 = Y2;

            double d = ((xp-x1)*(y2-y1))-((yp-y1)*(x2-x1));
            //qDebug() << "d :" << d;

            if(d > 0){
                double_cad_array[cad_counter][11] = 180/M_PI*atan2(Y3-y_center, X3-x_center);    //start angle G2
                double_cad_array[cad_counter][12] = 180/M_PI*atan2(Y1-y_center, X1-x_center);    //end angle G2

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
                double_cad_array[cad_counter][15] = rotate_x + double_cad_array[cad_counter][6];//x_center..
                double_cad_array[cad_counter][16] = rotate_y + double_cad_array[cad_counter][7];//y_center..
            }

            if(d < 0){
                double_cad_array[cad_counter][11] = 180/M_PI*atan2(Y1-y_center, X1-x_center);    //start angle G3
                double_cad_array[cad_counter][12] = 180/M_PI*atan2(Y3-y_center, X3-x_center);    //end angle G3

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
                double_cad_array[cad_counter][15] = rotate_x + double_cad_array[cad_counter][6];//x_center..
                double_cad_array[cad_counter][16] = rotate_y + double_cad_array[cad_counter][7];//y_center..
            }
            if(d == 0){
                //draw a straight line..
            }
        }
    }

    if(click == 4){
        cad_counter++;
        click = 0;
        mode_arc = 0;
        no_selection();
        messagebox_text = "<b><i>mode arc </i></b> enter for repeat or Esc for cancel";






    }
}












