#include "object_select_line_perpendicular.h"
#include <core_functions/variables.h>

object_select_line_perpendicular::object_select_line_perpendicular()
{
    for(int i=0 ; i < cad_counter ; i++) { //include the currently drawed line..

        //mirror line
        double startpoint_mirrorline_x = double_cad_array[i][0];
        double startpoint_mirrorline_y = double_cad_array[i][1];
        double endpoint_mirrorline_x = double_cad_array[i][3];
        double endpoint_mirrorline_y = double_cad_array[i][4];

        //line to draw perpendicular to mirror line..
        double point_to_mirror_x = double_cad_array[cad_counter][0]; //currently drawed line startpoint..
        double point_to_mirror_y = double_cad_array[cad_counter][1];

        //mirror function..
        double dx  = endpoint_mirrorline_x - startpoint_mirrorline_x;
        double dy  = endpoint_mirrorline_y - startpoint_mirrorline_y;

        double a_   = (dx * dx - dy * dy) / (dx * dx + dy*dy);
        double b   = 2 * dx * dy / (dx*dx + dy*dy);

        double mirrored_point_x  = (a_ * (point_to_mirror_x - startpoint_mirrorline_x) + b*(point_to_mirror_y - startpoint_mirrorline_y) + startpoint_mirrorline_x);
        double mirrored_point_y  = (b * (point_to_mirror_x - startpoint_mirrorline_x) - a_*(point_to_mirror_y - startpoint_mirrorline_y) + startpoint_mirrorline_y);

        //perpendicular intersection point on virtual triangle line..
        double perpendicular_point_x = (double_cad_array[cad_counter][0] + mirrored_point_x) /2;
        double perpendicular_point_y = (double_cad_array[cad_counter][1] + mirrored_point_y) /2;

        //check for snap startpoint..
        if(mouse_cad_pos_x < perpendicular_point_x + snap_dist && mouse_cad_pos_x > perpendicular_point_x - snap_dist &&
                mouse_cad_pos_y < perpendicular_point_y + snap_dist && mouse_cad_pos_y > perpendicular_point_y - snap_dist ){

            //draw snap rectangular..
            glColor3f(0.0f, 0.0f, 1.0f);        //blue
            glBegin(GL_LINES);
            //bottom line
            glVertex3d(perpendicular_point_x-snap_dist, perpendicular_point_y-snap_dist, mouse_cad_pos_z);  //xyz start
            glVertex3d(perpendicular_point_x+snap_dist, perpendicular_point_y-snap_dist, mouse_cad_pos_z);  //xyz end
            //left line
            glVertex3d(perpendicular_point_x-snap_dist, perpendicular_point_y-snap_dist, mouse_cad_pos_z);  //xyz start
            glVertex3d(perpendicular_point_x-snap_dist, perpendicular_point_y+snap_dist, mouse_cad_pos_z);  //xyz end

            glEnd();

            snap_cad_pos_x = perpendicular_point_x;
            snap_cad_pos_y = perpendicular_point_y;
            snap_cad_pos_z = mouse_cad_pos_z;

            break;
        }
    }
}

