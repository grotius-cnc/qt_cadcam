#include "dimension.h"
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
#include <display_functions/simple_line_select.h>

#define myqDebug() qDebug() << fixed << qSetRealNumberPrecision(3)

double p0x = 0;
double p0y = 0;
double p0z = 0;
double p1x = 0;
double p1y = 0;
double p1z = 0;
double p2x = 0;
double p2y = 0;
double p2z = 0;
//double arrow_lenght = 5;
//double arrow_height = 2.5;
//double dimension_text_height = 10;

int angle_select_1 = 0;
int angle_select_2 = 0;

void add_object_items(int i);

dimension::dimension()
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
        object_select_line_nearest(0);
        object_select_arc_nearest(0);
        object_select_circle_nearest(0);
        object_select_ellipse_nearest(0);
        object_select_hermite_spline_nearest(0);
        object_select_bezier_curve_nearest(0);
    }

    if(click == 0){

        if(dimension_type == "horizontal"){
            messagebox_text = "<b><i>mode dimension </i></b> type : horizontal, click first point";
        }
        if(dimension_type == "vertical"){
            messagebox_text = "<b><i>mode dimension </i></b> type : vertical, click first point";
        }
        if(dimension_type == "non_ortho"){
            messagebox_text = "<b><i>mode dimension </i></b> type : non_ortho, click first point";
        }
        if(dimension_type == "diameter"){
            messagebox_text = "<b><i>mode dimension </i></b> type : diameter, click circle";
            object_select_arc_nearest(0);
            object_select_circle_nearest(0);
        }
        if(dimension_type == "radius"){
            messagebox_text = "<b><i>mode dimension </i></b> type : radius, click arc or circle";
            object_select_arc_nearest(0);
            object_select_circle_nearest(0);
        }
        if(dimension_type == "angle_2p"){
            messagebox_text = "<b><i>mode dimension </i></b> type : angle_2p, click first line";
            //object_select_line_nearest(0);
            simple_line_select();
        }
        if(dimension_type == "angle_3p"){
            messagebox_text = "<b><i>mode dimension </i></b> type : angle_3p, click first point";
        }
    }

    if(click == 1){
        //store p0x,p0y..
        p0x = snap_cad_pos_x; //qDebug()<< "p0x" << p0x;
        p0y = snap_cad_pos_y; //qDebug()<< "p0y" << p0y;

        if(dimension_type == "angle_2p"){
            angle_select_1 = select_id; //qDebug()<< "id 1 :" << angle_select_1;
        }

        click = 2;
    }

    if(click == 2){
        if(dimension_type == "horizontal"){
            messagebox_text = "<b><i>mode dimension </i></b> type : horizontal, click second point";
        } else if(dimension_type == "vertical"){
            messagebox_text = "<b><i>mode dimension </i></b> type : vertical, click second point";
        } else if(dimension_type == "non_ortho"){
            messagebox_text = "<b><i>mode dimension </i></b> type : non_ortho, click second point";
        } else if(dimension_type == "angle_2p"){
            messagebox_text = "<b><i>mode dimension </i></b> type : angle_2p, click second line";
            object_select_line_nearest(0);
        } else if(dimension_type == "angle_3p"){
            messagebox_text = "<b><i>mode dimension </i></b> type : angle_3p, click corner point";
        } else {click = 7;}
    }

    if(click == 3){
        //store p1x,p1y..
        p1x = snap_cad_pos_x; //qDebug()<< "p1x" << p1x;
        p1y = snap_cad_pos_y; //qDebug()<< "p1y" << p1y;

        if(dimension_type == "angle_2p"){
            angle_select_2 = select_id; //qDebug()<< "id 1 :" << angle_select_2;
            click = 7;
        }

        click = 4;
    }

    if(click == 4){
        if(dimension_type == "angle_3p"){
            messagebox_text = "<b><i>mode dimension </i></b> type : angle_3p, click thirth point";
        } else {click = 5;}
    }

    if(click == 5){
        //store p2x,p2y..
        p2x = snap_cad_pos_x; //qDebug()<< "p2x" << p2x;
        p2y = snap_cad_pos_y; //qDebug()<< "p2y" << p2y;
        click = 6;
    }

    if(click == 6){ //preview section..

        if(dimension_type == "horizontal"){
            messagebox_text = "<b><i>mode dimension </i></b> type : horizontal, click position";

            //left dimension line
            int_cad_array[cad_counter][0] = 1; //id line
            int_cad_array[cad_counter][5] = current_linetype;
            double_cad_array[cad_counter][0] = p0x;
            double_cad_array[cad_counter][1] = p0y;
            double_cad_array[cad_counter][2] = p0z;
            double_cad_array[cad_counter][3] = p0x;
            double_cad_array[cad_counter][4] = snap_cad_pos_y;
            double_cad_array[cad_counter][5] = p0z;
            double_cad_array[cad_counter][18] = current_linetype_scale;
            double_cad_array[cad_counter][19] = current_linewidth;
            double_cad_array[cad_counter][56] = current_gui_color_red_gl;
            double_cad_array[cad_counter][57] = current_gui_color_green_gl;
            double_cad_array[cad_counter][58] = current_gui_color_blue_gl;
            double_cad_array[cad_counter][59] = current_gui_color_alpha_gl;

            //right dimension line
            int_cad_array[cad_counter+1][0] = 1; //id line
            int_cad_array[cad_counter+1][5] = current_linetype;
            double_cad_array[cad_counter+1][0] = p1x;
            double_cad_array[cad_counter+1][1] = p1y;
            double_cad_array[cad_counter+1][2] = p1z;
            double_cad_array[cad_counter+1][3] = p1x;
            double_cad_array[cad_counter+1][4] = snap_cad_pos_y;
            double_cad_array[cad_counter+1][5] = p1z;
            double_cad_array[cad_counter+1][18] = current_linetype_scale;
            double_cad_array[cad_counter+1][19] = current_linewidth;
            double_cad_array[cad_counter+1][56] = current_gui_color_red_gl;
            double_cad_array[cad_counter+1][57] = current_gui_color_green_gl;
            double_cad_array[cad_counter+1][58] = current_gui_color_blue_gl;
            double_cad_array[cad_counter+1][59] = current_gui_color_alpha_gl;

            //main dimension line
            int_cad_array[cad_counter+2][0] = 1; //id line
            int_cad_array[cad_counter+2][5] = current_linetype;
            if(p0x<p1x){
                double_cad_array[cad_counter+2][0] = p0x+arrow_lenght; //inside arrow
            } else { double_cad_array[cad_counter+2][0] = p0x; } //outside arrow
            double_cad_array[cad_counter+2][1] = snap_cad_pos_y;
            double_cad_array[cad_counter+2][2] = p0z;
            if(p0x<p1x){
                double_cad_array[cad_counter+2][3] = p1x-arrow_lenght;
            } else { double_cad_array[cad_counter+2][3] = p1x; }
            double_cad_array[cad_counter+2][4] = snap_cad_pos_y;
            double_cad_array[cad_counter+2][5] = p1z;
            double_cad_array[cad_counter+2][18] = current_linetype_scale;
            double_cad_array[cad_counter+2][19] = current_linewidth;
            double_cad_array[cad_counter+2][56] = current_gui_color_red_gl;
            double_cad_array[cad_counter+2][57] = current_gui_color_green_gl;
            double_cad_array[cad_counter+2][58] = current_gui_color_blue_gl;
            double_cad_array[cad_counter+2][59] = current_gui_color_alpha_gl;

            //left arrow above
            int_cad_array[cad_counter+3][0] = 1; //id line
            int_cad_array[cad_counter+3][5] = current_linetype;
            double_cad_array[cad_counter+3][0] = p0x;
            double_cad_array[cad_counter+3][1] = snap_cad_pos_y;
            double_cad_array[cad_counter+3][2] = p0z;
            double_cad_array[cad_counter+3][3] = p0x+arrow_lenght;
            double_cad_array[cad_counter+3][4] = snap_cad_pos_y+(0.5*arrow_height);
            double_cad_array[cad_counter+3][5] = p0z;
            double_cad_array[cad_counter+3][18] = current_linetype_scale;
            double_cad_array[cad_counter+3][19] = current_linewidth;
            double_cad_array[cad_counter+3][56] = current_gui_color_red_gl;
            double_cad_array[cad_counter+3][57] = current_gui_color_green_gl;
            double_cad_array[cad_counter+3][58] = current_gui_color_blue_gl;
            double_cad_array[cad_counter+3][59] = current_gui_color_alpha_gl;

            //left arrow under
            int_cad_array[cad_counter+4][0] = 1; //id line
            int_cad_array[cad_counter+4][5] = current_linetype;
            double_cad_array[cad_counter+4][0] = p0x;
            double_cad_array[cad_counter+4][1] = snap_cad_pos_y;
            double_cad_array[cad_counter+4][2] = p0z;
            double_cad_array[cad_counter+4][3] = p0x+arrow_lenght;
            double_cad_array[cad_counter+4][4] = snap_cad_pos_y-(0.5*arrow_height);
            double_cad_array[cad_counter+4][5] = p0z;
            double_cad_array[cad_counter+4][18] = current_linetype_scale;
            double_cad_array[cad_counter+4][19] = current_linewidth;
            double_cad_array[cad_counter+4][56] = current_gui_color_red_gl;
            double_cad_array[cad_counter+4][57] = current_gui_color_green_gl;
            double_cad_array[cad_counter+4][58] = current_gui_color_blue_gl;
            double_cad_array[cad_counter+4][59] = current_gui_color_alpha_gl;

            //left arrow vertical
            int_cad_array[cad_counter+5][0] = 1; //id line
            int_cad_array[cad_counter+5][5] = current_linetype;
            double_cad_array[cad_counter+5][0] = p0x+arrow_lenght;
            double_cad_array[cad_counter+5][1] = snap_cad_pos_y+(0.5*arrow_height);
            double_cad_array[cad_counter+5][2] = p0z;
            double_cad_array[cad_counter+5][3] = p0x+arrow_lenght;
            double_cad_array[cad_counter+5][4] = snap_cad_pos_y-(0.5*arrow_height);
            double_cad_array[cad_counter+5][5] = p0z;
            double_cad_array[cad_counter+5][18] = current_linetype_scale;
            double_cad_array[cad_counter+5][19] = current_linewidth;
            double_cad_array[cad_counter+5][56] = current_gui_color_red_gl;
            double_cad_array[cad_counter+5][57] = current_gui_color_green_gl;
            double_cad_array[cad_counter+5][58] = current_gui_color_blue_gl;
            double_cad_array[cad_counter+5][59] = current_gui_color_alpha_gl;

            //right arrow above
            int_cad_array[cad_counter+6][0] = 1; //id line
            int_cad_array[cad_counter+6][5] = current_linetype;
            double_cad_array[cad_counter+6][0] = p1x;
            double_cad_array[cad_counter+6][1] = snap_cad_pos_y;
            double_cad_array[cad_counter+6][2] = p1z;
            double_cad_array[cad_counter+6][3] = p1x-arrow_lenght;
            double_cad_array[cad_counter+6][4] = snap_cad_pos_y+(0.5*arrow_height);
            double_cad_array[cad_counter+6][5] = p1z;
            double_cad_array[cad_counter+6][18] = current_linetype_scale;
            double_cad_array[cad_counter+6][19] = current_linewidth;
            double_cad_array[cad_counter+6][56] = current_gui_color_red_gl;
            double_cad_array[cad_counter+6][57] = current_gui_color_green_gl;
            double_cad_array[cad_counter+6][58] = current_gui_color_blue_gl;
            double_cad_array[cad_counter+6][59] = current_gui_color_alpha_gl;

            //right arrow under
            int_cad_array[cad_counter+7][0] = 1; //id line
            int_cad_array[cad_counter+7][5] = current_linetype;
            double_cad_array[cad_counter+7][0] = p1x;
            double_cad_array[cad_counter+7][1] = snap_cad_pos_y;
            double_cad_array[cad_counter+7][2] = p1z;
            double_cad_array[cad_counter+7][3] = p1x-arrow_lenght;
            double_cad_array[cad_counter+7][4] = snap_cad_pos_y-(0.5*arrow_height);
            double_cad_array[cad_counter+7][5] = p1z;
            double_cad_array[cad_counter+7][18] = current_linetype_scale;
            double_cad_array[cad_counter+7][19] = current_linewidth;
            double_cad_array[cad_counter+7][56] = current_gui_color_red_gl;
            double_cad_array[cad_counter+7][57] = current_gui_color_green_gl;
            double_cad_array[cad_counter+7][58] = current_gui_color_blue_gl;
            double_cad_array[cad_counter+7][59] = current_gui_color_alpha_gl;

            //right arrow vertical
            int_cad_array[cad_counter+8][0] = 1; //id line
            int_cad_array[cad_counter+8][5] = current_linetype;
            double_cad_array[cad_counter+8][0] = p1x-arrow_lenght;
            double_cad_array[cad_counter+8][1] = snap_cad_pos_y+(0.5*arrow_height);
            double_cad_array[cad_counter+8][2] = p1z;
            double_cad_array[cad_counter+8][3] = p1x-arrow_lenght;
            double_cad_array[cad_counter+8][4] = snap_cad_pos_y-(0.5*arrow_height);
            double_cad_array[cad_counter+8][5] = p1z;
            double_cad_array[cad_counter+8][18] = current_linetype_scale;
            double_cad_array[cad_counter+8][19] = current_linewidth;
            double_cad_array[cad_counter+8][56] = current_gui_color_red_gl;
            double_cad_array[cad_counter+8][57] = current_gui_color_green_gl;
            double_cad_array[cad_counter+8][58] = current_gui_color_blue_gl;
            double_cad_array[cad_counter+8][59] = current_gui_color_alpha_gl;


        }
        if(dimension_type == "vertical"){
            messagebox_text = "<b><i>mode dimension </i></b> type : vertical, click position";

            //left dimension line
            int_cad_array[cad_counter][0] = 1; //id line
            int_cad_array[cad_counter][5] = current_linetype;
            double_cad_array[cad_counter][0] = p0x;
            double_cad_array[cad_counter][1] = p0y;
            double_cad_array[cad_counter][2] = p0z;
            double_cad_array[cad_counter][3] = snap_cad_pos_x;
            double_cad_array[cad_counter][4] = p0y;
            double_cad_array[cad_counter][5] = p0z;
            double_cad_array[cad_counter][18] = current_linetype_scale;
            double_cad_array[cad_counter][19] = current_linewidth;
            double_cad_array[cad_counter][56] = current_gui_color_red_gl;
            double_cad_array[cad_counter][57] = current_gui_color_green_gl;
            double_cad_array[cad_counter][58] = current_gui_color_blue_gl;
            double_cad_array[cad_counter][59] = current_gui_color_alpha_gl;

            //right dimension line
            int_cad_array[cad_counter+1][0] = 1; //id line
            int_cad_array[cad_counter+1][5] = current_linetype;
            double_cad_array[cad_counter+1][0] = p1x;
            double_cad_array[cad_counter+1][1] = p1y;
            double_cad_array[cad_counter+1][2] = p1z;
            double_cad_array[cad_counter+1][3] = snap_cad_pos_x;
            double_cad_array[cad_counter+1][4] = p1y;
            double_cad_array[cad_counter+1][5] = p1z;
            double_cad_array[cad_counter+1][18] = current_linetype_scale;
            double_cad_array[cad_counter+1][19] = current_linewidth;
            double_cad_array[cad_counter+1][56] = current_gui_color_red_gl;
            double_cad_array[cad_counter+1][57] = current_gui_color_green_gl;
            double_cad_array[cad_counter+1][58] = current_gui_color_blue_gl;
            double_cad_array[cad_counter+1][59] = current_gui_color_alpha_gl;

            //main dimension line
            int_cad_array[cad_counter+2][0] = 1; //id line
            int_cad_array[cad_counter+2][5] = current_linetype;

            double_cad_array[cad_counter+2][0] = snap_cad_pos_x;
            if(p0y<p1y){
                double_cad_array[cad_counter+2][1] = p0y+arrow_lenght; //inside arrow
            } else { double_cad_array[cad_counter+2][1] = p0y; } //outside arrow
            double_cad_array[cad_counter+2][2] = p0z;


            double_cad_array[cad_counter+2][3] = snap_cad_pos_x;
            if(p0y<p1y){
                double_cad_array[cad_counter+2][4] = p1y-arrow_lenght;
            } else { double_cad_array[cad_counter+2][4] = p1y; }
            double_cad_array[cad_counter+2][5] = p1z;


            double_cad_array[cad_counter+2][18] = current_linetype_scale;
            double_cad_array[cad_counter+2][19] = current_linewidth;
            double_cad_array[cad_counter+2][56] = current_gui_color_red_gl;
            double_cad_array[cad_counter+2][57] = current_gui_color_green_gl;
            double_cad_array[cad_counter+2][58] = current_gui_color_blue_gl;
            double_cad_array[cad_counter+2][59] = current_gui_color_alpha_gl;

            //arrow bottom right
            int_cad_array[cad_counter+3][0] = 1; //id line
            int_cad_array[cad_counter+3][5] = current_linetype;
            double_cad_array[cad_counter+3][0] = snap_cad_pos_x;
            double_cad_array[cad_counter+3][1] = p0y;
            double_cad_array[cad_counter+3][2] = p0z;
            double_cad_array[cad_counter+3][3] = snap_cad_pos_x+(0.5*arrow_height);
            double_cad_array[cad_counter+3][4] = p0y+arrow_lenght;
            double_cad_array[cad_counter+3][5] = p0z;
            double_cad_array[cad_counter+3][18] = current_linetype_scale;
            double_cad_array[cad_counter+3][19] = current_linewidth;
            double_cad_array[cad_counter+3][56] = current_gui_color_red_gl;
            double_cad_array[cad_counter+3][57] = current_gui_color_green_gl;
            double_cad_array[cad_counter+3][58] = current_gui_color_blue_gl;
            double_cad_array[cad_counter+3][59] = current_gui_color_alpha_gl;

            //arrow bottom left
            int_cad_array[cad_counter+4][0] = 1; //id line
            int_cad_array[cad_counter+4][5] = current_linetype;
            double_cad_array[cad_counter+4][0] = snap_cad_pos_x;
            double_cad_array[cad_counter+4][1] = p0y;
            double_cad_array[cad_counter+4][2] = p0z;
            double_cad_array[cad_counter+4][3] = snap_cad_pos_x-(0.5*arrow_height);
            double_cad_array[cad_counter+4][4] = p0y+arrow_lenght;
            double_cad_array[cad_counter+4][5] = p0z;
            double_cad_array[cad_counter+4][18] = current_linetype_scale;
            double_cad_array[cad_counter+4][19] = current_linewidth;
            double_cad_array[cad_counter+4][56] = current_gui_color_red_gl;
            double_cad_array[cad_counter+4][57] = current_gui_color_green_gl;
            double_cad_array[cad_counter+4][58] = current_gui_color_blue_gl;
            double_cad_array[cad_counter+4][59] = current_gui_color_alpha_gl;

            //arrow bottom horizontal
            int_cad_array[cad_counter+5][0] = 1; //id line
            int_cad_array[cad_counter+5][5] = current_linetype;
            double_cad_array[cad_counter+5][0] = snap_cad_pos_x-(0.5*arrow_height);
            double_cad_array[cad_counter+5][1] = p0y+arrow_lenght;
            double_cad_array[cad_counter+5][2] = p0z;
            double_cad_array[cad_counter+5][3] = snap_cad_pos_x+(0.5*arrow_height);
            double_cad_array[cad_counter+5][4] = p0y+arrow_lenght;
            double_cad_array[cad_counter+5][5] = p0z;
            double_cad_array[cad_counter+5][18] = current_linetype_scale;
            double_cad_array[cad_counter+5][19] = current_linewidth;
            double_cad_array[cad_counter+5][56] = current_gui_color_red_gl;
            double_cad_array[cad_counter+5][57] = current_gui_color_green_gl;
            double_cad_array[cad_counter+5][58] = current_gui_color_blue_gl;
            double_cad_array[cad_counter+5][59] = current_gui_color_alpha_gl;

            //arrow up right
            int_cad_array[cad_counter+6][0] = 1; //id line
            int_cad_array[cad_counter+6][5] = current_linetype;
            double_cad_array[cad_counter+6][0] = snap_cad_pos_x;
            double_cad_array[cad_counter+6][1] = p1y;
            double_cad_array[cad_counter+6][2] = p1z;
            double_cad_array[cad_counter+6][3] = snap_cad_pos_x+(0.5*arrow_height);
            double_cad_array[cad_counter+6][4] = p1y-arrow_lenght;
            double_cad_array[cad_counter+6][5] = p1z;
            double_cad_array[cad_counter+6][18] = current_linetype_scale;
            double_cad_array[cad_counter+6][19] = current_linewidth;
            double_cad_array[cad_counter+6][56] = current_gui_color_red_gl;
            double_cad_array[cad_counter+6][57] = current_gui_color_green_gl;
            double_cad_array[cad_counter+6][58] = current_gui_color_blue_gl;
            double_cad_array[cad_counter+6][59] = current_gui_color_alpha_gl;

            //arrow up left
            int_cad_array[cad_counter+7][0] = 1; //id line
            int_cad_array[cad_counter+7][5] = current_linetype;
            double_cad_array[cad_counter+7][0] = snap_cad_pos_x;
            double_cad_array[cad_counter+7][1] = p1y;
            double_cad_array[cad_counter+7][2] = p1z;
            double_cad_array[cad_counter+7][3] = snap_cad_pos_x-(0.5*arrow_height);
            double_cad_array[cad_counter+7][4] = p1y-arrow_lenght;
            double_cad_array[cad_counter+7][5] = p1z;
            double_cad_array[cad_counter+7][18] = current_linetype_scale;
            double_cad_array[cad_counter+7][19] = current_linewidth;
            double_cad_array[cad_counter+7][56] = current_gui_color_red_gl;
            double_cad_array[cad_counter+7][57] = current_gui_color_green_gl;
            double_cad_array[cad_counter+7][58] = current_gui_color_blue_gl;
            double_cad_array[cad_counter+7][59] = current_gui_color_alpha_gl;

            //arrow up horizontal
            int_cad_array[cad_counter+8][0] = 1; //id line
            int_cad_array[cad_counter+8][5] = current_linetype;
            double_cad_array[cad_counter+8][0] = snap_cad_pos_x-(0.5*arrow_height);
            double_cad_array[cad_counter+8][1] = p1y-arrow_lenght;
            double_cad_array[cad_counter+8][2] = p1z;
            double_cad_array[cad_counter+8][3] = snap_cad_pos_x+(0.5*arrow_height);
            double_cad_array[cad_counter+8][4] = p1y-arrow_lenght;
            double_cad_array[cad_counter+8][5] = p1z;
            double_cad_array[cad_counter+8][18] = current_linetype_scale;
            double_cad_array[cad_counter+8][19] = current_linewidth;
            double_cad_array[cad_counter+8][56] = current_gui_color_red_gl;
            double_cad_array[cad_counter+8][57] = current_gui_color_green_gl;
            double_cad_array[cad_counter+8][58] = current_gui_color_blue_gl;
            double_cad_array[cad_counter+8][59] = current_gui_color_alpha_gl;

        }
        if(dimension_type == "non_ortho"){
            messagebox_text = "<b><i>mode dimension </i></b> type : non_ortho, click position";

            //mirror snap_cad_pos to clicked dimension points..
            QList<double> mirror;
            mirror = mirror_point(p0x, p0y, p1x, p1y, snap_cad_pos_x, snap_cad_pos_y);

            //calculate perpendicular intersection point on virtual triangle line..
            double intersection_x = (snap_cad_pos_x + mirror.at(0)) /2;
            double intersection_y = (snap_cad_pos_y + mirror.at(1)) /2; //qDebug()<< "intersection x : " << intersection_x << " y : " << intersection_y;
            double offset = sqrt(pow(snap_cad_pos_x-intersection_x,2)+pow(snap_cad_pos_y-intersection_y,2));
            mirror.clear();

            //wich side to offset..
            double d = (snap_cad_pos_x-p0x)*(p1y-p0y) - (snap_cad_pos_y-p0y)*(p1x - p0x);
            //qDebug()<< " d : " << d;
            if(d<0){
                //rotate orginal line..
                rotate_degrees = 90;
            }
            if(d>0){
                rotate_degrees = -90;
            }
            //offset line..
            QList<double> base_line_list;
            base_line_list = offset_line(p0x, p0y, p1x, p1y,offset,rotate_degrees);
            //qDebug() << "list : " << base_line_list;

            //dimension base line..
            add_object_items(cad_counter);
            double_cad_array[cad_counter][0] = base_line_list.at(0);
            double_cad_array[cad_counter][1] = base_line_list.at(1);
            double_cad_array[cad_counter][3] = base_line_list.at(2);
            double_cad_array[cad_counter][4] = base_line_list.at(3);

            //left dimension line
            add_object_items(cad_counter+1);
            double_cad_array[cad_counter+1][0] = p0x;
            double_cad_array[cad_counter+1][1] = p0y;
            double_cad_array[cad_counter+1][3] = base_line_list.at(0);
            double_cad_array[cad_counter+1][4] = base_line_list.at(1);

            //right dimension line
            add_object_items(cad_counter+2);
            double_cad_array[cad_counter+2][0] = p1x;
            double_cad_array[cad_counter+2][1] = p1y;
            double_cad_array[cad_counter+2][3] = base_line_list.at(2);
            double_cad_array[cad_counter+2][4] = base_line_list.at(3);

            double AC = sqrt(pow(p1x-p0x,2)+pow(p1y-p0y,2)); //has the dimension text value..
            double AB = arrow_lenght;
            double Xa = base_line_list.at(0) + (AB * (base_line_list.at(2) - base_line_list.at(0)) / AC);
            double Ya = base_line_list.at(1) + (AB * (base_line_list.at(3) - base_line_list.at(1)) / AC); //qDebug()<< "arrow left intersection x : " << Xa << " y : " << Ya;
            double Xb = base_line_list.at(2) + (AB * (base_line_list.at(0) - base_line_list.at(2)) / AC);
            double Yb = base_line_list.at(3) + (AB * (base_line_list.at(1) - base_line_list.at(3)) / AC); //qDebug()<< "arrow left intersection x : " << Xb << " y : " << Yb;

            //offset half arrowheight left..
            QList<double> left_arrow_line_above;
            left_arrow_line_above = offset_line(base_line_list.at(0), base_line_list.at(1),Xa,Ya,(0.5*arrow_height),90);

            //offset half arrowheight right..
            QList<double> right_arrow_line_above;
            right_arrow_line_above = offset_line(base_line_list.at(0), base_line_list.at(1),Xb,Yb,(0.5*arrow_height),90);

            //left above arrow line
            add_object_items(cad_counter+3);
            double_cad_array[cad_counter+3][0] = base_line_list.at(0);
            double_cad_array[cad_counter+3][1] = base_line_list.at(1);
            double_cad_array[cad_counter+3][3] = left_arrow_line_above.at(2);
            double_cad_array[cad_counter+3][4] = left_arrow_line_above.at(3);

            //mirror arrow line point
            QList<double> arrow_point_under;
            arrow_point_under = mirror_point(base_line_list.at(0),base_line_list.at(1),base_line_list.at(2),base_line_list.at(3),left_arrow_line_above.at(2), left_arrow_line_above.at(3));

            //left under arrow line
            add_object_items(cad_counter+4);
            double_cad_array[cad_counter+4][0] = base_line_list.at(0);
            double_cad_array[cad_counter+4][1] = base_line_list.at(1);
            double_cad_array[cad_counter+4][3] = arrow_point_under.at(0);
            double_cad_array[cad_counter+4][4] = arrow_point_under.at(1);

            //left under arrow upstand line
            add_object_items(cad_counter+5);
            double_cad_array[cad_counter+5][0] = left_arrow_line_above.at(2);
            double_cad_array[cad_counter+5][1] = left_arrow_line_above.at(3);
            double_cad_array[cad_counter+5][3] = arrow_point_under.at(0);
            double_cad_array[cad_counter+5][4] = arrow_point_under.at(1);

            ///////////RIGHT ARROW..

            //right above arrow line
            add_object_items(cad_counter+6);
            double_cad_array[cad_counter+6][0] = base_line_list.at(2);
            double_cad_array[cad_counter+6][1] = base_line_list.at(3);
            double_cad_array[cad_counter+6][3] = right_arrow_line_above.at(2);
            double_cad_array[cad_counter+6][4] = right_arrow_line_above.at(3);

            //mirror arrow line point
            QList<double> mirrored_arrow_point;
            mirrored_arrow_point = mirror_point(base_line_list.at(0),base_line_list.at(1),base_line_list.at(2),base_line_list.at(3),right_arrow_line_above.at(2), right_arrow_line_above.at(3));

            //right under arrow line
            add_object_items(cad_counter+7);
            double_cad_array[cad_counter+7][0] = base_line_list.at(2);
            double_cad_array[cad_counter+7][1] = base_line_list.at(3);
            double_cad_array[cad_counter+7][3] = mirrored_arrow_point.at(0);
            double_cad_array[cad_counter+7][4] = mirrored_arrow_point.at(1);

            //right arrow standup line
            add_object_items(cad_counter+8);
            double_cad_array[cad_counter+8][0] = right_arrow_line_above.at(2);
            double_cad_array[cad_counter+8][1] = right_arrow_line_above.at(3);
            double_cad_array[cad_counter+8][3] = mirrored_arrow_point.at(0);
            double_cad_array[cad_counter+8][4] = mirrored_arrow_point.at(1);

            //short in the base line.. line between the arrows.. add baseline midpoint..
            add_object_items(cad_counter);
            double_cad_array[cad_counter][0] = Xa;
            double_cad_array[cad_counter][1] = Ya;
            double_cad_array[cad_counter][3] = Xb;
            double_cad_array[cad_counter][4] = Yb;
            double_cad_array[cad_counter][15] = (double_cad_array[cad_counter][0] + double_cad_array[cad_counter][3])/2; //x midpoint..
            double_cad_array[cad_counter][16] = (double_cad_array[cad_counter][1] + double_cad_array[cad_counter][4])/2; //y midpoint..
            double_cad_array[cad_counter][17] = (double_cad_array[cad_counter][2] + double_cad_array[cad_counter][5])/2; //z midpoint..

            //clean up lists..
            mirror.clear();
            base_line_list.clear();
            left_arrow_line_above.clear();
            right_arrow_line_above.clear();
            arrow_point_under.clear();
            mirrored_arrow_point.clear();

        }
        if(dimension_type == "angle_2p"){
            messagebox_text = "<b><i>mode dimension </i></b> type : angle 2 points";

            //dimension base line..
            //left under arrow upstand line
            int_cad_array[cad_counter][0] = 3; //id arc
            int_cad_array[cad_counter][5] = current_linetype;
            double_cad_array[cad_counter][2] = 0; //z start
            double_cad_array[cad_counter][5] = 0; //z end
            double_cad_array[cad_counter][18] = current_linetype_scale;
            double_cad_array[cad_counter][19] = current_linewidth;
            double_cad_array[cad_counter][56] = current_gui_color_red_gl;
            double_cad_array[cad_counter][57] = current_gui_color_green_gl;
            double_cad_array[cad_counter][58] = current_gui_color_blue_gl;
            double_cad_array[cad_counter][59] = current_gui_color_alpha_gl;

            //arc center..
            QList<double> list = line_line_intersection_by_id(angle_select_1, angle_select_2);
            if(list.size()==2){
                double_cad_array[cad_counter][6] = list.at(0); //arc center..
                double_cad_array[cad_counter][7] = list.at(1); //qDebug()<< "arc center x : " << double_cad_array[cad_counter][6] << " y : " << double_cad_array[cad_counter][7];
                list.clear();
            }

            //arc radius..
            double_cad_array[cad_counter][9] = sqrt(pow(snap_cad_pos_x-double_cad_array[cad_counter][6],2)+pow(snap_cad_pos_y-double_cad_array[cad_counter][7],2)); //qDebug()<< "arc radius : " << double_cad_array[cad_counter][9];

            //intersection 1..
            list = circle_line_intersection_by_points(double_cad_array[cad_counter][6],double_cad_array[cad_counter][7],double_cad_array[cad_counter][9],double_cad_array[angle_select_1][0],double_cad_array[angle_select_1][1],double_cad_array[angle_select_1][3],double_cad_array[angle_select_1][4]);
            if(list.size()==2){
                double_cad_array[cad_counter][0] = list.at(0);
                double_cad_array[cad_counter][1] = list.at(1); //qDebug()<< "intersection 1 x : " <<  double_cad_array[cad_counter][0] << " y : " <<  double_cad_array[cad_counter][1];
                list.clear();
            }

            //intersection 2..
            list = circle_line_intersection_by_points(double_cad_array[cad_counter][6],double_cad_array[cad_counter][7],double_cad_array[cad_counter][9],double_cad_array[angle_select_2][0],double_cad_array[angle_select_2][1],double_cad_array[angle_select_2][3],double_cad_array[angle_select_2][4]);
            if(list.size()==2){
                double_cad_array[cad_counter][3] = list.at(0);
                double_cad_array[cad_counter][4] = list.at(1); //qDebug()<< "intersection 2 x : " <<  double_cad_array[cad_counter][3] << " y : " <<  double_cad_array[cad_counter][4];
                list.clear();
            }

            //draw arc..
            list = draw_3p_arc(double_cad_array[cad_counter][0],double_cad_array[cad_counter][1],snap_cad_pos_x,snap_cad_pos_y,double_cad_array[cad_counter][3],double_cad_array[cad_counter][4]);
            if(list.size()==4){
                double_cad_array[cad_counter][11] = list.at(0);
                double_cad_array[cad_counter][12] = list.at(1);
                double_cad_array[cad_counter][15] = list.at(2); //midpoint x
                double_cad_array[cad_counter][16] = list.at(3);
                list.clear();
            }

            //offset select 1 line..
            QList<double> line_offset = offset_line_by_points_to_side(double_cad_array[angle_select_1][0],double_cad_array[angle_select_1][1], double_cad_array[cad_counter][0],double_cad_array[cad_counter][1],arrow_lenght,double_cad_array[cad_counter][15],double_cad_array[cad_counter][16]);
            if(line_offset.size()==4){

                //arrowlenght middle line..
                double ax = double_cad_array[cad_counter][0];
                double ay = double_cad_array[cad_counter][1];
                double bx = line_offset.at(2);
                double by = line_offset.at(3);

                //arrowlenght offset line.. direction is arc center..
                QList<double> arrow_offset = offset_line_by_points_to_side(ax,ay,bx,by,(0.5*arrow_height),0,0);
                if(arrow_offset.size()==4){
                    //first arrow line
                    add_object_items(cad_counter+1);
                    double_cad_array[cad_counter+1][0] = ax;
                    double_cad_array[cad_counter+1][1] = ay;
                    double_cad_array[cad_counter+1][3] = arrow_offset.at(2);
                    double_cad_array[cad_counter+1][4] = arrow_offset.at(3);

                }

                QList<double> mirror = mirror_point(ax,ay,bx,by,arrow_offset.at(2),arrow_offset.at(3));
                if(mirror.size()==2){
                    //second arrow line
                    add_object_items(cad_counter+2);
                    double_cad_array[cad_counter+2][0] = ax;
                    double_cad_array[cad_counter+2][1] = ay;
                    double_cad_array[cad_counter+2][3] = mirror.at(0);
                    double_cad_array[cad_counter+2][4] = mirror.at(1);
                }

                //add arrow standup line
                add_object_items(cad_counter+3);
                double_cad_array[cad_counter+3][0] = arrow_offset.at(2);
                double_cad_array[cad_counter+3][1] = arrow_offset.at(3);
                double_cad_array[cad_counter+3][3] = mirror.at(0);
                double_cad_array[cad_counter+3][4] = mirror.at(1);

                arrow_offset.clear();
                mirror.clear();
                line_offset.clear();
            }

            //offset select 2 line..
            line_offset = offset_line_by_points_to_side(double_cad_array[angle_select_2][0],double_cad_array[angle_select_2][1], double_cad_array[cad_counter][3],double_cad_array[cad_counter][4],arrow_lenght,double_cad_array[cad_counter][15],double_cad_array[cad_counter][16]);
            if(line_offset.size()==4){

                //arrowlenght middle line..
                double ax = double_cad_array[cad_counter][3];
                double ay = double_cad_array[cad_counter][4];
                double bx = line_offset.at(2);
                double by = line_offset.at(3);

                //arrowlenght offset line.. direction is arc center..
                QList<double> arrow_offset = offset_line_by_points_to_side(ax,ay,bx,by,(0.5*arrow_height),0,0);
                if(arrow_offset.size()==4){
                    //first arrow line..
                    add_object_items(cad_counter+4);
                    double_cad_array[cad_counter+4][0] = ax;
                    double_cad_array[cad_counter+4][1] = ay;
                    double_cad_array[cad_counter+4][3] = arrow_offset.at(2);
                    double_cad_array[cad_counter+4][4] = arrow_offset.at(3);

                }

                QList<double> mirror = mirror_point(ax,ay,bx,by,arrow_offset.at(2),arrow_offset.at(3));
                if(mirror.size()==2){
                    //second arrow line..
                    add_object_items(cad_counter+5);
                    double_cad_array[cad_counter+5][0] = ax;
                    double_cad_array[cad_counter+5][1] = ay;
                    double_cad_array[cad_counter+5][3] = mirror.at(0);
                    double_cad_array[cad_counter+5][4] = mirror.at(1);
                }

                //add arrow standup line
                add_object_items(cad_counter+6);
                double_cad_array[cad_counter+6][0] = arrow_offset.at(2);
                double_cad_array[cad_counter+6][1] = arrow_offset.at(3);
                double_cad_array[cad_counter+6][3] = mirror.at(0);
                double_cad_array[cad_counter+6][4] = mirror.at(1);

                arrow_offset.clear();
                mirror.clear();
                line_offset.clear();
            }

        }
        if(dimension_type == "angle_3p"){
            messagebox_text = "<b><i>mode dimension </i></b> type : angle 3 points";

            //dimension base line..
            //left under arrow upstand line
            int_cad_array[cad_counter][0] = 3; //id arc
            int_cad_array[cad_counter][5] = current_linetype;
            double_cad_array[cad_counter][2] = 0; //z start
            double_cad_array[cad_counter][5] = 0; //z end
            double_cad_array[cad_counter][18] = current_linetype_scale;
            double_cad_array[cad_counter][19] = current_linewidth;
            double_cad_array[cad_counter][56] = current_gui_color_red_gl;
            double_cad_array[cad_counter][57] = current_gui_color_green_gl;
            double_cad_array[cad_counter][58] = current_gui_color_blue_gl;
            double_cad_array[cad_counter][59] = current_gui_color_alpha_gl;

            //arc center..
            double_cad_array[cad_counter][6] = p1x;
            double_cad_array[cad_counter][7] = p1y;

            //arc radius..
            double_cad_array[cad_counter][9] = sqrt(pow(snap_cad_pos_x-double_cad_array[cad_counter][6],2)+pow(snap_cad_pos_y-double_cad_array[cad_counter][7],2)); //qDebug()<< "arc radius : " << double_cad_array[cad_counter][9];

            //intersection 1..
            QList<double> list = circle_line_intersection_by_points(p1x,p1y,double_cad_array[cad_counter][9],p1x,p1y,p0x,p0y);
            if(list.size()==2){
                double_cad_array[cad_counter][0] = list.at(0);
                double_cad_array[cad_counter][1] = list.at(1); //qDebug()<< "intersection 1 x : " <<  double_cad_array[cad_counter][0] << " y : " <<  double_cad_array[cad_counter][1];
                list.clear();
            }

            //intersection 2..
            list = circle_line_intersection_by_points(p1x,p1y,double_cad_array[cad_counter][9],p1x,p1y,p2x,p2y);
            if(list.size()==2){
                double_cad_array[cad_counter][3] = list.at(0);
                double_cad_array[cad_counter][4] = list.at(1); //qDebug()<< "intersection 2 x : " <<  double_cad_array[cad_counter][3] << " y : " <<  double_cad_array[cad_counter][4];
                list.clear();
            }

            //draw arc..
            list = draw_3p_arc(double_cad_array[cad_counter][0],double_cad_array[cad_counter][1],snap_cad_pos_x,snap_cad_pos_y,double_cad_array[cad_counter][3],double_cad_array[cad_counter][4]);
            if(list.size()==4){
                double_cad_array[cad_counter][11] = list.at(0);
                double_cad_array[cad_counter][12] = list.at(1);
                double_cad_array[cad_counter][15] = list.at(2); //midpoint x
                double_cad_array[cad_counter][16] = list.at(3);
                list.clear();
            }

            //offset select 1 line..
            QList<double> line_offset = offset_line_by_points_to_side(p1x,p1y, double_cad_array[cad_counter][0],double_cad_array[cad_counter][1],arrow_lenght,double_cad_array[cad_counter][15],double_cad_array[cad_counter][16]);
            if(line_offset.size()==4){

                //arrowlenght middle line..
                double ax = double_cad_array[cad_counter][0];
                double ay = double_cad_array[cad_counter][1];
                double bx = line_offset.at(2);
                double by = line_offset.at(3);

                //arrowlenght offset line.. direction is arc center..
                QList<double> arrow_offset = offset_line_by_points_to_side(ax,ay,bx,by,(0.5*arrow_height),0,0);
                if(arrow_offset.size()==4){
                    //first arrow line
                    add_object_items(cad_counter+1);
                    double_cad_array[cad_counter+1][0] = ax;
                    double_cad_array[cad_counter+1][1] = ay;
                    double_cad_array[cad_counter+1][3] = arrow_offset.at(2);
                    double_cad_array[cad_counter+1][4] = arrow_offset.at(3);

                }

                QList<double> mirror = mirror_point(ax,ay,bx,by,arrow_offset.at(2),arrow_offset.at(3));
                if(mirror.size()==2){
                    //second arrow line
                    add_object_items(cad_counter+2);
                    double_cad_array[cad_counter+2][0] = ax;
                    double_cad_array[cad_counter+2][1] = ay;
                    double_cad_array[cad_counter+2][3] = mirror.at(0);
                    double_cad_array[cad_counter+2][4] = mirror.at(1);
                }

                //add arrow standup line
                add_object_items(cad_counter+3);
                double_cad_array[cad_counter+3][0] = arrow_offset.at(2);
                double_cad_array[cad_counter+3][1] = arrow_offset.at(3);
                double_cad_array[cad_counter+3][3] = mirror.at(0);
                double_cad_array[cad_counter+3][4] = mirror.at(1);

                arrow_offset.clear();
                mirror.clear();
                line_offset.clear();
            }

            //offset select 2 line..
            line_offset = offset_line_by_points_to_side(p1x,p1y, double_cad_array[cad_counter][3],double_cad_array[cad_counter][4],arrow_lenght,double_cad_array[cad_counter][15],double_cad_array[cad_counter][16]);
            if(line_offset.size()==4){

                //arrowlenght middle line..
                double ax = double_cad_array[cad_counter][3];
                double ay = double_cad_array[cad_counter][4];
                double bx = line_offset.at(2);
                double by = line_offset.at(3);

                //arrowlenght offset line.. direction is arc center..
                QList<double> arrow_offset = offset_line_by_points_to_side(ax,ay,bx,by,(0.5*arrow_height),0,0);
                if(arrow_offset.size()==4){
                    //first arrow line..
                    add_object_items(cad_counter+4);
                    double_cad_array[cad_counter+4][0] = ax;
                    double_cad_array[cad_counter+4][1] = ay;
                    double_cad_array[cad_counter+4][3] = arrow_offset.at(2);
                    double_cad_array[cad_counter+4][4] = arrow_offset.at(3);

                }

                QList<double> mirror = mirror_point(ax,ay,bx,by,arrow_offset.at(2),arrow_offset.at(3));
                if(mirror.size()==2){
                    //second arrow line..
                    add_object_items(cad_counter+5);
                    double_cad_array[cad_counter+5][0] = ax;
                    double_cad_array[cad_counter+5][1] = ay;
                    double_cad_array[cad_counter+5][3] = mirror.at(0);
                    double_cad_array[cad_counter+5][4] = mirror.at(1);
                }

                //add arrow standup line
                add_object_items(cad_counter+6);
                double_cad_array[cad_counter+6][0] = arrow_offset.at(2);
                double_cad_array[cad_counter+6][1] = arrow_offset.at(3);
                double_cad_array[cad_counter+6][3] = mirror.at(0);
                double_cad_array[cad_counter+6][4] = mirror.at(1);

                arrow_offset.clear();
                mirror.clear();
                line_offset.clear();
            }
        }
    }

    if(click == 7){ //write data section..
        if(dimension_type == "horizontal"){
            int_cad_array[cad_counter+2][9] = 1; //add flag 1 = dimension base line + horizontal text..
            //displaying text value is done in opengl display_text section..

            double_cad_array[cad_counter+2][21] = p0x;
            double_cad_array[cad_counter+2][22] = p0y;
            double_cad_array[cad_counter+2][23] = p1x;
            double_cad_array[cad_counter+2][24] = p1y;
            double_cad_array[cad_counter+2][13] = dimension_text_height; //dimension text height..



            cad_counter+=9;
            click = 8;
        }
        if(dimension_type == "vertical"){
            int_cad_array[cad_counter+2][9] = 2; //add flag 2 = dimension base line + vertical text..
            double_cad_array[cad_counter+2][21] = p0x;
            double_cad_array[cad_counter+2][22] = p0y;
            double_cad_array[cad_counter+2][23] = p1x;
            double_cad_array[cad_counter+2][24] = p1y;
            double_cad_array[cad_counter+2][13] = dimension_text_height; //dimension text height..

            cad_counter+=9;
            click = 8;
        }
        if(dimension_type == "non_ortho"){
            int_cad_array[cad_counter][9] = 3; //add flag 3 = dimension base line + non_ortho text..
            double_cad_array[cad_counter][21] = p0x;
            double_cad_array[cad_counter][22] = p0y;
            double_cad_array[cad_counter][23] = p1x;
            double_cad_array[cad_counter][24] = p1y;
            double_cad_array[cad_counter][13] = dimension_text_height; //dimension text height..

            cad_counter+=9;
            click = 8;
        }
        if(dimension_type == "diameter" || dimension_type == "radius"){

            if(dimension_type == "diameter"){
                int_cad_array[cad_counter][9] = 4; //add flag 4 = diameter..
            }
            if(dimension_type == "radius"){
                int_cad_array[cad_counter][9] = 5; //add flag 5 = radius..
            }

            double_cad_array[cad_counter][9] = double_cad_array[select_id][9]; //add radius value to base line..
            double_cad_array[cad_counter][21] = p0x;
            double_cad_array[cad_counter][22] = p0y;
            double_cad_array[cad_counter][23] = double_cad_array[select_id][6];
            double_cad_array[cad_counter][24] = double_cad_array[select_id][7];
            double_cad_array[cad_counter][13] = dimension_text_height; //dimension text height..

            //dimension base line..
            add_object_items(cad_counter);
            double_cad_array[cad_counter][0] = p0x;
            double_cad_array[cad_counter][1] = p0y;
            double_cad_array[cad_counter][3] = double_cad_array[select_id][6];
            double_cad_array[cad_counter][4] = double_cad_array[select_id][7];

            //arrow standup line intersection..
            QList<double> list;
            list = offset_point_on_line(p0x,p0y,double_cad_array[select_id][6],double_cad_array[select_id][7],arrow_lenght);
            double i_x = list.at(0);
            double i_y = list.at(1);
            list.clear();

            list = offset_line(p0x,p0y,i_x,i_y,(0.5*arrow_height),90);
            //arrow line above..
            add_object_items(cad_counter+1);
            double_cad_array[cad_counter+1][0] = p0x;
            double_cad_array[cad_counter+1][1] = p0y;
            double_cad_array[cad_counter+1][3] = list.at(2);
            double_cad_array[cad_counter+1][4] = list.at(3);
            list.clear();

            list = mirror_point(p0x,p0y,double_cad_array[select_id][6],double_cad_array[select_id][7],double_cad_array[cad_counter+1][3],double_cad_array[cad_counter+1][4]);

            //arrow line under..
            add_object_items(cad_counter+2);
            double_cad_array[cad_counter+2][0] = p0x;
            double_cad_array[cad_counter+2][1] = p0y;
            double_cad_array[cad_counter+2][3] = list.at(0);
            double_cad_array[cad_counter+2][4] = list.at(1);
            list.clear();

            //arrow line standup..
            add_object_items(cad_counter+3);
            double_cad_array[cad_counter+3][0] = double_cad_array[cad_counter+1][3];
            double_cad_array[cad_counter+3][1] = double_cad_array[cad_counter+1][4];
            double_cad_array[cad_counter+3][3] = double_cad_array[cad_counter+2][3];
            double_cad_array[cad_counter+3][4] = double_cad_array[cad_counter+2][4];

            //short in base line..
            add_object_items(cad_counter);
            double_cad_array[cad_counter][0] = i_x;
            double_cad_array[cad_counter][1] = i_y;
            double_cad_array[cad_counter][3] = double_cad_array[select_id][6];
            double_cad_array[cad_counter][4] = double_cad_array[select_id][7];

            cad_counter+=4;
            click = 8;
        }
        if(dimension_type == "angle_2p"){
            int_cad_array[cad_counter][9] = 6; //add flag 6
            double_cad_array[cad_counter][13] = dimension_text_height; //dimension text height..
            cad_counter+=7;
            click = 8;
        }
        if(dimension_type == "angle_3p"){
            int_cad_array[cad_counter][9] = 6; //add flag 6
            double_cad_array[cad_counter][13] = dimension_text_height; //dimension text height..
            cad_counter+=7;
            click = 8;
        }
    }

    if(click == 8){
        click = 0;
        mode_dimension = 0;
        key_enter = 0;
        int_key = 0;
        entry_focus = 0;
        keyboard = 0;
        clear_user_input = 1;
        no_selection();
        messagebox_text = "<b><i>mode dimension </i></b> enter for repeat or Esc for cancel";
    }
}

