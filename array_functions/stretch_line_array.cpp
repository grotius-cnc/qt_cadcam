#include "stretch_line_array.h"
#include <core_functions/variables.h>

stretch_line_array::stretch_line_array(int in, int out, QString type, double dist_x, double dist_y, double dist_z)
{
    if(type == "startpoint"){
        double_cad_array[out][0] = double_cad_array[in][0] + dist_x;
        double_cad_array[out][1] = double_cad_array[in][1] + dist_y;
        double_cad_array[out][2] = double_cad_array[in][2] + dist_z;

        //dimension text..
        double_cad_array[out][21] = double_cad_array[in][21] + dist_x; //p0x
        double_cad_array[out][22] = double_cad_array[in][22] + dist_y;
    }

    if(type == "endpoint"){
        double_cad_array[out][3] = double_cad_array[in][3] + dist_x;
        double_cad_array[out][4] = double_cad_array[in][4] + dist_y;
        double_cad_array[out][5] = double_cad_array[in][5] + dist_z;

        //dimension text..
        double_cad_array[out][23] = double_cad_array[in][23] + dist_x; //p1x
        double_cad_array[out][24] = double_cad_array[in][24] + dist_y;
    }

    if(type == "full_object"){
        double_cad_array[out][0] = double_cad_array[in][0] + dist_x;
        double_cad_array[out][1] = double_cad_array[in][1] + dist_y;
        double_cad_array[out][2] = double_cad_array[in][2] + dist_z;
        double_cad_array[out][3] = double_cad_array[in][3] + dist_x;
        double_cad_array[out][4] = double_cad_array[in][4] + dist_y;
        double_cad_array[out][5] = double_cad_array[in][5] + dist_z;

        //dimension text..
        double_cad_array[out][21] = double_cad_array[in][21] + dist_x;
        double_cad_array[out][22] = double_cad_array[in][22] + dist_y;
        double_cad_array[out][23] = double_cad_array[in][23] + dist_x;
        double_cad_array[out][24] = double_cad_array[in][24] + dist_y;
    }

    //calculate new midpoint..
    double_cad_array[out][15] =  (double_cad_array[out][0] +  double_cad_array[out][3]) / 2; //x midpoint..
    double_cad_array[out][16] =  (double_cad_array[out][1] +  double_cad_array[out][4]) / 2; //y midpoint..
    double_cad_array[out][17] =  (double_cad_array[out][2] +  double_cad_array[out][5]) / 2; //z midpoint..
}

