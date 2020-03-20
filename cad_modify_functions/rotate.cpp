#include "rotate.h"
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
#include <array_functions/copy_rotate_array.h>

rotate::rotate()
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
        messagebox_text = "<b><i>mode rotate </i></b> select objects and press enter";
        clear_user_input = 1;
    }

    if(click < 998){
        window_select(1); //object select procedure..
    }

    if(key_enter){
        messagebox_text = "<b><i>mode rotate </i></b> insert rotation value, click rotation base point"; //specify x start point
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
        messagebox_text = "<b><i>mode rotate </i></b> delete orginal objects? press <font color=#0000ff><u>y </u></font> or <font color=#0000ff><u> n</u></font>";
        int_key = 0;
        click = 1001;
    }

    if(click == 1001){
        //preview.. rotate..
        if(int_key == 89){ //key y
            //target point..
            rotate_degrees = double_user_input;
            for(int i = 0; i < cad_counter; i++){
                if(int_cad_array[i][3] == 1){ //selected items..
                    copy_rotate_array(i, i, rotate_degrees, base_x, base_y); //base = rotate origin in this case..
                    if(int_cad_array[i][0] == 3){//id arc
                        recalculate_start_end_angle_arc(i);
                    }
                    //temp_counter++;
                }
            }
            no_highlight();
            no_selection();
            mode_rotate = 0;
            select_click = 0;
            click = 0;
            int_key = 0;
            key_enter = 0;
            keyboard = 0;
            messagebox_text = "<b><i>mode rotate </i></b> enter for repeat or Esc for cancel";
        }
        if(int_key == 78){ //key n
            //target point..
            rotate_degrees = double_user_input;
            int temp_counter = cad_counter;
            for(int i = 0; i < cad_counter; i++){
                if(int_cad_array[i][3] == 1){ //selected items..
                    copy_rotate_array(i, temp_counter, rotate_degrees, base_x, base_y); //base = rotate origin in this case..
                    if(int_cad_array[i][0] == 3){//id arc
                        recalculate_start_end_angle_arc(temp_counter);
                    }
                    temp_counter++;
                }
            }
            cad_counter = temp_counter;
            temp_counter = 0;
            no_highlight();
            no_selection();
            mode_rotate = 0;
            select_click = 0;
            click = 0;
            int_key = 0;
            key_enter = 0;
            keyboard = 0;
            messagebox_text = "<b><i>mode rotate </i></b> enter for repeat or Esc for cancel";
        }
    }
}

void rotate::recalculate_start_end_angle_arc(int i){

    //recalculate start angle + end angle arc's..
    double arc_cpx = double_cad_array[i][6];
    double arc_cpy = double_cad_array[i][7];
    double p1x = double_cad_array[i][0];
    double p1y = double_cad_array[i][1];
    double p2x = double_cad_array[i][3];
    double p2y = double_cad_array[i][4];

    //okey not very clean, but works for now..
    double xp =  double_cad_array[i][3];
    double yp =  double_cad_array[i][4];
    double x1 =  double_cad_array[i][0];
    double y1 =  double_cad_array[i][1];
    double x2 =  double_cad_array[i][15];
    double y2 =  double_cad_array[i][16];

    double d = ((xp-x1)*(y2-y1))-((yp-y1)*(x2-x1));

    //qDebug() << "d :" << d;

    if(d > 0){
        double_cad_array[i][11] = 180/M_PI*atan2(p2y-arc_cpy, p2x-arc_cpx);    //start angle g2
        double_cad_array[i][12] = 180/M_PI*atan2(p1y-arc_cpy, p1x-arc_cpx);    //end angle g2
    }

    if(d < 0){
        double_cad_array[i][11] = 180/M_PI*atan2(p1y-arc_cpy, p1x-arc_cpx);    //start angle g2
        double_cad_array[i][12] = 180/M_PI*atan2(p2y-arc_cpy, p2x-arc_cpx);    //end angle g2
    }
}



























