#include "zoom_extends.h"
#include <core_functions/variables.h>

zoom_extends::zoom_extends()
{

    double x_min = 0;
    double x_max = 0;
    double y_min = 0;
    double y_max = 0;

    //find the extends within the cad array..
    for (int i=0; i < cad_counter; i++) {
        if(x_min > double_cad_array[i][0]){
            x_min = double_cad_array[i][0];
        }
        if(x_max < double_cad_array[i][0]){
            x_max = double_cad_array[i][0];
        }
        if(y_min > double_cad_array[i][1]){
            y_min = double_cad_array[i][1];
        }
        if(y_max < double_cad_array[i][1]){
            y_max = double_cad_array[i][1];
        }
    }

    zoom_cad_left = x_min;
    zoom_cad_right = x_max;
    zoom_cad_bottom = y_min;
    zoom_cad_top = y_max;

    //try to reset the ratio as it should be..
    double x_mid = (zoom_cad_right + zoom_cad_left)/2;
    double y_mid = (zoom_cad_top + zoom_cad_bottom)/2;
    double x_distx = zoom_cad_right - zoom_cad_left;

    zoom_cad_left = (x_mid - (0.6*x_distx) *aspect) ;
    zoom_cad_right = (x_mid + (0.6*x_distx) *aspect) ;
    zoom_cad_bottom = (y_mid - (0.6*x_distx)) * aspect;
    zoom_cad_top = (y_mid + (0.6*x_distx)) * aspect;

}


























