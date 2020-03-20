#include "purge_array.h"
#include <core_functions/variables.h>
#include <array_functions/copy_move_array.h>
#include <array_functions/copy_move_cam_array.h>
#include <array_functions/emtpy_current_cad_counter.h>

purge_array::purge_array()
{   
    for(int k=0; k<5; k++){
        for(int i=cad_counter; i>0; i--){
            if(int_cad_array[i][0]!=0){
                cad_counter = i+1;
                break;
            }

        }

        for(int i=0; i<cad_counter; i++){
            if(int_cad_array[i][0]==0){
                for(int pos=i; pos<cad_counter; pos++){
                    copy_move_array(pos+1,pos,0,0,0);
                }
            }
        }

        for(int i=cad_counter; i>0; i--){
            if(int_cad_array[i][0]!=0){
                cad_counter = i+1;
                break;
            }
            if(i==1 && int_cad_array[i][0]==0){
                cad_counter=1;
            }
        }

    }

    qDebug()<<"array purge is done !";
}
