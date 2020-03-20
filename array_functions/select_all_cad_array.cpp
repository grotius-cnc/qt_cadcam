#include "select_all_cad_array.h"
#include <core_functions/variables.h>

select_all_cad_array::select_all_cad_array()
{
    for(int i=0; i < cad_counter; i++){
            int_cad_array[i][3] = 1;
    }
}
