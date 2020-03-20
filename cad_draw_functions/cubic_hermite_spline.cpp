#include "cubic_hermite_spline.h"
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
#include <display_functions/color.h>
#include <display_functions/object_select_line_intersection.h>

cubic_hermite_spline::cubic_hermite_spline()
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
        messagebox_text = "<b><i>mode cubic hermite spline </i></b> click first point";
    }

    //first spline..
    if(click == 1){
        messagebox_text = "<b><i>mode cubic hermite spline </i></b> click next control point, Esc to finish";
        //point 1
        //int_cad_array[cad_counter][0] = 6; //id is spline curve
        //int_cad_array[cad_counter][1] = current_gui_color; //color white
        double_cad_array[cad_counter][56] = current_gui_color_red_gl;
        double_cad_array[cad_counter][57] = current_gui_color_green_gl;
        double_cad_array[cad_counter][58] = current_gui_color_blue_gl;
        double_cad_array[cad_counter][59] = current_gui_color_alpha_gl;

        int_cad_array[cad_counter][5] = current_linetype;
        double_cad_array[cad_counter][18] = current_linetype_scale;
        double_cad_array[cad_counter][19] = current_linewidth;



        int_cad_array[cad_counter][5] = current_linetype;
        double_cad_array[cad_counter][0] = snap_cad_pos_x;
        double_cad_array[cad_counter][1] = snap_cad_pos_y;
        double_cad_array[cad_counter][2] = snap_cad_pos_z;
        double_cad_array[cad_counter][50] = snap_cad_pos_x;
        double_cad_array[cad_counter][51] = snap_cad_pos_y;
        double_cad_array[cad_counter][52] = snap_cad_pos_z;
        click = 2;
    }

    if(click == 2){
        glBegin(GL_LINE_STRIP);

        for(double t = 0; t <= 1; t+=0.1){ //choose a different resolution for t ..
            //qDebug() << "t = " << t;

            int i = cad_counter;
            (color(i));

            //start point A..
            Ax = double_cad_array[i][0];
            Ay = double_cad_array[i][1];
            Az = double_cad_array[i][2];

            //control point B..
            Bx = double_cad_array[i][50];
            By = double_cad_array[i][51];
            Bz = double_cad_array[i][52];

            //control point C..
            Cx = snap_cad_pos_x;
            Cy = snap_cad_pos_y;
            Cz = snap_cad_pos_z;

            //end point D..
            Dx = snap_cad_pos_x;
            Dy = snap_cad_pos_y;
            Dz = snap_cad_pos_z;

            double ax = -Ax/2 + (3*Bx)/2 - (3*Cx)/2 + Dx/2;
            double bx = Ax - (5*Bx)/2 + 2*Cx - Dx / 2;
            double cx = -Ax/2 + Cx/2;
            double dx = Bx;
            double Px = ax*t*t*t + bx*t*t + cx*t + dx;

            double ay = -Ay/2 + (3*By)/2 - (3*Cy)/2 + Dy/2;
            double by = Ay - (5*By)/2 + 2*Cy - Dy / 2;
            double cy = -Ay/2 + Cy/2;
            double dy = By;
            double Py = ay*t*t*t + by*t*t + cy*t + dy;

            double az = -Az/2 + (3*Bz)/2 - (3*Cz)/2 + Dz/2;
            double bz = Az - (5*Bz)/2 + 2*Cz - Dz / 2;
            double cz = -Az/2 + Cz/2;
            double dz = Bz;
            double Pz = az*t*t*t + bz*t*t + cz*t + dz;

            glVertex3d(Px, Py, Pz);  //draw linestrip..
        }
        glEnd();

    }

    if(click == 3){
        //Point 3
        double_cad_array[cad_counter][53] = snap_cad_pos_x;
        double_cad_array[cad_counter][54] = snap_cad_pos_y;
        double_cad_array[cad_counter][55] = snap_cad_pos_z;

        //Point 4
        double_cad_array[cad_counter][3] = snap_cad_pos_x;
        double_cad_array[cad_counter][4] = snap_cad_pos_y;
        double_cad_array[cad_counter][5] = snap_cad_pos_z;

        int_cad_array[cad_counter][0] = 6; //id is spline curve
        cad_counter++;
        click = 4;
    }

    //second spline..
    if(click == 4){

        //preview function..
        //affect previous endpoint..
        double_cad_array[cad_counter-1][3] = snap_cad_pos_x;
        double_cad_array[cad_counter-1][4] = snap_cad_pos_y;
        double_cad_array[cad_counter-1][5] = snap_cad_pos_z;

        int_cad_array[cad_counter][0] = 6; //id is spline curve
        //int_cad_array[cad_counter][1] = current_gui_color; //color white
        double_cad_array[cad_counter][56] = current_gui_color_red_gl;
        double_cad_array[cad_counter][57] = current_gui_color_green_gl;
        double_cad_array[cad_counter][58] = current_gui_color_blue_gl;
        double_cad_array[cad_counter][59] = current_gui_color_alpha_gl;

        int_cad_array[cad_counter][5] = current_linetype;
        double_cad_array[cad_counter][18] = current_linetype_scale;
        double_cad_array[cad_counter][19] = current_linewidth;

        double_cad_array[cad_counter][0] = double_cad_array[cad_counter-1][50];
        double_cad_array[cad_counter][1] = double_cad_array[cad_counter-1][51];
        double_cad_array[cad_counter][2] = double_cad_array[cad_counter-1][52];

        double_cad_array[cad_counter][50] = double_cad_array[cad_counter-1][53];
        double_cad_array[cad_counter][51] = double_cad_array[cad_counter-1][54];
        double_cad_array[cad_counter][52] = double_cad_array[cad_counter-1][55];

        double_cad_array[cad_counter][53] = snap_cad_pos_x;
        double_cad_array[cad_counter][54] = snap_cad_pos_y;
        double_cad_array[cad_counter][55] = snap_cad_pos_z;

        double_cad_array[cad_counter][3] = snap_cad_pos_x;
        double_cad_array[cad_counter][4] = snap_cad_pos_y;
        double_cad_array[cad_counter][5] = snap_cad_pos_z;

    }

    if(click == 5){

        //write data function..
        //affect previous endpoint..
        double_cad_array[cad_counter-1][3] = snap_cad_pos_x;
        double_cad_array[cad_counter-1][4] = snap_cad_pos_y;
        double_cad_array[cad_counter-1][5] = snap_cad_pos_z;

        int_cad_array[cad_counter][0] = 6; //id is spline curve
        //int_cad_array[cad_counter][1] = current_gui_color; //color white
        double_cad_array[cad_counter][56] = current_gui_color_red_gl;
        double_cad_array[cad_counter][57] = current_gui_color_green_gl;
        double_cad_array[cad_counter][58] = current_gui_color_blue_gl;
        double_cad_array[cad_counter][59] = current_gui_color_alpha_gl;

        int_cad_array[cad_counter][5] = current_linetype;
        double_cad_array[cad_counter][18] = current_linetype_scale;
        double_cad_array[cad_counter][19] = current_linewidth;

        double_cad_array[cad_counter][0] = double_cad_array[cad_counter-1][50];
        double_cad_array[cad_counter][1] = double_cad_array[cad_counter-1][51];
        double_cad_array[cad_counter][2] = double_cad_array[cad_counter-1][52];

        double_cad_array[cad_counter][50] = double_cad_array[cad_counter-1][53];
        double_cad_array[cad_counter][51] = double_cad_array[cad_counter-1][54];
        double_cad_array[cad_counter][52] = double_cad_array[cad_counter-1][55];

        double_cad_array[cad_counter][53] = snap_cad_pos_x;
        double_cad_array[cad_counter][54] = snap_cad_pos_y;
        double_cad_array[cad_counter][55] = snap_cad_pos_z;

        double_cad_array[cad_counter][3] = snap_cad_pos_x;
        double_cad_array[cad_counter][4] = snap_cad_pos_y;
        double_cad_array[cad_counter][5] = snap_cad_pos_z;

        cad_counter++;
        click = 4; //loop back to preview..
        //mode_cubic_hermite_spline = 0;
    }


//    if(key_escape){
//        (emtpy_current_cad_counter(cad_counter));
//        no_selection();
//        click = 0;
//        mode_cubic_hermite_spline = 0;
//        messagebox_text = "<b><i>mode cubic hermite spline </i></b> enter for repeat or Esc for cancel";
//    }
}






























