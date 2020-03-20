#include "move.h"
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

move::move()
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
        messagebox_text = "<b><i>mode move </i></b> select objects and press enter";
        clear_user_input = 1;
    }

    if(click < 998){
        window_select(1); //object select procedure..
    }

    if(key_enter){
        messagebox_text = "<b><i>mode move </i></b> click base point"; //specify x start point
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
        messagebox_text = "<b><i>mode move </i></b> click target point";

        //qDebug() << "base_x : " << base_x;
        //qDebug() << "base_y : " << base_y;

        click = 1001;
    }

    if(click == 1001){

        //preview
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

        for(int i = 0; i < cad_counter; i++){
            if(int_cad_array[i][3] == 1){
                preview_displacement(i, dist_x, dist_y, dist_z);
            }
        }
    }

    if(click == 1002){

        //write position data..
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

        //write data to array..
        for(int i = 0; i < cad_counter; i++){
            if(int_cad_array[i][3] == 1){ //select

                double_cad_array[i][0] = double_cad_array[i][0] + dist_x; //startpoint
                double_cad_array[i][1] = double_cad_array[i][1] + dist_y;
                double_cad_array[i][2] = double_cad_array[i][2] + dist_z;

                double_cad_array[i][3] = double_cad_array[i][3] + dist_x; //endpoint
                double_cad_array[i][4] = double_cad_array[i][4] + dist_y;
                double_cad_array[i][5] = double_cad_array[i][5] + dist_z;

                double_cad_array[i][6] = double_cad_array[i][6] + dist_x; //centerpoint
                double_cad_array[i][7] = double_cad_array[i][7] + dist_y;
                double_cad_array[i][8] = double_cad_array[i][8] + dist_z;

                double_cad_array[i][15] = double_cad_array[i][15] + dist_x; //midpoint
                double_cad_array[i][16] = double_cad_array[i][16] + dist_y;
                double_cad_array[i][17] = double_cad_array[i][17] + dist_z;

                double_cad_array[i][25] = double_cad_array[i][25] + dist_x; //circle left
                double_cad_array[i][26] = double_cad_array[i][26] + dist_y;
                double_cad_array[i][27] = double_cad_array[i][27] + dist_z;

                double_cad_array[i][28] = double_cad_array[i][28] + dist_x; //circle right
                double_cad_array[i][29] = double_cad_array[i][29] + dist_y;
                double_cad_array[i][30] = double_cad_array[i][30] + dist_z;

                double_cad_array[i][31] = double_cad_array[i][31] + dist_x; //circle top
                double_cad_array[i][32] = double_cad_array[i][32] + dist_y;
                double_cad_array[i][33] = double_cad_array[i][33] + dist_z;

                double_cad_array[i][34] = double_cad_array[i][34] + dist_x; //circle right
                double_cad_array[i][35] = double_cad_array[i][35] + dist_y;
                double_cad_array[i][36] = double_cad_array[i][36] + dist_z;

                double_cad_array[i][40] = double_cad_array[i][40] + dist_x; //ellipse
                double_cad_array[i][41] = double_cad_array[i][41] + dist_y;
                double_cad_array[i][42] = double_cad_array[i][42] + dist_x;
                double_cad_array[i][43] = double_cad_array[i][43] + dist_y;

                double_cad_array[i][50] = double_cad_array[i][50] + dist_x; //bezier curve
                double_cad_array[i][51] = double_cad_array[i][51] + dist_y;
                double_cad_array[i][52] = double_cad_array[i][52] + dist_z;
                double_cad_array[i][53] = double_cad_array[i][53] + dist_x;
                double_cad_array[i][54] = double_cad_array[i][54] + dist_y;
                double_cad_array[i][55] = double_cad_array[i][55] + dist_z;
            }
        }

        no_highlight();
        no_selection();
        mode_move = 0;
        select_click = 0;
        click = 0;
        int_key = 0;
        key_enter = 0;
        messagebox_text = "<b><i>mode move </i></b> enter for repeat or Esc for cancel";
    }
}























