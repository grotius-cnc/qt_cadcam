#include "display.h"
#include <core_functions/variables.h>
#include <display_functions/color.h>
#include <display_functions/linetype.h>
#include <display_functions/origin.h>
#include <display_functions/preview_selection.h>
#include <cad_draw_functions/point.h>
#include <cad_draw_functions/line.h>
#include <cad_draw_functions/linestrip.h>
#include <cad_draw_functions/rectangular.h>
#include <cad_draw_functions/arc.h>
#include <cad_draw_functions/circle_2p.h>
#include <cad_draw_functions/circle_3p.h>
#include <cad_draw_functions/polygon.h>
#include <cad_draw_functions/ellipse.h>
#include <cad_draw_functions/cubic_bezier_curve.h>
#include <cad_draw_functions/cubic_hermite_spline.h>
#include <cad_draw_functions/text.h>
#include <dimension/dimension.h>
#include <interface_functions/zoom_window.h>
#include <interface_functions/snapshot.h>
#include <display_functions/object_select_line_startpoint.h>
#include <display_functions/object_select_line_endpoint.h>
#include <display_functions/object_select_line_midpoint.h>
#include <display_functions/object_select_line_nearest.h>
#include <display_functions/object_select_circle_nearest.h>
#include <display_functions/object_select_circle_4p_intersection.h>
#include <display_functions/object_select_arc_nearest.h>
#include <display_functions/object_select_line_perpendicular.h>
#include <display_functions/object_select_centerpoint.h>
#include <display_functions/object_select_line_tangent_circle.h>
#include <display_functions/object_select_line_tangent_arc.h>
#include <display_functions/highlight.h>
#include <display_functions/no_highlight.h>
#include <display_functions/no_selection.h>
#include <display_functions/show_startpoint.h>
#include <display_functions/show_midpoint.h>
#include <display_functions/show_endpoint.h>
#include <display_functions/show_centerpoint.h>
#include <display_functions/window_select.h>
#include <display_functions/display_user_text.h>
#include <cad_modify_functions/chamfer.h>
#include <cad_modify_functions/copy.h>
#include <cad_modify_functions/del.h>
#include <cad_modify_functions/extend.h>
#include <cad_modify_functions/fillet.h>
#include <cad_modify_functions/mirror.h>
#include <cad_modify_functions/move.h>
#include <cad_modify_functions/offset.h>
#include <cad_modify_functions/rotate.h>
#include <cad_modify_functions/scale.h>
#include <cad_modify_functions/stretch.h>
#include <cad_modify_functions/trim.h>
#include <cad_modify_functions/text_edit.h>
#include <cad_modify_functions/match_properties.h>
#include <array_functions/update_undo_array.h>
#include <array_functions/restore_undo_array.h>
#include <interface_functions/cw_ccw.h>
#include <cad_modify_functions/trim.h>
#include <cad_modify_functions/extend.h>
#include <array_functions/emtpy_current_cad_counter.h>
#include <cam_functions/contour_offset.h>
#include <display_functions/display_cad.h>
#include <display_functions/display_cam.h>
#include <display_functions/display_dimension_text.h>
#include <display_functions/print.h>

#define DEG2RAD M_PI/180;
static QString lastmode = "nothing";
bool cam_text_trigger = 0;

