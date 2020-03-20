#include "offset.h"
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

offset::offset()
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
        messagebox_text = "<b><i>mode offset </i></b> input offset distance, select object";
        entry_focus = 1;
    }

    if(click < 998){
        window_select(1); //object select procedure..

        //if we spot a selection, go on..
        for(int i = 0; i < cad_counter; i++){
            if(int_cad_array[i][3] == 1){//selected object
                   click = 999;
            }
        }

    }

//    if(key_enter){
//        messagebox_text = "<b><i>mode offset </i></b> click offset side";
//        click = 999;
//        key_enter = 0;
//    }

    if(click == 999){
        messagebox_text = "<b><i>mode offset </i></b> click offset side";

    }

    if(click == 1000){

        //d point..
        base_x = snap_cad_pos_x;
        base_y = snap_cad_pos_y;
        base_z = snap_cad_pos_z;

        click = 1001;
    }

    if(click == 1001){
        //To determine which side of the line from A=(x1,y1) to B=(x2,y2) a point P=(x,y) falls on you need to compute the value:-
        //d=(x−x1)(y2−y1)−(y−y1)(x2−x1)
        //If d<0 then the point lies on one side of the line, and if d>0 then it lies on the other side. If d=0 then the point lies exactly line.

        for(int i = 0; i < cad_counter; i++){

            if(int_cad_array[i][3] == 1){//selected object

                if(int_cad_array[i][0] == 3){//id arc

                    double radius = double_cad_array[i][9];
                    double x_center = double_cad_array[i][6];
                    double y_center = double_cad_array[i][7];

                    double click_radius = sqrt(pow(base_x-x_center,2)+pow(base_y-y_center,2));

                    if(click_radius > radius){ //outside offset

                        //keep orginal object..
                        int_cad_array[cad_counter][0] = 3; //arc

//                        int_cad_array[cad_counter][1] = current_gui_color;
//                        int_cad_array[cad_counter][2] = 1; //linewidth
//                        int_cad_array[cad_counter][5] = current_linetype;

                        double_cad_array[cad_counter][56] = current_gui_color_red_gl;
                        double_cad_array[cad_counter][57] = current_gui_color_green_gl;
                        double_cad_array[cad_counter][58] = current_gui_color_blue_gl;
                        double_cad_array[cad_counter][59] = current_gui_color_alpha_gl;

                        int_cad_array[cad_counter][5] = current_linetype;
                        double_cad_array[cad_counter][18] = current_linetype_scale;
                        double_cad_array[cad_counter][19] = current_linewidth;

                        double_cad_array[cad_counter][6] = x_center;
                        double_cad_array[cad_counter][7] = y_center;
                        double_cad_array[cad_counter][9] = radius + double_user_input;

                        double_cad_array[cad_counter][11] = double_cad_array[i][11]; //keep the same start angle..
                        double_cad_array[cad_counter][12] = double_cad_array[i][12];

                        //calculate new startpoint and endpoint and arc mid coordinates through given offset distance..

                        //  cross calculation
                        //    A-----------B------------C
                        // (Xa,Ya)     (Xb,Yb)      (Xc,Yc)

                        //    AB = sqrt( (Xb - Xa)² + (Yb - Ya)² )
                        //    AC = 1000

                        //    Xc = Xa + (AC * (Xb - Xa) / AB)
                        //    Yc = Ya + (AC * (Yb - Ya) / AB)

                        //arc offset startpoint calculation
                        double Xa = x_center;
                        double Ya = y_center;
                        double Xb = double_cad_array[i][0]; //x start
                        double Yb = double_cad_array[i][1]; //y start
                        double AC = radius + double_user_input;
                        double AB = radius;
                        double Xc = Xa + (AC * (Xb - Xa) / AB); //new startpoint coordinate..
                        double Yc = Ya + (AC * (Yb - Ya) / AB);
                        double_cad_array[cad_counter][0] = Xc;
                        double_cad_array[cad_counter][1] = Yc;

                        //arc offset endpoint calculation
                        Xb = double_cad_array[i][3]; //x end
                        Yb = double_cad_array[i][4]; //y end
                        Xc = Xa + (AC * (Xb - Xa) / AB); //new startpoint coordinate..
                        Yc = Ya + (AC * (Yb - Ya) / AB);
                        double_cad_array[cad_counter][3] = Xc;
                        double_cad_array[cad_counter][4] = Yc;

                        //arc offset mid on curve calculation
                        Xb = double_cad_array[i][15]; //x end
                        Yb = double_cad_array[i][16]; //y end
                        Xc = Xa + (AC * (Xb - Xa) / AB); //new startpoint coordinate..
                        Yc = Ya + (AC * (Yb - Ya) / AB);
                        double_cad_array[cad_counter][15] = Xc;
                        double_cad_array[cad_counter][16] = Yc;

                        cad_counter++;
                        mode_offset = 0;
                        click = 0;
                        no_selection();
                        messagebox_text = "<b><i>mode offset </i></b> enter for repeat or Esc for cancel";
                    }

                    if(click_radius < radius){ //inside offset

                        //keep orginal object..
                        int_cad_array[cad_counter][0] = 3; //arc

//                        int_cad_array[cad_counter][1] = current_gui_color;
//                        int_cad_array[cad_counter][2] = 1; //linewidth
//                        int_cad_array[cad_counter][5] = current_linetype;
                        double_cad_array[cad_counter][56] = current_gui_color_red_gl;
                        double_cad_array[cad_counter][57] = current_gui_color_green_gl;
                        double_cad_array[cad_counter][58] = current_gui_color_blue_gl;
                        double_cad_array[cad_counter][59] = current_gui_color_alpha_gl;

                        int_cad_array[cad_counter][5] = current_linetype;
                        double_cad_array[cad_counter][18] = current_linetype_scale;
                        double_cad_array[cad_counter][19] = current_linewidth;

                        double_cad_array[cad_counter][6] = x_center;
                        double_cad_array[cad_counter][7] = y_center;
                        double_cad_array[cad_counter][9] = radius - double_user_input;

                        double_cad_array[cad_counter][11] = double_cad_array[i][11]; //keep the same start angle..
                        double_cad_array[cad_counter][12] = double_cad_array[i][12];

                        //calculate new startpoint and endpoint and arc mid coordinates through given offset distance..

                        //  cross calculation
                        //    A-----------B------------C
                        // (Xa,Ya)     (Xb,Yb)      (Xc,Yc)

                        //    AB = sqrt( (Xb - Xa)² + (Yb - Ya)² )
                        //    AC = 1000

                        //    Xc = Xa + (AC * (Xb - Xa) / AB)
                        //    Yc = Ya + (AC * (Yb - Ya) / AB)

                        //arc offset startpoint calculation
                        double Xa = x_center;
                        double Ya = y_center;
                        double Xb = double_cad_array[i][0]; //x start
                        double Yb = double_cad_array[i][1]; //y start
                        double AC = radius - double_user_input;
                        double AB = radius;
                        double Xc = Xa + (AC * (Xb - Xa) / AB); //new startpoint coordinate..
                        double Yc = Ya + (AC * (Yb - Ya) / AB);
                        double_cad_array[cad_counter][0] = Xc;
                        double_cad_array[cad_counter][1] = Yc;

                        //arc offset endpoint calculation
                        Xb = double_cad_array[i][3]; //x end
                        Yb = double_cad_array[i][4]; //y end
                        Xc = Xa + (AC * (Xb - Xa) / AB); //new startpoint coordinate..
                        Yc = Ya + (AC * (Yb - Ya) / AB);
                        double_cad_array[cad_counter][3] = Xc;
                        double_cad_array[cad_counter][4] = Yc;

                        //arc offset mid on curve calculation
                        Xb = double_cad_array[i][15]; //x end
                        Yb = double_cad_array[i][16]; //y end
                        Xc = Xa + (AC * (Xb - Xa) / AB); //new startpoint coordinate..
                        Yc = Ya + (AC * (Yb - Ya) / AB);
                        double_cad_array[cad_counter][15] = Xc;
                        double_cad_array[cad_counter][16] = Yc;

                        cad_counter++;
                        mode_offset = 0;
                        click = 0;
                        no_selection();
                        messagebox_text = "<b><i>mode offset </i></b> enter for repeat or Esc for cancel";
                    }

                }

                if(int_cad_array[i][0] == 2){//id circle

                    double radius = double_cad_array[i][9];
                    double x_center = double_cad_array[i][6];
                    double y_center = double_cad_array[i][7];

                    double click_radius = sqrt(pow(base_x-x_center,2)+pow(base_y-y_center,2));

                    if(click_radius > radius){ //outside offset

                        //keep orginal object..
                        int_cad_array[cad_counter][0] = 2; //circle
//                        int_cad_array[cad_counter][1] = current_gui_color;
//                        int_cad_array[cad_counter][2] = 1; //linewidth
//                        int_cad_array[cad_counter][5] = current_linetype;

                        double_cad_array[cad_counter][56] = current_gui_color_red_gl;
                        double_cad_array[cad_counter][57] = current_gui_color_green_gl;
                        double_cad_array[cad_counter][58] = current_gui_color_blue_gl;
                        double_cad_array[cad_counter][59] = current_gui_color_alpha_gl;

                        int_cad_array[cad_counter][5] = current_linetype;
                        double_cad_array[cad_counter][18] = current_linetype_scale;
                        double_cad_array[cad_counter][19] = current_linewidth;

                        double_cad_array[cad_counter][6] = x_center;
                        double_cad_array[cad_counter][7] = y_center;
                        double_cad_array[cad_counter][9] = radius + double_user_input;

                        //write the four intersection points..
                        //left point :
                        double_cad_array[cad_counter][25] = double_cad_array[cad_counter][6] - double_cad_array[cad_counter][9] ; //radius - center x..
                        double_cad_array[cad_counter][26] = double_cad_array[cad_counter][7]; //is centerheight..
                        double_cad_array[cad_counter][27] = snap_cad_pos_z;
                        //right point :
                        double_cad_array[cad_counter][28] = double_cad_array[cad_counter][6] + double_cad_array[cad_counter][9] ; //radius + center x..
                        double_cad_array[cad_counter][29] = double_cad_array[cad_counter][7]; //is centerheight..
                        double_cad_array[cad_counter][30] = snap_cad_pos_z;
                        //top point :
                        double_cad_array[cad_counter][31] = double_cad_array[cad_counter][6]; //center x..
                        double_cad_array[cad_counter][32] = double_cad_array[cad_counter][7] + double_cad_array[cad_counter][9] ; //is centerheight..
                        double_cad_array[cad_counter][33] = snap_cad_pos_z;
                        //bottom point :
                        double_cad_array[cad_counter][34] = double_cad_array[cad_counter][6]; //center x..
                        double_cad_array[cad_counter][35] = double_cad_array[cad_counter][7] - double_cad_array[cad_counter][9] ; //is centerheight..
                        double_cad_array[cad_counter][36] = snap_cad_pos_z;

                        cad_counter++;
                        mode_offset = 0;
                        click = 0;
                        no_selection();
                        messagebox_text = "<b><i>mode offset </i></b> enter for repeat or Esc for cancel";
                    }

                    if(click_radius < radius){ //inside offset

                        //keep orginal object..
                        int_cad_array[cad_counter][0] = 2; //circle
//                        int_cad_array[cad_counter][1] = current_gui_color;
//                        int_cad_array[cad_counter][2] = 1; //linewidth
//                        int_cad_array[cad_counter][5] = current_linetype;
                        double_cad_array[cad_counter][56] = current_gui_color_red_gl;
                        double_cad_array[cad_counter][57] = current_gui_color_green_gl;
                        double_cad_array[cad_counter][58] = current_gui_color_blue_gl;
                        double_cad_array[cad_counter][59] = current_gui_color_alpha_gl;

                        int_cad_array[cad_counter][5] = current_linetype;
                        double_cad_array[cad_counter][18] = current_linetype_scale;
                        double_cad_array[cad_counter][19] = current_linewidth;

                        double_cad_array[cad_counter][6] = x_center;
                        double_cad_array[cad_counter][7] = y_center;
                        double_cad_array[cad_counter][9] = radius - double_user_input;

                        //write the four intersection points..
                        //left point :
                        double_cad_array[cad_counter][25] = double_cad_array[cad_counter][6] - double_cad_array[cad_counter][9] ; //radius - center x..
                        double_cad_array[cad_counter][26] = double_cad_array[cad_counter][7]; //is centerheight..
                        double_cad_array[cad_counter][27] = snap_cad_pos_z;
                        //right point :
                        double_cad_array[cad_counter][28] = double_cad_array[cad_counter][6] + double_cad_array[cad_counter][9] ; //radius + center x..
                        double_cad_array[cad_counter][29] = double_cad_array[cad_counter][7]; //is centerheight..
                        double_cad_array[cad_counter][30] = snap_cad_pos_z;
                        //top point :
                        double_cad_array[cad_counter][31] = double_cad_array[cad_counter][6]; //center x..
                        double_cad_array[cad_counter][32] = double_cad_array[cad_counter][7] + double_cad_array[cad_counter][9] ; //is centerheight..
                        double_cad_array[cad_counter][33] = snap_cad_pos_z;
                        //bottom point :
                        double_cad_array[cad_counter][34] = double_cad_array[cad_counter][6]; //center x..
                        double_cad_array[cad_counter][35] = double_cad_array[cad_counter][7] - double_cad_array[cad_counter][9] ; //is centerheight..
                        double_cad_array[cad_counter][36] = snap_cad_pos_z;

                        cad_counter++;
                        mode_offset = 0;
                        click = 0;
                        no_selection();
                        messagebox_text = "<b><i>mode offset </i></b> enter for repeat or Esc for cancel";
                    }
                }



                if(int_cad_array[i][0] == 1){//id line

                    double d = (base_x-double_cad_array[i][0])*(double_cad_array[i][4]-double_cad_array[i][1]) - (base_y-double_cad_array[i][1])*(double_cad_array[i][3] - double_cad_array[i][0]);
                    qDebug()<< " d : " << d;

                    if(d<0){
                        //rotate orginal line..
                        rotate_degrees = 90;
                    }

                    if(d>0){
                        rotate_degrees = -90;
                    }

                    //rotate orginal line..
                    double temp_x = double_cad_array[i][0];
                    double temp_y = double_cad_array[i][1];

                    double rotate_dist_x_endpoint = double_cad_array[i][3] - temp_x;
                    double rotate_dist_y_endpoint = double_cad_array[i][4] - temp_y;

                    double rotate_x1 = cos(rotate_degrees * M_PI / 180.0 )* rotate_dist_x_endpoint - sin(rotate_degrees * M_PI / 180.0 ) * rotate_dist_y_endpoint;
                    double rotate_y1 = sin(rotate_degrees * M_PI / 180.0 )* rotate_dist_x_endpoint + cos(rotate_degrees * M_PI / 180.0 ) * rotate_dist_y_endpoint;

                    //modify line lenght to offset input..
                    //calculate line length
                    double object_x0 = double_cad_array[i][0];
                    double object_y0 = double_cad_array[i][1];
                    double object_x1 = rotate_x1 + temp_x;
                    double object_y1 = rotate_y1 + temp_y;

                    //formulat : A2 + B2 = C2
                    double object_A = object_x1 - object_x0;
                    double object_B = object_y1 - object_y0;
                    double object_C = sqrt(pow(object_A,2)+pow(object_B,2));

                    double object_radius = double_user_input;
                    entry_focus = 0;

                    //  cross calculation
                    //    A-----------B------------C
                    // (Xa,Ya)     (Xb,Yb)      (Xc,Yc)

                    //    AB = sqrt( (Xb - Xa)² + (Yb - Ya)² )
                    //    AC = 1000

                    //    Xc = Xa + (AC * (Xb - Xa) / AB)
                    //    Yc = Ya + (AC * (Yb - Ya) / AB)

                    double object_AB = object_C;
                    double object_AC = object_radius;

                    double object_x_end = object_x0 + (object_AC * (object_x1 - object_x0) / object_AB);
                    double object_y_end = object_y0 + (object_AC * (object_y1 - object_y0) / object_AB);

                    //calculate second line point..
                    double dist_x = object_x_end - double_cad_array[i][0];
                    double dist_y = object_y_end - double_cad_array[i][1];
                    double object_x2 = double_cad_array[i][3] + dist_x;
                    double object_y2 = double_cad_array[i][4] + dist_y;

                    //delete orginal object..
//                    double_cad_array[i][0] =
//                    double_cad_array[i][1] = object_y_end;
//                    double_cad_array[i][3] = object_x2;
//                    double_cad_array[i][4] = object_y2;

                    //keep orginal object..
                    int_cad_array[cad_counter][0] = 1; //id line
//                    int_cad_array[cad_counter][1] = current_gui_color; //color white
//                    int_cad_array[cad_counter][2] = 1; //linewidth
//                    int_cad_array[cad_counter][5] = current_linetype;
                    double_cad_array[cad_counter][56] = current_gui_color_red_gl;
                    double_cad_array[cad_counter][57] = current_gui_color_green_gl;
                    double_cad_array[cad_counter][58] = current_gui_color_blue_gl;
                    double_cad_array[cad_counter][59] = current_gui_color_alpha_gl;

                    int_cad_array[cad_counter][5] = current_linetype;
                    double_cad_array[cad_counter][18] = current_linetype_scale;
                    double_cad_array[cad_counter][19] = current_linewidth;

                    double_cad_array[cad_counter][0] = object_x_end;
                    double_cad_array[cad_counter][1] = object_y_end;
                    double_cad_array[cad_counter][2] = snap_cad_pos_z;
                    double_cad_array[cad_counter][3] = object_x2;
                    double_cad_array[cad_counter][4] = object_y2;
                    double_cad_array[cad_counter][5] = snap_cad_pos_z;
                    //calculate midpoint..
                    double_cad_array[cad_counter][15] =  (double_cad_array[cad_counter][0] +  double_cad_array[cad_counter][3]) / 2; //x midpoint..
                    double_cad_array[cad_counter][16] =  (double_cad_array[cad_counter][1] +  double_cad_array[cad_counter][4]) / 2; //y midpoint..
                    double_cad_array[cad_counter][17] =  (double_cad_array[cad_counter][2] +  double_cad_array[cad_counter][5]) / 2; //z midpoint..
                }
            }
        }
        cad_counter++;
        mode_offset = 0;
        click = 0;
        no_selection();
        messagebox_text = "<b><i>mode offset </i></b> enter for repeat or Esc for cancel";
    }
}




































