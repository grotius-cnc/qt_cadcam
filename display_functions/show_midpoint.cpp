#include "show_midpoint.h"
#include <core_functions/variables.h>

show_midpoint::show_midpoint(int i, double dist_x, double dist_y, double dist_z)
{
    int a = 15; //x axis
    int b = 16; //y axis
    int c = 17; //z axis

    //draw rectangular..
    glColor3f(0.0f, 0.0f, 1.0f);        //blue
    glBegin(GL_LINES);
    //bottom line
    glVertex3d(double_cad_array[i][a]-snap_dist+dist_x, double_cad_array[i][b]-snap_dist+dist_y, double_cad_array[i][c]+dist_z);  //xyz start
    glVertex3d(double_cad_array[i][a]+snap_dist+dist_x, double_cad_array[i][b]-snap_dist+dist_y, double_cad_array[i][c]+dist_z);  //xyz end
    //right side line
    glVertex3d(double_cad_array[i][a]+snap_dist+dist_x, double_cad_array[i][b]-snap_dist+dist_y, double_cad_array[i][c]+dist_z);  //xyz start
    glVertex3d(double_cad_array[i][a]+snap_dist+dist_x, double_cad_array[i][b]+snap_dist+dist_y, double_cad_array[i][c]+dist_z);  //xyz end
    //top line
    glVertex3d(double_cad_array[i][a]+snap_dist+dist_x, double_cad_array[i][b]+snap_dist+dist_y, double_cad_array[i][c]+dist_z);  //xyz start
    glVertex3d(double_cad_array[i][a]-snap_dist+dist_x, double_cad_array[i][b]+snap_dist+dist_y, double_cad_array[i][c]+dist_z);  //xyz end
    //left line
    glVertex3d(double_cad_array[i][a]-snap_dist+dist_x, double_cad_array[i][b]+snap_dist+dist_y, double_cad_array[i][c]+dist_z);  //xyz start
    glVertex3d(double_cad_array[i][a]-snap_dist+dist_x, double_cad_array[i][b]-snap_dist+dist_y, double_cad_array[i][c]+dist_z);  //xyz end
    glEnd();
}
