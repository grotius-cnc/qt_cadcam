#include "object_select_bezier_curve_nearest.h"
#include <core_functions/variables.h>

object_select_bezier_curve_nearest::object_select_bezier_curve_nearest(bool nearest_sign)
{
    for (int i = 0; i < cad_counter; i++) {

        if(mode_nearest && int_cad_array[i][0] == 5){ //id = cubic bezier curve..

            for(double t = 0; t < 1; t+=0.001){ //choose a different resolution for t ..
                //qDebug() << "t = " << t;

                int_cad_array[i][4] = 0; //no highlight hovering..

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

                //at this stage we have defined all the points and de lines of the cubic bezier curve..
                //Calculate Point E, on the line AB
                double Ex = ((1-t) * Ax) + (t * Bx);
                double Ey = ((1-t) * Ay) + (t * By);
                double Ez = ((1-t) * Az) + (t * Bz);

                //Calculate Point F, on the line BC
                double Fx = ((1-t) * Bx) + (t * Cx);
                double Fy = ((1-t) * By) + (t * Cy);
                double Fz = ((1-t) * Bz) + (t * Cz);

                //Calculate Point G, on the line CD
                double Gx = ((1-t) * Cx) + (t * Dx);
                double Gy = ((1-t) * Cy) + (t * Dy);
                double Gz = ((1-t) * Cz) + (t * Dz);

                //Calculate Point Q, on the line EF
                double Qx = ((1-t) * Ex) + (t * Fx);
                double Qy = ((1-t) * Ey) + (t * Fy);
                double Qz = ((1-t) * Ez) + (t * Fz);

                //Calculate Point R, on the line FG
                double Rx = ((1-t) * Fx) + (t * Gx);
                double Ry = ((1-t) * Fy) + (t * Gy);
                double Rz = ((1-t) * Fz) + (t * Gz);

                //Calculate Point P, on the line QR
                double Px = ((1-t) * Qx) + (t * Rx);
                double Py = ((1-t) * Qy) + (t * Ry);
                double Pz = ((1-t) * Qz) + (t * Rz);

                //glVertex3d(Px, Py, Pz);  //draw linestrip..

                if(mouse_cad_pos_x < Px + snap_dist && mouse_cad_pos_x > Px - snap_dist &&
                        mouse_cad_pos_y < Py + snap_dist && mouse_cad_pos_y > Py - snap_dist ){

                    int_cad_array[i][4] = 1; //highlight hovering..
                    select_id = i;

                    snap_cad_pos_x = Px;
                    snap_cad_pos_y = Py;
                    snap_cad_pos_z = Pz;

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
