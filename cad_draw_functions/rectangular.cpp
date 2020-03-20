#include "rectangular.h"
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
#include <display_functions/object_select_line_intersection.h>

QList<double> keyboard_endpoint();

rectangular::rectangular()
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
        messagebox_text = "<b><i>mode rectangular </i></b> input startpoint coordinates xyz '0,0,0' or click start point";

        if(key_enter){
            //create 4 lines..
            for(int i = 0; i<4; i++){
                (keyboard_startpoint(cad_counter+i)); //id = 1 .. line
            }
            click = 2;
            key_enter = 0;
            clear_user_input = 1;
        }
    }


    if(click == 1){

        //create 4 lines..
        for(int i = 0; i<4; i++){
            //horizontal bottom line
            int_cad_array[cad_counter+i][0] = 1; //id line
            double_cad_array[cad_counter+i][56] = current_gui_color_red_gl;
            double_cad_array[cad_counter+i][57] = current_gui_color_green_gl;
            double_cad_array[cad_counter+i][58] = current_gui_color_blue_gl;
            double_cad_array[cad_counter+i][59] = current_gui_color_alpha_gl;
            int_cad_array[cad_counter+i][5] = current_linetype;
            double_cad_array[cad_counter+i][18] = current_linetype_scale;
            double_cad_array[cad_counter+i][19] = current_linewidth;
            int_cad_array[cad_counter+i][5] = current_linetype;
            double_cad_array[cad_counter+i][0] = snap_cad_pos_x;
            double_cad_array[cad_counter+i][1] = snap_cad_pos_y;
            double_cad_array[cad_counter+i][2] = 0;
            double_cad_array[cad_counter+i][3] = snap_cad_pos_x;
            double_cad_array[cad_counter+i][4] = snap_cad_pos_y;
            double_cad_array[cad_counter+i][5] = 0;
        }
        click = 2;
    }

    if(click == 2){

        //preview function..
        double dist_x = snap_cad_pos_x - double_cad_array[cad_counter][0];
        double dist_y = snap_cad_pos_y - double_cad_array[cad_counter][1];

        //horizontal bottom line
        double_cad_array[cad_counter][3] = double_cad_array[cad_counter][0] + dist_x;
        //horizontal top line
        double_cad_array[cad_counter+1][1] = double_cad_array[cad_counter][1] + dist_y;
        double_cad_array[cad_counter+1][3] = double_cad_array[cad_counter][0] + dist_x;
        double_cad_array[cad_counter+1][4] = double_cad_array[cad_counter][1] + dist_y;
        //vertical left line
        double_cad_array[cad_counter+2][4] = double_cad_array[cad_counter][1] + dist_y;
        //vertical right line
        double_cad_array[cad_counter+3][0] = double_cad_array[cad_counter][0] + dist_x;
        double_cad_array[cad_counter+3][3] = double_cad_array[cad_counter][0] + dist_x;
        double_cad_array[cad_counter+3][4] = double_cad_array[cad_counter][1] + dist_y;

        messagebox_text = "<b><i>mode rectangular </i></b> input endpoint coordinates xyz '0,0,0' or click end point";

        if(key_enter){
            key_enter = 0;
            clear_user_input = 1;

            QList<double> list=keyboard_endpoint();
            double x = list.at(0);
            double y = list.at(1);

            //horizontal bottom line
            double_cad_array[cad_counter][3] = x;
            //horizontal top line
            double_cad_array[cad_counter+1][1] = y;
            double_cad_array[cad_counter+1][3] = x;
            double_cad_array[cad_counter+1][4] = y;
            //vertical left line
            double_cad_array[cad_counter+2][4] = y;
            //vertical right line
            double_cad_array[cad_counter+3][0] = x;
            double_cad_array[cad_counter+3][3] = x;
            double_cad_array[cad_counter+3][4] = y;
            click=3;
        }
    }

    if(click ==3){

        //create midpoints..
        for(int i = 0; i<4; i++){
            double_cad_array[cad_counter+i][15] =  (double_cad_array[cad_counter+i][0] +  double_cad_array[cad_counter+i][3]) / 2; //x midpoint..
            double_cad_array[cad_counter+i][16] =  (double_cad_array[cad_counter+i][1] +  double_cad_array[cad_counter+i][4]) / 2; //y midpoint..
            double_cad_array[cad_counter+i][17] =  (double_cad_array[cad_counter+i][2] +  double_cad_array[cad_counter+i][5]) / 2; //z midpoint..
        }

        cad_counter += 4;
        mode_rectangular = 0;
        click = 0;
        key_enter = 0;
        entry_focus = 0;
        keyboard = 0;
        relative = 0;
        clear_user_input = 1;
        no_selection();
        messagebox_text = "<b><i>mode rectangular </i></b> enter for repeat or Esc for cancel";
    }
}


QList<double> keyboard_endpoint(){
    QList<double> list;

    int aa = 0; //start value from first ,
    int bb = 0; //start value from next ,

    //strip left text..
    for(int i = 0; i < string_user_input.size(); i++){
        x.append(string_user_input.at(i));
        if(string_user_input.at(i) == ","){
            x.chop(1);
            aa = i+1;
            break;
        }
    }
    //qDebug() << "the left text is : " << x;

    //strip middle text..
    for(int i = aa; i < string_user_input.size(); i++){

        y.append(string_user_input.at(i));
        if(string_user_input.at(i) == ","){
            y.chop(1);
            bb = i + 1;
            break;
        }
    }
    //qDebug() << "the middle text is : " << y;

    //strip right text..
    for(int i = bb; i < string_user_input.size(); i++){

        z.append(string_user_input.at(i));
        if(string_user_input.at(i) == " "){
            z.chop(1);
            break;
        }
    }
    //qDebug() << "the right text is : " << z;

    list.append(x.toDouble());
    list.append(y.toDouble());
    list.append(z.toDouble());
    return list;
}

















