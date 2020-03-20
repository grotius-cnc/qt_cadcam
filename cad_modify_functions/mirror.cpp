#include "mirror.h"
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
#include <array_functions/copy_mirror_array.h>
#include <cad_draw_functions/redraw_arc.h>
#include <display_functions/simple_line_select.h>

mirror::mirror()
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
        messagebox_text = "<b><i>mode mirror </i></b> select objects and press enter";
        clear_user_input = 1;
    }

    if(click < 998){
        window_select(1); //object select procedure..
    }

    if(key_enter){
        messagebox_text = "<b><i>mode mirror </i></b> click first point on mirror line"; //specify x start point
        click = 999;
        key_enter = 0;
    }

    if(click == 999){
        //wait for mouse click..
    }

    if(click == 1000){

        //base point..
        p1x_mirror = snap_cad_pos_x;
        p1y_mirror = snap_cad_pos_y;
        p1z_mirror = snap_cad_pos_z;
        messagebox_text = "<b><i>mode mirror </i></b> click second point on mirror line";

        qDebug() << "p1x_mirror : " << p1x_mirror;
        qDebug() << "p1y_mirror : " << p1y_mirror;
        qDebug() << "p1z_mirror : " << p1z_mirror;
        click = 1001;
    }

    if(click == 1001){
        //wait for second mouse click..

        //preview ortho function..
        if(!mode_ortho){
            //preview mirror line..
            glColor4f(1.0f, 1.0f, 1.0f, 1.0f);  //white
            glLineStipple(1, 0xAAAA); //1-2-3-4
            glEnable(GL_LINE_STIPPLE);
            glLineWidth(1);
            glBegin(GL_LINES);
            glVertex2d(p1x_mirror, p1y_mirror);                   //xy start
            glVertex2d(snap_cad_pos_x, snap_cad_pos_y);           //xy end
            glEnd();
            glLineWidth(gl_linewidth);
            //glDisable(GL_LINE_STIPPLE);
        }
        if(mode_ortho){
            //make snapshot..
            double distance_x = p1x_mirror - snap_cad_pos_x;
            double distance_y = p1y_mirror - snap_cad_pos_y;
            double distance_z = p1z_mirror - snap_cad_pos_z;

            if(distance_x<0){distance_x *= -1;}
            if(distance_y<0){distance_y *= -1;}
            if(distance_z<0){distance_z *= -1;}

            if(distance_x>=distance_y){
                p2x_mirror = snap_cad_pos_x;
                p2y_mirror = p1y_mirror;
                p2z_mirror = p1z_mirror;
            } else {
                p2x_mirror = p1x_mirror;
                p2y_mirror = snap_cad_pos_y;
                p2z_mirror = p1z_mirror;
            }

            //preview mirror line..
            glColor4f(1.0f, 1.0f, 1.0f, 1.0f);  //white
            glLineStipple(1, 0xAAAA); //1-2-3-4
            glEnable(GL_LINE_STIPPLE);
            glLineWidth(1);
            glBegin(GL_LINES);
            glVertex2d(p1x_mirror, p1y_mirror);                   //xy start
            glVertex2d(p2x_mirror, p2y_mirror);           //xy end
            glEnd();
            glLineWidth(gl_linewidth);
            //glDisable(GL_LINE_STIPPLE);
        }
    }

    if(click == 1002){

        //target point..
        if(!mode_ortho){
            p2x_mirror = snap_cad_pos_x;
            p2y_mirror = snap_cad_pos_y;
            p2z_mirror = snap_cad_pos_z;

            qDebug() << "p2x_mirror : " << p2x_mirror;
            qDebug() << "p2y_mirror : " << p2y_mirror;
            qDebug() << "p2z_mirror : " << p2z_mirror;
        }
        if(mode_ortho){
            //make snapshot..
            double distance_x = p1x_mirror - snap_cad_pos_x;
            double distance_y = p1y_mirror - snap_cad_pos_y;
            double distance_z = p1z_mirror - snap_cad_pos_z;

            if(distance_x<0){distance_x *= -1;}
            if(distance_y<0){distance_y *= -1;}
            if(distance_z<0){distance_z *= -1;}

            if(distance_x>=distance_y){
                p2x_mirror = snap_cad_pos_x;
                p2y_mirror = p1y_mirror;
                p2z_mirror = p1z_mirror;
            } else {
                p2x_mirror = p1x_mirror;
                p2y_mirror = snap_cad_pos_y;
                p2z_mirror = p1z_mirror;
            }
        }
        click = 1003;
    }

    if(click == 1003){

        double angle = atan2(p2y_mirror - p1y_mirror, p2x_mirror - p1x_mirror)* 180.0 / M_PI;
        qDebug() << "mirror line has angle : " << angle;

        messagebox_text = "<b><i>mode mirror </i></b> delete orginal objects? press <font color=#0000ff><u>y </u></font> or <font color=#0000ff><u> n</u></font>";

        if(int_key == 89){ //key y
            //do the mirror copy
            for(int i=0; i<cad_counter; i++){
                if(int_cad_array[i][3]==1){ //selected items..
                    copy_mirror_array(i, i, p1x_mirror, p1y_mirror, p2x_mirror, p2y_mirror, angle); //copy to the same counter, only change array coordinates..

                    if(int_cad_array[i][0]==3){
                        (redraw_arc(i)); //calculate new start angle + new end angle..
                    }
                    //temp_counter++;

                }
            }
            no_highlight();
            no_selection();
            mode_mirror = 0;
            select_click = 0;
            click = 0;
            int_key = 0;
            key_enter = 0;
            //keyboard = 0;
            messagebox_text = "<b><i>mode mirror </i></b> enter for repeat or Esc for cancel";
        }

        if(int_key == 78){ //key n
            //do the mirror copy
            int temp_counter = cad_counter;
            for(int i=0; i<cad_counter; i++){
                if(int_cad_array[i][3]==1){ //selected items..
                    copy_mirror_array(i, temp_counter, p1x_mirror, p1y_mirror, p2x_mirror, p2y_mirror, angle);

                    if(int_cad_array[temp_counter][0]==3){
                        (redraw_arc(temp_counter)); //calculate new start angle + new end angle..
                    }
                }
                temp_counter++;

            }
            cad_counter = temp_counter;
            temp_counter = 0;

            no_highlight();
            no_selection();
            mode_mirror = 0;
            select_click = 0;
            click = 0;
            int_key = 0;
            key_enter = 0;
            //keyboard = 0;
            messagebox_text = "<b><i>mode mirror </i></b> enter for repeat or Esc for cancel";

        }
    }
}


























