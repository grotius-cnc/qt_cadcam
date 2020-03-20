#include "empty_triangle_array.h"
#include <core_functions/variables.h>

empty_triangle_array::empty_triangle_array()
{
    for(int i=0; i < triangle_counter; i++){

        for(int j=0; j<4; j++){
            double_triangle_array[i][j] = 0;
            }
    }

    triangle_counter = 0;
}
//double double_triangle_array[10000][4];
