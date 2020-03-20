#include "object_select_circle_nearest.h"
#include <core_functions/variables.h>
#include <math.h>

object_select_circle_nearest::object_select_circle_nearest(bool nearest_sign)
{
    for (int i = 0; i < cad_counter; i++) {

        if(int_cad_array[i][0] == 2){ //id = circle..

            //circle - circle intersection...
            double cx0 = mouse_cad_pos_x;
            double cy0 = mouse_cad_pos_y;
            double radius0 = snap_dist; //search dist for mouse pointer..

            double cx1 = double_cad_array[i][6];
            double cy1 = double_cad_array[i][7];
            double radius1 = double_cad_array[i][9];

            // Find the distance between the centers.
            double dx = cx0 - cx1;
            double dy = cy0 - cy1;
            double dist = sqrt(dx * dx + dy * dy);

            // See how many solutions there are.
            if (dist > radius0 + radius1)
            {
                //qDebug() << "No solution";
                int_cad_array[i][4] = 0;
            }
            else if (dist < abs(radius0 - radius1))
            {
                //qDebug() << "No solutions, one circle contains the other";
                int_cad_array[i][4] = 0;
            }
            else if ((dist == 0) && (radius0 == radius1))
            {
                //qDebug() << "No solutions, the circles coincide";
                int_cad_array[i][4] = 0;
            }
            else
            {
                //at this stage we end up with 2 intersections.. but we don't need the intersection points.. we now know wich circle is the target for a line-circle intersect calculation..
                // Find a and h.

                //line - circle intersection..
                double circle_center_x = double_cad_array[i][6];    //array target circle center x
                double circle_center_y = double_cad_array[i][7];    //array target circle center y
                double radius = double_cad_array[i][9];             //array target circle radius

                double start_line_x1 = double_cad_array[i][6];      //line from target circle center x
                double start_line_y1 = double_cad_array[i][7];      //line from target circle center y
                double end_line_x2 = mouse_cad_pos_x;               //line from actual mouse coordinate x..
                double end_line_y2 = mouse_cad_pos_y;               //line from actual mouse coordinate y..
                double dx, dy, A, B, C, det, t;
                //double AB, AP, PB;

                dx = end_line_x2 - start_line_x1;
                dy = end_line_y2 - start_line_y1;

                A = dx * dx + dy * dy;
                B = 2 * (dx * (start_line_x1 - circle_center_x) + dy * (start_line_y1 - circle_center_y));
                C = (start_line_x1 - circle_center_x) * (start_line_x1 - circle_center_x) + (start_line_y1 - circle_center_y) * (start_line_y1 - circle_center_y) - radius * radius;

                det = B * B - 4 * A * C;

                t = (-B + sqrt(det)) / (2 * A);
                double intersection_x1 = (start_line_x1 + t * dx);
                double intersection_y1 = (start_line_y1 + t * dy);

                t = (-B - sqrt(det)) / (2 * A);
                double intersection_x2 = (start_line_x1 + t * dx);
                double intersection_y2 = (start_line_y1 + t * dy);

                //look for closest solution..
                double c1 = sqrt(pow(mouse_cad_pos_x-intersection_x1,2) + pow(mouse_cad_pos_y-intersection_y1,2));
                double c2 = sqrt(pow(mouse_cad_pos_x-intersection_x2,2) + pow(mouse_cad_pos_y-intersection_y2,2));
                if(c1<c2){

                    //qDebug() << "nearest x :" << intersection_x1 << "y :" << intersection_y1;
                    int_cad_array[i][4] = 1; //object highlight..
                    select_id = i;
                    qDebug()<< "circle id.." << select_id;

                    intersection_type = "circle";
                    g2 = intersection_x1;
                    intersection_text_y = intersection_y1;

                    snap_cad_pos_x = intersection_x1;
                    snap_cad_pos_y = intersection_y1;
                    snap_cad_pos_z = mouse_cad_pos_z;

                    //draw cross..
                    if(nearest_sign){
                        glColor3f(0.0f, 0.0f, 1.0f);        //blue
                        glBegin(GL_LINES);
                        //first cross line
                        glVertex3d(intersection_x1-snap_dist, intersection_y1-snap_dist, snap_cad_pos_z);  //xyz start
                        glVertex3d(intersection_x1+snap_dist, intersection_y1+snap_dist, snap_cad_pos_z);  //xyz start
                        //second cross line
                        glVertex3d(intersection_x1-snap_dist, intersection_y1+snap_dist, snap_cad_pos_z);  //xyz start
                        glVertex3d(intersection_x1+snap_dist, intersection_y1-snap_dist, snap_cad_pos_z);  //xyz start
                        //top line
                        glEnd();
                    }

                    break;

                } else {

                    //qDebug() << "nearest x :" << intersection_x2 << "y :" << intersection_y2;
                    int_cad_array[i][4] = 1; //object highlight..
                    select_id = i;
                    qDebug()<< "circle id.." << select_id;

                    intersection_type = "circle";
                    g2 = intersection_x2;
                    intersection_text_y = intersection_y2;

                    snap_cad_pos_x = intersection_x2;
                    snap_cad_pos_y = intersection_y2;
                    snap_cad_pos_z = mouse_cad_pos_z;

                    //draw cross..
                    if(nearest_sign){
                        glColor3f(0.0f, 0.0f, 1.0f);        //blue
                        glBegin(GL_LINES);
                        //first cross line
                        glVertex3d(intersection_x2-snap_dist, intersection_y2-snap_dist, snap_cad_pos_z);  //xyz start
                        glVertex3d(intersection_x2+snap_dist, intersection_y2+snap_dist, snap_cad_pos_z);  //xyz start
                        //second cross line
                        glVertex3d(intersection_x2-snap_dist, intersection_y2+snap_dist, snap_cad_pos_z);  //xyz start
                        glVertex3d(intersection_x2+snap_dist, intersection_y2-snap_dist, snap_cad_pos_z);  //xyz start
                        //top line
                        glEnd();
                    }

                    break;
                }
            }
        }
    }
}





































