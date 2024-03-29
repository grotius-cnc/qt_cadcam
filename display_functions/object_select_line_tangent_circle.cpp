#include "object_select_line_tangent_circle.h"
#include <core_functions/variables.h>
#include <math.h>

object_select_line_tangent_circle::object_select_line_tangent_circle()
{
    for (int i = 0; i < cad_counter; i++) {

        if(mode_tangent && int_cad_array[i][0] == 2){ //id = circle..

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

                //qDebug() << "intersection found for i :" << i ;
                //http://csharphelper.com/blog/2014/11/find-the-tangent-lines-between-a-point-and-a-circle-in-c/

                double D = sqrt( pow(double_cad_array[i][6] - double_cad_array[cad_counter][0],2) + pow(double_cad_array[i][7] - double_cad_array[cad_counter][1],2) );
                //qDebug() << "D = center to center distance :" << D ; //checked..

                double R = double_cad_array[i][9]; //target radius..

                double L = sqrt( pow(D,2)-pow(R,2));
                //qDebug() << "L = tangent line lenght :" << L ;

                //circle - circle intersection..
                //line
                double cx0 = double_cad_array[cad_counter][0];
                double cy0 = double_cad_array[cad_counter][1];
                double radius0 = L;

                //target circle
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
                    double intersection_x1((cx2 + h * (cy1 - cy0) / dist));
                    double intersection_y1((cy2 - h * (cx1 - cx0) / dist));

                    double intersection_x2 = (cx2 - h * (cy1 - cy0) / dist);
                    double intersection_y2 = ((cy2 + h * (cx1 - cx0) / dist));

                    //qDebug() << "intersection x1 : " << intersection_x1 << " y1 : " << intersection_y1;
                    //qDebug() << "intersection x2 : " << intersection_x2 << " y2 : " << intersection_y2;

                    //draw cross..
                    glColor3f(0.0f, 0.0f, 1.0f);        //blue
                    glBegin(GL_LINES);
                    //first cross line
                    glVertex3d(intersection_x1-snap_dist, intersection_y1-snap_dist, 0);  //xyz start
                    glVertex3d(intersection_x1+snap_dist, intersection_y1+snap_dist, 0);  //xyz start
                    //second cross line
                    glVertex3d(intersection_x1-snap_dist, intersection_y1+snap_dist, 0);  //xyz start
                    glVertex3d(intersection_x1+snap_dist, intersection_y1-snap_dist, 0);  //xyz start
                    //top line
                    glEnd();

                    //draw cross..
                    glColor3f(0.0f, 0.0f, 1.0f);        //blue
                    glBegin(GL_LINES);
                    //first cross line
                    glVertex3d(intersection_x2-snap_dist, intersection_y2-snap_dist, 0);  //xyz start
                    glVertex3d(intersection_x2+snap_dist, intersection_y2+snap_dist, 0);  //xyz start
                    //second cross line
                    glVertex3d(intersection_x2-snap_dist, intersection_y2+snap_dist, 0);  //xyz start
                    glVertex3d(intersection_x2+snap_dist, intersection_y2-snap_dist, 0);  //xyz start
                    //top line
                    glEnd();

                    //calculate closest snap point related to mouse position..
                    double c1 = sqrt(pow(mouse_cad_pos_x-intersection_x1,2) + pow(mouse_cad_pos_y-intersection_y1,2));
                    double c2 = sqrt(pow(mouse_cad_pos_x-intersection_x2,2) + pow(mouse_cad_pos_y-intersection_y2,2));
                    if(c1<c2){

                        snap_cad_pos_x = intersection_x1;
                        snap_cad_pos_y = intersection_y1;
                        snap_cad_pos_z = mouse_cad_pos_z;

                        break;

                    } else {

                        snap_cad_pos_x = intersection_x2;
                        snap_cad_pos_y = intersection_y2;
                        snap_cad_pos_z = mouse_cad_pos_z;

                        break;
                    }
                }
            }
        }
    }
}





























