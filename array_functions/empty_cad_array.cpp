#include "empty_cad_array.h"
#include <core_functions/variables.h>

empty_cad_array::empty_cad_array()
{
    for(int i=0; i < cad_counter; i++){

        for(int j=0; j<30; j++){
            int_cad_array[i][j] = 0;
            }
    }

    for(int i=0; i < cad_counter; i++){

        for(int j=0; j<60; j++){
            double_cad_array[i][j] = 0;
            }
    }

    cad_counter = 0;
}
