#include "update_undo_array.h"
#include <core_functions/variables.h>

update_undo_array::update_undo_array()
{
    for(int i=0; i < cad_counter; i++){

            for(int j=0; j<30; j++){
                int_undo_array[i][j] = int_cad_array[i][j];
            }

            for(int j=0; j<60; j++){
                double_undo_array[i][j] = double_cad_array[i][j];
            }

    }
}
