#include "delete_selected_cad_array_objects.h"
#include <core_functions/variables.h>

delete_selected_cad_array_objects::delete_selected_cad_array_objects()
{
        for(int i=0; i < cad_counter; i++){

            if(int_cad_array[i][3] == 1){ // this one maybe change..

                for(int j=0; j<30; j++){
                    int_cad_array[i][j] = 0;
                }
                for(int j=0; j<60; j++){
                    double_cad_array[i][j] = 0;
                }
            }

        }
}