QList<double>dimension::offset_line_by_points_to_side(double p0x, double p0y, double p1x, double p1y, double offset, double side_px, double side_py){

    QList<double> list;

    //offset line 1.. offset direction to other intersection..
    double d = ((p1x-p0x)*(side_py-p0y))-((p1y-p0y)*(side_px-p0x));
    if(d<0){
        rotate_degrees = -90;
    }
    if(d>0){
        rotate_degrees = 90;
    }
    //rotate orginal line..
    double dx = p1x - p0x;
    double dy = p1y - p0y;
    double rotate_x1 = cos(rotate_degrees * M_PI / 180.0 )* dx - sin(rotate_degrees * M_PI / 180.0 ) * dy;
    double rotate_y1 = sin(rotate_degrees * M_PI / 180.0 )* dx + cos(rotate_degrees * M_PI / 180.0 ) * dy;

    //modify line lenght to offset input..
    //calculate line length
    double object_x1 = rotate_x1 + p0x;
    double object_y1 = rotate_y1 + p0y;

    //formulat : A2 + B2 = C2
    double lenght = sqrt(pow(object_x1 - p0x,2)+pow(object_y1 - p0y,2));
    double p0x_out = p0x + (offset * (object_x1 - p0x) / lenght);
    double p0y_out = p0y + (offset * (object_y1 - p0y) / lenght);

    //calculate second line point..
    double p1x_out = p1x + (p0x_out - p0x);
    double p1y_out = p1y + (p0y_out - p0y);

    //fill list with line offset values..
    list.append(p0x_out);
    list.append(p0y_out);
    list.append(p1x_out);
    list.append(p1y_out);
    return list;
}

