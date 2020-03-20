#include "match_properties.h"
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
#include <display_functions/simple_line_select.h>

int source=0;
int int_enter=0;
QList<int> list;

match_properties::match_properties()
{
    //initialiation..
    snap_cad_pos_x = mouse_cad_pos_x;
    snap_cad_pos_y = mouse_cad_pos_y;
    snap_cad_pos_z = mouse_cad_pos_z;

    simple_line_select();
    //object_select_line_nearest(0);
    object_select_arc_nearest(0);
    object_select_circle_nearest(0);
    object_select_ellipse_nearest(0);
    object_select_hermite_spline_nearest(0);
    object_select_bezier_curve_nearest(0);
    window_select(1);

    //qDebug()<< "click : " <<  click;

    if(click == 0){
        messagebox_text = "<b><i>mode match properties </i></b> select source object and press enter";
        clear_user_input = 1;
    }

    if(key_enter){
        int_enter++;
        key_enter=0;
        qDebug()<< "key enter : " << int_enter;
    }

    if(int_enter == 1){
        for(int i=0; i<cad_counter; i++){ //select
            if(int_cad_array[i][3]==1 || int_cad_array[i][4]==1  ){
                source = i;
                break;
            }
        }
        for(int i=0; i<cad_counter; i++){ //empty selection
            int_cad_array[i][3]=0;
        }
        qDebug()<< "source : " <<  source;
        click=1000;
        int_enter=2;
    }

    if(click==1000){
        messagebox_text = "<b><i>mode match properties </i></b> select target object and press enter";
    }

    if(int_enter ==3){
        for(int i=0; i<cad_counter; i++){ //select
            if(int_cad_array[i][3]==1 || int_cad_array[i][4]==1  ){
                if(!list.contains(i)){
                    list.append(i);
                }
            }
        }
        no_selection();

        QList<int>::iterator it;
        for(it=list.begin(); it!=list.end(); it++){
            int_cad_array[*it][5] = int_cad_array[source][5];         //linetype
            if(double_cad_array[source][13]>0){
                double_cad_array[*it][13] = double_cad_array[source][13]; //textheight
            }
            double_cad_array[*it][18] = double_cad_array[source][18]; //linetype scale
            double_cad_array[*it][19] = double_cad_array[source][19]; //linewidth
            double_cad_array[*it][56] = double_cad_array[source][56]; //red
            double_cad_array[*it][57] = double_cad_array[source][57]; //green
            double_cad_array[*it][58] = double_cad_array[source][58]; //blue
            double_cad_array[*it][59] = double_cad_array[source][59]; //alpha
        }
        list.clear();
        click=2000;
        int_enter=0;
    }

    if(click == 2000){
        no_highlight();
        no_selection();
        mode_match_properties = 0;
        select_click = 0;
        click = 0;
        int_key = 0;
        key_enter = 0;
        int_enter=0;
        messagebox_text = "<b><i>mode match properties </i></b> enter for repeat or Esc for cancel";
    }
}
























