#include "del.h"
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
#include <array_functions/emtpy_current_cad_counter.h>
#include <array_functions/purge_array.h>
#include <array_functions/copy_move_array.h>

void purge();

del::del()
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
        messagebox_text = "<b><i>mode delete </i></b> select objects and press enter";
        clear_user_input = 1;
    }

    if(click < 998){
        window_select(1); //object select procedure..
    }

    if(key_enter){
        click = 999;
        key_enter = 0;
    }

    if(click == 999){


        for(int i = 0; i < cad_counter; i++){

            if(int_cad_array[i][3] == 1){ //select

                (emtpy_current_cad_counter(i));

            }
        }

        //try to purge..
        purge();

        no_highlight();
        no_selection();
        mode_delete = 0;
        select_click = 0;
        click = 0;
        int_key = 0;
        key_enter = 0;
        keyboard = 0;
        messagebox_text = "<b><i>mode delete </i></b> enter for repeat or Esc for cancel";
    }
}

void purge(){
    for(int k=0; k<5; k++){
        for(int i=cad_counter; i>0; i--){
            if(int_cad_array[i][0]!=0){
                cad_counter = i+1;
                break;
            }

        }

        for(int i=0; i<cad_counter; i++){
            if(int_cad_array[i][0]==0){
                for(int pos=i; pos<cad_counter; pos++){
                    copy_move_array(pos+1,pos,0,0,0);
                }
            }
        }

        for(int i=cad_counter; i>0; i--){
            if(int_cad_array[i][0]!=0){
                cad_counter = i+1;
                break;
            }
            if(i==1 && int_cad_array[i][0]==0){
                cad_counter=1;
            }
        }

    }

    qDebug()<<"array purge is done !";
}



















