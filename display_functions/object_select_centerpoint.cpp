#include "object_select_centerpoint.h"
#include <core_functions/variables.h>

object_select_centerpoint::object_select_centerpoint()
{
    for(int i=0 ; i < cad_counter ; i++) {

        if(int_cad_array[i][0] == 2 || int_cad_array[i][0] == 3 || int_cad_array[i][0] == 4 ){ //id = circle or id = arc or id == ellipse..
            //check for snap midpoint..
            if(mouse_cad_pos_x < double_cad_array[i][6] + snap_dist && mouse_cad_pos_x > double_cad_array[i][6] - snap_dist &&
                    mouse_cad_pos_y < double_cad_array[i][7] + snap_dist && mouse_cad_pos_y > double_cad_array[i][7] - snap_dist ){

                snap_cad_pos_x = double_cad_array[i][6];
                snap_cad_pos_y = double_cad_array[i][7];
                snap_cad_pos_z = double_cad_array[i][8];

                //draw snap circle..
                glColor3f(0.0f, 0.0f, 1.0f);        //blue

                int num_segments = 10;
                glBegin(GL_LINE_LOOP);
                for (int ii = 0; ii < num_segments; ii++)   {
                    double theta = 2.0 * M_PI * int(ii) / int(num_segments);                                                                            //get the current angle
                    double x = snap_dist/*radius*/ * cosf(theta);                                                                                       //calculate the x component
                    double y = snap_dist/*radius*/ * sinf(theta);                                                                                       //calculate the y component
                    glVertex3d(x + double_cad_array[i][6]/*x center*/, y + double_cad_array[i][7]/*y center*/, double_cad_array[i][8]/*z center*/);     //output vertex
                }
                glEnd();

                break;
            }
        }
    }
}
