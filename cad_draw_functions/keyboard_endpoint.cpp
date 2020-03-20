#include "keyboard_endpoint.h"
#include <core_functions/variables.h>

keyboard_endpoint::keyboard_endpoint()
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

    double_cad_array[cad_counter][3] = x.toDouble();
    double_cad_array[cad_counter][4] = y.toDouble();
    double_cad_array[cad_counter][5] = z.toDouble();

    //calculate midpoint..
    double_cad_array[cad_counter][15] =  (double_cad_array[cad_counter][0] +  double_cad_array[cad_counter][3]) / 2; //x midpoint..
    double_cad_array[cad_counter][16] =  (double_cad_array[cad_counter][1] +  double_cad_array[cad_counter][4]) / 2; //y midpoint..
    double_cad_array[cad_counter][17] =  (double_cad_array[cad_counter][2] +  double_cad_array[cad_counter][5]) / 2; //z midpoint..

    x.clear();
    y.clear();
    z.clear();
}
