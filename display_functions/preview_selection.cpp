#include "preview_selection.h"
#include <core_functions/variables.h>

preview_selection::preview_selection(int i)
{
    // left mouse press event in opengl class makes the selection

    //for(int i=0 ; i < cad_counter ; i++) {

        if(int_cad_array[i][3] == 1){

            //preview startpoints..
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

            //preview midpoints..
            glColor3f(0.0f, 0.0f, 1.0f);        //blue
            glBegin(GL_LINES);
            //bottom line
            glVertex3d(double_cad_array[i][6]-snap_dist, double_cad_array[i][7]-snap_dist, double_cad_array[i][8]);  //xyz start
            glVertex3d(double_cad_array[i][6]+snap_dist, double_cad_array[i][7]-snap_dist, double_cad_array[i][8]);  //xyz end
            //right side line
            glVertex3d(double_cad_array[i][6]+snap_dist, double_cad_array[i][7]-snap_dist, double_cad_array[i][8]);  //xyz start
            glVertex3d(double_cad_array[i][6]+snap_dist, double_cad_array[i][7]+snap_dist, double_cad_array[i][8]);  //xyz end
            //top line
            glVertex3d(double_cad_array[i][6]+snap_dist, double_cad_array[i][7]+snap_dist, double_cad_array[i][8]);  //xyz start
            glVertex3d(double_cad_array[i][6]-snap_dist, double_cad_array[i][7]+snap_dist, double_cad_array[i][8]);  //xyz end
            //left line
            glVertex3d(double_cad_array[i][6]-snap_dist, double_cad_array[i][7]+snap_dist, double_cad_array[i][8]);  //xyz start
            glVertex3d(double_cad_array[i][6]-snap_dist, double_cad_array[i][7]-snap_dist, double_cad_array[i][8]);  //xyz end
            glEnd();

            //preview endpoints..
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


        }
    //}
}
