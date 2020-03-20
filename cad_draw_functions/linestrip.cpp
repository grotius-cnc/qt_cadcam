#include "linestrip.h"
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



linestrip::linestrip()
{
    //initialiation..
    snap_cad_pos_x = mouse_cad_pos_x;
    snap_cad_pos_y = mouse_cad_pos_y;
    //snap_cad_pos_z = mouse_cad_pos_z;

    //overwrite initialisation if we spot a snap somewhere..
    if(mode_snap_intersection){
        object_select_line_intersection();
    }

    //qDebug()<< "snap x 2" << snap_cad_pos_x;
    //qDebug()<< "snap y 2" << snap_cad_pos_y;
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



    entry_focus = 1;

    if(click == 0){

        messagebox_text = "<b><i>mode linestrip </i></b> input startpoint coordinates xyz '0,0,0' or click start point";
        (keyboard_startpoint(cad_counter)); //id = 1 .. line
        if(key_enter){
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

        int_cad_array[cad_counter][0] = 1; //id line
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

        messagebox_text = "<b><i>mode linestrip </i></b> input endpoint coordinates xyz '0,0,0' or input 'lenght' in mode Ortho 'F8', end linestrip with 'Esc'";

        if(!mode_ortho){
            //preview function..
            double_cad_array[cad_counter][3] = snap_cad_pos_x;
            double_cad_array[cad_counter][4] = snap_cad_pos_y;
            double_cad_array[cad_counter][5] = snap_cad_pos_z;

            if(key_enter){
                if(string_user_input.size()==0){
                    click=5;
                } else {
                    keyboard_endpoint();
                    click = 3;
                    key_enter = 0;
                    clear_user_input = 1;
                }
            }
        }

        if(mode_ortho){
            //preview function..
            double distance_x = double_cad_array[cad_counter][0] - snap_cad_pos_x;
            double distance_y = double_cad_array[cad_counter][1] - snap_cad_pos_y;
            double distance_z = double_cad_array[cad_counter][2] - snap_cad_pos_z;

            if(distance_x<0){distance_x *= -1;}
            if(distance_y<0){distance_y *= -1;}
            if(distance_z<0){distance_z *= -1;}

            if(distance_x>=distance_y){
                double_cad_array[cad_counter][3] = snap_cad_pos_x;
                double_cad_array[cad_counter][4] = double_cad_array[cad_counter][1];
                double_cad_array[cad_counter][5] = double_cad_array[cad_counter][2];
            } else {
                double_cad_array[cad_counter][3] = double_cad_array[cad_counter][0];
                double_cad_array[cad_counter][4] = snap_cad_pos_y;
                double_cad_array[cad_counter][5] = double_cad_array[cad_counter][2];
            }
        }

        if(mode_ortho && key_enter){

            if(string_user_input.contains(",")){
                keyboard_endpoint();

            }
            if(!string_user_input.contains(",")){

                //write final line data..
                double distance_x = double_cad_array[cad_counter][0] - snap_cad_pos_x;
                double distance_y = double_cad_array[cad_counter][1] - snap_cad_pos_y;
                double distance_z = double_cad_array[cad_counter][2] - snap_cad_pos_z;

                double distance_x2 = double_cad_array[cad_counter][0] - snap_cad_pos_x;
                double distance_y2 = double_cad_array[cad_counter][1] - snap_cad_pos_y;

                if(distance_x<0){distance_x *= -1;}
                if(distance_y<0){distance_y *= -1;}
                if(distance_z<0){distance_z *= -1;}

                if(distance_x>=distance_y){

                    if(distance_x2>0){
                        double_cad_array[cad_counter][3] = double_cad_array[cad_counter][0] - double_user_input;
                    }
                    if(distance_x2<0){
                        double_cad_array[cad_counter][3] = double_cad_array[cad_counter][0] + double_user_input;
                    }
                    double_cad_array[cad_counter][4] = double_cad_array[cad_counter][1];
                    double_cad_array[cad_counter][5] = double_cad_array[cad_counter][2];

                    //calculate midpoint..
                    double_cad_array[cad_counter][15] =  (double_cad_array[cad_counter][0] +  double_cad_array[cad_counter][3]) / 2; //x midpoint..
                    double_cad_array[cad_counter][16] =  (double_cad_array[cad_counter][1] +  double_cad_array[cad_counter][4]) / 2; //y midpoint..
                    double_cad_array[cad_counter][17] =  (double_cad_array[cad_counter][2] +  double_cad_array[cad_counter][5]) / 2; //z midpoint..

                } else {

                    if(distance_y2>0){
                        double_cad_array[cad_counter][4] = double_cad_array[cad_counter][1] - double_user_input;
                    }
                    if(distance_y2<0){
                        double_cad_array[cad_counter][4] = double_cad_array[cad_counter][1] + double_user_input;
                    }
                    double_cad_array[cad_counter][3] = double_cad_array[cad_counter][0];
                    //double_cad_array[cad_counter][4] = double_user_input + double_cad_array[cad_counter][1];
                    double_cad_array[cad_counter][5] = double_cad_array[cad_counter][2];

                    //calculate midpoint..
                    double_cad_array[cad_counter][15] =  (double_cad_array[cad_counter][0] +  double_cad_array[cad_counter][3]) / 2; //x midpoint..
                    double_cad_array[cad_counter][16] =  (double_cad_array[cad_counter][1] +  double_cad_array[cad_counter][4]) / 2; //y midpoint..
                    double_cad_array[cad_counter][17] =  (double_cad_array[cad_counter][2] +  double_cad_array[cad_counter][5]) / 2; //z midpoint..
                }
            }
            clear_user_input = 1;
            key_enter = 0;
            click = 3; //finish function..
        }
    }

    if(click == 4){ //second line startpoint..

        double_cad_array[cad_counter][0] = double_cad_array[cad_counter-1][3];
        double_cad_array[cad_counter][1] = double_cad_array[cad_counter-1][4];
        double_cad_array[cad_counter][2] = double_cad_array[cad_counter-1][5];
        double_cad_array[cad_counter][3] = double_cad_array[cad_counter-1][3];
        double_cad_array[cad_counter][4] = double_cad_array[cad_counter-1][4];
        double_cad_array[cad_counter][5] = double_cad_array[cad_counter-1][5];

        int_cad_array[cad_counter][0] = 1; //id line
        double_cad_array[cad_counter][56] = current_gui_color_red_gl;
        double_cad_array[cad_counter][57] = current_gui_color_green_gl;
        double_cad_array[cad_counter][58] = current_gui_color_blue_gl;
        double_cad_array[cad_counter][59] = current_gui_color_alpha_gl;
        int_cad_array[cad_counter][5] = current_linetype;
        double_cad_array[cad_counter][18] = current_linetype_scale;
        double_cad_array[cad_counter][19] = current_linewidth;

        click = 2;


    }

    if(click == 3){
        cad_counter++;
        click = 4;
        mode_line = 0;
        key_enter = 0;
        int_key = 0;
        entry_focus = 0;
        clear_user_input = 1;
        no_selection();
        messagebox_text = "<b><i>mode linestrip </i></b> enter for repeat or Esc for cancel";
    }

    if(click == 5){ //when enter was pressed..
        int_cad_array[cad_counter][0] = 0; //no id..
        double_cad_array[cad_counter][0] = 0;
        double_cad_array[cad_counter][1] = 0;
        double_cad_array[cad_counter][2] = 0;
        double_cad_array[cad_counter][3] = 0;
        double_cad_array[cad_counter][4] = 0;
        double_cad_array[cad_counter][5] = 0;

        click=0;
        mode_linestrip = 0;
        key_enter = 0;
        int_key = 0;
        entry_focus = 0;
        clear_user_input = 1;
        no_selection();
        messagebox_text = "<b><i>mode linestrip </i></b> enter for repeat or Esc for cancel";
    }
}























