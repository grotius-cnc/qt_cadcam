#include "object_select_hermite_spline_nearest.h"
#include <core_functions/variables.h>
#include <math.h>

object_select_hermite_spline_nearest::object_select_hermite_spline_nearest(bool nearest_sign)
{
    for (int i = 0; i < cad_counter; i++) {

        if(int_cad_array[i][0] == 6){ //id = cubic hermite spline..

            for(double t = 0; t <= 1; t+=0.001){ //choose a different resolution for t ..
                //qDebug() << "t = " << t;

                int_cad_array[i][4] = 0; //no highlight..

                //start point A..
                Ax = double_cad_array[i][0];
                Ay = double_cad_array[i][1];
                Az = double_cad_array[i][2];

                //control point B..
                Bx = double_cad_array[i][50];
                By = double_cad_array[i][51];
                Bz = double_cad_array[i][52];

                //control point C..
                Cx = double_cad_array[i][53];
                Cy = double_cad_array[i][54];
                Cz = double_cad_array[i][55];

                //end point D..
                Dx = double_cad_array[i][3];
                Dy = double_cad_array[i][4];
                Dz = double_cad_array[i][5];

                double ax = -Ax/2 + (3*Bx)/2 - (3*Cx)/2 + Dx/2;
                double bx = Ax - (5*Bx)/2 + 2*Cx - Dx / 2;
                double cx = -Ax/2 + Cx/2;
                double dx = Bx;
                double Px = ax*t*t*t + bx*t*t + cx*t + dx;

                double ay = -Ay/2 + (3*By)/2 - (3*Cy)/2 + Dy/2;
                double by = Ay - (5*By)/2 + 2*Cy - Dy / 2;
                double cy = -Ay/2 + Cy/2;
                double dy = By;
                double Py = ay*t*t*t + by*t*t + cy*t + dy;

                double az = -Az/2 + (3*Bz)/2 - (3*Cz)/2 + Dz/2;
                double bz = Az - (5*Bz)/2 + 2*Cz - Dz / 2;
                double cz = -Az/2 + Cz/2;
                double dz = Bz;
                double Pz = az*t*t*t + bz*t*t + cz*t + dz;

                //glVertex3d(Px, Py, Pz);  //draw linestrip..

                if(mouse_cad_pos_x < Px + snap_dist && mouse_cad_pos_x > Px - snap_dist &&
                        mouse_cad_pos_y < Py + snap_dist && mouse_cad_pos_y > Py - snap_dist ){

                    //glVertex3d(Px, Py, Pz);  //draw linestrip..
                    snap_cad_pos_x = Px;
                    snap_cad_pos_y = Py;
                    snap_cad_pos_z = Pz;

                    int_cad_array[i][4] = 1; //highlight hovering..
                    select_id = i;

                    //draw intersection cross..

                    //draw cross..
                    if(nearest_sign){
                        glColor3f(0.0f, 0.0f, 1.0f);        //blue
                        glBegin(GL_LINES);
                        //first cross line
                        glVertex3d(Px-snap_dist, Py-snap_dist, snap_cad_pos_z);  //xyz start
                        glVertex3d(Px+snap_dist, Py+snap_dist, snap_cad_pos_z);  //xyz start
                        //second cross line
                        glVertex3d(Px-snap_dist, Py+snap_dist, snap_cad_pos_z);  //xyz start
                        glVertex3d(Px+snap_dist, Py-snap_dist, snap_cad_pos_z);  //xyz start
                        //top line
                        glEnd();
                    }

                    break;
                }
            }
        }
    }
}












