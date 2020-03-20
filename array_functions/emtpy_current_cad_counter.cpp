#include "emtpy_current_cad_counter.h"
#include <core_functions/variables.h>

emtpy_current_cad_counter::emtpy_current_cad_counter(int cad_counter)
{
        for(int j=0; j<30; j++){
            int_cad_array[cad_counter][j] = 0;
            }
        for(int j=0; j<60; j++){
            double_cad_array[cad_counter][j] = 0;
            }
}
