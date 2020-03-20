#include "cam_array.h"
#include <core_functions/variables.h>
#define myqDebug() qDebug() << fixed << qSetRealNumberPrecision(3)

cam_array::cam_array()
{
    myqDebug()  << "\n"
                << "Grotius 2019 Cam Array Analys\n\n"
                << "- Parallel Multidimensional Arrays\n"
                << "- Data Input External Variables\n"
                << "- Used For Cad Cam Processing\n";

    //out.setRealNumberNotation(QTextStream::FixedNotation);

    for (int i=0 ; i < cam_counter; i++) {
    myqDebug()  << "\t" << "arrayline           "   << "\t"     << i                             <<"\n"
                << "\t" << "dxf integer parameters : "                                           <<"\n"
                << "\t" << "id                  "   << "\t"     << int_cam_array[i][0]       <<"\n" //id 1 = line, id 2 = circle, id 3 = arc, id 4 = ellipse, id 5 = cubic bezier curve, id 6 = cubic hermite spline

                << "\t" << "linewidth           "   << "\t"     << int_cam_array[i][2]       <<"\n"
                << "\t" << "selected 1 or 0     "   << "\t"     << int_cam_array[i][3]       <<"\n"
                << "\t" << "object highlight    "   << "\t"     << int_cam_array[i][4]       <<"\n"
                << "\t" << "linetype            "   << "\t"     << int_cam_array[i][5]       <<"\n"
                << "\t" << "selected startpoint "   << "\t"     << int_cam_array[i][6]       <<"\n" //bool selected
                << "\t" << "selected endpoint   "   << "\t"     << int_cam_array[i][7]       <<"\n"
                << "\t" << "selected midpoint   "   << "\t"     << int_cam_array[i][8]       <<"\n"

                << "\t" << "start match         "   << "\t"     << int_cam_array[i][10]      <<"\n"
                << "\t" << "end match           "   << "\t"     << int_cam_array[i][11]      <<"\n"
                << "\t" << "contour cw          "   << "\t"     << int_cam_array[i][12]      <<"\n"
                << "\t" << "contour ccw         "   << "\t"     << int_cam_array[i][13]      <<"\n"
                << "\t" << "contournumber       "   << "\t"     << int_cam_array[i][14]      <<"\n"
                << "\t" << "closed contour mark "   << "\t"     << int_cam_array[i][15]      <<"\n"
                << "\t" << "depth               "   << "\t"     << int_cam_array[i][16]      <<"\n"

                << "\t" << "g2 arc              "   << "\t"     << int_cam_array[i][20]      <<"\n"
                << "\t" << "g3 arc              "   << "\t"     << int_cam_array[i][21]      <<"\n"
                << "\t" << "Gcode arc I         "   << "\t"     << int_cam_array[i][22]      <<"\n"
                << "\t" << "Gcode arc J         "   << "\t"     << int_cam_array[i][23]      <<"\n"
                << "\t" << "Is lead in i        "   << "\t"     << int_cam_array[i][24]      <<"\n"
                << "\t" << "Is lead out i       "   << "\t"     << int_cam_array[i][25]      <<"\n"
                << "\t" << "gcode id text       "   << "\t"     << int_cam_array[i][26]      <<"\n"

                << "\t" << "dxf double parameters : "                                        <<"\n"
                << "\t" << "x start             "   << "\t"     << double_cam_array[i][0]    <<"\n"
                << "\t" << "y start             "   << "\t"     << double_cam_array[i][1]    <<"\n"
                << "\t" << "z start             "   << "\t"     << double_cam_array[i][2]    <<"\n"
                << "\t" << "x end               "   << "\t"     << double_cam_array[i][3]    <<"\n"
                << "\t" << "y end               "   << "\t"     << double_cam_array[i][4]    <<"\n"
                << "\t" << "z end               "   << "\t"     << double_cam_array[i][5]    <<"\n"
                << "\t" << "x center            "   << "\t"     << double_cam_array[i][6]    <<"\n"
                << "\t" << "y_center            "   << "\t"     << double_cam_array[i][7]    <<"\n"
                << "\t" << "z_center            "   << "\t"     << double_cam_array[i][8]    <<"\n"
                << "\t" << "radius x (circle)   "   << "\t"     << double_cam_array[i][9]    <<"\n"
                << "\t" << "radius y (ellipse)  "   << "\t"     << double_cam_array[i][10]   <<"\n"

                << "\t" << "start angle         "   << "\t"     << double_cam_array[i][11]   <<"\n"
                << "\t" << "end angle           "   << "\t"     << double_cam_array[i][12]   <<"\n"

                << "\t" << "x mid (on arc line) "   << "\t"     << double_cam_array[i][15]    <<"\n"
                << "\t" << "y mid               "   << "\t"     << double_cam_array[i][16]    <<"\n"
                << "\t" << "z mid               "   << "\t"     << double_cam_array[i][17]    <<"\n"

                << "\t" << "linewidth           "   << "\t"     << double_cam_array[i][19]   <<"\n"
                << "\t" << "contour area        "   << "\t"     << double_cam_array[i][20]   <<"\n" //mention..

                << "\t" << "x circle left       "   << "\t"     << double_cam_array[i][25]   <<"\n"
                << "\t" << "y circle left       "   << "\t"     << double_cam_array[i][26]   <<"\n"
                << "\t" << "z circle left       "   << "\t"     << double_cam_array[i][27]   <<"\n"
                << "\t" << "x circle right      "   << "\t"     << double_cam_array[i][28]   <<"\n"
                << "\t" << "y circle right      "   << "\t"     << double_cam_array[i][29]   <<"\n"
                << "\t" << "z circle right      "   << "\t"     << double_cam_array[i][30]   <<"\n"
                << "\t" << "x circle top        "   << "\t"     << double_cam_array[i][31]   <<"\n"
                << "\t" << "y circle top        "   << "\t"     << double_cam_array[i][32]   <<"\n"
                << "\t" << "z circle top        "   << "\t"     << double_cam_array[i][33]   <<"\n"
                << "\t" << "x circle bottom     "   << "\t"     << double_cam_array[i][34]   <<"\n"
                << "\t" << "y circle bottom     "   << "\t"     << double_cam_array[i][35]   <<"\n"
                << "\t" << "z circle bottom     "   << "\t"     << double_cam_array[i][36]   <<"\n"

                << "\t" << "Fx_right (ellips focus) "   << "\t"     << double_cam_array[i][40]   <<"\n"
                << "\t" << "Fy_right                "   << "\t"     << double_cam_array[i][41]   <<"\n"
                << "\t" << "Fx_left  (ellips focus) "   << "\t"     << double_cam_array[i][42]   <<"\n"
                << "\t" << "Fy_left                 "   << "\t"     << double_cam_array[i][43]   <<"\n"
                << "\t" << "AB                      "   << "\t"     << double_cam_array[i][44]   <<"\n"

                << "\t" << "Bx (bezier curve)       "   << "\t"     << double_cam_array[i][50]   <<"\n"
                << "\t" << "By (bezier curve)       "   << "\t"     << double_cam_array[i][51]   <<"\n"
                << "\t" << "Bz (bezier curve)       "   << "\t"     << double_cam_array[i][52]   <<"\n"
                << "\t" << "Cx (bezier curve)       "   << "\t"     << double_cam_array[i][53]   <<"\n"
                << "\t" << "Cy (bezier curve)       "   << "\t"     << double_cam_array[i][54]   <<"\n"
                << "\t" << "Cz (bezier curve)       "   << "\t"     << double_cam_array[i][55]   <<"\n"

                << "\t" << "rgb colors : "                                                       <<"\n"
                << "\t" << "red                    "   << "\t"     << double_cam_array[i][56]    <<"\n"
                << "\t" << "green                  "   << "\t"     << double_cam_array[i][57]    <<"\n"
                << "\t" << "blue                   "   << "\t"     << double_cam_array[i][58]    <<"\n"
                << "\t" << "alpha                  "   << "\t"     << double_cam_array[i][59]    <<"\n"

                << "\t" << "text string            "   << "\t"     << string_cad_array[i][0]     <<"\n"
                << "\t" << "layer name             "   << "\t"     << string_cad_array[i][1]     <<"\n";
    }
}
