#include "ellipse.h"
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

ellipse::ellipse()
{
    //initialiation..
    snap_cad_pos_x = mouse_cad_pos_x;
    snap_cad_pos_y = mouse_cad_pos_y;
    snap_cad_pos_z = mouse_cad_pos_z;

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
        messagebox_text = "<b><i>mode ellipse </i></b> click first point base line";
    }

    if(click == 1){
        //qDebug() << "click = 1";
        messagebox_text = "<b><i>mode ellipse </i></b> click second point base line";

        //initialize ellipse
        int_cad_array[cad_counter][0] = 4; //id = ellipse
        //int_cad_array[cad_counter][1] = current_gui_color; //color white
        double_cad_array[cad_counter][56] = current_gui_color_red_gl;
        double_cad_array[cad_counter][57] = current_gui_color_green_gl;
        double_cad_array[cad_counter][58] = current_gui_color_blue_gl;
        double_cad_array[cad_counter][59] = current_gui_color_alpha_gl;

        int_cad_array[cad_counter][5] = current_linetype;
        double_cad_array[cad_counter][18] = current_linetype_scale;
        double_cad_array[cad_counter][19] = current_linewidth;

        //ellipse left point
        double_cad_array[cad_counter][0] = snap_cad_pos_x;
        double_cad_array[cad_counter][1] = snap_cad_pos_y;
        double_cad_array[cad_counter][2] = snap_cad_pos_z;

        click = 2;

    }

    if(click == 2){
        //preview

        //ellipse center point
        double_cad_array[cad_counter][6] = (double_cad_array[cad_counter][0] + snap_cad_pos_x)/2;
        double_cad_array[cad_counter][7] = (double_cad_array[cad_counter][1] + snap_cad_pos_y)/2;
        double_cad_array[cad_counter][8] = (double_cad_array[cad_counter][2] + snap_cad_pos_z)/2;

        double cx = double_cad_array[cad_counter][6];
        double cy = double_cad_array[cad_counter][7];
        double px_right = snap_cad_pos_x; //right side of ellipse.. array 28+29??
        double py_right = snap_cad_pos_y;
        double rx = sqrt(pow(px_right-cx,2)+pow(py_right-cy,2));

        //ellipse radius x..
        double_cad_array[cad_counter][9] = rx;

        //ellipse angle..
        double angle = atan2(py_right - cy, px_right - cx)* 180.0 / M_PI;
        qDebug() << "ellipse angle is : " << angle;
        double_cad_array[cad_counter][11] = angle;
        //qDebug() << "angle : " << angle;

        double_cad_array[cad_counter][3] = px_right;
        double_cad_array[cad_counter][4] = py_right;

    }

    if(click == 3){
        messagebox_text = "<b><i>mode ellipse </i></b> click ellipse top point";

        //ellipse radius y..
        double cx = double_cad_array[cad_counter][6];
        double cy = double_cad_array[cad_counter][7];
        double px_top = snap_cad_pos_x;
        double py_top = snap_cad_pos_y;

        double ry = sqrt(pow(px_top-cx,2)+pow(py_top-cy,2));
        double_cad_array[cad_counter][10] = ry;

    }

    if(click == 4){
        //write data..
        #define DEG2RAD M_PI/180;

        //radius x, radius y..
        double cx = double_cad_array[cad_counter][6];
        double cy = double_cad_array[cad_counter][7];
        double rx = double_cad_array[cad_counter][9];
        double ry = double_cad_array[cad_counter][10];
        double angle = double_cad_array[cad_counter][11];
        double rad, non_rotated_x, non_rotated_y, px, py;

        //write ellipse left intersection point to array..
        rad = 180*DEG2RAD;
        non_rotated_x = cos(rad)*rx;
        non_rotated_y = sin(rad)*ry;
        px = cx  + cos(angle * M_PI / 180.0 )* non_rotated_x - sin(angle * M_PI / 180.0 ) * non_rotated_y;
        py = cy  + sin(angle * M_PI / 180.0 )* non_rotated_x + cos(angle * M_PI / 180.0 ) * non_rotated_y;
        double_cad_array[cad_counter][25] = px;
        double_cad_array[cad_counter][26] = py;
        //double Ax = px;
        //double Ay = py;

        //write ellipse right intersection point to array..
        rad = 0*DEG2RAD;
        non_rotated_x = cos(rad)*rx;
        non_rotated_y = sin(rad)*ry;
        px = cx  + cos(angle * M_PI / 180.0 )* non_rotated_x - sin(angle * M_PI / 180.0 ) * non_rotated_y;
        py = cy  + sin(angle * M_PI / 180.0 )* non_rotated_x + cos(angle * M_PI / 180.0 ) * non_rotated_y;
        double_cad_array[cad_counter][28] = px;
        double_cad_array[cad_counter][29] = py;
        //double Bx = py;
        //double By = py;

        //write ellipse top intersection point to array..
        rad = 90*DEG2RAD;
        non_rotated_x = cos(rad)*rx;
        non_rotated_y = sin(rad)*ry;
        px = cx  + cos(angle * M_PI / 180.0 )* non_rotated_x - sin(angle * M_PI / 180.0 ) * non_rotated_y;
        py = cy  + sin(angle * M_PI / 180.0 )* non_rotated_x + cos(angle * M_PI / 180.0 ) * non_rotated_y;
        double_cad_array[cad_counter][31] = px;
        double_cad_array[cad_counter][32] = py;
        //double Px_top = px;
        //double Py_top = py;

        //write ellipse bottom intersection point to array..
        rad = 270*DEG2RAD;
        non_rotated_x = cos(rad)*rx;
        non_rotated_y = sin(rad)*ry;
        px = cx  + cos(angle * M_PI / 180.0 )* non_rotated_x - sin(angle * M_PI / 180.0 ) * non_rotated_y;
        py = cy  + sin(angle * M_PI / 180.0 )* non_rotated_x + cos(angle * M_PI / 180.0 ) * non_rotated_y;
        double_cad_array[cad_counter][34] = px;
        double_cad_array[cad_counter][35] = py;

        //write F0 and F1 FOCUS points..
        double AB = sqrt( pow(( double_cad_array[cad_counter][3] - double_cad_array[cad_counter][0]),2) + pow(( double_cad_array[cad_counter][4] -  double_cad_array[cad_counter][1]),2));     //qDebug() << "AB : " << AB;  //ellipse base line lenght..

        //calculate static FOCUS point's, line => circle intersection
        double circle_center_x = double_cad_array[cad_counter][31];
        double circle_center_y = double_cad_array[cad_counter][32];
        double radius = AB/2;                   //intersection F line AB

        double start_line_x1 = double_cad_array[cad_counter][25];
        double start_line_y1 = double_cad_array[cad_counter][26];
        double end_line_x2 = double_cad_array[cad_counter][28];
        double end_line_y2 = double_cad_array[cad_counter][29];

        double dx, dy, A, B, C, det, t;

        dx = end_line_x2 - start_line_x1;
        dy = end_line_y2 - start_line_y1;

        A = dx * dx + dy * dy;
        B = 2 * (dx * (start_line_x1 - circle_center_x) + dy * (start_line_y1 - circle_center_y));
        C = (start_line_x1 - circle_center_x) * (start_line_x1 - circle_center_x) + (start_line_y1 - circle_center_y) * (start_line_y1 - circle_center_y) - radius * radius;

        det = B * B - 4 * A * C;

        t = (-B + sqrt(det)) / (2 * A);
        double intersection_x1 = (start_line_x1 + t * dx); //right F0 = center point
        double intersection_y1 = (start_line_y1 + t * dy);

        t = (-B - sqrt(det)) / (2 * A);
        double intersection_x2 = (start_line_x1 + t * dx); //left F0 = center point
        double intersection_y2 = (start_line_y1 + t * dy);

        double_cad_array[cad_counter][40] = intersection_x1; //Fx_right (ellips focus)
        double_cad_array[cad_counter][41] = intersection_y1; //Fy_right
        double_cad_array[cad_counter][42] = intersection_x2; //Fx_left  (ellips focus)
        double_cad_array[cad_counter][43] = intersection_y2; //Fy_left
        double_cad_array[cad_counter][44] = AB;              //ellipse base line lenght..

//        //preview the 2 F points..
//        glColor3f(0.0f, 0.0f, 1.0f);        //blue
//        glBegin(GL_LINES);
//        //first cross
//        glVertex3d(intersection_x1-snap_dist, intersection_y1-snap_dist, snap_cad_pos_z);  //xyz start
//        glVertex3d(intersection_x1+snap_dist, intersection_y1+snap_dist, snap_cad_pos_z);  //xyz start
//        glVertex3d(intersection_x1-snap_dist, intersection_y1+snap_dist, snap_cad_pos_z);  //xyz start
//        glVertex3d(intersection_x1+snap_dist, intersection_y1-snap_dist, snap_cad_pos_z);  //xyz start
//        //second cross
//        glVertex3d(intersection_x2-snap_dist, intersection_y2-snap_dist, snap_cad_pos_z);  //xyz start
//        glVertex3d(intersection_x2+snap_dist, intersection_y2+snap_dist, snap_cad_pos_z);  //xyz start
//        glVertex3d(intersection_x2-snap_dist, intersection_y2+snap_dist, snap_cad_pos_z);  //xyz start
//        glVertex3d(intersection_x2+snap_dist, intersection_y2-snap_dist, snap_cad_pos_z);  //xyz start
//        glEnd();

        cad_counter++;
        click = 0;
        mode_ellipse = 0;
        no_selection();
        messagebox_text = "<b><i>mode ellipse </i></b> enter for repeat or Esc for cancel";
    }
}






































