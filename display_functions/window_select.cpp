#include "window_select.h"
#include <core_functions/variables.h>
#include <interface_functions/snapshot.h>
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

window_select::window_select(bool preview)
{
    object_select_line_nearest(0); //look if we can click something near the mouse pointer..
    object_select_circle_nearest(0);
    object_select_arc_nearest(0);
    object_select_ellipse_nearest(0);
    object_select_hermite_spline_nearest(0);
    object_select_bezier_curve_nearest(0);

    if(select_click == 0){
        select_id = -1;
    }

    if(select_click == 1){

        if(select_id > -1 && key_shift == 1){ //+key shift for disselect..
            int_cad_array[select_id][3] = 0;
            select_click = 0;
            //key_shift = 0;
        } else
        if(select_id > -1){
            int_cad_array[select_id][3] = 1;
            select_click = 0;
        } else
            if(select_id == -1){ //if nothing is near the mouse pointer, start drawing a window..
                x_start = mouse_cad_pos_x;
                y_start = mouse_cad_pos_y;
                select_click = 2;
            }
    }

    if(select_click == 2){

        if(preview){ //select window..

            glColor4f(1, 1, 1, 1);  //white
            glLineWidth(1);
            glLineStipple(1, 0xAAAA);
            glEnable(GL_LINE_STIPPLE);

            glBegin(GL_LINES);
            glVertex2d(x_start, y_start);                   //xy start
            glVertex2d(mouse_cad_pos_x, y_start);           //xy end
            glVertex2d(mouse_cad_pos_x, y_start);           //xy start
            glVertex2d(mouse_cad_pos_x, mouse_cad_pos_y);   //xy end
            glVertex2d(mouse_cad_pos_x, mouse_cad_pos_y);   //xy start
            glVertex2d(x_start, mouse_cad_pos_y);           //xy end
            glVertex2d(x_start, mouse_cad_pos_y);           //xy start
            glVertex2d(x_start, y_start);                   //xy start
            glEnd();
            //glDisable(GL_LINE_STIPPLE);
        }

        x_end = mouse_cad_pos_x;
        y_end = mouse_cad_pos_y;
    }

    if(select_click == 3){

        for(int i = 0; i < cad_counter; i++){

            //window from left to right, top to bottom.. only select object's if they are fully in the selected window..
            if( (x_start < x_end) && (y_start > y_end) ){

                if(int_cad_array[i][0] == 1 || int_cad_array[i][0] == 3 || int_cad_array[i][0] == 4 || int_cad_array[i][0] == 5 || int_cad_array[i][0] == 10 || int_cad_array[i][0] == 7 ){ //id 1 = line.. id 2 = circle.. id 3 = arc.. id 10 = text
                    //if startpoint and endpoint is in the window..
                    if( (double_cad_array[i][0] > x_start) && (double_cad_array[i][0] < x_end) &&
                            (double_cad_array[i][1] < y_start) && (double_cad_array[i][1] > y_end) &&
                            (double_cad_array[i][3] > x_start) && (double_cad_array[i][3] < x_end) &&
                            (double_cad_array[i][4] < y_start) && (double_cad_array[i][4] > y_end)
                            ){

                        int_cad_array[i][3] = 1;
                    }
                }

                if(int_cad_array[i][0] == 2){ //id = circle..
                    //if left, right, top and bottom circlepoint is in the window..
                    if( (double_cad_array[i][25] > x_start) && (double_cad_array[i][25] < x_end) &&
                            (double_cad_array[i][26] < y_start) && (double_cad_array[i][26] > y_end) &&

                            (double_cad_array[i][28] > x_start) && (double_cad_array[i][28] < x_end) &&
                            (double_cad_array[i][29] < y_start) && (double_cad_array[i][29] > y_end) &&

                            (double_cad_array[i][31] > x_start) && (double_cad_array[i][31] < x_end) &&
                            (double_cad_array[i][32] < y_start) && (double_cad_array[i][32] > y_end) &&


                            (double_cad_array[i][34] > x_start) && (double_cad_array[i][34] < x_end) &&
                            (double_cad_array[i][35] < y_start) && (double_cad_array[i][35] > y_end) ){

                        int_cad_array[i][3] = 1;
                    }
                }


                if(int_cad_array[i][0] == 6){ //id = cubic hermite spline.. use the control points. these are if fact the begin and end point of the visible spline..
                    //if startpoint and endpoint is in the window..
                    if( (double_cad_array[i][50] > x_start) && (double_cad_array[i][50] < x_end) &&
                            (double_cad_array[i][51] < y_start) && (double_cad_array[i][51] > y_end) &&
                            (double_cad_array[i][53] > x_start) && (double_cad_array[i][53] < x_end) &&
                            (double_cad_array[i][54] < y_start) && (double_cad_array[i][54] > y_end)
                            ){

                        int_cad_array[i][3] = 1;
                    }
                }
            }

            //window from right to left, bottom to top.. select all objects directly even when some points are outside the selected window..
            if( x_start > x_end && y_start < y_end ){

                if(int_cad_array[i][0] == 1 || int_cad_array[i][0] == 3 || int_cad_array[i][0] == 4 || int_cad_array[i][0] == 5 || int_cad_array[i][0] == 10 || int_cad_array[i][0] == 7 ){ //id = line.. id = arc..
                    //if startpoint and endpoint is in the window..
                    if(double_cad_array[i][0] < x_start && double_cad_array[i][0] > x_end && double_cad_array[i][1] > y_start && double_cad_array[i][1] < y_end){
                        int_cad_array[i][3] = 1;
                    }
                    if(double_cad_array[i][3] < x_start && double_cad_array[i][3] > x_end && double_cad_array[i][4] > y_start && double_cad_array[i][4] < y_end){
                        int_cad_array[i][3] = 1;
                    }
                }

                if(int_cad_array[i][0] == 2){ //id = circle..

                    if(double_cad_array[i][25] < x_start && double_cad_array[i][25] > x_end && double_cad_array[i][26] > y_start && double_cad_array[i][26] < y_end){
                        int_cad_array[i][3] = 1;
                    }
                    if(double_cad_array[i][28] < x_start && double_cad_array[i][28] > x_end && double_cad_array[i][29] > y_start && double_cad_array[i][29] < y_end){
                        int_cad_array[i][3] = 1;
                    }
                    if(double_cad_array[i][31] < x_start && double_cad_array[i][31] > x_end && double_cad_array[i][32] > y_start && double_cad_array[i][32] < y_end){
                        int_cad_array[i][3] = 1;
                    }
                    if(double_cad_array[i][34] < x_start && double_cad_array[i][34] > x_end && double_cad_array[i][35] > y_start && double_cad_array[i][35] < y_end){
                        int_cad_array[i][3] = 1;
                    }
                }

                if(int_cad_array[i][0] == 6){ //id = cubic hermite spline..
                    if(double_cad_array[i][50] < x_start && double_cad_array[i][50] > x_end && double_cad_array[i][51] > y_start && double_cad_array[i][51] < y_end){
                        int_cad_array[i][3] = 1;
                    }
                    if(double_cad_array[i][53] < x_start && double_cad_array[i][53] > x_end && double_cad_array[i][54] > y_start && double_cad_array[i][54] < y_end){
                        int_cad_array[i][3] = 1;
                    }
                }
            }
        }
        select_click = 0;
    }
}