QList<double>dimension::offset_line_by_id_to_side(int id, double offset, double side_px, double side_py){

    QList<double> list;

    double p0x=double_cad_array[id][0];
    double p0y=double_cad_array[id][1];
    double p1x=double_cad_array[id][3];
    double p1y=double_cad_array[id][4];

    //offset line 1.. offset direction to other intersection..
    double d = ((p1x-p0x)*(side_py-p0y))-((p1y-p0y)*(side_px-p0x));
    if(d<0){
        rotate_degrees = -90;
    }
    if(d>0){
        rotate_degrees = 90;
    }
    //rotate orginal line..
    double dx = p1x - p0x;
    double dy = p1y - p0y;
    double rotate_x1 = cos(rotate_degrees * M_PI / 180.0 )* dx - sin(rotate_degrees * M_PI / 180.0 ) * dy;
    double rotate_y1 = sin(rotate_degrees * M_PI / 180.0 )* dx + cos(rotate_degrees * M_PI / 180.0 ) * dy;

    //modify line lenght to offset input..
    //calculate line length
    double object_x1 = rotate_x1 + p0x;
    double object_y1 = rotate_y1 + p0y;

    //formulat : A2 + B2 = C2
    double lenght = sqrt(pow(object_x1 - p0x,2)+pow(object_y1 - p0y,2));
    double p0x_out = p0x + (offset * (object_x1 - p0x) / lenght);
    double p0y_out = p0y + (offset * (object_y1 - p0y) / lenght);

    //calculate second line point..
    double p1x_out = p1x + (p0x_out - p0x);
    double p1y_out = p1y + (p0y_out - p0y);

    //fill list with line offset values..
    list.append(p0x_out);
    list.append(p0y_out);
    list.append(p1x_out);
    list.append(p1y_out);
    return list;
}

