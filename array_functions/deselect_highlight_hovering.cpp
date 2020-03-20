#include "deselect_highlight_hovering.h"
#include <core_functions/variables.h>

deselect_highlight_hovering::deselect_highlight_hovering()
{
    for(int i=0; i < cad_counter; i++){
            int_cad_array[i][4] = 0;
    }
}