display::display()
{
    //draw functions..
    if(mode_arc){
        update_undo_array();
        lastmode = "arc";
        arc();
    }
    if(mode_circle_2p){
        update_undo_array();
        lastmode = "circle_2p";
        circle_2p();
    }
    if(mode_circle_3p){
        update_undo_array();
        lastmode = "circle_3p";
        circle_3p();
    }
    if(mode_cubic_hermite_spline){
        update_undo_array();
        lastmode = "cubic_hermite_spline";
        cubic_hermite_spline();
    }
    if(mode_ellipse){
        update_undo_array();
        lastmode = "ellipse";
        ellipse();
    }
    if(mode_point){
        update_undo_array();
        lastmode = "point";
        point();
    }
    if(mode_line){
        update_undo_array();
        lastmode = "line";
        line();
    }
    if(mode_linestrip){
        update_undo_array();
        lastmode = "linestrip";
        linestrip();
    }
    if(mode_polygon){
        update_undo_array();
        lastmode = "polygon";
        polygon();
    }
    if(mode_cubic_bezier_curve){
        update_undo_array();
        lastmode = "cubic_bezier_curve";
        cubic_bezier_curve();
    }
    if(mode_rectangular){
        update_undo_array();
        lastmode = "rectangular";
        rectangular();
    }
    if(mode_text){
        update_undo_array();
        lastmode = "text";
        text();
    }
    if(mode_text_edit){
        update_undo_array();
        lastmode = "text_edit";
        text_edit();
    }

    //modify functions
    if(mode_chamfer){
        update_undo_array();
        lastmode = "chamfer";
        chamfer();
    }
    if(mode_copy){
        update_undo_array();
        lastmode = "copy";
        copy();
    }
    if(mode_delete){
        update_undo_array();
        lastmode = "delete";
        del();
    }
    if(mode_extend){
        update_undo_array();
        lastmode = "extend";
        extend();
    }
    if(mode_fillet){
        update_undo_array();
        lastmode = "fillet";
        fillet();
    }
    if(mode_mirror){
        update_undo_array();
        lastmode = "mirror";
        mirror();
    }
    if(mode_move){
        update_undo_array();
        lastmode = "move";
        move();
    }
    if(mode_offset){
        update_undo_array();
        lastmode = "offset";
        offset();
    }
    if(mode_rotate){
        update_undo_array();
        lastmode = "rotate";
        rotate();
    }
    if(mode_scale){
        update_undo_array();
        lastmode = "scale";
        scale();
    }
    if(mode_stretch){
        update_undo_array();
        lastmode = "stretch";
        stretch();
    }
    if(mode_trim){
        update_undo_array();
        lastmode = "trim";
        trim();
    }
    if(mode_print){
        update_undo_array();
        lastmode = "print";
        print();
    }
    if(mode_match_properties){
        update_undo_array();
        lastmode = "match_properties";
        match_properties();
    }

    //dimension
    if(mode_dimension){
        update_undo_array();
        lastmode = "dimension";
        dimension();
    }

    //cam functions
    if(mode_contour_offset){
        contour_offset();
        lastmode = "contour_offset";
    }



    //various functions
    if(mode_zoom_window){
        zoom_window();
    }
    if(key_control && key_z){ //undo function..
        restore_undo_array();
        //qDebug() << "control_z pressed";
    }
    //    if(mode_define_cw_ccw){
    //        update_undo_array();
    //        cw_ccw();
    //    }


    //reset function
    if(key_escape){

        mode_point = 0;
        mode_line = 0;
        mode_linestrip = 0;
        mode_arc = 0;
        mode_circle_2p = 0;
        mode_circle_3p = 0;
        mode_polygon = 0;
        mode_ellipse = 0;
        mode_cubic_hermite_spline = 0;
        mode_cubic_bezier_curve = 0;
        mode_rectangular = 0;
        mode_text = 0;
        mode_text_edit = 0;
        mode_chamfer = 0;
        mode_copy = 0;
        mode_extend = 0;
        mode_mirror = 0;
        mode_move = 0;
        mode_offset = 0;
        mode_rotate = 0;
        mode_scale = 0;
        mode_stretch = 0;
        mode_trim = 0;
        mode_fillet = 0;
        mode_delete = 0;
        mode_dimension = 0;
        mode_contour_recognize = 0;
        mode_contour_offset = 0;
        mode_contour_autonest = 0;
        mode_print = 0;
        mode_match_properties = 0;

        for(int i = 0; i<100; i++){
            (emtpy_current_cad_counter(cad_counter + i)); //done for polygon with 99 objects..
        }

        no_highlight();
        no_selection();

        click = 0;
        select_click = 0;
        zoom_click = 0;
        key_enter = 0;
        int_key = 0;
        entry_focus = 0;
        keyboard = 0;
        relative = 0;
        messagebox_text = "";
        clear_user_input = 1;
        key_escape = 0;
        loop_times = 0; //cam..

        //clean a bit..
        for(int i = 0; i<cad_counter; i++){
            int_cad_array[i][10] = 0;
            int_cad_array[i][11] = 0;
        }
        contournumber = 0;

        //focus to opengl screen.
        opengl_focus=1;
    }

    //repeat last function
    if(key_enter == 1){

        //draw functions
        if(lastmode == "arc"){
            mode_arc = 1;
        }
        if(lastmode == "circle_2p"){
            mode_circle_2p = 1;
        }
        if(lastmode == "circle_3p"){
            mode_circle_3p = 1;
        }
        if(lastmode == "cubic_hermite_spline"){
            mode_cubic_hermite_spline = 1;
        }
        if(lastmode == "ellipse"){
            mode_ellipse = 1;
        }
        if(lastmode == "point"){
            mode_point = 1;
        }
        if(lastmode == "line"){
            mode_line = 1;
        }
        if(lastmode == "linestrip"){
            mode_linestrip = 1;
        }
        if(lastmode == "polygon"){
            mode_polygon = 1;
        }
        if(lastmode == "cubic_bezier_curve"){
            mode_cubic_bezier_curve = 1;
        }
        if(lastmode == "rectangular"){
            mode_rectangular = 1;
        }
        if(lastmode == "text"){
            mode_text = 1;
        }
        if(lastmode == "text_edit"){
            mode_text_edit = 1;
        }

        //modify functions
        if(lastmode == "chamfer"){
            mode_chamfer = 1;
        }
        if(lastmode == "copy"){
            mode_copy = 1;
        }
        if(lastmode == "delete"){
            mode_delete = 1;
        }
        if(lastmode == "extend"){
            mode_extend = 1;
        }
        if(lastmode == "fillet"){
            mode_fillet = 1;
        }
        if(lastmode == "mirror"){
            mode_mirror = 1;
        }
        if(lastmode == "move"){
            mode_move = 1;
        }
        if(lastmode == "offset"){
            mode_offset = 1;
        }
        if(lastmode == "rotate"){
            mode_rotate = 1;
        }
        if(lastmode == "scale"){
            mode_scale = 1;
        }
        if(lastmode == "stretch"){
            mode_stretch = 1;
        }
        if(lastmode == "trim"){
            mode_trim = 1;
        }
        if(lastmode == "print"){
            mode_print = 1;
        }
        if(lastmode == "match_properties"){
            mode_match_properties = 1;
        }


        //dimension
        if(lastmode == "dimension"){
            mode_dimension = 1;
        }

        //cam functions
        if(lastmode == "contour_offset"){
            mode_contour_offset = 1;
        }

        no_highlight();
        no_selection();
        click = 0;
        select_click = 0;
        zoom_click = 0;
        key_enter = 0;
        int_key = 0;
        entry_focus = 0;
        keyboard = 0;
        relative = 0;
        key_escape = 0;
    }

    //glEnable(GL_BLEND);
    //glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    if(mode_solid){
        for(int i=0 ; i < triangle_counter; i+=3) {
            //You need to have the blend function turned on and setup there alpha value for the color.
            //glColor4f( R,G,B,A) A values: 1 = non-transparent, 0.5 = 50% transparent, 0 = total transparent.
            //Use glDisable(GL_BLEND), to turn off blend.

            if(mode_cull_face){
                //glCullFace(GL_FRONT);
            }
            if(mode_show_triangles){
                //glPolygonMode(GL_FRONT_AND_BACK,GL_LINE); //display only triangle lines..
            }
            if(!mode_show_triangles){
                //glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
            }

            glBegin(GL_TRIANGLE_STRIP);
            //glColor4f(0.1f, 0.1f, 0.1f, 0.5);  //grey 50% transparant..
            //glColor4f(0.81f, 0.71f, 0.23f, 0.5f);  //old gold..
            glColor4f(solid_color_red, solid_color_green, solid_color_blue, solid_color_alpha);
            //(color(i));

            glVertex3d(double_triangle_array[i+0][0],double_triangle_array[i+0][1],double_triangle_array[i+0][2]);
            glVertex3d(double_triangle_array[i+1][0],double_triangle_array[i+1][1],double_triangle_array[i+1][2]);
            glVertex3d(double_triangle_array[i+2][0],double_triangle_array[i+2][1],double_triangle_array[i+2][2]);
            glEnd();


        }
    }

    if(mode_cad){
        cam_text_trigger=0;
        display_cad();

        for(int i=0 ; i < cad_counter+100 ; i++) {
            (display_dimension_text(i));
            (display_user_text(i,0,0));
        }

        if(mode_grid){
            glPointSize(2);
            glBegin(GL_POINTS);
            int s=0;
            for(double x = 0; x<=gridsize; x+=gridspace){
                s++;
                if(s>100000){break;}
                for(double y = 0; y<=gridsize; y+=gridspace){
                        s++;
                        if(s>100000){break;}
                        glColor4f(0.6, 0.6, 0.6, 1); //color grey
                        glVertex2d(x, y);      
                }
            }
            glEnd();
        }
    }

    if(mode_cam){
        display_cam();
    }

    //glDisable(GL_BLEND);
}






















