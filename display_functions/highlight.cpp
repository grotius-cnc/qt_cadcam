#include "highlight.h"
#include <core_functions/variables.h>

highlight::highlight(int i)
{
    if(mode_cad){
        if(int_cad_array[i][4] == 1 || int_cad_array[i][3] == 1  ){ //bool highlight.. //bool selected

            glLineWidth(double_cad_array[i][19]+2); //increase linewidth..
            glPointSize(double_cad_array[i][19]+2);
            //qDebug()<< "highlight on";

        } else {
            glLineWidth(double_cad_array[i][19]);
            glPointSize(double_cad_array[i][19]);
        }
    }

    if(mode_cam){
        if(int_cam_array[i][4] == 1 || int_cam_array[i][3] == 1  ){ //bool highlight.. //bool selected

            glLineWidth(double_cam_array[i][19]+2); //increase linewidth..
            glPointSize(double_cam_array[i][19]+2);

        } else {
            glLineWidth(double_cam_array[i][19]);
            glPointSize(double_cam_array[i][19]);
        }
    }

}
