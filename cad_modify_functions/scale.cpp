#include "scale.h"
#include <core_functions/variables.h>
#include <display_functions/no_highlight.h>
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
#include <display_functions/window_select.h>
#include <display_functions/no_selection.h>
#include <cad_modify_functions/preview_displacement.h>
#include <array_functions/copy_scale_array.h>

scale::scale()
{
    //initialiation..
    snap_cad_pos_x = mouse_cad_pos_x;
    snap_cad_pos_y = mouse_cad_pos_y;
    snap_cad_pos_z = mouse_cad_pos_z;

    //overwrite initialisation if we spot a snap somewhere..
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
        messagebox_text = "<b><i>mode scale </i></b> select objects and press enter";
        clear_user_input = 1;
    }

    if(click < 998){
        window_select(1); //object select procedure..
    }

    if(key_enter){
        messagebox_text = "<b><i>mode scale </i></b> insert scale value, click scale base point"; //specify x start point
        entry_focus = 1;
        click = 999;
        key_enter = 0;
    }

    if(click == 999){
        //wait for mouse click..
    }

    if(click == 1000){

        entry_focus = 0;
        //base point..
        base_x = snap_cad_pos_x;
        base_y = snap_cad_pos_y;
        base_z = snap_cad_pos_z;
        int_key = 0;
        click = 1001;
    }

    if(click == 1001){

            //target point..
            scale_factor = double_user_input;
            for(int i = 0; i < cad_counter; i++){
                if(int_cad_array[i][3] == 1){ //selected items..
                    copy_scale_array(i, i, scale_factor, base_x, base_y, base_z); //base = rotate origin in this case..
                    temp_counter++;
                }
            }
            no_highlight();
            no_selection();
            mode_scale = 0;
            select_click = 0;
            click = 0;
            int_key = 0;
            key_enter = 0;
            keyboard = 0;
            messagebox_text = "<b><i>mode scale </i></b> enter for repeat or Esc for cancel";


    }
}
