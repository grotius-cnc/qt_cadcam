#include "print.h"
#include <core_functions/variables.h>
#include <dialog_functions/dialog_print.h>

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
#include <display_functions/object_select_line_intersection.h>

double preview_x = 0;
double preview_y = 0;

print::print()
{
    //initialiation..
    snap_cad_pos_x = mouse_cad_pos_x;
    snap_cad_pos_y = mouse_cad_pos_y;
    snap_cad_pos_z = mouse_cad_pos_z;

    //overwrite initialisation if we spot a snap somewhere..
    if(mode_snap_intersection){
        object_select_line_intersection();
    }
    //if(mode_endpoint){
        object_select_line_startpoint();
        object_select_line_endpoint();
   //}
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
        messagebox_text = "<b><i>mode print </i></b> select left-top window coordinate";
    }
    if(click == 1){
        print_x0 = mouse_pixel_pos_x;
        print_y0 = printer_pixel_pos_y;

        preview_x = snap_cad_pos_x;
        preview_y = snap_cad_pos_y;
        click = 2;
    }
    if(click==2){
        messagebox_text = "<b><i>mode print </i></b> select right-bottom window coordinate";
        //preview select window..

        if(!mode_background_white){
        glColor4f(1, 1, 1, 1);  //white
        } else {
           glColor4f(0, 0, 0, 1);  //black
        }
        glLineWidth(1);
        glLineStipple(1, 0xAAAA);
        glEnable(GL_LINE_STIPPLE);
        glBegin(GL_LINES);
        glVertex2d(preview_x, preview_y);
        glVertex2d(snap_cad_pos_x, preview_y);
        glVertex2d(preview_x, preview_y);
        glVertex2d(preview_x, snap_cad_pos_y);
        glVertex2d(snap_cad_pos_x, preview_y);
        glVertex2d(snap_cad_pos_x, snap_cad_pos_y);
        glVertex2d(preview_x, snap_cad_pos_y);
        glVertex2d(snap_cad_pos_x, snap_cad_pos_y);
        glEnd();
        glDisable(GL_LINE_STIPPLE);
    }
    if(click == 3){
        print_x1 = mouse_pixel_pos_x;
        print_y1 = printer_pixel_pos_y;
        click = 4;
    }

    if(click==4){
        Dialog_print().exec();
        Dialog_print().setModal(true);
        click = 5;
    }
    if(click==5){

    }
}









































