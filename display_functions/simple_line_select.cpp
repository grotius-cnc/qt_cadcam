#include "simple_line_select.h"
#include <core_functions/variables.h>
#include <math.h>
#define myqDebug() qDebug() << fixed << qSetRealNumberPrecision(3)

simple_line_select::simple_line_select() //used for non critical selections.. (no coordinate selection, only id retrieve..)
{
    if(mode_cad){
        for (int i = 0; i < cad_counter; i++) {

            if(int_cad_array[i][0] == 1 /*|| mode_chamfer || mode_fillet*/){ //id = line..

                double x0 = double_cad_array[i][0];
                double y0 = double_cad_array[i][1];
                double x1 = double_cad_array[i][3];
                double y1 = double_cad_array[i][4];

                double cx = mouse_cad_pos_x;
                double cy = mouse_cad_pos_y;
                double radius = snap_dist;

                double dx, dy, A, B, C, det, t;

                dx = x1 - x0;
                dy = y1 - y0;

                A = dx * dx + dy * dy;
                B = 2 * (dx * (x0 - cx) + dy * (y0 - cy));
                C = (x0 - cx) * (x0 - cx) + (y0 - cy) * (y0 - cy) - radius * radius;

                det = B * B - 4 * A * C;

                t = (-B + sqrt(det)) / (2 * A);
                double ix0 = (x0 + t * dx); //myqDebug()<< "ix0 : " << ix0;
                double iy0 = (y0 + t * dy); //myqDebug()<< "iy0 : " << iy0;

                t = (-B - sqrt(det)) / (2 * A);
                double ix1 = (x0 + t * dx); //myqDebug()<< "ix1 : " << ix1;
                double iy1 = (y0 + t * dy); //myqDebug()<< "iy1 : " << iy1;

                //qDebug()<< isnan(ix0);
                double ac = sqrt(pow(x0-x1,2)+pow(y0-y1,2));
                double ab = sqrt(pow(x0-mouse_cad_pos_x,2)+pow(y0-mouse_cad_pos_y,2));
                double bc = sqrt(pow(x1-mouse_cad_pos_x,2)+pow(y1-mouse_cad_pos_y,2));

                if(/*(isnan(ix0)==true || isnan(ix1)==true)*/  ac-2<ab+bc && ac+2>ab+bc){
                    int_cad_array[i][4] = 1; //highlight hovering..
                    select_id = i;
                    break;
                } else {
                    int_cad_array[i][4] = 0;
                    select_id = -1;
                }
            }
        }
    }
}