QList<double>dimension::draw_3p_arc(double p0x, double p0y, double p1x, double p1y, double p2x, double p2y)
{
    QList<double> list;

    //calculate 3 point circle... calculate xy center and radius..
    // Get the perpendicular bisector of (x1, y1) and (x2, y2).
    double x1 = (p1x + p0x) / 2;
    double y1 = (p1y + p0y) / 2;
    double dy1 = p1x - p0x;
    double dx1 = -(p1y - p0y);

    // Get the perpendicular bisector of (x2, y2) and (x3, y3).
    double x2 = (p2x + p1x) / 2;
    double y2 = (p2y + p1y) / 2;
    double dy2 = p2x - p1x;
    double dx2 = -(p2y - p1y);

    double endpoint_x0 = x1 + dx1;
    double endpoint_y0 = y1 + dy1;
    double endpoint_x1 = x2 + dx2;
    double endpoint_y1 = y2 + dy2;

    //line 1
    double delta_y0 = endpoint_y0 - y1;
    double delta_x0 = x1 - endpoint_x0;
    double c0 = delta_y0 * x1 + delta_x0 * y1;
    //line 2
    double delta_y1 = endpoint_y1 - y2;
    double delta_x1 = x2 - endpoint_x1;
    double c1 = delta_y1 * x2 + delta_x1 * y2;

    double determinant = delta_y0*delta_x1 - delta_y1*delta_x0;
    //qDebug() << "determinant is : " << determinant;

    if (determinant == 0) // The lines are parallel.
    {
        //qDebug() << "the lines are parallel";
        list.append(0);
        list.append(0);
        list.append(0);
        list.append(0);
        return list;
    }
    else  {
        double x_center = (delta_x1*c0 - delta_x0*c1)/determinant;
        double y_center = (delta_y0*c1 - delta_y1*c0)/determinant;
        double radius = sqrt(pow(x_center - p0x,2) + pow(y_center - p0y,2));
        double d = ((p1x-p0x)*(p2y-p0y))-((p1y-p0y)*(p2x-p0x));

        if(d < 0){
            list.append(180/M_PI*atan2(p2y-y_center, p2x-x_center));    //start angle G2
            list.append(180/M_PI*atan2(p0y-y_center, p0x-x_center));    //end angle G2

            //calculate arc midpoint..
            double radian_start = atan2(p2y-y_center, p2x-x_center); //qDebug() << "radian_start : " << radian_start;
            double radian_end = atan2(p0y-y_center, p0x-x_center);   //qDebug() << "radian_end : " << radian_end;
            if (radian_end < radian_start){  //this to avoid the start angle is bigger then the end angle value
                radian_end += 2*M_PI;
            }
            double radian_mid = (radian_start+radian_end)/2;       //qDebug() << "radian_mid : " << radian_mid;
            double rotate_x = cos(radian_mid)* radius - sin(radian_mid) * 0;
            double rotate_y = sin(radian_mid)* radius + cos(radian_mid) * 0;
            list.append(rotate_x + double_cad_array[cad_counter][6]);//x_center..
            list.append(double_cad_array[cad_counter][16] = rotate_y + double_cad_array[cad_counter][7]);//y_center..
            return list;
        }

        if(d > 0){
            list.append(180/M_PI*atan2(p0y-y_center, p0x-x_center));    //start angle G3
            list.append(180/M_PI*atan2(p2y-y_center, p2x-x_center));    //end angle G3

            //calculate arc midpoint..
            double radian_start = atan2(p0y-y_center, p0x-x_center); //qDebug() << "radian_start : " << radian_start;
            double radian_end = atan2(p2y-y_center, p2x-x_center);   //qDebug() << "radian_end : " << radian_end;
            if (radian_end < radian_start){  //this to avoid the start angle is bigger then the end angle value
                radian_end += 2*M_PI;
            }
            double radian_mid = (radian_start+radian_end)/2;       //qDebug() << "radian_mid : " << radian_mid;
            double rotate_x = cos(radian_mid)* radius - sin(radian_mid) * 0;
            double rotate_y = sin(radian_mid)* radius + cos(radian_mid) * 0;
            list.append(rotate_x + double_cad_array[cad_counter][6]);//x_center..
            list.append(double_cad_array[cad_counter][16] = rotate_y + double_cad_array[cad_counter][7]);//y_center..
            return list;
        }
        if(d == 0){
            list.append(0);
            list.append(0);
            list.append(0);
            list.append(0);
            return list;
        }
    }
}

