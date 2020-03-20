#include "object_select_ellipse_nearest.h"
#include <core_functions/variables.h>
#include <math.h>

object_select_ellipse_nearest::object_select_ellipse_nearest(bool nearest_sign)
{

    for (int i = 0; i < cad_counter; i++) {

        if(int_cad_array[i][0] == 4){ //id = ellipse..

            double Fx_right = double_cad_array[i][40];
            double Fy_right = double_cad_array[i][41];
            double Fx_left  = double_cad_array[i][42];
            double Fy_left  = double_cad_array[i][43];
            double AB       = double_cad_array[i][44];

            double dist_mouse_right = sqrt(pow(snap_cad_pos_x-Fx_right,2)+pow(snap_cad_pos_y-Fy_right,2)); // this is a line between the ellipse focus and the mouse pointer.. AB = dist_left + dist_right..
            double dist_mouse_left  = sqrt(pow(snap_cad_pos_x-Fx_left,2)+pow(snap_cad_pos_y-Fy_left,2));

            if( (dist_mouse_right + dist_mouse_left > AB - snap_dist) && (dist_mouse_right + dist_mouse_left < AB + snap_dist) ){

                int_cad_array[i][4] = 1; //highlight..
                //qDebug() << "mouse pointer is at the ellipse line..";

                //calculate exact intersection..
                double dist_right = AB - dist_mouse_left;
                //qDebug() << "dist right : " << dist_right;

                //calculate last triangle point, given 2 focus points, and 3 side lenghts..
                //circle -> circle intersection is the most easy to use..

                double cx0 = double_cad_array[i][40];
                double cy0 = double_cad_array[i][41];
                double radius0 = dist_right; //exact calculation after highlight..
                double cx1 = double_cad_array[i][42];
                double cy1 = double_cad_array[i][43];
                double radius1 = dist_mouse_left;

                // Find the distance between the centers.
                double dx = cx0 - cx1;
                double dy = cy0 - cy1;
                double dist = sqrt(dx * dx + dy * dy);

                // See how many solutions there are.
                if (dist > radius0 + radius1)
                {
                    //qDebug() << "No solution";

                }
                else if (dist < abs(radius0 - radius1))
                {
                    //qDebug() << "No solutions, one circle contains the other";
                }
                else if ((dist == 0) && (radius0 == radius1))
                {
                    //qDebug() << "No solutions, the circles coincide";
                }
                else
                {
                    // Find a and h.
                    double a = (radius0 * radius0 -
                                radius1 * radius1 + dist * dist) / (2 * dist);
                    double h = sqrt(radius0 * radius0 - a * a);

                    // Find P2.
                    double cx2 = cx0 + a * (cx1 - cx0) / dist;
                    double cy2 = cy0 + a * (cy1 - cy0) / dist;

                    // Get the points P3.
                    double px1 = ((cx2 + h * (cy1 - cy0) / dist));
                    double py1 = ((cy2 - h * (cx1 - cx0) / dist));

                    double px2 = (cx2 - h * (cy1 - cy0) / dist);
                    double py2 = ((cy2 + h * (cx1 - cx0) / dist));

                    //calculate the closest by intersection..
                    //dist mouse to px1,py1 :

                    double dist_p1 = sqrt(pow(snap_cad_pos_x-px1,2)+pow(snap_cad_pos_y-py1,2));
                    double dist_p2 = sqrt(pow(snap_cad_pos_x-px2,2)+pow(snap_cad_pos_y-py2,2));

                    if(dist_p1<dist_p2){
                        snap_cad_pos_x = px1;
                        snap_cad_pos_y = py1;
                        snap_cad_pos_z = mouse_cad_pos_z;

                        int_cad_array[i][4] = 1; //object highlight..
                        select_id = i;

                        //draw first cross..
                        if(nearest_sign){
                            glColor3f(0.0f, 0.0f, 1.0f);        //blue
                            glBegin(GL_LINES);
                            //first cross line
                            glVertex3d(px1-snap_dist, py1-snap_dist, snap_cad_pos_z);  //xyz start
                            glVertex3d(px1+snap_dist, py1+snap_dist, snap_cad_pos_z);  //xyz start
                            //second cross line
                            glVertex3d(px1-snap_dist, py1+snap_dist, snap_cad_pos_z);  //xyz start
                            glVertex3d(px1+snap_dist, py1-snap_dist, snap_cad_pos_z);  //xyz start
                            //top line
                            glEnd();
                        }

                        break;

                    } else {
                        snap_cad_pos_x = px2;
                        snap_cad_pos_y = py2;
                        snap_cad_pos_z = mouse_cad_pos_z;

                        int_cad_array[i][4] = 1; //object highlight..
                        select_id = i;

                        //draw second cross..
                        if(nearest_sign){
                            glColor3f(0.0f, 0.0f, 1.0f);        //blue
                            glBegin(GL_LINES);
                            //first cross line
                            glVertex3d(px2-snap_dist, py2-snap_dist, snap_cad_pos_z);  //xyz start
                            glVertex3d(px2+snap_dist, py2+snap_dist, snap_cad_pos_z);  //xyz start
                            //second cross line
                            glVertex3d(px2-snap_dist, py2+snap_dist, snap_cad_pos_z);  //xyz start
                            glVertex3d(px2+snap_dist, py2-snap_dist, snap_cad_pos_z);  //xyz start
                            //top line
                            glEnd();
                        }

                        break;

                    }
                }
            } else {int_cad_array[i][4] = 0;}  //no highlight..
        }
    }
}





























