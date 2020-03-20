#include "zoom_rotate.h"
#include <core_functions/variables.h>

zoom_rotate::zoom_rotate()
{
    if(mouse_cad_pos_x > snapshot_cad_mousepos_x +20){ //trim value
        gl_rotate_z -=1;
    }
    if(mouse_cad_pos_x < snapshot_cad_mousepos_x -20){
        gl_rotate_z +=1;
    }
    if(mouse_cad_pos_y > snapshot_cad_mousepos_y +20){
        gl_rotate_x +=1;
    }
    if(mouse_cad_pos_y < snapshot_cad_mousepos_y -20){
        gl_rotate_x -=1;
    }
}
