#include "object_select_line_intersection.h"
#include <core_functions/variables.h>
#include <math.h>

object_select_line_intersection::object_select_line_intersection()
{
    if(mode_cad){

        QList<int> line_list = line_nearest();
        QList<int> arc_list = arc_nearest();

        if(line_list.size()==2){

            qDebug()<< "line-line";
            QList<double> intersection_xy = line_line_intersection_by_id(line_list.at(0), line_list.at(1));
            if(intersection_xy.size()==2){
                snap_cad_pos_x = intersection_xy.at(0);
                snap_cad_pos_y = intersection_xy.at(1);
            }
            intersection_xy.clear();

            //draw snap..
            glColor3f(0.0f, 0.0f, 1.0f);        //blue
            glBegin(GL_LINE_STRIP);
            glVertex2d(snap_cad_pos_x-snap_dist, snap_cad_pos_y-snap_dist);
            glVertex2d(snap_cad_pos_x-snap_dist, snap_cad_pos_y+snap_dist);
            glVertex2d(snap_cad_pos_x+snap_dist, snap_cad_pos_y+snap_dist);
            glVertex2d(snap_cad_pos_x+snap_dist, snap_cad_pos_y-snap_dist);
            glVertex2d(snap_cad_pos_x-snap_dist, snap_cad_pos_y-snap_dist);
            glEnd();
        }

        if(line_list.size()==1 && arc_list.size()==1){

            qDebug()<< "line-arc";
            QList<double> intersection_xy = line_arc_intersection_by_id(line_list.at(0), arc_list.at(0));
            if(intersection_xy.size()==2){
                snap_cad_pos_x = intersection_xy.at(0);
                snap_cad_pos_y = intersection_xy.at(1);
            }
            intersection_xy.clear();

            //draw snap..
            glColor3f(0.0f, 0.0f, 1.0f);        //blue
            glBegin(GL_LINE_STRIP);
            glVertex2d(snap_cad_pos_x-snap_dist, snap_cad_pos_y-snap_dist);
            glVertex2d(snap_cad_pos_x-snap_dist, snap_cad_pos_y+snap_dist);
            glVertex2d(snap_cad_pos_x+snap_dist, snap_cad_pos_y+snap_dist);
            glVertex2d(snap_cad_pos_x+snap_dist, snap_cad_pos_y-snap_dist);
            glVertex2d(snap_cad_pos_x-snap_dist, snap_cad_pos_y-snap_dist);
            glEnd();
        }
    }
}

QList<int> object_select_line_intersection::arc_nearest()
{
    QList<int> list;
    for (int i = 0; i < cad_counter; i++) {

        if(int_cad_array[i][0]==2 || int_cad_array[i][0]==3){ //id = circle or id = arc..

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
                //snap_nearest = -1;
                int_cad_array[i][4] = 0; //highlight

                snap_cad_pos_x = mouse_cad_pos_x;
                snap_cad_pos_y = mouse_cad_pos_y;
                snap_cad_pos_z = mouse_cad_pos_z;
            }
            else if (dist < abs(radius0 - radius1))
            {
                //qDebug() << "No solutions, one circle contains the other";
                //snap_nearest = -1;
                int_cad_array[i][4] = 0;

                snap_cad_pos_x = mouse_cad_pos_x;
                snap_cad_pos_y = mouse_cad_pos_y;
                snap_cad_pos_z = mouse_cad_pos_z;
            }
            else if ((dist == 0) && (radius0 == radius1))
            {
                //qDebug() << "No solutions, the circles coincide";
                //snap_nearest = -1;
                int_cad_array[i][4] = 0;

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

                if(c1<c2){

                    int_cad_array[i][4] = 1; //highlight hovering..
                    if(!list.contains(i)){
                        list.append(i);
                    }

                } else {

                    int_cad_array[i][4] = 1; //highlight hovering..
                    if(!list.contains(i)){
                        list.append(i);
                    }
                }
            }
        }
    }
    //qDebug()<< "list : " << list;
    return list;

}

QList<int> object_select_line_intersection::line_nearest()
{
    QList<int> list;
    for (int i = 0; i < cad_counter; i++) {

        if(int_cad_array[i][0] == 1 /*|| mode_chamfer || mode_fillet*/){ //id = line..
            //mouse pointer..
            double circle_center_x = mouse_cad_pos_x;     //orginal circle center x
            double circle_center_y = mouse_cad_pos_y;     //orginal circle center y
            double radius = snap_dist;                    //search dist for mouse pointer..
            //line to intersect..
            double start_line_x1 = double_cad_array[i][0];          //x_start c
            double start_line_y1 = double_cad_array[i][1];          //y_start
            double end_line_x2 = double_cad_array[i][3];            //x_end
            double end_line_y2 = double_cad_array[i][4];            //y_end

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

                int_cad_array[i][4] = 0; //no highlight hovering..

            } else if(AB == AP + PB){

                int_cad_array[i][4] = 1; //highlight hovering..
                if(!list.contains(i)){
                    list.append(i);
                }
            }
        }
    }
    return list;
}

QList<double> object_select_line_intersection::line_line_intersection_by_id(int id_1, int id_2)
{
    QList<double> list;
    //line 1
    double startpoint_x0 = double_cad_array[id_1][0];
    double startpoint_y0 = double_cad_array[id_1][1];
    double endpoint_x0 = double_cad_array[id_1][3];
    double endpoint_y0 = double_cad_array[id_1][4];

    //line 2
    double startpoint_x1 = double_cad_array[id_2][0];
    double startpoint_y1 = double_cad_array[id_2][1];
    double endpoint_x1 = double_cad_array[id_2][3];
    double endpoint_y1 = double_cad_array[id_2][4];

    //line 1
    double delta_y0 = endpoint_y0 - startpoint_y0;
    double delta_x0 = startpoint_x0 - endpoint_x0;
    double c0 = delta_y0 * startpoint_x0 + delta_x0 * startpoint_y0;

    //line 2
    double delta_y1 = endpoint_y1 - startpoint_y1;
    double delta_x1 = startpoint_x1 - endpoint_x1;
    double c1 = delta_y1 * startpoint_x1 + delta_x1 * startpoint_y1;

    double determinant = delta_y0*delta_x1 - delta_y1*delta_x0;
    //qDebug() << "determinant is : " << determinant;

    if (determinant == 0) // The lines are parallel.
    {
        //qDebug() << "the lines are parallel";
    }
    else  {
        list.append((delta_x1*c0 - delta_x0*c1)/determinant); //x
        list.append((delta_y0*c1 - delta_y1*c0)/determinant); //y
        return list;
    }
}

QList<double> object_select_line_intersection::line_arc_intersection_by_id(int id_1, int id_2)
{

    QList<double> list;

    //line - circle intersection..
    double circle_center_x = double_cad_array[id_2][6];    //array target circle center x
    double circle_center_y = double_cad_array[id_2][7];    //array target circle center y
    double radius = double_cad_array[id_2][9];             //array target circle radius

    double start_line_x1 = double_cad_array[id_1][0];
    double start_line_y1 = double_cad_array[id_1][1];
    double end_line_x2 = double_cad_array[id_1][3];
    double end_line_y2 = double_cad_array[id_1][4];

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

    if(c1<c2){
        list.append(intersection_x1);
        list.append(intersection_y1);

    } else {
        list.append(intersection_x2);
        list.append(intersection_y2);
    }
    return list;

}


