QList<double>dimension::circle_line_intersection_by_points(double cpx, double cpy, double radius, double p0x, double p0y, double p1x, double p1y)
{
    QList<double> list; //circle = cpx,xpy,radius    line = p0x,p0y,p1x,p1y

    double dx, dy, A, B, C, det, t;
    dx = p1x - p0x;
    dy = p1y - p0y;
    A = dx * dx + dy * dy;
    B = 2 * (dx * (p0x - cpx) + dy * (p0y - cpy));
    C = (p0x - cpx) * (p0x - cpx) + (p0y - cpy) * (p0y - cpy) - radius * radius;
    det = B * B - 4 * A * C;
    t = (-B + sqrt(det)) / (2 * A);

    double i_x0 = (p0x + t * dx);
    double i_y0 = (p0y + t * dy);

    t = (-B - sqrt(det)) / (2 * A);
    double i_x1 = (p0x + t * dx);
    double i_y1 = (p0y + t * dy);

    //check wich side of intersection the point is on the line..
    double a = sqrt(pow(i_x0-p0x,2) + pow(i_y0-p0y,2));
    double b = sqrt(pow(p1x-i_x0,2) + pow(p1y-i_y0,2));
    double c = sqrt(pow(p1x-p0x,2) + pow(p1y-p0y,2));

    double a1 = sqrt(pow(i_x1-p0x,2) + pow(i_y1-p0y,2));
    double b1 = sqrt(pow(p1x-i_x1,2) + pow(p1y-i_y1,2));
    double c1 = sqrt(pow(p1x-p0x,2) + pow(p1y-p0y,2));

    if(a+b==c){

        list.append(i_x0);
        list.append(i_y0);
        return list;
    }
    if(a1+b1==c1){

        list.append(i_x1);
        list.append(i_y1);
        return list;

    }
}

