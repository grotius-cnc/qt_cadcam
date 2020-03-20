#include "snapshot.h"
#include <core_functions/variables.h>

snapshot::snapshot()
{
    snapshot_cad_mousepos_x = mouse_cad_pos_x;
    snapshot_cad_mousepos_y = mouse_cad_pos_y;
    snapshot_cad_mousepos_z = mouse_cad_pos_z;

    //qDebug() << "snapshot_cad_mousepos_x" << snapshot_cad_mousepos_x;
    //qDebug() << "snapshot_cad_mousepos_y" << snapshot_cad_mousepos_y;
    //qDebug() << "snapshot_cad_mousepos_z" << snapshot_cad_mousepos_z;
}
