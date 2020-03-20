#include "object_select_line_endpoint.h"
#include <core_functions/variables.h>

object_select_line_endpoint::object_select_line_endpoint()
{
    int number = 0;
    if(mode_cubic_hermite_spline){number = cad_counter - 1;} else {number = cad_counter;}

    for(int i=0 ; i < number ; i++) {

        //check for snap endpoint..
        if(mouse_cad_pos_x < double_cad_array[i][3] + snap_dist && mouse_cad_pos_x > double_cad_array[i][3] - snap_dist &&
                mouse_cad_pos_y < double_cad_array[i][4] + snap_dist && mouse_cad_pos_y > double_cad_array[i][4] - snap_dist ){

            //draw snap rectangular..
            glColor3f(0.0f, 0.0f, 1.0f);        //blue
            glBegin(GL_LINES);
            //bottom line
            glVertex3d(double_cad_array[i][3]-snap_dist, double_cad_array[i][4]-snap_dist, double_cad_array[i][5]);  //xyz start
            glVertex3d(double_cad_array[i][3]+snap_dist, double_cad_array[i][4]-snap_dist, double_cad_array[i][5]);  //xyz end
            //right side line
            glVertex3d(double_cad_array[i][3]+snap_dist, double_cad_array[i][4]-snap_dist, double_cad_array[i][5]);  //xyz start
            glVertex3d(double_cad_array[i][3]+snap_dist, double_cad_array[i][4]+snap_dist, double_cad_array[i][5]);  //xyz end
            //top line
            glVertex3d(double_cad_array[i][3]+snap_dist, double_cad_array[i][4]+snap_dist, double_cad_array[i][5]);  //xyz start
            glVertex3d(double_cad_array[i][3]-snap_dist, double_cad_array[i][4]+snap_dist, double_cad_array[i][5]);  //xyz end
            //left line
            glVertex3d(double_cad_array[i][3]-snap_dist, double_cad_array[i][4]+snap_dist, double_cad_array[i][5]);  //xyz start
            glVertex3d(double_cad_array[i][3]-snap_dist, double_cad_array[i][4]-snap_dist, double_cad_array[i][5]);  //xyz end
            glEnd();

            snap_cad_pos_x = double_cad_array[i][3];
            snap_cad_pos_y = double_cad_array[i][4];
            snap_cad_pos_z = double_cad_array[i][5];

            break;
        }
    }
}
