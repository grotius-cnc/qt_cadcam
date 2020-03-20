#include "text.h"
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
#include <text_functions/read_line_text.h>
#include <text_functions/read_circle_text.h>
#include <text_functions/read_arc_text.h>
#include <dialog_functions/dialog_textedit.h>
#include <display_functions/object_select_line_intersection.h>

bool text_dialog_trigger=0;
double text_pos_x = 0;
double text_pos_y = 0;

text::text()
{
    //initialiation..
    snap_cad_pos_x = mouse_cad_pos_x;
    snap_cad_pos_y = mouse_cad_pos_y;
    snap_cad_pos_z = mouse_cad_pos_z;

    //overwrite initialisation if we spot a snap somewhere..
    if(mode_snap_intersection){
        object_select_line_intersection();
    }
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
        messagebox_text = "<b><i>mode text </i></b> click start point";
        //entry_focus = 1;
    }

    if(click == 1){

        text_pos_x = snap_cad_pos_x;
        text_pos_y = snap_cad_pos_y;

        if(!text_dialog_trigger){
            Dialog_textedit textedit;
            textedit.exec();
            text_dialog_trigger=1;
        }
        click = 2;
    }

    if(click == 2){
        messagebox_text = "<b><i>mode text </i></b> click to display text";
    }

    if(click == 3){

        //qDebug()<< "text_edit_string : " << text_edit_string;
        //construct text input data over here..

        if(text_edit_string.contains("\n")){

            text_edit_string.replace("\n","new_line",Qt::CaseSensitive);
        }

        int_cad_array[cad_counter][0] = 10; //id text
        int_cad_array[cad_counter][5] = current_linetype;

        double_cad_array[cad_counter][0] = text_pos_x; //text position
        double_cad_array[cad_counter][1] = text_pos_y;
        double_cad_array[cad_counter][3] = text_pos_x; //text position, end point needed for window select..
        double_cad_array[cad_counter][4] = text_pos_y;

        double_cad_array[cad_counter][13] = text_height; //text height user mainwindow input..
        double_cad_array[cad_counter][18] = current_linetype_scale;
        double_cad_array[cad_counter][19] = current_linewidth;
        double_cad_array[cad_counter][56] = current_gui_color_red_gl;
        double_cad_array[cad_counter][57] = current_gui_color_green_gl;
        double_cad_array[cad_counter][58] = current_gui_color_blue_gl;
        double_cad_array[cad_counter][59] = current_gui_color_alpha_gl;

        //string data :
        string_cad_array[cad_counter][0] = text_edit_string;

        cad_counter++;

        click = 10;
    }

    if(click == 10){
        click = 0;
        mode_text = 0;
        entry_focus = 0;
        text_dialog_trigger=0;
        no_selection();
        messagebox_text = "<b><i>mode text </i></b> enter for repeat";
    }
}

////copy the fonts directory from the source directory to the debug, profile or release directory..

////initialiation..
//snap_cad_pos_x = mouse_cad_pos_x;
//snap_cad_pos_y = mouse_cad_pos_y;
//snap_cad_pos_z = mouse_cad_pos_z;

////overwrite initialisation if we spot a snap somewhere..
//if(mode_endpoint){
//    object_select_line_startpoint();
//    object_select_line_endpoint();
//}

//if(mode_midpoint){
//    object_select_line_midpoint();
//}

//if(mode_centerpoint){
//    object_select_centerpoint();
//}

//if(mode_perpendicular){
//    object_select_line_perpendicular();
//}

//if(mode_snap_circle_4p){
//    object_select_circle_4p_intersection();
//}

//if(mode_tangent){
//    object_select_line_tangent_arc();
//    object_select_line_tangent_circle();
//}

//if(mode_nearest){
//    object_select_line_nearest(1);
//    object_select_arc_nearest(1);
//    object_select_circle_nearest(1);
//    object_select_ellipse_nearest(1);
//    object_select_hermite_spline_nearest(1);
//    object_select_bezier_curve_nearest(1);
//}

