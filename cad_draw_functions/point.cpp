#include "point.h"
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

point::point()
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

        entry_focus = 1;
        messagebox_text = "<b><i>mode point </i></b> input point coordinates xyz '0,0,0' or click point";

        //preview point
        double_cad_array[cad_counter][0] = snap_cad_pos_x;
        double_cad_array[cad_counter][1] = snap_cad_pos_y;
        double_cad_array[cad_counter][2] = snap_cad_pos_z;

        int_cad_array[cad_counter][0] = 7; //id point
        double_cad_array[cad_counter][56] = current_gui_color_red_gl;
        double_cad_array[cad_counter][57] = current_gui_color_green_gl;
        double_cad_array[cad_counter][58] = current_gui_color_blue_gl;
        double_cad_array[cad_counter][59] = current_gui_color_alpha_gl;
        int_cad_array[cad_counter][5] = current_linetype;
        double_cad_array[cad_counter][18] = current_linetype_scale;
        double_cad_array[cad_counter][19] = current_linewidth;

        (keyboard_startpoint(cad_counter));
        if(key_enter){

            //add extra centerpoint for snap..
            int_cad_array[cad_counter][0] = 7;
            double_cad_array[cad_counter][6] = double_cad_array[cad_counter][0];
            double_cad_array[cad_counter][7] = double_cad_array[cad_counter][1];
            double_cad_array[cad_counter][8] = double_cad_array[cad_counter][2];

            click = 2;
            key_enter = 0;
            clear_user_input = 1;
        }
    }

    if(click == 1){

        double_cad_array[cad_counter][0] = snap_cad_pos_x;
        double_cad_array[cad_counter][1] = snap_cad_pos_y;
        double_cad_array[cad_counter][2] = snap_cad_pos_z;
        double_cad_array[cad_counter][3] = snap_cad_pos_x;
        double_cad_array[cad_counter][4] = snap_cad_pos_y;
        double_cad_array[cad_counter][5] = snap_cad_pos_z;
        double_cad_array[cad_counter][6] = snap_cad_pos_x;
        double_cad_array[cad_counter][7] = snap_cad_pos_y;
        double_cad_array[cad_counter][8] = snap_cad_pos_z;
        int_cad_array[cad_counter][0] = 7; //id point
        double_cad_array[cad_counter][56] = current_gui_color_red_gl;
        double_cad_array[cad_counter][57] = current_gui_color_green_gl;
        double_cad_array[cad_counter][58] = current_gui_color_blue_gl;
        double_cad_array[cad_counter][59] = current_gui_color_alpha_gl;
        int_cad_array[cad_counter][5] = current_linetype;
        double_cad_array[cad_counter][18] = current_linetype_scale;
        double_cad_array[cad_counter][19] = current_linewidth;

        click = 2;
    }

    if(click == 2){
        cad_counter++;
        click = 0;
        mode_point = 0;
        key_enter = 0;
        int_key = 0;
        entry_focus = 0;
        clear_user_input = 1;
        no_selection();
        messagebox_text = "<b><i>mode point </i></b> enter for repeat or Esc for cancel";
    }
}


















