#include "show_centerpoint.h"
#include <core_functions/variables.h>

show_centerpoint::show_centerpoint(int i)
{
    int a = 6; //x axis
    int b = 7; //y axis
    int c = 8; //z axis

    //draw rectangular..
    glColor3f(0.0f, 0.0f, 1.0f);        //blue
    glBegin(GL_LINES);
    //bottom line
    glVertex3d(double_cad_array[i][a]-snap_dist, double_cad_array[i][b]-snap_dist, double_cad_array[i][c]);  //xyz start
    glVertex3d(double_cad_array[i][a]+snap_dist, double_cad_array[i][b]-snap_dist, double_cad_array[i][c]);  //xyz end
    //right side line
    glVertex3d(double_cad_array[i][a]+snap_dist, double_cad_array[i][b]-snap_dist, double_cad_array[i][c]);  //xyz start
    glVertex3d(double_cad_array[i][a]+snap_dist, double_cad_array[i][b]+snap_dist, double_cad_array[i][c]);  //xyz end
    //top line
    glVertex3d(double_cad_array[i][a]+snap_dist, double_cad_array[i][b]+snap_dist, double_cad_array[i][c]);  //xyz start
    glVertex3d(double_cad_array[i][a]-snap_dist, double_cad_array[i][b]+snap_dist, double_cad_array[i][c]);  //xyz end
    //left line
    glVertex3d(double_cad_array[i][a]-snap_dist, double_cad_array[i][b]+snap_dist, double_cad_array[i][c]);  //xyz start
    glVertex3d(double_cad_array[i][a]-snap_dist, double_cad_array[i][b]-snap_dist, double_cad_array[i][c]);  //xyz end
    glEnd();
}
