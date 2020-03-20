#include "stretch.h"
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
#include <display_functions/window_select_stretch.h>
#include <display_functions/no_selection.h>
#include <cad_modify_functions/preview_displacement_line_stretch.h>
#include <cad_modify_functions/preview_displacement_arc_stretch.h>
#include <cad_modify_functions/preview_displacement.h>
#include <array_functions/stretch_line_array.h>
#include <array_functions/stretch_arc_array.h>
#include <array_functions/copy_move_array.h>


stretch::stretch()
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
        messagebox_text = "<b><i>mode stretch </i></b> select window and press enter";
        clear_user_input = 1;
    }

    if(click < 998){

        window_select_stretch(1); //object select procedure..
    }

    if(key_enter){
        messagebox_text = "<b><i>mode stretch </i></b> click base point"; //specify x start point
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
        messagebox_text = "<b><i>mode stretch </i></b> click target point";

        //qDebug() << "base_x : " << base_x;
        //qDebug() << "base_y : " << base_y;

        click = 1001;
    }

    if(click == 1001){

        //preview..
        if(!mode_ortho){
            dist_x = snap_cad_pos_x - base_x;
            dist_y = snap_cad_pos_y - base_y;
            dist_z = snap_cad_pos_z - base_z;

            //preview stretch line..
            glColor4f(1.0f, 1.0f, 1.0f, 1.0f);  //white
            glLineStipple(1, 0xAAAA); //1-2-3-4
            glEnable(GL_LINE_STIPPLE);
            glLineWidth(1);
            glBegin(GL_LINES);
            glVertex3d(base_x, base_y, base_z);  //xy start
            glVertex3d(snap_cad_pos_x, snap_cad_pos_y, snap_cad_pos_z);  //xy end
            glEnd();
            glLineWidth(gl_linewidth);
            //glDisable(GL_LINE_STIPPLE);
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

                //preview stretch line..
                glColor4f(1.0f, 1.0f, 1.0f, 1.0f);  //white
                glLineStipple(1, 0xAAAA); //1-2-3-4
                glEnable(GL_LINE_STIPPLE);
                glLineWidth(1);
                glBegin(GL_LINES);
                glVertex3d(base_x, base_y, base_z);  //xy start
                glVertex3d(snap_cad_pos_x, base_y, base_z);  //xy end
                glEnd();
                glLineWidth(gl_linewidth);
                //glDisable(GL_LINE_STIPPLE);

            } else {

                dist_x = 0;
                dist_y = snap_cad_pos_y - base_y;
                dist_z = 0;

                //preview stretch line..
                glColor4f(1.0f, 1.0f, 1.0f, 1.0f);  //white
                glLineStipple(1, 0xAAAA); //1-2-3-4
                glEnable(GL_LINE_STIPPLE);
                glLineWidth(1);
                glBegin(GL_LINES);
                glVertex3d(base_x, base_y, base_z);  //xy start
                glVertex3d(base_x, snap_cad_pos_y, base_z);  //xy end
                glEnd();
                glLineWidth(gl_linewidth);
                //glDisable(GL_LINE_STIPPLE);
            }
        }

        for(int i=0; i<cad_counter; i++){

            if(int_cad_array[i][0] == 1){ //id = line
                if(int_cad_array[i][6] == 1){ //selected startpoint..
                    preview_displacement_line_stretch(i,1,0,0,dist_x,dist_y,dist_z);
                }
                if(int_cad_array[i][7] == 1){ //selected endpoint..
                    preview_displacement_line_stretch(i,0,1,0,dist_x,dist_y,dist_z);
                }
                if(int_cad_array[i][3] == 1){ //full object..
                    preview_displacement_line_stretch(i,0,0,1,dist_x,dist_y,dist_z);
                }
            }

            if(int_cad_array[i][0] == 3){ //id = arc
//                if(int_cad_array[i][6] == 1){ //selected startpoint..
//                    preview_displacement_arc_stretch(i,1,0,0,dist_x,dist_y,dist_z);
//                }
//                if(int_cad_array[i][7] == 1){ //selected endpoint..
//                    preview_displacement_arc_stretch(i,0,0,1,dist_x,dist_y,dist_z);
//                }
                if(int_cad_array[i][3] == 1){ //full object..
                    preview_displacement(i,dist_x,dist_y,dist_z);
                }
            }

            if(int_cad_array[i][0] == 2){ //id = circle
                if(int_cad_array[i][3] == 1){
                    preview_displacement(i, dist_x, dist_y, dist_z);
                }

            }
        }
    }

    if(click == 1002){

        //target point..
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

        QString type;
        for(int i = 0; i<cad_counter; i++){

            if(int_cad_array[i][0] == 1){//id = line
                if(int_cad_array[i][6] == 1){
                    type = "startpoint";
                    stretch_line_array(i,i, type, dist_x, dist_y, dist_z);
                    int_cad_array[i][6] = 0;

                }
                if(int_cad_array[i][7] == 1){
                    type = "endpoint";
                    stretch_line_array(i,i, type, dist_x, dist_y, dist_z);
                    int_cad_array[i][7] = 0;

                }
                if(int_cad_array[i][3] == 1){
                    type = "full_object";
                    stretch_line_array(i,i, type, dist_x, dist_y, dist_z);
                    int_cad_array[i][3] = 0;
                }
            }

            if(int_cad_array[i][0] == 3){//id = arc
//                if(int_cad_array[i][6] == 1 ){ //selected startpoint..
//                    stretch_arc_array(i,1,0,0,dist_x,dist_y,dist_z);
//                    int_cad_array[i][6] = 0;
//                }
//                if(int_cad_array[i][7] == 1 ){ //selected endpoint..
//                    stretch_arc_array(i,0,0,1,dist_x,dist_y,dist_z);
//                    int_cad_array[i][7] = 0;
//                }
                if(int_cad_array[i][3] == 1 ){ //full object..
                    copy_move_array(i,i,dist_x,dist_y,dist_z);
                    int_cad_array[i][3] = 0;
                }
            }

            if(int_cad_array[i][0] == 2){ //id = circle
                if(int_cad_array[i][3] == 1){
                    copy_move_array(i, i, dist_x, dist_y, dist_z); //no copy, only move..
                }
            }
        }



        no_highlight();
        no_selection();
        mode_stretch = 0;
        select_click = 0;
        click = 0;
        int_key = 0;
        key_enter = 0;
        keyboard = 0;
        messagebox_text = "<b><i>mode stretch </i></b> enter for repeat or Esc for cancel";
    }
}

























