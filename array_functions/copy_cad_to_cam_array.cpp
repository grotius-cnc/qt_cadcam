#include "copy_cad_to_cam_array.h"
#include <core_functions/variables.h>

copy_cad_to_cam_array::copy_cad_to_cam_array(int in, int out)
{
    for(int j=0; j<30; j++){
        int_cam_array[out][j] = int_cad_array[in][j];
    }

    for(int j=0; j<60; j++){
        double_cam_array[out][j] = double_cad_array[in][j];
    }
}
