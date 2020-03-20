#include "no_selection.h"
#include <core_functions/variables.h>

no_selection::no_selection()
{
    for(int i=0; i<cad_counter+100; i++){
        int_cad_array[i][3] = 0; //full object select
        int_cad_array[i][4] = 0; //no hightlight
        int_cad_array[i][6] = 0; //selected startpoint
        int_cad_array[i][7] = 0; //selected endpoint
        int_cad_array[i][8] = 0; //selected midpoint
    }
}

