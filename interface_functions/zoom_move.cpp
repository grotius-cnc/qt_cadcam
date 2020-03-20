#include "zoom_move.h"
#include <core_functions/variables.h>

zoom_move::zoom_move()
{
    distance_cad_mousepos_x = snapshot_cad_mousepos_x - mouse_cad_pos_x;
    distance_cad_mousepos_y = snapshot_cad_mousepos_y - mouse_cad_pos_y;
    distance_cad_mousepos_z = snapshot_cad_mousepos_z - mouse_cad_pos_z;

    qDebug () << "distance_cad_mousepos_x : " << distance_cad_mousepos_x;
    qDebug () << "distance_cad_mousepos_y : " << distance_cad_mousepos_y;

    zoom_left = zoom_left + distance_cad_mousepos_x;
    zoom_right = zoom_right + distance_cad_mousepos_x;
    zoom_top = zoom_top + distance_cad_mousepos_y;
    zoom_bottom = zoom_bottom + distance_cad_mousepos_y;

        qDebug() << "zoom_left" << zoom_left;
        qDebug() << "zoom_right" << zoom_right;
        qDebug() << "zoom_bottom" << zoom_bottom;
        qDebug() << "zoom_top" << zoom_top;
}