//if(click == 0){
//    messagebox_text = "<b><i>mode text </i></b> enter text and click point";
//    //qDebug() << "text height : " << text_height;
//    entry_focus = 1;

//}

//if(click == 1){
//    int items = string_user_input.size(); //qDebug() << "items : " << items;
//    double offset = 0;

//    for(int i = 0; i < items; i++){
//        //qDebug() << "character position : " << i << " character of alphabet : " << string_user_input.at(i);
//        //qDebug() << "current_gui_color : " << current_gui_color;

//        //show output..

//        filename_in =  QDir::currentPath() + "/fonts/" + string_user_input.at(i) + ".dxf"; //alphabet ordered dxf files from a to z, and from 0 to 9..

//        read_line_text(snap_cad_pos_x + offset, snap_cad_pos_y, snap_cad_pos_z);
//        read_circle_text(snap_cad_pos_x + offset, snap_cad_pos_y, snap_cad_pos_z);
//        read_arc_text(snap_cad_pos_x + offset, snap_cad_pos_y, snap_cad_pos_z);

//        if(string_user_input.at(i) == "i" || string_user_input.at(i) == "j" || string_user_input.at(i) == "l" || string_user_input.at(i) == "1"){
//            offset += 0.55;
//        } else
//            if(string_user_input.at(i) == "r" || string_user_input.at(i) == "t" || string_user_input.at(i) == "f"){
//                offset += 0.60;
//            } else
//                if(string_user_input.at(i) == "m" || string_user_input.at(i) == "w"){
//                    offset += 1.3;
//                } else
//                    if(string_user_input.at(i) == "c" || string_user_input.at(i) == "s" || string_user_input.at(i) == "o" || string_user_input.at(i) == "7"){
//                        offset += 0.8;
//                    } else {
//                            offset += 0.9;
//                        }

//        scale();
//    }
//    click = 2;
//}

//if(click == 2){
//    click = 0;
//    mode_text = 0;
//    entry_focus = 0;
//    no_selection();
//    messagebox_text = "<b><i>mode text </i></b> enter for repeat";
//}
//}

//void text::scale(){

////qDebug() << "scale function is active ..";
//double base_x = snap_cad_pos_x;
//double base_y = snap_cad_pos_y;
//double scaled_base_x = snap_cad_pos_x * text_height;
//double scaled_base_y = snap_cad_pos_y * text_height;
//double dist_base_x = scaled_base_x - base_x;
//double dist_base_y = scaled_base_y - base_y;

//for(int i = 0; i < cad_counter; i++){
//    if(int_cad_array[i][3] == 1){ // scale only selected items..

//        //int_cad_array[i][1] = current_gui_color; //done here..
//        double_cad_array[i][56] = current_gui_color_red_gl;
//        double_cad_array[i][57] = current_gui_color_green_gl;
//        double_cad_array[i][58] = current_gui_color_blue_gl;
//        double_cad_array[i][59] = current_gui_color_alpha_gl;

//        //int_cad_array[i][5] = current_linetype;
//        //double_cad_array[i][19] = segments; //linewidth

//        int_cad_array[i][5] = current_linetype;
//        double_cad_array[i][18] = current_linetype_scale;
//        double_cad_array[i][19] = current_linewidth;


//        double_cad_array[i][0] = double_cad_array[i][0] * text_height;
//        double_cad_array[i][1] = double_cad_array[i][1] * text_height;
//        double_cad_array[i][3] = double_cad_array[i][3] * text_height;
//        double_cad_array[i][4] = double_cad_array[i][4] * text_height;

//        //move the object back to base point dist xy..
//        double_cad_array[i][0] = double_cad_array[i][0] - dist_base_x;
//        double_cad_array[i][1] = double_cad_array[i][1] - dist_base_y;
//        double_cad_array[i][3] = double_cad_array[i][3] - dist_base_x;
//        double_cad_array[i][4] = double_cad_array[i][4] - dist_base_y;
//    }
//}

////end selection ..
//for(int i = 0; i < cad_counter; i++){
//    int_cad_array[i][3] = 0;
//}



















