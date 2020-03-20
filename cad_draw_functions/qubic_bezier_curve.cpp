#include "cubic_bezier_curve.h"
#include <math.h>
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

cubic_bezier_curve::cubic_bezier_curve()
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
        messagebox_text = "<b><i>mode cubic bezier curve </i></b> click first point";
    }

    //click the control points..
    if(click == 1){
        messagebox_text = "<b><i>mode cubic bezier curve </i></b> click next control point";

        //int_cad_array[cad_counter][1] = current_gui_color; //color white
        double_cad_array[cad_counter][56] = current_gui_color_red_gl;
        double_cad_array[cad_counter][57] = current_gui_color_green_gl;
        double_cad_array[cad_counter][58] = current_gui_color_blue_gl;
        double_cad_array[cad_counter][59] = current_gui_color_alpha_gl;

        int_cad_array[cad_counter][5] = current_linetype;
        double_cad_array[cad_counter][18] = current_linetype_scale;
        double_cad_array[cad_counter][19] = current_linewidth;

        double_cad_array[cad_counter][0] = snap_cad_pos_x;
        double_cad_array[cad_counter][1] = snap_cad_pos_y;
        double_cad_array[cad_counter][2] = snap_cad_pos_z;

        //Ax = snap_cad_pos_x;  qDebug() << "Ax : " << Ax;
        //Ay = snap_cad_pos_y;  qDebug() << "Ay : " << Ay;
        //Az = snap_cad_pos_z;  qDebug() << "Az : " << Az;

        click = 2;
    }

    if(click == 2){

        glBegin(GL_LINE_STRIP);

        for(double t = 0; t < 1; t+=0.001){
            //qDebug() << "t = " << t;

            //start point A..
            Ax = double_cad_array[cad_counter][0];
            Ay = double_cad_array[cad_counter][1];
            Az = double_cad_array[cad_counter][2];

            //control point B..
            Bx = snap_cad_pos_x;
            By = snap_cad_pos_y;
            Bz = snap_cad_pos_z;

            //control point C..
            Cx = snap_cad_pos_x;
            Cy = snap_cad_pos_y;
            Cz = snap_cad_pos_z;

            //end point D..
            Dx = snap_cad_pos_x;
            Dy = snap_cad_pos_y;
            Dz = snap_cad_pos_z;

            //at this stage we have defined all the points and de lines of the cubic bezier curve..
            //Calculate Point E, on the line AB
            double Ex = ((1-t) * Ax) + (t * Bx);
            double Ey = ((1-t) * Ay) + (t * By);
            double Ez = ((1-t) * Az) + (t * Bz);

            //Calculate Point F, on the line BC
            double Fx = ((1-t) * Bx) + (t * Cx);
            double Fy = ((1-t) * By) + (t * Cy);
            double Fz = ((1-t) * Bz) + (t * Cz);

            //Calculate Point G, on the line CD
            double Gx = ((1-t) * Cx) + (t * Dx);
            double Gy = ((1-t) * Cy) + (t * Dy);
            double Gz = ((1-t) * Cz) + (t * Dz);

            //Calculate Point Q, on the line EF
            double Qx = ((1-t) * Ex) + (t * Fx);
            double Qy = ((1-t) * Ey) + (t * Fy);
            double Qz = ((1-t) * Ez) + (t * Fz);

            //Calculate Point R, on the line FG
            double Rx = ((1-t) * Fx) + (t * Gx);
            double Ry = ((1-t) * Fy) + (t * Gy);
            double Rz = ((1-t) * Fz) + (t * Gz);

            //Calculate Point P, on the line QR
            double Px = ((1-t) * Qx) + (t * Rx);
            double Py = ((1-t) * Qy) + (t * Ry);
            double Pz = ((1-t) * Qz) + (t * Rz);

            glVertex3d(Px, Py, Pz);  //draw linestrip..
        }
        glEnd();

    }

    if(click == 3){
        //Bx = snap_cad_pos_x;  qDebug() << "Bx : " << Bx;
        //By = snap_cad_pos_y;  qDebug() << "By : " << By;
        //Bz = snap_cad_pos_z;  qDebug() << "Bz : " << Bz;

        double_cad_array[cad_counter][50] = snap_cad_pos_x;
        double_cad_array[cad_counter][51] = snap_cad_pos_y;
        double_cad_array[cad_counter][52] = snap_cad_pos_z;

        click = 4;
    }

    if(click == 4){

        glBegin(GL_LINE_STRIP);

        for(double t = 0; t < 1; t+=0.001){
            //qDebug() << "t = " << t;

            //start point A..
            Ax = double_cad_array[cad_counter][0];
            Ay = double_cad_array[cad_counter][1];
            Az = double_cad_array[cad_counter][2];

            //control point B..
            Bx = double_cad_array[cad_counter][50];
            By = double_cad_array[cad_counter][51];
            Bz = double_cad_array[cad_counter][52];

            //control point C..
            Cx = snap_cad_pos_x;
            Cy = snap_cad_pos_y;
            Cz = snap_cad_pos_z;

            //end point D..
            Dx = snap_cad_pos_x;
            Dy = snap_cad_pos_y;
            Dz = snap_cad_pos_z;

            //at this stage we have defined all the points and de lines of the cubic bezier curve..
            //Calculate Point E, on the line AB
            double Ex = ((1-t) * Ax) + (t * Bx);
            double Ey = ((1-t) * Ay) + (t * By);
            double Ez = ((1-t) * Az) + (t * Bz);

            //Calculate Point F, on the line BC
            double Fx = ((1-t) * Bx) + (t * Cx);
            double Fy = ((1-t) * By) + (t * Cy);
            double Fz = ((1-t) * Bz) + (t * Cz);

            //Calculate Point G, on the line CD
            double Gx = ((1-t) * Cx) + (t * Dx);
            double Gy = ((1-t) * Cy) + (t * Dy);
            double Gz = ((1-t) * Cz) + (t * Dz);

            //Calculate Point Q, on the line EF
            double Qx = ((1-t) * Ex) + (t * Fx);
            double Qy = ((1-t) * Ey) + (t * Fy);
            double Qz = ((1-t) * Ez) + (t * Fz);

            //Calculate Point R, on the line FG
            double Rx = ((1-t) * Fx) + (t * Gx);
            double Ry = ((1-t) * Fy) + (t * Gy);
            double Rz = ((1-t) * Fz) + (t * Gz);

            //Calculate Point P, on the line QR
            double Px = ((1-t) * Qx) + (t * Rx);
            double Py = ((1-t) * Qy) + (t * Ry);
            double Pz = ((1-t) * Qz) + (t * Rz);

            glVertex3d(Px, Py, Pz);  //draw linestrip..
        }
        glEnd();

    }

    if(click == 5){
        //Cx = snap_cad_pos_x;  qDebug() << "Cx : " << Cx;
        //Cy = snap_cad_pos_y;  qDebug() << "Cy : " << Cy;
        //Cz = snap_cad_pos_z;  qDebug() << "Cz : " << Cz;

        double_cad_array[cad_counter][53] = snap_cad_pos_x;
        double_cad_array[cad_counter][54] = snap_cad_pos_y;
        double_cad_array[cad_counter][55] = snap_cad_pos_z;

        click = 6;
    }

    if(click == 6){

        glBegin(GL_LINE_STRIP);

        for(double t = 0; t < 1; t+=0.001){
            //qDebug() << "t = " << t;

            //start point A..
            Ax = double_cad_array[cad_counter][0];
            Ay = double_cad_array[cad_counter][1];
            Az = double_cad_array[cad_counter][2];

            //control point B..
            Bx = double_cad_array[cad_counter][50];
            By = double_cad_array[cad_counter][51];
            Bz = double_cad_array[cad_counter][52];

            //control point C..
            Cx = double_cad_array[cad_counter][53];
            Cy = double_cad_array[cad_counter][54];
            Cz = double_cad_array[cad_counter][55];

            //end point D..
            Dx = snap_cad_pos_x;
            Dy = snap_cad_pos_y;
            Dz = snap_cad_pos_z;

            //at this stage we have defined all the points and de lines of the cubic bezier curve..
            //Calculate Point E, on the line AB
            double Ex = ((1-t) * Ax) + (t * Bx);
            double Ey = ((1-t) * Ay) + (t * By);
            double Ez = ((1-t) * Az) + (t * Bz);

            //Calculate Point F, on the line BC
            double Fx = ((1-t) * Bx) + (t * Cx);
            double Fy = ((1-t) * By) + (t * Cy);
            double Fz = ((1-t) * Bz) + (t * Cz);

            //Calculate Point G, on the line CD
            double Gx = ((1-t) * Cx) + (t * Dx);
            double Gy = ((1-t) * Cy) + (t * Dy);
            double Gz = ((1-t) * Cz) + (t * Dz);

            //Calculate Point Q, on the line EF
            double Qx = ((1-t) * Ex) + (t * Fx);
            double Qy = ((1-t) * Ey) + (t * Fy);
            double Qz = ((1-t) * Ez) + (t * Fz);

            //Calculate Point R, on the line FG
            double Rx = ((1-t) * Fx) + (t * Gx);
            double Ry = ((1-t) * Fy) + (t * Gy);
            double Rz = ((1-t) * Fz) + (t * Gz);

            //Calculate Point P, on the line QR
            double Px = ((1-t) * Qx) + (t * Rx);
            double Py = ((1-t) * Qy) + (t * Ry);
            double Pz = ((1-t) * Qz) + (t * Rz);

            glVertex3d(Px, Py, Pz);  //draw linestrip..
        }
        glEnd();

    }

    if(click == 7){
        //Dx = snap_cad_pos_x;  qDebug() << "Dx : " << Dx;
        //Dy = snap_cad_pos_y;  qDebug() << "Dy : " << Dy;
        //Dz = snap_cad_pos_z;  qDebug() << "Dz : " << Dz;

        double_cad_array[cad_counter][3] = snap_cad_pos_x;
        double_cad_array[cad_counter][4] = snap_cad_pos_y;
        double_cad_array[cad_counter][5] = snap_cad_pos_z;

        click = 8;
    }

    if(click == 8){

        //the next preview is done in the display class..
        int_cad_array[cad_counter][0] = 5; // write the id for the qubic bezier curve to display it in the display class..
        cad_counter++;
        mode_cubic_bezier_curve = 0;
        click = 0;
        no_selection();
        messagebox_text = "<b><i>mode cubic bezier curve </i></b> enter for repeat or Esc for cancel";
    }
}






















