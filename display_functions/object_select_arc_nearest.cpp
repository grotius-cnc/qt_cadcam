#include "object_select_arc_nearest.h"
#include <core_functions/variables.h>
#include <math.h>
void draw_nearest(double x, double y);

object_select_arc_nearest::object_select_arc_nearest(bool nearest_sign)
{
    for (int i = 0; i < cad_counter; i++) {

        if(int_cad_array[i][0] == 3){ //id = arc..

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
                //select_id = -1;
                int_cad_array[i][4] = 0; //highlight

                snap_cad_pos_x = mouse_cad_pos_x;
                snap_cad_pos_y = mouse_cad_pos_y;
                snap_cad_pos_z = mouse_cad_pos_z;
            }
            else if (dist < abs(radius0 - radius1))
            {
                //qDebug() << "No solutions, one circle contains the other";
                int_cad_array[i][4] = 0;
                //select_id = -1;

                snap_cad_pos_x = mouse_cad_pos_x;
                snap_cad_pos_y = mouse_cad_pos_y;
                snap_cad_pos_z = mouse_cad_pos_z;
            }
            else if ((dist == 0) && (radius0 == radius1))
            {
                //qDebug() << "No solutions, the circles coincide";
                int_cad_array[i][4] = 0;
                //select_id = -1;

                snap_cad_pos_x = mouse_cad_pos_x;
                snap_cad_pos_y = mouse_cad_pos_y;
                snap_cad_pos_z = mouse_cad_pos_z;
            }
            else
            {
                //at this stage we end up with 2 intersections.. but we don't need the intersection points.. we now know wich circle is the target for a line-circle intersect calculation..
                //line - circle intersection..
                double circle_center_x = double_cad_array[i][6];    //array target circle center x
                double circle_center_y = double_cad_array[i][7];    //array target circle center y
                double radius = double_cad_array[i][9];             //array target circle radius

                double start_line_x1 = double_cad_array[i][6];      //line from target circle center x
                double start_line_y1 = double_cad_array[i][7];      //line from target circle center y
                double end_line_x2 = mouse_cad_pos_x;               //line from actual mouse coordinate x..
                double end_line_y2 = mouse_cad_pos_y;               //line from actual mouse coordinate y..

                //test code.... to find if point is between arc start and arc end angle to determine if we can do a arc select and arc nearest intersection..
                //double_cad_array[cad_counter][0][13] = 180/M_PI*atan2(Y3-y_center, X3-x_center);    //start angle g2
                //double angle = 180/M_PI*atan2(mouse_cad_pos_y - circle_center_y, mouse_cad_pos_x - circle_center_x);

                //transform to cad 0 to 360 degrees instead of the above 0 to 180 and -180 to 0..
                //if(angle<=0){angle = 360 - (angle*-1);} //solved in one line..
                //if(double_cad_array[i][12] == 0){double_cad_array[i][12] = 360;} //spotted a cad bug while reading a autodesk dxf.. when a end angle = 0, we mean the end angle = 360 degrees..
                //qDebug() << "angle = : " << angle; //sucess..

                //arc start angle, arc end angle..
                //double start_angle = double_cad_array[i][11];
                //double end_angle = double_cad_array[i][12];

                //if(angle > start_angle && angle < end_angle){ // works only for G2 arc's at the moment, turned of now, it could be handy not to use this while drawing with nearest..

                //end test code..

                double dx, dy, A, B, C, det, t;

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

                //find closest solution..
                double c1 = sqrt(pow(mouse_cad_pos_x-intersection_x1,2) + pow(mouse_cad_pos_y-intersection_y1,2));
                double c2 = sqrt(pow(mouse_cad_pos_x-intersection_x2,2) + pow(mouse_cad_pos_y-intersection_y2,2));

                //calculate if arc is g2 or g3..
                double x1 = double_cad_array[i][0]; //startpoint
                double y1 = double_cad_array[i][1];
                double x2 = double_cad_array[i][15]; //midpoint on arc circumfence
                double y2 = double_cad_array[i][16];
                double x = double_cad_array[i][3];
                double y = double_cad_array[i][4]; //endpoint
                double d=(x-x1)*(y2-y1)-(y-y1)*(x2-x1); //d<0=g2, d>0=g3
                //if(d>0){qDebug()<< "g2";} else {qDebug()<< "g3";}

                //implement if mouse is betweem start angle and end angle..
                double mouse_angle =0;
                double start_angle = 0;
                double end_angle = 0;

                start_angle = 180/M_PI*atan2(double_cad_array[i][1] - circle_center_y, double_cad_array[i][0] - circle_center_x);
                if(start_angle<=0){start_angle = 360 - (start_angle*-1);}
                end_angle = 180/M_PI*atan2(double_cad_array[i][4] - circle_center_y, double_cad_array[i][3] - circle_center_x);
                if(end_angle<=0){end_angle = 360 - (end_angle*-1);}
                mouse_angle = 180/M_PI*atan2(snap_cad_pos_y - circle_center_y, snap_cad_pos_x - circle_center_x);
                if(mouse_angle<=0){mouse_angle = 360 - (mouse_angle*-1);}

                //qDebug() << "start_angle : " << start_angle;
                //qDebug() << "end_angle : " << end_angle;
                //qDebug() << "mouse_angle : " << mouse_angle;

                if(c1<c2){ //stackoverflow : how te determine whether a point (X,Y) is contained within an arc section of a circle..
                    if(d<0 && ((start_angle<end_angle && start_angle<mouse_angle && mouse_angle<end_angle) || /*senario when it crossen the 0*/(start_angle>end_angle && (mouse_angle>start_angle || mouse_angle<end_angle)))){ //g3
                        int_cad_array[i][4] = 1; //highlight hovering..
                        select_id = i;
                        snap_cad_pos_x = intersection_x1;
                        snap_cad_pos_y = intersection_y1;
                        snap_cad_pos_z = mouse_cad_pos_z;
                        if(nearest_sign){
                            draw_nearest(intersection_x1,intersection_y1);
                        }
                        break;
                    }
                    if(d>0 && ((start_angle>end_angle && start_angle>mouse_angle && mouse_angle>end_angle) || (start_angle<end_angle && (mouse_angle<start_angle || mouse_angle>end_angle)))){ //g2
                        int_cad_array[i][4] = 1; //highlight hovering..
                        select_id = i;
                        snap_cad_pos_x = intersection_x1;
                        snap_cad_pos_y = intersection_y1;
                        snap_cad_pos_z = mouse_cad_pos_z;
                        if(nearest_sign){
                            draw_nearest(intersection_x1,intersection_y1);
                        }
                        break;
                    }
                }
                if(c1>c2){
                    if(d<0 && ((start_angle<end_angle && start_angle<mouse_angle && mouse_angle<end_angle)|| (start_angle>end_angle && (mouse_angle>start_angle || mouse_angle<end_angle)))){ //g3
                        int_cad_array[i][4] = 1; //highlight hovering..
                        select_id = i;
                        snap_cad_pos_x = intersection_x2;
                        snap_cad_pos_y = intersection_y2;
                        snap_cad_pos_z = mouse_cad_pos_z;
                        if(nearest_sign){
                            draw_nearest(intersection_x2,intersection_y2);
                        }
                        break;
                    }
                    if(d>0 && ((start_angle>end_angle && start_angle>mouse_angle && mouse_angle>end_angle) || (start_angle<end_angle && (mouse_angle<start_angle || mouse_angle>end_angle)))){ //g2
                        int_cad_array[i][4] = 1; //highlight hovering..
                        select_id = i;
                        snap_cad_pos_x = intersection_x2;
                        snap_cad_pos_y = intersection_y2;
                        snap_cad_pos_z = mouse_cad_pos_z;
                        if(nearest_sign){
                            draw_nearest(intersection_x2,intersection_y2);
                        }
                        break;
                    }
                }
            }
        }
    }
}

