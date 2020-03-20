#include "copy.h"
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
#include <array_functions/copy_move_array.h>
#include <display_functions/simple_line_select.h>

copy::copy()
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
        messagebox_text = "<b><i>mode copy </i></b> select objects and press enter";
        clear_user_input = 1;
    }

    if(click < 998){
        window_select(1); //object select procedure..
    }

    if(key_enter && click < 998){
        messagebox_text = "<b><i>mode copy </i></b> click base point"; //specify x start point
        click = 999;
        key_enter = 0;
    }

    if(click == 999){
        //wait for mouse click..
    }

    if(click == 1000){

        //base point..
        base_x = snap_cad_pos_x;
        base_y = snap_cad_pos_y;
        base_z = snap_cad_pos_z;
        messagebox_text = "<b><i>mode copy </i></b> click target point or insert value and press enter in ortho mode";
        entry_focus = 1;

        //qDebug() << "base_x : " << base_x;
        //qDebug() << "base_y : " << base_y;

        click = 1001;
    }

    if(click == 1001){

        //preview..
        if(!mode_ortho){
            dist_x = snap_cad_pos_x - base_x;
            dist_y = snap_cad_pos_y - base_y;
            dist_z = snap_cad_pos_z - base_z;
        }
        if(mode_ortho){
            double distance_x = base_x - snap_cad_pos_x;
            double distance_y = base_y - snap_cad_pos_y;
            double distance_z = base_z - snap_cad_pos_z;

            if(distance_x<0){distance_x *= -1;}
            if(distance_y<0){distance_y *= -1;}
            if(distance_z<0){distance_z *= -1;}

            if(distance_x>=distance_y){
                dist_x = snap_cad_pos_x - base_x;
                dist_y = 0;
                dist_z = 0;

            } else {
                dist_x = 0;
                dist_y = snap_cad_pos_y - base_y;
                dist_z = 0;
            }
        }

        if(key_enter){
            click = 1003;
        }


        for(int i = 0; i < cad_counter; i++){
            if(int_cad_array[i][3] == 1){
                preview_displacement(i, dist_x, dist_y, dist_z);
            }
        }
    }

    if(click == 1002){

        //target point..
        if(!mode_ortho && !key_enter){
            dist_x = snap_cad_pos_x - base_x;
            dist_y = snap_cad_pos_y - base_y;
            dist_z = snap_cad_pos_z - base_z;
            end_function();
        }
        if(mode_ortho && !key_enter){
            double distance_x = base_x - snap_cad_pos_x;
            double distance_y = base_y - snap_cad_pos_y;
            double distance_z = base_z - snap_cad_pos_z;

            if(distance_x<0){distance_x *= -1;}
            if(distance_y<0){distance_y *= -1;}
            if(distance_z<0){distance_z *= -1;}

            if(distance_x>=distance_y){
                dist_x = snap_cad_pos_x - base_x;
                dist_y = 0;
                dist_z = 0;

            } else {
                dist_x = 0;
                dist_y = snap_cad_pos_y - base_y;
                dist_z = 0;
            }
            end_function();
        }
    }

    if(click == 1003){

        double distance_x = base_x - snap_cad_pos_x;
        double distance_y = base_y - snap_cad_pos_y;
        double distance_z = base_z - snap_cad_pos_z;

        if(distance_x<0){distance_x *= -1;}
        if(distance_y<0){distance_y *= -1;}
        if(distance_z<0){distance_z *= -1;}

        double temp_input = double_user_input;

        if(distance_x>=distance_y){

            //avoid negative user input.. look for y direction that mouse is at the moment..
            if(snap_cad_pos_x < base_x){
                temp_input = temp_input *-1;
            }
            if(snap_cad_pos_x > base_x){
                //nothing happens..
            }

            dist_x = temp_input; qDebug() << "dist_x : " << dist_x;
            dist_y = 0;
            dist_z = 0;

        } else {

            if(snap_cad_pos_y < base_y){ //copy to below..
                temp_input = temp_input *-1;
            }
            if(snap_cad_pos_y > base_y){ //copy up..
                //nothing happens..
            }

            dist_x = 0;
            dist_y = temp_input; qDebug() << "dist_y : " << dist_y;
            dist_z = 0;
        }
        end_function();
    }
}

void copy::end_function(){

    //write data to array..
    int temp_counter = cad_counter;
    for(int i = 0; i < cad_counter; i++){
        if(int_cad_array[i][3] == 1){ //select
            copy_move_array(i, temp_counter, dist_x, dist_y, dist_z); //copy move array function..
            temp_counter++;
        }
    }

    cad_counter = temp_counter;
    temp_counter = 0;

    no_highlight();
    no_selection();
    mode_copy = 0;
    select_click = 0;
    click = 0;
    int_key = 0;
    key_enter = 0;
    keyboard = 0;
    entry_focus = 0;
    messagebox_text = "<b><i>mode copy </i></b> enter for repeat or Esc for cancel";
}
























