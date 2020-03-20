#include "keyboard_interaction.h"
#include <core_functions/variables.h>
#include <array_functions/delete_selected_cad_array_objects.h>

keyboard_interaction::keyboard_interaction(int key)
{

    if(key == Qt::Key_Delete)
    {
        delete_selected_cad_array_objects();
    }
    if(key == Qt::Key_Escape)
    {
        key_escape = 1;
    }
    if(key == Qt::Key_F3)
    {

    }
    if(key == Qt::Key_Control)
    {
        key_control = 1;
    }
    if(key == Qt::Key_Z)
    {
        key_z = 1;
    }
    if(key == Qt::Key_Shift){
        key_shift = 1;
    }

    if(
            mode_arc == 0 &&
            mode_circle_2p == 0 &&
            mode_circle_3p == 0 &&
            mode_cubic_hermite_spline == 0 &&
            mode_ellipse == 0 &&
            mode_line == 0 &&
            mode_linestrip == 0 &&
            mode_polygon == 0 &&
            mode_cubic_bezier_curve == 0 &&
            mode_rectangular == 0 &&
            mode_text == 0 &&
            mode_text_edit == 0 &&
            mode_chamfer == 0 &&
            mode_copy == 0 &&
            mode_delete == 0 &&
            mode_extend == 0 &&
            mode_fillet == 0 &&
            mode_mirror == 0 &&
            mode_move == 0 &&
            mode_offset == 0 &&
            mode_rotate == 0 &&
            mode_scale == 0 &&
            mode_stretch == 0 &&
            mode_trim == 0 &&
            mode_dimension == 0 &&
            mode_contour_recognize == 0 &&
            mode_contour_offset == 0 &&
            mode_contour_autonest == 0 &&
            mode_print == 0){

        click=0;
        //qDebug() << "key :" << key;

        if(key == 76){ //l
            mode_linestrip=1;
        }
        if(key == 67){ //c
            mode_copy=1;
        }
        if(key == 77){ //m
            mode_mirror=1;
        }
        if(key == 82){ //r
            mode_mirror=1;
        }
        if(key == 84){ //t
            mode_trim=1;
        }
        if(key == 69){ //e
            mode_extend=1;
        }


    }
}






















