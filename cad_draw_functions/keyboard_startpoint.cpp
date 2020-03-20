#include "keyboard_startpoint.h"
#include <core_functions/variables.h>

keyboard_startpoint::keyboard_startpoint(int i)
{
    int aa = 0; //start value from first ,
    int bb = 0; //start value from next ,

    //strip left text..
    for(int i = 0; i < string_user_input.size(); i++){
        x.append(string_user_input.at(i));
        if(string_user_input.at(i) == ","){
            x.chop(1);
            aa = i+1;
            break;
        }
    }
    //qDebug() << "the left text is : " << x;

    //strip middle text..
    for(int i = aa; i < string_user_input.size(); i++){

        y.append(string_user_input.at(i));
        if(string_user_input.at(i) == ","){
            y.chop(1);
            bb = i + 1;
            break;
        }
    }
    //qDebug() << "the middle text is : " << y;

    //strip right text..
    for(int i = bb; i < string_user_input.size(); i++){

        z.append(string_user_input.at(i));
        if(string_user_input.at(i) == " "){
            z.chop(1);
            break;
        }
    }
    //qDebug() << "the right text is : " << z;

    int_cad_array[i][0] = 1; //id line
    double_cad_array[i][56] = current_gui_color_red_gl;
    double_cad_array[i][57] = current_gui_color_green_gl;
    double_cad_array[i][58] = current_gui_color_blue_gl;
    double_cad_array[i][59] = current_gui_color_alpha_gl;
    int_cad_array[i][5] = current_linetype;
    double_cad_array[i][18] = current_linetype_scale;
    double_cad_array[i][19] = current_linewidth;
    double_cad_array[i][0] = x.toDouble();
    double_cad_array[i][1] = y.toDouble();
    double_cad_array[i][2] = z.toDouble();
    double_cad_array[i][3] = x.toDouble();
    double_cad_array[i][4] = y.toDouble();
    double_cad_array[i][5] = z.toDouble();

    x.clear();
    y.clear();
    z.clear();
}