QList<double>dimension::offset_line(double p0x, double p0y, double p1x, double p1y, double offset, double rotate_degrees){ //rotate degrees 90 or -90

    QList<double> list;

    //rotate orginal line..
    double dx = p1x - p0x;
    double dy = p1y - p0y;
    double rotate_x1 = cos(rotate_degrees * M_PI / 180.0 )* dx - sin(rotate_degrees * M_PI / 180.0 ) * dy;
    double rotate_y1 = sin(rotate_degrees * M_PI / 180.0 )* dx + cos(rotate_degrees * M_PI / 180.0 ) * dy;

    //modify line lenght to offset input..
    //calculate line length
    double object_x1 = rotate_x1 + p0x;
    double object_y1 = rotate_y1 + p0y;

    //formulat : A2 + B2 = C2
    double lenght = sqrt(pow(object_x1 - p0x,2)+pow(object_y1 - p0y,2));
    double p0x_out = p0x + (offset * (object_x1 - p0x) / lenght);
    double p0y_out = p0y + (offset * (object_y1 - p0y) / lenght);

    //calculate second line point..
    double p1x_out = p1x + (p0x_out - p0x);
    double p1y_out = p1y + (p0y_out - p0y);

    //fill list with line offset values..
    list.append(p0x_out);
    list.append(p0y_out);
    list.append(p1x_out);
    list.append(p1y_out);
    return list;
}

