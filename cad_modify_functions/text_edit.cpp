#include "text_edit.h"
#include <core_functions/variables.h>
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
#include <display_functions/no_highlight.h>
#include <dialog_functions/dialog_textedit.h>

bool text_dialog_trigger1=0;

text_edit::text_edit()
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
        messagebox_text = "<b><i>mode text edit </i></b> select text and press enter";
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

        if(!text_dialog_trigger1){

            for(int i = 0; i < cad_counter; i++){
                if(int_cad_array[i][3] == 1){ //select
                    text_edit_string = string_cad_array[i][0];

                }
            }
             //qDebug()<< "selected text : " << text_edit_string;

             Dialog_textedit().exec();
             text_dialog_trigger1=1;
        }
        click=1000;
    }

    if(click == 1000){
        no_highlight();
        no_selection();
        text_dialog_trigger1=0;
        mode_text_edit = 0;
        select_click = 0;
        click = 0;
        int_key = 0;
        key_enter = 0;
        keyboard = 0;
        messagebox_text = "<b><i>mode delete </i></b> enter for repeat or Esc for cancel";
    }
}




























