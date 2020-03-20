#include "polygon.h"
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

polygon::polygon()
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
        object_select_line_nearest(1);
        object_select_arc_nearest(1);
        object_select_circle_nearest(1);
        object_select_ellipse_nearest(1);
        object_select_hermite_spline_nearest(1);
        object_select_bezier_curve_nearest(1);
    }

    if(click == 0){
        messagebox_text = "<b><i>mode polygon </i></b> insert polygon sides, click polygon centerpoint";
        entry_focus = 1;
    }

    if(click == 1){

        //qDebug() << "click = 1";
        x_center = snap_cad_pos_x;
        y_center = snap_cad_pos_y;
        click = 2;

        polygon_sides = string_user_input.toInt();
        entry_focus = 0;
    }

    if(click == 2){

        if(polygon_sides<3){polygon_sides = 3;}

        messagebox_text = "<b><i>mode polygon </i></b> click second polygon point ";
        //polygon preview..

        //qDebug() << "click = 2";

        //mouse clicked radius of polygon
        double x_start = snap_cad_pos_x; //radius x
        double y_start = snap_cad_pos_y; //radius y

        double dist_x = x_start - x_center;
        double dist_y = y_start - y_center;
        double radius = sqrt(pow(dist_x,2) + pow(dist_y,2)); //radius
        //qDebug() << "radius is : " << radius;

        double cake_angle = 360 / polygon_sides;
        //qDebug() << "cake angle is : " << cake_angle;

        if (polygon_sides % 2 == 0){
            even = 1;
            //qDebug() << "value is even";

        } else {
            even = 0;
            //qDebug() << "value is odd";
        }

        if(!mode_ortho){ //ortho off
            if(even == 1){
                //next polygon lines....
                start_angle = atan2(y_center - y_start, x_center - x_start)* 180.0 / M_PI;

                //qDebug() << "start_angle = " << start_angle;
                for(int i=0; i<polygon_sides; i++){

                    x3 = x_center + (radius * cos ( start_angle * M_PI / 180.0 ));
                    y3 = y_center + (radius * sin ( start_angle * M_PI / 180.0 ));
                    x4 = x_center + (radius * cos ( (start_angle + cake_angle) * M_PI / 180.0 ));
                    y4 = y_center + (radius * sin ( (start_angle + cake_angle) * M_PI / 180.0 ));

                    int_cad_array[cad_counter + i][0] = 1; //id line

                    double_cad_array[cad_counter+i][56] = current_gui_color_red_gl;
                    double_cad_array[cad_counter+i][57] = current_gui_color_green_gl;
                    double_cad_array[cad_counter+i][58] = current_gui_color_blue_gl;
                    double_cad_array[cad_counter+i][59] = current_gui_color_alpha_gl;

                    int_cad_array[cad_counter+i][5] = current_linetype;
                    double_cad_array[cad_counter+i][18] = current_linetype_scale;
                    double_cad_array[cad_counter+i][19] = current_linewidth;

                    double_cad_array[cad_counter + i][0] = x3;
                    double_cad_array[cad_counter + i][1] = y3;
                    double_cad_array[cad_counter + i][2] = snap_cad_pos_z;
                    double_cad_array[cad_counter + i][3] = x4;
                    double_cad_array[cad_counter + i][4] = y4;
                    double_cad_array[cad_counter + i][5] = snap_cad_pos_z;
                    //cad_counter++;

                    start_angle += cake_angle;
                    //qDebug() << "start_angle = " << start_angle;
                }
                //cad_counter++;
            }

            if(even == 0){
                //next polygon lines....
                start_angle = atan2(y_center - y_start, x_center - x_start)* 180.0 / M_PI;

                //qDebug() << "start_angle = " << start_angle;
                for(int i=0; i<polygon_sides; i++){

                    x3 = x_center + (radius * cos ( (start_angle + (0.5*cake_angle)) * M_PI / 180.0 ));
                    y3 = y_center + (radius * sin ( (start_angle + (0.5*cake_angle)) * M_PI / 180.0 ));
                    x4 = x_center + (radius * cos ( ((start_angle + cake_angle) + (0.5*cake_angle)) * M_PI / 180.0 ));
                    y4 = y_center + (radius * sin ( ((start_angle + cake_angle) + (0.5*cake_angle)) * M_PI / 180.0 ));

                    int_cad_array[cad_counter + i][0] = 1; //id line
                    //int_cad_array[cad_counter + i][1] = current_gui_color; //color white
                    double_cad_array[cad_counter+i][56] = current_gui_color_red_gl;
                    double_cad_array[cad_counter+i][57] = current_gui_color_green_gl;
                    double_cad_array[cad_counter+i][58] = current_gui_color_blue_gl;
                    double_cad_array[cad_counter+i][59] = current_gui_color_alpha_gl;

                    int_cad_array[cad_counter+i][5] = current_linetype;
                    double_cad_array[cad_counter+i][18] = current_linetype_scale;
                    double_cad_array[cad_counter+i][19] = segments;

                    double_cad_array[cad_counter + i][0] = x3;
                    double_cad_array[cad_counter + i][1] = y3;
                    double_cad_array[cad_counter + i][2] = snap_cad_pos_z;
                    double_cad_array[cad_counter + i][3] = x4;
                    double_cad_array[cad_counter + i][4] = y4;
                    double_cad_array[cad_counter + i][5] = snap_cad_pos_z;
                    //cad_counter++;

                    start_angle += cake_angle;
                    //qDebug() << "start_angle = " << start_angle;
                }
                //cad_counter++;
            }
        }

        if(mode_ortho){ //ortho on
            //next polygon lines....
            start_angle = cake_angle;

            for(int i=0; i<polygon_sides; i++){

                x3 = x_center + (radius * cos ( start_angle * M_PI / 180.0 ));
                y3 = y_center + (radius * sin ( start_angle * M_PI / 180.0 ));
                x4 = x_center + (radius * cos ( (start_angle + cake_angle) * M_PI / 180.0 ));
                y4 = y_center + (radius * sin ( (start_angle + cake_angle) * M_PI / 180.0 ));

                int_cad_array[cad_counter + i][0] = 1; //id line

                double_cad_array[cad_counter+i][56] = current_gui_color_red_gl;
                double_cad_array[cad_counter+i][57] = current_gui_color_green_gl;
                double_cad_array[cad_counter+i][58] = current_gui_color_blue_gl;
                double_cad_array[cad_counter+i][59] = current_gui_color_alpha_gl;

                int_cad_array[cad_counter+i][5] = current_linetype;
                double_cad_array[cad_counter+i][18] = current_linetype_scale;
                double_cad_array[cad_counter+i][19] = segments;

                double_cad_array[cad_counter + i][0] = x3;
                double_cad_array[cad_counter + i][1] = y3;
                double_cad_array[cad_counter + i][2] = snap_cad_pos_z;
                double_cad_array[cad_counter + i][3] = x4;
                double_cad_array[cad_counter + i][4] = y4;
                double_cad_array[cad_counter + i][5] = snap_cad_pos_z;
                //cad_counter++;

                start_angle += cake_angle;
                //qDebug() << "start_angle = " << start_angle;
            }
        }
    }

    if(click == 3){

        //write polygon..

        //result = asin (param) * 180.0 / PI;
        //X = Cx + (r * cosine(angle))
        //Y = Cy + (r * sine(angle))
        //float angle between 2 points = atan2(p1.y - p2.y, p1.x - p2.x)* 180.0 / PI;

        //qDebug() << "click = 2";

        //mouse clicked radius of polygon
        double x_start = snap_cad_pos_x; //radius x
        double y_start = snap_cad_pos_y; //radius y

        double dist_x = x_start - x_center;
        double dist_y = y_start - y_center;
        double radius = sqrt(pow(dist_x,2) + pow(dist_y,2)); //radius
        //qDebug() << "radius is : " << radius;

        double cake_angle = 360 / polygon_sides;
        //qDebug() << "cake angle is : " << cake_angle;

        if (polygon_sides % 2 == 0){
            even = 1;
            //qDebug() << "value is even";

        } else {
            even = 0;
            //qDebug() << "value is odd";
        }

        if(!mode_ortho){ //ortho off
            if(even == 1){
                //next polygon lines....
                start_angle = atan2(y_center - y_start, x_center - x_start)* 180.0 / M_PI;

                //qDebug() << "start_angle = " << start_angle;
                for(int i=0; i<polygon_sides; i++){

                    x3 = x_center + (radius * cos ( start_angle * M_PI / 180.0 ));
                    y3 = y_center + (radius * sin ( start_angle * M_PI / 180.0 ));
                    x4 = x_center + (radius * cos ( (start_angle + cake_angle) * M_PI / 180.0 ));
                    y4 = y_center + (radius * sin ( (start_angle + cake_angle) * M_PI / 180.0 ));

                    int_cad_array[cad_counter][0] = 1; //id line
                    //int_cad_array[cad_counter][1] = current_gui_color; //color white
                    double_cad_array[cad_counter][56] = current_gui_color_red_gl;
                    double_cad_array[cad_counter][57] = current_gui_color_green_gl;
                    double_cad_array[cad_counter][58] = current_gui_color_blue_gl;
                    double_cad_array[cad_counter][59] = current_gui_color_alpha_gl;

                    int_cad_array[cad_counter][5] = current_linetype;
                    double_cad_array[cad_counter][18] = current_linetype_scale;
                    double_cad_array[cad_counter][19] = current_linewidth;

                    double_cad_array[cad_counter][0] = x3;
                    double_cad_array[cad_counter][1] = y3;
                    double_cad_array[cad_counter][2] = snap_cad_pos_z;
                    double_cad_array[cad_counter][3] = x4;
                    double_cad_array[cad_counter][4] = y4;
                    double_cad_array[cad_counter][5] = snap_cad_pos_z;

                    //write midpoints..
                    double_cad_array[cad_counter][15] =  (double_cad_array[cad_counter][0] +  double_cad_array[cad_counter][3]) / 2; //x midpoint..
                    double_cad_array[cad_counter][16] =  (double_cad_array[cad_counter][1] +  double_cad_array[cad_counter][4]) / 2; //y midpoint..
                    double_cad_array[cad_counter][17] =  (double_cad_array[cad_counter][2] +  double_cad_array[cad_counter][5]) / 2; //z midpoint..

                    cad_counter++;

                    start_angle += cake_angle;
                    //qDebug() << "start_angle = " << start_angle;
                }
                //cad_counter++;
            }

            if(even == 0){
                //next polygon lines....
                start_angle = atan2(y_center - y_start, x_center - x_start)* 180.0 / M_PI;

                //qDebug() << "start_angle = " << start_angle;
                for(int i=0; i<polygon_sides; i++){

                    x3 = x_center + (radius * cos ( (start_angle + (0.5*cake_angle)) * M_PI / 180.0 ));
                    y3 = y_center + (radius * sin ( (start_angle + (0.5*cake_angle)) * M_PI / 180.0 ));
                    x4 = x_center + (radius * cos ( ((start_angle + cake_angle) + (0.5*cake_angle)) * M_PI / 180.0 ));
                    y4 = y_center + (radius * sin ( ((start_angle + cake_angle) + (0.5*cake_angle)) * M_PI / 180.0 ));

                    int_cad_array[cad_counter][0] = 1; //id line
                    //int_cad_array[cad_counter][1] = current_gui_color; //color white
                    double_cad_array[cad_counter][56] = current_gui_color_red_gl;
                    double_cad_array[cad_counter][57] = current_gui_color_green_gl;
                    double_cad_array[cad_counter][58] = current_gui_color_blue_gl;
                    double_cad_array[cad_counter][59] = current_gui_color_alpha_gl;

                    int_cad_array[cad_counter][5] = current_linetype;
                    double_cad_array[cad_counter][18] = current_linetype_scale;
                    double_cad_array[cad_counter][19] = current_linewidth;

                    double_cad_array[cad_counter][0] = x3;
                    double_cad_array[cad_counter][1] = y3;
                    double_cad_array[cad_counter][2] = snap_cad_pos_z;
                    double_cad_array[cad_counter][3] = x4;
                    double_cad_array[cad_counter][4] = y4;
                    double_cad_array[cad_counter][5] = snap_cad_pos_z;

                    //write midpoints..
                    double_cad_array[cad_counter][15] =  (double_cad_array[cad_counter][0] +  double_cad_array[cad_counter][3]) / 2; //x midpoint..
                    double_cad_array[cad_counter][16] =  (double_cad_array[cad_counter][1] +  double_cad_array[cad_counter][4]) / 2; //y midpoint..
                    double_cad_array[cad_counter][17] =  (double_cad_array[cad_counter][2] +  double_cad_array[cad_counter][5]) / 2; //z midpoint..

                    cad_counter++;

                    start_angle += cake_angle;
                    //qDebug() << "start_angle = " << start_angle;
                }
                //cad_counter++;
            }
        }

        if(mode_ortho){ //ortho on
            //next polygon lines....
            start_angle = cake_angle;

            for(int i=0; i<polygon_sides; i++){

                x3 = x_center + (radius * cos ( start_angle * M_PI / 180.0 ));
                y3 = y_center + (radius * sin ( start_angle * M_PI / 180.0 ));
                x4 = x_center + (radius * cos ( (start_angle + cake_angle) * M_PI / 180.0 ));
                y4 = y_center + (radius * sin ( (start_angle + cake_angle) * M_PI / 180.0 ));

                int_cad_array[cad_counter][0] = 1; //id line
                //int_cad_array[cad_counter][1] = current_gui_color; //color white
                double_cad_array[cad_counter][56] = current_gui_color_red_gl;
                double_cad_array[cad_counter][57] = current_gui_color_green_gl;
                double_cad_array[cad_counter][58] = current_gui_color_blue_gl;
                double_cad_array[cad_counter][59] = current_gui_color_alpha_gl;

                int_cad_array[cad_counter][5] = current_linetype;
                double_cad_array[cad_counter][18] = current_linetype_scale;
                double_cad_array[cad_counter][19] = current_linewidth;

                double_cad_array[cad_counter][0] = x3;
                double_cad_array[cad_counter][1] = y3;
                double_cad_array[cad_counter][2] = snap_cad_pos_z;
                double_cad_array[cad_counter][3] = x4;
                double_cad_array[cad_counter][4] = y4;
                double_cad_array[cad_counter][5] = snap_cad_pos_z;

                //write midpoints..
                double_cad_array[cad_counter][15] =  (double_cad_array[cad_counter][0] +  double_cad_array[cad_counter][3]) / 2; //x midpoint..
                double_cad_array[cad_counter][16] =  (double_cad_array[cad_counter][1] +  double_cad_array[cad_counter][4]) / 2; //y midpoint..
                double_cad_array[cad_counter][17] =  (double_cad_array[cad_counter][2] +  double_cad_array[cad_counter][5]) / 2; //z midpoint..

                cad_counter++;

                start_angle += cake_angle;
                //qDebug() << "start_angle = " << start_angle;
            }
        }

        click = 0;
        mode_polygon = 0;
        clear_user_input = 1;
        no_selection();
        messagebox_text = "<b><i>mode polygon </i></b> enter for repeat or Esc for cancel";
    }

}































