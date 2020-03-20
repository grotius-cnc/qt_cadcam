#include "empty_cam_array.h"
#include <core_functions/variables.h>

empty_cam_array::empty_cam_array()
{
    for(int i=0; i < 100000; i++){
        for(int j=0; j<30; j++){
            int_cam_array[i][j] = 0;
        }
    }
    for(int i=0; i < 100000; i++){

        for(int j=0; j<60; j++){
            double_cam_array[i][j] = 0;
        }
    }
    cam_counter = 0;
}
