#include "no_highlight.h"
#include <core_functions/variables.h>

no_highlight::no_highlight()
{
    for(int i=0; i<cad_counter; i++){
          int_cad_array[i][3] = 0; //full object select
          int_cad_array[i][4] = 0; //no highlight
          int_cad_array[i][6] = 0; //selected startpoint
          int_cad_array[i][7] = 0; //selected endpoint
          int_cad_array[i][8] = 0; //selected midpoint
    }

}
