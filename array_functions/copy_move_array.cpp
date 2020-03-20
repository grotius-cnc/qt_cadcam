#include "copy_move_array.h"
#include <core_functions/variables.h>

copy_move_array::copy_move_array(int in, int out, double dist_x, double dist_y, double dist_z)
{
    for(int j=0; j<30; j++){
        int_cad_array[out][j] = int_cad_array[in][j];
    }

        string_cad_array[out][0] = string_cad_array[in][0];

        double_cad_array[out][0] = double_cad_array[in][0] + dist_x; //startpoint
        double_cad_array[out][1] = double_cad_array[in][1] + dist_y;
        double_cad_array[out][2] = double_cad_array[in][2] + dist_z;

        double_cad_array[out][3] = double_cad_array[in][3] + dist_x; //endpoint
        double_cad_array[out][4] = double_cad_array[in][4] + dist_y;
        double_cad_array[out][5] = double_cad_array[in][5] + dist_z;

        double_cad_array[out][6] = double_cad_array[in][6] + dist_x; //centerpoint
        double_cad_array[out][7] = double_cad_array[in][7] + dist_y;
        double_cad_array[out][8] = double_cad_array[in][8] + dist_z;

        double_cad_array[out][9] = double_cad_array[in][9];
        double_cad_array[out][10] = double_cad_array[in][10];
        double_cad_array[out][11] = double_cad_array[in][11];
        double_cad_array[out][12] = double_cad_array[in][12];
        double_cad_array[out][13] = double_cad_array[in][13];
        double_cad_array[out][14] = double_cad_array[in][14];

        double_cad_array[out][15] = double_cad_array[in][15] + dist_x; //midpoint
        double_cad_array[out][16] = double_cad_array[in][16] + dist_y;
        double_cad_array[out][17] = double_cad_array[in][17] + dist_z;

        double_cad_array[out][18] = double_cad_array[in][18]; //linetype scale
        double_cad_array[out][19] = double_cad_array[in][19]; //linewidht
        //double_cad_array[out][20] = double_cad_array[in][20]; //contour area

        double_cad_array[out][21] = double_cad_array[in][21] + dist_x; //dimension p0x
        double_cad_array[out][22] = double_cad_array[in][22] + dist_y;
        double_cad_array[out][23] = double_cad_array[in][23] + dist_x; //dimension p1x
        double_cad_array[out][24] = double_cad_array[in][24] + dist_y;

        double_cad_array[out][25] = double_cad_array[in][25] + dist_x; //circle left
        double_cad_array[out][26] = double_cad_array[in][26] + dist_y;
        double_cad_array[out][27] = double_cad_array[in][27] + dist_z;

        double_cad_array[out][28] = double_cad_array[in][28] + dist_x; //circle right
        double_cad_array[out][29] = double_cad_array[in][29] + dist_y;
        double_cad_array[out][30] = double_cad_array[in][30] + dist_z;

        double_cad_array[out][31] = double_cad_array[in][31] + dist_x; //circle top
        double_cad_array[out][32] = double_cad_array[in][32] + dist_y;
        double_cad_array[out][33] = double_cad_array[in][33] + dist_z;

        double_cad_array[out][34] = double_cad_array[in][34] + dist_x; //circle bottom
        double_cad_array[out][35] = double_cad_array[in][35] + dist_y;
        double_cad_array[out][36] = double_cad_array[in][36] + dist_z;

        double_cad_array[out][40] = double_cad_array[in][40] + dist_x; //ellipse
        double_cad_array[out][41] = double_cad_array[in][41] + dist_y;
        double_cad_array[out][42] = double_cad_array[in][42] + dist_x;
        double_cad_array[out][43] = double_cad_array[in][43] + dist_y;

        double_cad_array[out][44] = double_cad_array[in][44];

        double_cad_array[out][50] = double_cad_array[in][50] + dist_x; //bezier curve
        double_cad_array[out][51] = double_cad_array[in][51] + dist_y;
        double_cad_array[out][52] = double_cad_array[in][52] + dist_z;
        double_cad_array[out][53] = double_cad_array[in][53] + dist_x;
        double_cad_array[out][54] = double_cad_array[in][54] + dist_y;
        double_cad_array[out][55] = double_cad_array[in][55] + dist_z;

        double_cad_array[out][56] = double_cad_array[in][56]; //red
        double_cad_array[out][57] = double_cad_array[in][57]; //green
        double_cad_array[out][58] = double_cad_array[in][58]; //blue
        double_cad_array[out][59] = double_cad_array[in][59]; //alpha
}




