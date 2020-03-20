#include "object_select_line_nearest.h"
#include <core_functions/variables.h>

object_select_line_nearest::object_select_line_nearest(bool nearest_sign)
{
    if(mode_cad){
        for (int i = 0; i < cad_counter; i++) {

            //we look if we can get a intersection match if the current id = line..
            if(int_cad_array[i][0] == 1 /*|| mode_chamfer || mode_fillet*/){ //id = line..

                //mouse pointer..
                double cx0 = mouse_cad_pos_x;     //orginal circle center x
                double cy0 = mouse_cad_pos_y;     //orginal circle center y
                double radius = snap_dist;                    //search dist for mouse pointer..

                //line to intersect..
                double px0 = double_cad_array[i][0];          //x_start c
                double py0 = double_cad_array[i][1];          //y_start
                double px1 = double_cad_array[i][3];            //x_end
                double py1 = double_cad_array[i][4];            //y_end

                double nearest_x, nearest_y;
                double dx, dy, A, B, C, det, t, AB, AP, PB;

                dx = px1 - px0;
                dy = py1 - py0;

                A = dx * dx + dy * dy;
                B = 2 * (dx * (px0 - cx0) + dy * (py0 - cy0));
                C = (px0 - cx0) * (px0 - cx0) + (py0 - cy0) * (py0 - cy0) - radius * radius;

                det = B * B - 4 * A * C;

                t = (-B + sqrt(det)) / (2 * A);
                double ix0 = (px0 + t * dx);
                double iy0 = (py0 + t * dy);

                t = (-B - sqrt(det)) / (2 * A);
                double ix1 = (px0 + t * dx);
                double iy1 = (py0 + t * dy);

                //calculate the midpoint for the 2 intersections for a line..
                nearest_x = (ix0 + ix1)/2;
                nearest_y = (iy0 + iy1)/2;

                //check if point lives on the current line..
                //Find the distance of point P from both the line end points A, B. If AB = AP + PB, then P lies on the line segment AB.
                //when multiple lines are drawed in the same line (vector).. multiple lines will be highlited, to prevent this we add the formula below if pointer is on the current line..

                AB = sqrt(pow(px1-px0, 2) + pow(py1-py0, 2));
                AP = sqrt(pow(px1-nearest_x, 2) + pow(py1-nearest_y, 2));
                PB = sqrt(pow(px0-nearest_x, 2) + pow(py0-nearest_y, 2));

                if(AB == AP + PB){
                    int_cad_array[i][4] = 1; //highlight hovering..
                    select_id = i;
                    snap_cad_pos_x = nearest_x;
                    snap_cad_pos_y = nearest_y;
                    snap_cad_pos_z = mouse_cad_pos_z;
                    //draw cross..
                    if(nearest_sign){
                        glColor3f(0.0f, 0.0f, 1.0f);        //blue
                        glBegin(GL_LINES);
                        //first cross line
                        glVertex3d(nearest_x-snap_dist, nearest_y-snap_dist, mouse_cad_pos_z);  //xyz start
                        glVertex3d(nearest_x+snap_dist, nearest_y+snap_dist, mouse_cad_pos_z);  //xyz start
                        //second cross line
                        glVertex3d(nearest_x-snap_dist, nearest_y+snap_dist, mouse_cad_pos_z);  //xyz start
                        glVertex3d(nearest_x+snap_dist, nearest_y-snap_dist, mouse_cad_pos_z);  //xyz start
                        //top line
                        glEnd();
                    }
                    break;
                } else {
                    int_cad_array[i][4] = 0; //no highlight hovering..
                    select_id = -1;
                }
            }
        }
    }
}






















