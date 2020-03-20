#include "copy_scale_array.h"
#include <core_functions/variables.h>

copy_scale_array::copy_scale_array(int in, int out, double scale_factor, double base_x, double base_y, double base_z)
{
    for(int j=0; j<30; j++){
        int_cad_array[out][j] = int_cad_array[in][j];
    }

    double scaled_base_x = base_x * scale_factor;
    double scaled_base_y = base_y * scale_factor;
    double scaled_base_z = base_z * scale_factor;
    double dist_base_x = scaled_base_x - base_x;
    double dist_base_y = scaled_base_y - base_y;
    double dist_base_z = scaled_base_z - base_z;

    //startpoint scale
    double_cad_array[out][0] = double_cad_array[in][0] * scale_factor;
    double_cad_array[out][1] = double_cad_array[in][1] * scale_factor;
    double_cad_array[out][2] = double_cad_array[in][2] * scale_factor;
    //move the object back to base point..
    double_cad_array[out][0] = double_cad_array[out][0] - dist_base_x;
    double_cad_array[out][1] = double_cad_array[out][1] - dist_base_y;
    double_cad_array[out][2] = double_cad_array[out][2] - dist_base_z;

    //endpoint scale
    double_cad_array[out][3] = double_cad_array[in][3] * scale_factor;
    double_cad_array[out][4] = double_cad_array[in][4] * scale_factor;
    double_cad_array[out][5] = double_cad_array[in][5] * scale_factor;
    //move the object back to base point..
    double_cad_array[out][3] = double_cad_array[out][3] - dist_base_x;
    double_cad_array[out][4] = double_cad_array[out][4] - dist_base_y;
    double_cad_array[out][5] = double_cad_array[out][5] - dist_base_z;

    //centerpoint scale
    double_cad_array[out][6] = double_cad_array[in][6] * scale_factor;
    double_cad_array[out][7] = double_cad_array[in][7] * scale_factor;
    double_cad_array[out][8] = double_cad_array[in][8] * scale_factor;
    //move the object back to base point..
    double_cad_array[out][6] = double_cad_array[out][6] - dist_base_x;
    double_cad_array[out][7] = double_cad_array[out][7] - dist_base_y;
    double_cad_array[out][8] = double_cad_array[out][8] - dist_base_z;

    //<< "\t" << "radius x (circle)   "   << "\t"     << double_cad_array[i][9]    <<"\n"
    //<< "\t" << "radius y (ellipse)  "   << "\t"     << double_cad_array[i][10]   <<"\n"

    double_cad_array[out][9] = double_cad_array[in][9] * scale_factor;
    double_cad_array[out][10] = double_cad_array[in][10] * scale_factor;
    double_cad_array[out][11] = double_cad_array[in][11];
    double_cad_array[out][12] = double_cad_array[in][12];
    double_cad_array[out][13] = double_cad_array[in][13];
    double_cad_array[out][14] = double_cad_array[in][14];

    //midpoint scale
    double_cad_array[out][15] = double_cad_array[in][15] * scale_factor;
    double_cad_array[out][16] = double_cad_array[in][16] * scale_factor;
    double_cad_array[out][17] = double_cad_array[in][17] * scale_factor;
    //move the object back to base point..
    double_cad_array[out][15] = double_cad_array[out][15] - dist_base_x;
    double_cad_array[out][16] = double_cad_array[out][16] - dist_base_y;
    double_cad_array[out][17] = double_cad_array[out][17] - dist_base_z;

    //circle left scale
    double_cad_array[out][25] = double_cad_array[in][25] * scale_factor;
    double_cad_array[out][26] = double_cad_array[in][26] * scale_factor;
    double_cad_array[out][27] = double_cad_array[in][27] * scale_factor;
    //move the object back to base point..
    double_cad_array[out][25] = double_cad_array[out][25] - dist_base_x;
    double_cad_array[out][26] = double_cad_array[out][26] - dist_base_y;
    double_cad_array[out][27] = double_cad_array[out][27] - dist_base_z;

    //circle right scale
    double_cad_array[out][28] = double_cad_array[in][28] * scale_factor;
    double_cad_array[out][29] = double_cad_array[in][29] * scale_factor;
    double_cad_array[out][30] = double_cad_array[in][30] * scale_factor;
    //move the object back to base point..
    double_cad_array[out][28] = double_cad_array[out][28] - dist_base_x;
    double_cad_array[out][29] = double_cad_array[out][29] - dist_base_y;
    double_cad_array[out][30] = double_cad_array[out][30] - dist_base_z;

    //circle top scale
    double_cad_array[out][31] = double_cad_array[in][31] * scale_factor;
    double_cad_array[out][32] = double_cad_array[in][32] * scale_factor;
    double_cad_array[out][33] = double_cad_array[in][33] * scale_factor;
    //move the object back to base point..
    double_cad_array[out][31] = double_cad_array[out][31] - dist_base_x;
    double_cad_array[out][32] = double_cad_array[out][32] - dist_base_y;
    double_cad_array[out][33] = double_cad_array[out][33] - dist_base_z;

    //circle bottom scale
    double_cad_array[out][34] = double_cad_array[in][34] * scale_factor;
    double_cad_array[out][35] = double_cad_array[in][35] * scale_factor;
    double_cad_array[out][36] = double_cad_array[in][36] * scale_factor;
    //move the object back to base point..
    double_cad_array[out][34] = double_cad_array[out][34] - dist_base_x;
    double_cad_array[out][35] = double_cad_array[out][35] - dist_base_y;
    double_cad_array[out][36] = double_cad_array[out][36] - dist_base_z;

    //ellipse scale focus a
    double_cad_array[out][40] = double_cad_array[in][40] * scale_factor;
    double_cad_array[out][41] = double_cad_array[in][41] * scale_factor;
    //move the object back to base point..
    double_cad_array[out][40] = double_cad_array[out][40] - dist_base_x;
    double_cad_array[out][41] = double_cad_array[out][41] - dist_base_y;


    //ellipse scale focus b
    double_cad_array[out][42] = double_cad_array[in][42] * scale_factor;
    double_cad_array[out][43] = double_cad_array[in][43] * scale_factor;
    //move the object back to base point..
    double_cad_array[out][42] = double_cad_array[out][42] - dist_base_x;
    double_cad_array[out][43] = double_cad_array[out][43] - dist_base_y;

    double_cad_array[out][44] = double_cad_array[in][44];

    //bezier curve scale b
    double_cad_array[out][50] = double_cad_array[in][50] * scale_factor;
    double_cad_array[out][51] = double_cad_array[in][51] * scale_factor;
    double_cad_array[out][52] = double_cad_array[in][52] * scale_factor;
    //move the object back to base point..
    double_cad_array[out][50] = double_cad_array[out][50] - dist_base_x;
    double_cad_array[out][51] = double_cad_array[out][51] - dist_base_y;
    double_cad_array[out][52] = double_cad_array[out][52] - dist_base_z;

    //bezier curve scale c
    double_cad_array[out][53] = double_cad_array[in][53] * scale_factor;
    double_cad_array[out][54] = double_cad_array[in][54] * scale_factor;
    double_cad_array[out][55] = double_cad_array[in][55] * scale_factor;
    //move the object back to base point..
    double_cad_array[out][53] = double_cad_array[out][53] - dist_base_x;
    double_cad_array[out][54] = double_cad_array[out][54] - dist_base_y;
    double_cad_array[out][55] = double_cad_array[out][55] - dist_base_z;
}
