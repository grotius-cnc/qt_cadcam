#include "show_startpoint.h"
#include <core_functions/variables.h>

show_startpoint::show_startpoint(int i, double dist_x, double dist_y, double dist_z)
{
    int a = 0; //x axis
    int b = 1; //y axis
    int c = 2; //z axis

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
