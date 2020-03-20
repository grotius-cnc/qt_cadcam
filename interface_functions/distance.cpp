#include "distance.h"
#include <core_functions/variables.h>

distance::distance()
{
    distance_cad_mousepos_x = mouse_cad_pos_x - snapshot_cad_mousepos_x;
    distance_cad_mousepos_y = mouse_cad_pos_y - snapshot_cad_mousepos_y;
    distance_cad_mousepos_z = mouse_cad_pos_z - snapshot_cad_mousepos_z;
}
