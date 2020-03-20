#include "show_endpoint.h"
#include <core_functions/variables.h>

show_endpoint::show_endpoint(int i, double dist_x, double dist_y, double dist_z)
{
    int a = 3; //x axis
    int b = 4; //y axis
    int c = 5; //z axis

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
