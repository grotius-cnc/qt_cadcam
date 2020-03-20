#include "deselect_all_cad_array.h"
#include <core_functions/variables.h>

deselect_all_cad_array::deselect_all_cad_array()
{
    for(int i=0; i < cad_counter; i++){
            int_cad_array[i][3] = 0;
            int_cad_array[i][6] = 0;
            int_cad_array[i][7] = 0;
            int_cad_array[i][8] = 0;
    }
}