QList<double>dimension::mirror_point(double p0x, double p0y, double p1x, double p1y, double px, double py)
{
    QList<double> list;

    double dx  = p1x-p0x;
    double dy  = p1y-p0y;
    double c = (dx*dx-dy*dy)/(dx*dx+dy*dy);
    double d = 2*dx*dy/(dx*dx+dy*dy);
    double pxm = (c*(px-p0x)+d*(py-p0y)+p0x);
    double pym = (d*(px-p0x)-c*(py-p0y)+p0y);

    list.append(pxm);
    list.append(pym);
    return list;
}

QList<double>dimension::offset_point_on_line(double p0x, double p0y, double p1x, double p1y, double offset)
{
    // point : A----------B---------C
    //         |--offset--|
    // A(p0x,p0y)
    // C(p1x,p1y)

    QList<double> list;
    double AC = sqrt(pow(p1x-p0x,2)+pow(p1y-p0y,2)); //has the dimension text value..
    double AB = offset;

    //left offset..
    double Xa = p0x + (AB * (p1x - p0x) / AC);
    double Ya = p0y + (AB * (p1y - p0y) / AC); //qDebug()<< "arrow left intersection x : " << Xa << " y : " << Ya;
    //right offset..
    double Xb = p1x + (AB * (p0x - p1x) / AC);
    double Yb = p1y + (AB * (p0y - p1y) / AC); //qDebug()<< "arrow left intersection x : " << Xb << " y : " << Yb;

    list.append(Xa);
    list.append(Ya);
    list.append(Xb);
    list.append(Yb);
    return list;
}

