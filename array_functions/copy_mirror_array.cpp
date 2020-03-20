#include "copy_mirror_array.h"
#include <core_functions/variables.h>

copy_mirror_array::copy_mirror_array(int in, int out, double p1x_mirror, double p1y_mirror, double p2x_mirror, double p2y_mirror, double angle)
{
    for(int j=0; j<30; j++){
        int_cad_array[out][j] = int_cad_array[in][j];
    }

    //linetype..
    double_cad_array[out][18] = double_cad_array[in][18]; //linetype scale
    double_cad_array[out][19] = double_cad_array[in][19]; //linewidth

    //colors..
    double_cad_array[out][56] = double_cad_array[in][56];
    double_cad_array[out][57] = double_cad_array[in][57];
    double_cad_array[out][58] = double_cad_array[in][58];
    double_cad_array[out][59] = double_cad_array[in][59];

    //startpoint mirror..
    double px_in = double_cad_array[in][0];
    double py_in = double_cad_array[in][1];
    double pz_in = double_cad_array[in][2];

    double dx  = p2x_mirror - p1x_mirror;
    double dy  = p2y_mirror - p1y_mirror;
    double a_   = (dx * dx - dy * dy) / (dx * dx + dy*dy);
    double b   = 2 * dx * dy / (dx*dx + dy*dy);

    double px_out  = (a_ * (px_in - p1x_mirror) + b*(py_in - p1y_mirror) + p1x_mirror);
    double py_out  = (b * (px_in - p1x_mirror) - a_*(py_in - p1y_mirror) + p1y_mirror);
    double pz_out = pz_in;

    double_cad_array[out][0] = px_out;
    double_cad_array[out][1] = py_out;
    double_cad_array[out][2] = pz_out;

    //endpoint mirror..
    px_in = double_cad_array[in][3];
    py_in = double_cad_array[in][4];
    pz_in = double_cad_array[in][5];

    dx  = p2x_mirror - p1x_mirror;
    dy  = p2y_mirror - p1y_mirror;
    a_   = (dx * dx - dy * dy) / (dx * dx + dy*dy);
    b   = 2 * dx * dy / (dx*dx + dy*dy);

    px_out  = (a_ * (px_in - p1x_mirror) + b*(py_in - p1y_mirror) + p1x_mirror);
    py_out  = (b * (px_in - p1x_mirror) - a_*(py_in - p1y_mirror) + p1y_mirror);
    pz_out = pz_in;

    double_cad_array[out][3] = px_out;
    double_cad_array[out][4] = py_out;
    double_cad_array[out][5] = pz_out;

    //centerpoint mirror..
    px_in = double_cad_array[in][6];
    py_in = double_cad_array[in][7];
    pz_in = double_cad_array[in][8];

    dx  = p2x_mirror - p1x_mirror;
    dy  = p2y_mirror - p1y_mirror;
    a_   = (dx * dx - dy * dy) / (dx * dx + dy*dy);
    b   = 2 * dx * dy / (dx*dx + dy*dy);

    px_out  = (a_ * (px_in - p1x_mirror) + b*(py_in - p1y_mirror) + p1x_mirror);
    py_out  = (b * (px_in - p1x_mirror) - a_*(py_in - p1y_mirror) + p1y_mirror);
    pz_out = pz_in;

    double_cad_array[out][6] = px_out;
    double_cad_array[out][7] = py_out;
    double_cad_array[out][8] = pz_out;

    //keep as it is..
    double_cad_array[out][9] = double_cad_array[in][9]; //radius x (circle)
    double_cad_array[out][10] = double_cad_array[in][10]; //"radius y (ellipse)



    //calculate ellipse mirror angle..
    double ellipse_end_angle = double_cad_array[in][11];
    double mirrorline_angle = angle;
    double delta = ellipse_end_angle - mirrorline_angle;
    double mirrored_ellipse_angle = mirrorline_angle - delta;

    double_cad_array[out][11] = mirrored_ellipse_angle ; //ellipse angle - mirror line angle..

    double_cad_array[out][12] = double_cad_array[in][12];

    //<< "\t" << "start angle         "   << "\t"     << double_cad_array[i][11]   <<"\n"
    //<< "\t" << "end angle           "   << "\t"     << double_cad_array[i][12]   <<"\n"

    //midpoint mirror..
    px_in = double_cad_array[in][15];
    py_in = double_cad_array[in][16];
    pz_in = double_cad_array[in][17];

    dx  = p2x_mirror - p1x_mirror;
    dy  = p2y_mirror - p1y_mirror;
    a_   = (dx * dx - dy * dy) / (dx * dx + dy*dy);
    b   = 2 * dx * dy / (dx*dx + dy*dy);

    px_out  = (a_ * (px_in - p1x_mirror) + b*(py_in - p1y_mirror) + p1x_mirror);
    py_out  = (b * (px_in - p1x_mirror) - a_*(py_in - p1y_mirror) + p1y_mirror);
    pz_out = pz_in;

    double_cad_array[out][15] = px_out;
    double_cad_array[out][16] = py_out;
    double_cad_array[out][17] = pz_out;

    //circle left mirror..
    px_in = double_cad_array[in][25];
    py_in = double_cad_array[in][26];
    pz_in = double_cad_array[in][27];

    dx  = p2x_mirror - p1x_mirror;
    dy  = p2y_mirror - p1y_mirror;
    a_   = (dx * dx - dy * dy) / (dx * dx + dy*dy);
    b   = 2 * dx * dy / (dx*dx + dy*dy);

    px_out  = (a_ * (px_in - p1x_mirror) + b*(py_in - p1y_mirror) + p1x_mirror);
    py_out  = (b * (px_in - p1x_mirror) - a_*(py_in - p1y_mirror) + p1y_mirror);
    pz_out = pz_in;

    double_cad_array[out][25] = px_out;
    double_cad_array[out][26] = py_out;
    double_cad_array[out][27] = pz_out;

    //circle right mirror..
    px_in = double_cad_array[in][28];
    py_in = double_cad_array[in][29];
    pz_in = double_cad_array[in][30];

    dx  = p2x_mirror - p1x_mirror;
    dy  = p2y_mirror - p1y_mirror;
    a_   = (dx * dx - dy * dy) / (dx * dx + dy*dy);
    b   = 2 * dx * dy / (dx*dx + dy*dy);

    px_out  = (a_ * (px_in - p1x_mirror) + b*(py_in - p1y_mirror) + p1x_mirror);
    py_out  = (b * (px_in - p1x_mirror) - a_*(py_in - p1y_mirror) + p1y_mirror);
    pz_out = pz_in;

    double_cad_array[out][28] = px_out;
    double_cad_array[out][29] = py_out;
    double_cad_array[out][30] = pz_out;

    //circle top mirror..
    px_in = double_cad_array[in][31];
    py_in = double_cad_array[in][32];
    pz_in = double_cad_array[in][33];

    dx  = p2x_mirror - p1x_mirror;
    dy  = p2y_mirror - p1y_mirror;
    a_   = (dx * dx - dy * dy) / (dx * dx + dy*dy);
    b   = 2 * dx * dy / (dx*dx + dy*dy);

    px_out  = (a_ * (px_in - p1x_mirror) + b*(py_in - p1y_mirror) + p1x_mirror);
    py_out  = (b * (px_in - p1x_mirror) - a_*(py_in - p1y_mirror) + p1y_mirror);
    pz_out = pz_in;

    double_cad_array[out][31] = px_out;
    double_cad_array[out][32] = py_out;
    double_cad_array[out][33] = pz_out;

    //circle bottom mirror..
    px_in = double_cad_array[in][34];
    py_in = double_cad_array[in][35];
    pz_in = double_cad_array[in][36];

    dx  = p2x_mirror - p1x_mirror;
    dy  = p2y_mirror - p1y_mirror;
    a_   = (dx * dx - dy * dy) / (dx * dx + dy*dy);
    b   = 2 * dx * dy / (dx*dx + dy*dy);

    px_out  = (a_ * (px_in - p1x_mirror) + b*(py_in - p1y_mirror) + p1x_mirror);
    py_out  = (b * (px_in - p1x_mirror) - a_*(py_in - p1y_mirror) + p1y_mirror);
    pz_out = pz_in;

    double_cad_array[out][34] = px_out;
    double_cad_array[out][35] = py_out;
    double_cad_array[out][36] = pz_out;

    //ellipse mirror.. focus 1
    px_in = double_cad_array[in][40];
    py_in = double_cad_array[in][41];

    dx  = p2x_mirror - p1x_mirror;
    dy  = p2y_mirror - p1y_mirror;
    a_   = (dx * dx - dy * dy) / (dx * dx + dy*dy);
    b   = 2 * dx * dy / (dx*dx + dy*dy);

    px_out  = (a_ * (px_in - p1x_mirror) + b*(py_in - p1y_mirror) + p1x_mirror);
    py_out  = (b * (px_in - p1x_mirror) - a_*(py_in - p1y_mirror) + p1y_mirror);
    pz_out = pz_in;

    double_cad_array[out][40] = px_out;
    double_cad_array[out][41] = py_out;

    //ellipse mirror.. focus 2
    px_in = double_cad_array[in][42];
    py_in = double_cad_array[in][43];

    dx  = p2x_mirror - p1x_mirror;
    dy  = p2y_mirror - p1y_mirror;
    a_   = (dx * dx - dy * dy) / (dx * dx + dy*dy);
    b   = 2 * dx * dy / (dx*dx + dy*dy);

    px_out  = (a_ * (px_in - p1x_mirror) + b*(py_in - p1y_mirror) + p1x_mirror);
    py_out  = (b * (px_in - p1x_mirror) - a_*(py_in - p1y_mirror) + p1y_mirror);
    pz_out = pz_in;

    double_cad_array[out][42] = px_out;
    double_cad_array[out][43] = py_out;

    double_cad_array[out][44] = double_cad_array[in][44] ;

    //bezier curve mirror.. Bx, By
    px_in = double_cad_array[in][50];
    py_in = double_cad_array[in][51];
    pz_in = double_cad_array[in][52];

    dx  = p2x_mirror - p1x_mirror;
    dy  = p2y_mirror - p1y_mirror;
    a_   = (dx * dx - dy * dy) / (dx * dx + dy*dy);
    b   = 2 * dx * dy / (dx*dx + dy*dy);

    px_out  = (a_ * (px_in - p1x_mirror) + b*(py_in - p1y_mirror) + p1x_mirror);
    py_out  = (b * (px_in - p1x_mirror) - a_*(py_in - p1y_mirror) + p1y_mirror);
    pz_out = pz_in;

    double_cad_array[out][50] = px_out;
    double_cad_array[out][51] = py_out;
    double_cad_array[out][52] = pz_out;

    //bezier curve mirror.. Cx, Cy
    px_in = double_cad_array[in][53];
    py_in = double_cad_array[in][54];
    pz_in = double_cad_array[in][55];

    dx  = p2x_mirror - p1x_mirror;
    dy  = p2y_mirror - p1y_mirror;
    a_   = (dx * dx - dy * dy) / (dx * dx + dy*dy);
    b   = 2 * dx * dy / (dx*dx + dy*dy);

    px_out  = (a_ * (px_in - p1x_mirror) + b*(py_in - p1y_mirror) + p1x_mirror);
    py_out  = (b * (px_in - p1x_mirror) - a_*(py_in - p1y_mirror) + p1y_mirror);
    pz_out = pz_in;

    double_cad_array[out][53] = px_out;
    double_cad_array[out][54] = py_out;
    double_cad_array[out][55] = pz_out;

}


