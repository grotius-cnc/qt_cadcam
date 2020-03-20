#include "object_select_line_tangent_arc.h"
#include <core_functions/variables.h>
#include <math.h>

object_select_line_tangent_arc::object_select_line_tangent_arc()
{
    for (int i = 0; i < cad_counter; i++) {

        if(mode_tangent && int_cad_array[i][0] == 3){ //id = arc..

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

                //test code.... to find if point is between arc start and arc end angle to determine if we can do a arc select and arc nearest intersection..
                //double_cad_array[cad_counter][0][13] = 180/M_PI*atan2(Y3-y_center, X3-x_center);    //start angle g2
                double circle_center_x = double_cad_array[i][6];    //array target circle center x
                double circle_center_y = double_cad_array[i][7];    //array target circle center y

                double angle = 180/M_PI*atan2(mouse_cad_pos_y - circle_center_y, mouse_cad_pos_x - circle_center_x);
                //transform to cad 0 to 360 degrees instead of the above 0 to 180 and -180 to 0..
                if(angle<=0){angle = 360 - (angle*-1);} //solved in one line..
                if(double_cad_array[i][11] == 0){double_cad_array[i][11] = 360;} //spotted a cad bug while reading a autodesk dxf.. when a end angle = 0, we mean the end angle = 360 degrees..
                //qDebug() << "angle = : " << angle; //sucess..

                //arc start angle, arc end angle..
                //double start_angle = double_cad_array[i][10];
                //double end_angle = double_cad_array[i][11];

                //if(angle > start_angle && angle < end_angle){
                //end test code related to arc..

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

                        //calculate closest snap point related to mouse position..
                        double c1 = sqrt(pow(mouse_cad_pos_x-intersection_x1,2) + pow(mouse_cad_pos_y-intersection_y1,2));
                        double c2 = sqrt(pow(mouse_cad_pos_x-intersection_x2,2) + pow(mouse_cad_pos_y-intersection_y2,2));
                        if(c1<c2){

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

                            snap_cad_pos_x = intersection_x1;
                            snap_cad_pos_y = intersection_y1;
                            snap_cad_pos_z = mouse_cad_pos_z;

                            break;

                        } else {

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