QList<double>dimension::line_line_intersection_by_id(int id1, int id2)
{
    QList<double> list; //line 1 = p0x,p0y,p1x,p1y line 2 = p2x,p2y,p3x,p3y..

    double p0x=double_cad_array[id1][0];
    double p0y=double_cad_array[id1][1];
    double p1x=double_cad_array[id1][3];
    double p1y=double_cad_array[id1][4];

    double p2x=double_cad_array[id2][0];
    double p2y=double_cad_array[id2][1];
    double p3x=double_cad_array[id2][3];
    double p3y=double_cad_array[id2][4];

    double d_y1 = p1y - p0y; //line 1
    double d_x1 = p0x - p1x;
    double c0 = d_y1 * p0x + d_x1 * p0y;
    double d_y2 = p3y - p2y; //line 2
    double d_x2 = p2x - p3x;
    double c1 = d_y2 * p2x + d_x2 * p2y;
    double determinant = d_y1*d_x2 - d_y2*d_x1;

    if(determinant == 0){
        //qDebug() << "the lines are parallel";
        if(p0x==p2x){
            list.append(p0x);
            list.append(p0y);
        }
        if(p0x==p3x){
            list.append(p0x);
            list.append(p0y);
        }
        if(p1x==p2x){
            list.append(p1x);
            list.append(p1y);
        }
        if(p1x==p3x){
            list.append(p1x);
            list.append(p1y);
        }
        return list;
    } else  {
        double x = (d_x2*c0 - d_x1*c1)/determinant;
        double y = (d_y1*c1 - d_y2*c0)/determinant;
        list.append(x);
        list.append(y);
        return list;
    }
}

QList<double>dimension::line_line_intersection_by_points(double p0x, double p0y, double p1x, double p1y, double p2x, double p2y, double p3x, double p3y)
{
    QList<double> list; //line 1 = p0x,p0y,p1x,p1y line 2 = p2x,p2y,p3x,p3y..
    double d_y1 = p1y - p0y; //line 1
    double d_x1 = p0x - p1x;
    double c0 = d_y1 * p0x + d_x1 * p0y;
    double d_y2 = p3y - p2y; //line 2
    double d_x2 = p2x - p3x;
    double c1 = d_y2 * p2x + d_x2 * p2y;
    double determinant = d_y1*d_x2 - d_y2*d_x1;

    if(determinant == 0){
        //qDebug() << "the lines are parallel";
        if(p0x==p2x){
            list.append(p0x);
            list.append(p0y);
        }
        if(p0x==p3x){
            list.append(p0x);
            list.append(p0y);
        }
        if(p1x==p2x){
            list.append(p1x);
            list.append(p1y);
        }
        if(p1x==p3x){
            list.append(p1x);
            list.append(p1y);
        }
        return list;

    } else  {
        double x = (d_x2*c0 - d_x1*c1)/determinant;
        double y = (d_y1*c1 - d_y2*c0)/determinant;
        list.append(x);
        list.append(y);
        return list;
    }
}

void add_object_items(int i)
{
    //left under arrow upstand line
    int_cad_array[i][0] = 1; //id line
    int_cad_array[i][5] = current_linetype;
    double_cad_array[i][2] = 0; //z start
    double_cad_array[i][5] = 0; //z end
    double_cad_array[i][18] = current_linetype_scale;
    double_cad_array[i][19] = current_linewidth;
    double_cad_array[i][56] = current_gui_color_red_gl;
    double_cad_array[i][57] = current_gui_color_green_gl;
    double_cad_array[i][58] = current_gui_color_blue_gl;
    double_cad_array[i][59] = current_gui_color_alpha_gl;

}



















































