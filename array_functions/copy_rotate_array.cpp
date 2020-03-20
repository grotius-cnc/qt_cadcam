#include "copy_rotate_array.h"
#include <core_functions/variables.h>

copy_rotate_array::copy_rotate_array(int in, int out, double rotate_degrees, double rotate_origin_x, double rotate_origin_y)
{
    for(int j=0; j<30; j++){
        int_cad_array[out][j] = int_cad_array[in][j];
    }

    //startpoint
    double rotate_dist_x = double_cad_array[in][0] - rotate_origin_x;
    double rotate_dist_y = double_cad_array[in][1] - rotate_origin_y;
    double rotate_x = cos(rotate_degrees * M_PI / 180.0 )* rotate_dist_x - sin(rotate_degrees * M_PI / 180.0 ) * rotate_dist_y;
    double rotate_y = sin(rotate_degrees * M_PI / 180.0 )* rotate_dist_x + cos(rotate_degrees * M_PI / 180.0 ) * rotate_dist_y;
    double_cad_array[out][0] = rotate_x + rotate_origin_x;
    double_cad_array[out][1] = rotate_y + rotate_origin_y;
    double_cad_array[out][2] = double_cad_array[in][2];

    //endpoint
    rotate_dist_x = double_cad_array[in][3] - rotate_origin_x;
    rotate_dist_y = double_cad_array[in][4] - rotate_origin_y;
    rotate_x = cos(rotate_degrees * M_PI / 180.0 )* rotate_dist_x - sin(rotate_degrees * M_PI / 180.0 ) * rotate_dist_y;
    rotate_y = sin(rotate_degrees * M_PI / 180.0 )* rotate_dist_x + cos(rotate_degrees * M_PI / 180.0 ) * rotate_dist_y;
    double_cad_array[out][3] = rotate_x + rotate_origin_x;
    double_cad_array[out][4] = rotate_y + rotate_origin_y;
    double_cad_array[out][5] = double_cad_array[in][5];

    //centerpoint
    rotate_dist_x = double_cad_array[in][6] - rotate_origin_x;
    rotate_dist_y = double_cad_array[in][7] - rotate_origin_y;
    rotate_x = cos(rotate_degrees * M_PI / 180.0 )* rotate_dist_x - sin(rotate_degrees * M_PI / 180.0 ) * rotate_dist_y;
    rotate_y = sin(rotate_degrees * M_PI / 180.0 )* rotate_dist_x + cos(rotate_degrees * M_PI / 180.0 ) * rotate_dist_y;
    double_cad_array[out][6] = rotate_x + rotate_origin_x;
    double_cad_array[out][7] = rotate_y + rotate_origin_y;
    double_cad_array[out][8] = double_cad_array[in][5];

    double_cad_array[out][9] = double_cad_array[in][9];
    double_cad_array[out][10] = double_cad_array[in][10];
    double_cad_array[out][11] = double_cad_array[in][11];
    double_cad_array[out][12] = double_cad_array[in][12];
    double_cad_array[out][13] = double_cad_array[in][13];
    double_cad_array[out][14] = double_cad_array[in][14];

    //midpoint
    rotate_dist_x = double_cad_array[in][15] - rotate_origin_x;
    rotate_dist_y = double_cad_array[in][16] - rotate_origin_y;
    rotate_x = cos(rotate_degrees * M_PI / 180.0 )* rotate_dist_x - sin(rotate_degrees * M_PI / 180.0 ) * rotate_dist_y;
    rotate_y = sin(rotate_degrees * M_PI / 180.0 )* rotate_dist_x + cos(rotate_degrees * M_PI / 180.0 ) * rotate_dist_y;
    double_cad_array[out][15] = rotate_x + rotate_origin_x;
    double_cad_array[out][16] = rotate_y + rotate_origin_y;
    double_cad_array[out][17] = double_cad_array[in][17];

    //circle left
    rotate_dist_x = double_cad_array[in][25] - rotate_origin_x;
    rotate_dist_y = double_cad_array[in][26] - rotate_origin_y;
    rotate_x = cos(rotate_degrees * M_PI / 180.0 )* rotate_dist_x - sin(rotate_degrees * M_PI / 180.0 ) * rotate_dist_y;
    rotate_y = sin(rotate_degrees * M_PI / 180.0 )* rotate_dist_x + cos(rotate_degrees * M_PI / 180.0 ) * rotate_dist_y;
    double_cad_array[out][25] = rotate_x + rotate_origin_x;
    double_cad_array[out][26] = rotate_y + rotate_origin_y;
    double_cad_array[out][27] = double_cad_array[in][27];

    //circle right
    rotate_dist_x = double_cad_array[in][28] - rotate_origin_x;
    rotate_dist_y = double_cad_array[in][29] - rotate_origin_y;
    rotate_x = cos(rotate_degrees * M_PI / 180.0 )* rotate_dist_x - sin(rotate_degrees * M_PI / 180.0 ) * rotate_dist_y;
    rotate_y = sin(rotate_degrees * M_PI / 180.0 )* rotate_dist_x + cos(rotate_degrees * M_PI / 180.0 ) * rotate_dist_y;
    double_cad_array[out][28] = rotate_x + rotate_origin_x;
    double_cad_array[out][29] = rotate_y + rotate_origin_y;
    double_cad_array[out][30] = double_cad_array[in][30];

    //circle top
    rotate_dist_x = double_cad_array[in][31] - rotate_origin_x;
    rotate_dist_y = double_cad_array[in][32] - rotate_origin_y;
    rotate_x = cos(rotate_degrees * M_PI / 180.0 )* rotate_dist_x - sin(rotate_degrees * M_PI / 180.0 ) * rotate_dist_y;
    rotate_y = sin(rotate_degrees * M_PI / 180.0 )* rotate_dist_x + cos(rotate_degrees * M_PI / 180.0 ) * rotate_dist_y;
    double_cad_array[out][31] = rotate_x + rotate_origin_x;
    double_cad_array[out][32] = rotate_y + rotate_origin_y;
    double_cad_array[out][33] = double_cad_array[in][33];

    //circle bottom
    rotate_dist_x = double_cad_array[in][34] - rotate_origin_x;
    rotate_dist_y = double_cad_array[in][35] - rotate_origin_y;
    rotate_x = cos(rotate_degrees * M_PI / 180.0 )* rotate_dist_x - sin(rotate_degrees * M_PI / 180.0 ) * rotate_dist_y;
    rotate_y = sin(rotate_degrees * M_PI / 180.0 )* rotate_dist_x + cos(rotate_degrees * M_PI / 180.0 ) * rotate_dist_y;
    double_cad_array[out][34] = rotate_x + rotate_origin_x;
    double_cad_array[out][35] = rotate_y + rotate_origin_y;
    double_cad_array[out][36] = double_cad_array[in][36];

    //ellipse focus a
    rotate_dist_x = double_cad_array[in][40] - rotate_origin_x;
    rotate_dist_y = double_cad_array[in][41] - rotate_origin_y;
    rotate_x = cos(rotate_degrees * M_PI / 180.0 )* rotate_dist_x - sin(rotate_degrees * M_PI / 180.0 ) * rotate_dist_y;
    rotate_y = sin(rotate_degrees * M_PI / 180.0 )* rotate_dist_x + cos(rotate_degrees * M_PI / 180.0 ) * rotate_dist_y;
    double_cad_array[out][40] = rotate_x + rotate_origin_x;
    double_cad_array[out][41] = rotate_y + rotate_origin_y;

    //ellipse focus b
    rotate_dist_x = double_cad_array[in][42] - rotate_origin_x;
    rotate_dist_y = double_cad_array[in][43] - rotate_origin_y;
    rotate_x = cos(rotate_degrees * M_PI / 180.0 )* rotate_dist_x - sin(rotate_degrees * M_PI / 180.0 ) * rotate_dist_y;
    rotate_y = sin(rotate_degrees * M_PI / 180.0 )* rotate_dist_x + cos(rotate_degrees * M_PI / 180.0 ) * rotate_dist_y;
    double_cad_array[out][42] = rotate_x + rotate_origin_x;
    double_cad_array[out][43] = rotate_y + rotate_origin_y;

    //bezier curve B
    rotate_dist_x = double_cad_array[in][50] - rotate_origin_x;
    rotate_dist_y = double_cad_array[in][51] - rotate_origin_y;
    rotate_x = cos(rotate_degrees * M_PI / 180.0 )* rotate_dist_x - sin(rotate_degrees * M_PI / 180.0 ) * rotate_dist_y;
    rotate_y = sin(rotate_degrees * M_PI / 180.0 )* rotate_dist_x + cos(rotate_degrees * M_PI / 180.0 ) * rotate_dist_y;
    double_cad_array[out][50] = rotate_x + rotate_origin_x;
    double_cad_array[out][51] = rotate_y + rotate_origin_y;
    double_cad_array[out][52] = double_cad_array[in][52];

    //bezier curve C
    rotate_dist_x = double_cad_array[in][53] - rotate_origin_x;
    rotate_dist_y = double_cad_array[in][54] - rotate_origin_y;
    rotate_x = cos(rotate_degrees * M_PI / 180.0 )* rotate_dist_x - sin(rotate_degrees * M_PI / 180.0 ) * rotate_dist_y;
    rotate_y = sin(rotate_degrees * M_PI / 180.0 )* rotate_dist_x + cos(rotate_degrees * M_PI / 180.0 ) * rotate_dist_y;
    double_cad_array[out][53] = rotate_x + rotate_origin_x;
    double_cad_array[out][54] = rotate_y + rotate_origin_y;
    double_cad_array[out][55] = double_cad_array[in][55];

    //colors..
    double_cad_array[out][56] = double_cad_array[in][56];
    double_cad_array[out][57] = double_cad_array[in][57];
    double_cad_array[out][58] = double_cad_array[in][58];
    double_cad_array[out][59] = double_cad_array[in][59];

}






















