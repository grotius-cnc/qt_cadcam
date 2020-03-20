#include "circle_2p.h"
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

circle_2p::circle_2p()
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
        messagebox_text = "<b><i>mode circle </i></b> <font color=#0000ff><u>d</u></font>iameter or <font color=#0000ff><u>r</u></font>adius <br>or click circle centerpoint..";

        //qDebug() << "click = 0";

        // input diameter or radius..
        if(int_key == 68){ //key d..
            bool_diameter = 1;
            int_key = 0;
        }
        if(int_key == 82){ //key r..
            bool_radius = 1;
            int_key = 0;
        }

        //go on..
        if(bool_diameter){
            entry_focus = 1;
            messagebox_text = "<b><i>mode circle </i></b> input circle diameter, click circle centerpoint";

                diameter = double_user_input;
        }

        if(bool_radius){
            entry_focus = 1;
            messagebox_text = "<b><i>mode circle </i></b> input circle radius, click circle centerpoint";

                radius = double_user_input;
        }
    }

    if(click == 1){

        //qDebug() << "click = 1";

        messagebox_text = "<b><i>mode circle </i></b> click circle endpoint..";

        int_cad_array[cad_counter][0] = 2; //id circle
        double_cad_array[cad_counter][56] = current_gui_color_red_gl;
        double_cad_array[cad_counter][57] = current_gui_color_green_gl;
        double_cad_array[cad_counter][58] = current_gui_color_blue_gl;
        double_cad_array[cad_counter][59] = current_gui_color_alpha_gl;

        int_cad_array[cad_counter][5] = current_linetype;
        double_cad_array[cad_counter][18] = current_linetype_scale;
        double_cad_array[cad_counter][19] = current_linewidth;

        double_cad_array[cad_counter][6] = snap_cad_pos_x;
        double_cad_array[cad_counter][7] = snap_cad_pos_y;
        double_cad_array[cad_counter][8] = snap_cad_pos_z;

        click = 2;
    }

    if(click == 2){

        //qDebug() << "click = 2";

        double a = double_cad_array[cad_counter][6] - snap_cad_pos_x;
        double b = double_cad_array[cad_counter][7] - snap_cad_pos_y;

        if(!bool_diameter || !bool_radius){
            double draw_radius = sqrt( pow(a,2)+pow(b,2));
            double_cad_array[cad_counter][9] = draw_radius;

        }
        if(bool_diameter){
            double_cad_array[cad_counter][9] = diameter/2; //user input..
            bool_diameter = 0;
            diameter = 0;
            entry_focus = 0;

            click = 3; //end function..

        }
        if(bool_radius){
            double_cad_array[cad_counter][9] = radius; //user input..
            bool_radius = 0;
            radius = 0;
            entry_focus = 0;

            click = 3; //end function..
        }
    }

    if(click == 3){

        //write the four intersection points..
        //left point :
        double_cad_array[cad_counter][25] = double_cad_array[cad_counter][6] - double_cad_array[cad_counter][9] ; //radius - center x..
        double_cad_array[cad_counter][26] = double_cad_array[cad_counter][7]; //is centerheight..
        double_cad_array[cad_counter][27] = double_cad_array[snap_startpoint][2];
        //right point :
        double_cad_array[cad_counter][28] = double_cad_array[cad_counter][6] + double_cad_array[cad_counter][9] ; //radius + center x..
        double_cad_array[cad_counter][29] = double_cad_array[cad_counter][7]; //is centerheight..
        double_cad_array[cad_counter][30] = double_cad_array[snap_startpoint][2];
        //top point :
        double_cad_array[cad_counter][31] = double_cad_array[cad_counter][6]; //center x..
        double_cad_array[cad_counter][32] = double_cad_array[cad_counter][7] + double_cad_array[cad_counter][9] ; //is centerheight..
        double_cad_array[cad_counter][33] = double_cad_array[snap_startpoint][2];
        //bottom point :
        double_cad_array[cad_counter][34] = double_cad_array[cad_counter][6]; //center x..
        double_cad_array[cad_counter][35] = double_cad_array[cad_counter][7] - double_cad_array[cad_counter][9] ; //is centerheight..
        double_cad_array[cad_counter][36] = double_cad_array[snap_startpoint][2];

        cad_counter++;
        clear_user_input = 1;
        double_user_input = 0;
        click = 0;
        mode_circle_2p = 0;
        key_enter = 0;
        int_key = 0;
        keyboard = 0;
        no_selection();

        messagebox_text = "<b><i>mode circle </i></b> enter for repeat";
    }
}














