void draw_nearest(double x, double y)
{
    //draw cross..
    glColor3f(0.0f, 0.0f, 1.0f);        //blue
    glBegin(GL_LINES);
    //first cross line
    glVertex3d(x-snap_dist, y-snap_dist, mouse_cad_pos_z);  //xyz start
    glVertex3d(x+snap_dist, y+snap_dist, mouse_cad_pos_z);  //xyz start
    //second cross line
    glVertex3d(x-snap_dist, y+snap_dist, mouse_cad_pos_z);  //xyz start
    glVertex3d(x+snap_dist, y-snap_dist, mouse_cad_pos_z);  //xyz start
    //top line
    glEnd();
}

////calculate if arc's are g2 or g3..
//for(int i=0; i<cam_counter; i++){

//    if(int_cam_array[i][0]==3){ //id arc

//        double x1 = double_cam_array[i][0]; //startpoint
//        double y1 = double_cam_array[i][1];
//        double x2 = double_cam_array[i][15]; //midpoint on arc circumfence
//        double y2 = double_cam_array[i][16];
//        double x = double_cam_array[i][3];
//        double y = double_cam_array[i][4]; //endpoint

//        double d=(x-x1)*(y2-y1)-(y-y1)*(x2-x1);
//        if(d>0){
//            int_cam_array[i][20] = 1; //g2
//        }
//        if(d<0){
//            int_cam_array[i][21] = 1; //g3
//        }
//    }
//}






























