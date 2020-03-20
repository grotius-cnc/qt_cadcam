#include "swap_cam_array.h"
#include <core_functions/variables.h>

swap_cam_array::swap_cam_array(int item_a, int item_b)
{
    //only swapping array positions, no coordinate swapping over here to inverse path's !

    int int_temp_array[1][30];
    double double_temp_array[1][60];

    //save item_a array in temp array
    for(int i=0; i<30; i++){
        int_temp_array[0][i] = int_cam_array[item_a][i];
    }
    for(int i=0; i<60; i++){
        double_temp_array[0][i] = double_cam_array[item_a][i];
    }

    //save item_b array in item_a array
    for(int i=0; i<30; i++){
        int_cam_array[item_a][i] = int_cam_array[item_b][i];
    }
    for(int i=0; i<60; i++){
        double_cam_array[item_a][i] = double_cam_array[item_b][i];
    }

    //save temp array in item_b array
    for(int i=0; i<30; i++){
        int_cam_array[item_b][i] = int_temp_array[0][i];
    }
    for(int i=0; i<60; i++){
        double_cam_array[item_b][i] = double_temp_array[0][i];
    }
}
