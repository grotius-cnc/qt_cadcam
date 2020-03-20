#include "object_select_line_startpoint.h"
#include <core_functions/variables.h>

object_select_line_startpoint::object_select_line_startpoint()
{

    //grid snap..
    if(mode_grid){
        int s=0;
        for(double x = 0; x<=gridsize; x+=gridspace){
            s++;
            if(s>100000){s=0;}
            for(double y = 0; y<=gridsize; y+=gridspace){
                s++;
                if(s>100000){s=0;}
                //check for snap endpoint..
                if(snap_cad_pos_x < x + snap_dist && snap_cad_pos_x > x - snap_dist &&
                        snap_cad_pos_y < y + snap_dist && snap_cad_pos_y > y - snap_dist ){

                    //draw snap rectangular..
                    glColor3f(0.0f, 0.0f, 1.0f);        //blue
                    glBegin(GL_LINES);
                    //bottom line
                    glVertex3d(x-snap_dist, y-snap_dist, 0);
                    glVertex3d(x+snap_dist, y-snap_dist, 0);
                    //right side line
                    glVertex3d(x+snap_dist, y-snap_dist, 0);
                    glVertex3d(x+snap_dist, y+snap_dist, 0);
                    //top line
                    glVertex3d(x+snap_dist, y+snap_dist, 0);
                    glVertex3d(x-snap_dist, y+snap_dist, 0);
                    //left line
                    glVertex3d(x-snap_dist, y+snap_dist, 0);
                    glVertex3d(x-snap_dist, y-snap_dist, 0);
                    glEnd();

                    snap_cad_pos_x = x;
                    snap_cad_pos_y = y;

                    break;
                }
            }
        }
    }



    //qDebug()<< "snap x" << snap_cad_pos_x;
    //qDebug()<< "snap y" << snap_cad_pos_y;

    int number = 0;
    if(mode_cubic_hermite_spline){number = cad_counter - 1;} else {number = cad_counter;}

    for(int i=0 ; i < number; i++) {

        //check for snap startpoint..
        if(mouse_cad_pos_x < double_cad_array[i][0] + snap_dist && mouse_cad_pos_x > double_cad_array[i][0] - snap_dist &&
                mouse_cad_pos_y < double_cad_array[i][1] + snap_dist && mouse_cad_pos_y > double_cad_array[i][1] - snap_dist ){

            //draw snap rectangular..
            glColor3f(0.0f, 0.0f, 1.0f);        //blue
            glBegin(GL_LINES);
            //bottom line
            glVertex3d(double_cad_array[i][0]-snap_dist, double_cad_array[i][1]-snap_dist, double_cad_array[i][2]);  //xyz start
            glVertex3d(double_cad_array[i][0]+snap_dist, double_cad_array[i][1]-snap_dist, double_cad_array[i][2]);  //xyz end
            //right side line
            glVertex3d(double_cad_array[i][0]+snap_dist, double_cad_array[i][1]-snap_dist, double_cad_array[i][2]);  //xyz start
            glVertex3d(double_cad_array[i][0]+snap_dist, double_cad_array[i][1]+snap_dist, double_cad_array[i][2]);  //xyz end
            //top line
            glVertex3d(double_cad_array[i][0]+snap_dist, double_cad_array[i][1]+snap_dist, double_cad_array[i][2]);  //xyz start
            glVertex3d(double_cad_array[i][0]-snap_dist, double_cad_array[i][1]+snap_dist, double_cad_array[i][2]);  //xyz end
            //left line
            glVertex3d(double_cad_array[i][0]-snap_dist, double_cad_array[i][1]+snap_dist, double_cad_array[i][2]);  //xyz start
            glVertex3d(double_cad_array[i][0]-snap_dist, double_cad_array[i][1]-snap_dist, double_cad_array[i][2]);  //xyz end
            glEnd();

            snap_cad_pos_x = double_cad_array[i][0];
            snap_cad_pos_y = double_cad_array[i][1];
            snap_cad_pos_z = double_cad_array[i][2];

            break;
        }
    }
}
