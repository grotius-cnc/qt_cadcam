#include "nearest.h"
#include <core_functions/variables.h>

nearest::nearest()
{
    for (int i = 0; i < cam_counter; i++) {

        //we look if we can get a intersection match if the current id = line..
        if(int_cam_array[i][0] == 1 && double_cam_array[i][56]==0 && double_cam_array[i][57]==0 && double_cam_array[i][58]==1){ //color blue..

            //mouse pointer..
            double circle_center_x = mouse_cad_pos_x;     //orginal circle center x
            double circle_center_y = mouse_cad_pos_y;     //orginal circle center y
            double radius = snap_dist;                    //search dist for mouse pointer..

            //line to intersect..
            double start_line_x1 = double_cam_array[i][0];          //x_start c
            double start_line_y1 = double_cam_array[i][1];          //y_start
            double end_line_x2 = double_cam_array[i][3];            //x_end
            double end_line_y2 = double_cam_array[i][4];            //y_end

            double nearest_x, nearest_y;
            double dx, dy, A, B, C, det, t, AB, AP, PB;

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

            //calculate the midpoint for the 2 intersections for a line..
            nearest_x = (intersection_x1 + intersection_x2)/2;
            nearest_y = (intersection_y1 + intersection_y2)/2;

            //check if point lives on the current line..
            //Find the distance of point P from both the line end points A, B. If AB = AP + PB, then P lies on the line segment AB.
            //when multiple lines are drawed in the same line (vector).. multiple lines will be highlited, to prevent this we add the formula below if pointer is on the current line..

            AB = sqrt(pow(end_line_x2-start_line_x1, 2) + pow(end_line_y2-start_line_y1, 2));
            AP = sqrt(pow(end_line_x2-nearest_x, 2) + pow(end_line_y2-nearest_y, 2));
            PB = sqrt(pow(start_line_x1-nearest_x, 2) + pow(start_line_y1-nearest_y, 2));

            if(AB != AP + PB){

                int_cam_array[i][4] = 0; //no highlight hovering..
                select_id = -1;


            } else if(AB == AP + PB){

                int_cam_array[i][4] = 1; //highlight hovering..
                select_id = i;

                intersection_type = "line";
                g2 = nearest_x;
                intersection_text_y = nearest_y;

                snap_cad_pos_x = nearest_x;
                snap_cad_pos_y = nearest_y;
                snap_cad_pos_z = mouse_cad_pos_z;

                //draw cross..
                glColor3f(0.0f, 0.0f, 1.0f);        //blue
                glBegin(GL_LINES);
                //first cross line
                glVertex3d(g2-snap_dist, intersection_text_y-snap_dist, mouse_cad_pos_z);  //xyz start
                glVertex3d(g2+snap_dist, intersection_text_y+snap_dist, mouse_cad_pos_z);  //xyz start
                //second cross line
                glVertex3d(g2-snap_dist, intersection_text_y+snap_dist, mouse_cad_pos_z);  //xyz start
                glVertex3d(g2+snap_dist, intersection_text_y-snap_dist, mouse_cad_pos_z);  //xyz start
                //top line
                glEnd();

                //qDebug()<<"select id  : " << i;
                //qDebug()<<"contour nr  : " << int_cam_array[i][14];

                if(int_cam_array[i][12]==1){
                     //qDebug()<<"contour cw";
                }
                if(int_cam_array[i][13]==1){
                     //qDebug()<<"contour ccw";
                }

                //qDebug()<<"intersection x : " << nearest_x << " y : " << nearest_y;

                break;
            }
        }
    }

}




































