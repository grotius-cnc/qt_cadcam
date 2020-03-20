#include "object_select_circle_4p_intersection.h"
#include <core_functions/variables.h>

object_select_circle_4p_intersection::object_select_circle_4p_intersection()
{
    for(int i=0 ; i < cad_counter ; i++) {

        //check for snap startpoint..
        if(mode_snap_circle_4p && mouse_cad_pos_x < double_cad_array[i][25] + snap_dist && mouse_cad_pos_x > double_cad_array[i][25] - snap_dist &&
                mouse_cad_pos_y < double_cad_array[i][26] + snap_dist && mouse_cad_pos_y > double_cad_array[i][26] - snap_dist ){

            //draw snap rectangular..
            glColor3f(0.0f, 0.0f, 1.0f);        //blue
            glBegin(GL_LINES);
            //bottom line
            glVertex3d(double_cad_array[i][25]-snap_dist, double_cad_array[i][26]-snap_dist, double_cad_array[i][27]);  //xyz start
            glVertex3d(double_cad_array[i][25]+snap_dist, double_cad_array[i][26]-snap_dist, double_cad_array[i][27]);  //xyz end
            //right side line
            glVertex3d(double_cad_array[i][25]+snap_dist, double_cad_array[i][26]-snap_dist, double_cad_array[i][27]);  //xyz start
            glVertex3d(double_cad_array[i][25]+snap_dist, double_cad_array[i][26]+snap_dist, double_cad_array[i][27]);  //xyz end
            //top line
            glVertex3d(double_cad_array[i][25]+snap_dist, double_cad_array[i][26]+snap_dist, double_cad_array[i][27]);  //xyz start
            glVertex3d(double_cad_array[i][25]-snap_dist, double_cad_array[i][26]+snap_dist, double_cad_array[i][27]);  //xyz end
            //left line
            glVertex3d(double_cad_array[i][25]-snap_dist, double_cad_array[i][26]+snap_dist, double_cad_array[i][27]);  //xyz start
            glVertex3d(double_cad_array[i][25]-snap_dist, double_cad_array[i][26]-snap_dist, double_cad_array[i][27]);  //xyz end
            glEnd();

            snap_cad_pos_x = double_cad_array[i][25];
            snap_cad_pos_y = double_cad_array[i][26];
            snap_cad_pos_z = double_cad_array[i][27];
            break;

        }

        if(mode_snap_circle_4p && mouse_cad_pos_x < double_cad_array[i][28] + snap_dist && mouse_cad_pos_x > double_cad_array[i][28] - snap_dist &&
                  mouse_cad_pos_y < double_cad_array[i][29] + snap_dist && mouse_cad_pos_y > double_cad_array[i][29] - snap_dist ){

            //draw snap rectangular..
            glColor3f(0.0f, 0.0f, 1.0f);        //blue
            glBegin(GL_LINES);
            //bottom line
            glVertex3d(double_cad_array[i][28]-snap_dist, double_cad_array[i][29]-snap_dist, double_cad_array[i][30]);  //xyz start
            glVertex3d(double_cad_array[i][28]+snap_dist, double_cad_array[i][29]-snap_dist, double_cad_array[i][30]);  //xyz end
            //right side line
            glVertex3d(double_cad_array[i][28]+snap_dist, double_cad_array[i][29]-snap_dist, double_cad_array[i][30]);  //xyz start
            glVertex3d(double_cad_array[i][28]+snap_dist, double_cad_array[i][29]+snap_dist, double_cad_array[i][30]);  //xyz end
            //top line
            glVertex3d(double_cad_array[i][28]+snap_dist, double_cad_array[i][29]+snap_dist, double_cad_array[i][30]);  //xyz start
            glVertex3d(double_cad_array[i][28]-snap_dist, double_cad_array[i][29]+snap_dist, double_cad_array[i][30]);  //xyz end
            //left line
            glVertex3d(double_cad_array[i][28]-snap_dist, double_cad_array[i][29]+snap_dist, double_cad_array[i][30]);  //xyz start
            glVertex3d(double_cad_array[i][28]-snap_dist, double_cad_array[i][29]-snap_dist, double_cad_array[i][30]);  //xyz end
            glEnd();

            snap_cad_pos_x = double_cad_array[i][28];
            snap_cad_pos_y = double_cad_array[i][29];
            snap_cad_pos_z = double_cad_array[i][30];
            break;

        }

        if(mode_snap_circle_4p  && mouse_cad_pos_x < double_cad_array[i][31] + snap_dist && mouse_cad_pos_x > double_cad_array[i][31] - snap_dist &&
                  mouse_cad_pos_y < double_cad_array[i][32] + snap_dist && mouse_cad_pos_y > double_cad_array[i][32] - snap_dist ){

            //draw snap rectangular..
            glColor3f(0.0f, 0.0f, 1.0f);        //blue
            glBegin(GL_LINES);
            //bottom line
            glVertex3d(double_cad_array[i][31]-snap_dist, double_cad_array[i][32]-snap_dist, double_cad_array[i][33]);  //xyz start
            glVertex3d(double_cad_array[i][31]+snap_dist, double_cad_array[i][32]-snap_dist, double_cad_array[i][33]);  //xyz end
            //right side line
            glVertex3d(double_cad_array[i][31]+snap_dist, double_cad_array[i][32]-snap_dist, double_cad_array[i][33]);  //xyz start
            glVertex3d(double_cad_array[i][31]+snap_dist, double_cad_array[i][32]+snap_dist, double_cad_array[i][33]);  //xyz end
            //top line
            glVertex3d(double_cad_array[i][31]+snap_dist, double_cad_array[i][32]+snap_dist, double_cad_array[i][33]);  //xyz start
            glVertex3d(double_cad_array[i][31]-snap_dist, double_cad_array[i][32]+snap_dist, double_cad_array[i][33]);  //xyz end
            //left line
            glVertex3d(double_cad_array[i][31]-snap_dist, double_cad_array[i][32]+snap_dist, double_cad_array[i][33]);  //xyz start
            glVertex3d(double_cad_array[i][31]-snap_dist, double_cad_array[i][32]-snap_dist, double_cad_array[i][33]);  //xyz end
            glEnd();

            snap_cad_pos_x = double_cad_array[i][31];
            snap_cad_pos_y = double_cad_array[i][32];
            snap_cad_pos_z = double_cad_array[i][33];
            break;

        }

        if(mode_snap_circle_4p  && mouse_cad_pos_x < double_cad_array[i][34] + snap_dist && mouse_cad_pos_x > double_cad_array[i][34] - snap_dist &&
                  mouse_cad_pos_y < double_cad_array[i][35] + snap_dist && mouse_cad_pos_y > double_cad_array[i][35] - snap_dist ){

            //draw snap rectangular..
            glColor3f(0.0f, 0.0f, 1.0f);        //blue
            glBegin(GL_LINES);
            //bottom line
            glVertex3d(double_cad_array[i][34]-snap_dist, double_cad_array[i][35]-snap_dist, double_cad_array[i][36]);  //xyz start
            glVertex3d(double_cad_array[i][34]+snap_dist, double_cad_array[i][35]-snap_dist, double_cad_array[i][36]);  //xyz end
            //right side line
            glVertex3d(double_cad_array[i][34]+snap_dist, double_cad_array[i][35]-snap_dist, double_cad_array[i][36]);  //xyz start
            glVertex3d(double_cad_array[i][34]+snap_dist, double_cad_array[i][35]+snap_dist, double_cad_array[i][36]);  //xyz end
            //top line
            glVertex3d(double_cad_array[i][34]+snap_dist, double_cad_array[i][35]+snap_dist, double_cad_array[i][36]);  //xyz start
            glVertex3d(double_cad_array[i][34]-snap_dist, double_cad_array[i][35]+snap_dist, double_cad_array[i][36]);  //xyz end
            //left line
            glVertex3d(double_cad_array[i][34]-snap_dist, double_cad_array[i][35]+snap_dist, double_cad_array[i][36]);  //xyz start
            glVertex3d(double_cad_array[i][34]-snap_dist, double_cad_array[i][35]-snap_dist, double_cad_array[i][36]);  //xyz end
            glEnd();

            snap_cad_pos_x = double_cad_array[i][34];
            snap_cad_pos_y = double_cad_array[i][35];
            snap_cad_pos_z = double_cad_array[i][36];
            break;

        }
    }
}

