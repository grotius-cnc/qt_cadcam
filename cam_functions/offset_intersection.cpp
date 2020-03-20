#include "offset_intersection.h"
#include <core_functions/variables.h>
#include <math.h>

void line_line(int id_1, int id_2);
void line_arc(int id_1, int id_2);
void arc_line(int id_1, int id_2);
void arc_arc(int id_1, int id_2);
void lead_in(int startpoint_id, double lead_in);

offset_intersection::offset_intersection()
{
    temp_counter = cam_counter;

    int contour = 0;
    bool trigger = 0;
    int first_line = 0;
    //int temp_counter = cad_counter;
    for(int i =0; i<cam_counter; i++){

        if(double_cam_array[i][56] == 0 && double_cam_array[i][57] == 0 && double_cam_array[i][58] == 1){//color blue..

            if(!trigger){
                contour = int_cam_array[i][14];
                first_line = i;
                trigger = 1;
            }

            //intersect next item
            if(trigger && int_cam_array[i+1][14]==contour){


                if(int_cam_array[i][0] == 1 && int_cam_array[i+1][0] == 1){ //line-line
                    line_line(i, i+1);
                }
                if(int_cam_array[i][0] == 1 && int_cam_array[i+1][0] == 3){ //line-arc
                    line_arc(i, i+1);
                }
                if(int_cam_array[i][0] == 3 && int_cam_array[i+1][0] == 1){ //arc-line
                    arc_line(i, i+1);
                }
                if(int_cam_array[i][0] == 3 && int_cam_array[i+1][0] == 3){ //arc-arc
                    arc_arc(i, i+1);
                }
            }

            //intersect last line with first line
            if(trigger && int_cam_array[i+1][14]!=contour){

                if(int_cam_array[i][0] == 1 && int_cam_array[first_line][0] == 1){ //line-line
                    line_line(i, first_line);
                }
                if(int_cam_array[i][0] == 1 && int_cam_array[first_line][0] == 3){ //line-arc
                    line_arc(i, first_line);
                }
                if(int_cam_array[i][0] == 3 && int_cam_array[first_line][0] == 1){ //arc-line
                    arc_line(i, first_line);
                }
                if(int_cam_array[i][0] == 3 && int_cam_array[first_line][0] == 3){ //arc-arc
                    arc_arc(i, first_line);
                }
                if(int_cam_array[i][0] == 2){ //circle
                    //no intersection calc needed..
                }

                lead_in(first_line, leadin);
                trigger=0;
            }
        }
    }
    cam_counter = temp_counter;

}

void lead_in(int startpoint_id, double lead_in)
{
    if(int_cam_array[startpoint_id][0] == 2){//id circle
        //startpoint circle left..
        int_cam_array[temp_counter][0] = 1; //line
        //int_cam_array[temp_counter][1] = 5;
        double_cam_array[temp_counter][56] = 0; //red
        double_cam_array[temp_counter][57] = 0; //green
        double_cam_array[temp_counter][58] = 1; //blue
        double_cam_array[temp_counter][59] = 1; //alpha

        int_cam_array[temp_counter][2] = 1; //linewidth
        int_cam_array[temp_counter][5] = current_linetype;
        int_cam_array[temp_counter][14] = int_cam_array[startpoint_id][14]; //contournumber
        int_cam_array[temp_counter][15] = int_cam_array[startpoint_id][15]; //closed contour mark
        int_cam_array[temp_counter][24] = 1; //lead in mark for i..

        if(int_cam_array[startpoint_id][20]==1){//g2 contour

            //add startpoint seen from circle center.. when circle rotates, we have to rotate the lead in with it..

            //  cross calculation
            //    A-----------B------------C
            // (Xa,Ya)     (Xb,Yb)      (Xc,Yc)

            //    AB = sqrt( (Xb - Xa)² + (Yb - Ya)² )
            //    AC = 1000

            //    Xc = Xa + (AC * (Xb - Xa) / AB)
            //    Yc = Ya + (AC * (Yb - Ya) / AB)

            //arc lead_in startpoint calculation.. outside lead in..
            double Xa = double_cam_array[startpoint_id][6];
            double Ya = double_cam_array[startpoint_id][7];
            double Xb = double_cam_array[startpoint_id][25];
            double Yb = double_cam_array[startpoint_id][26];
            double AC = double_cam_array[startpoint_id][9]+lead_in; //radius
            double AB = double_cam_array[startpoint_id][9];
            double Xc = Xa + (AC * (Xb - Xa) / AB); //new startpoint coordinate..
            double Yc = Ya + (AC * (Yb - Ya) / AB);

            double_cam_array[temp_counter][0] = Xc;
            double_cam_array[temp_counter][1] = Yc;
            double_cam_array[temp_counter][3] = double_cam_array[startpoint_id][25];
            double_cam_array[temp_counter][4] = double_cam_array[startpoint_id][26];
        }
        if(int_cam_array[startpoint_id][21]==1){//g3 contour

            //add startpoint seen from circle center.. when circle rotates, we have to rotate the lead in with it..

            //  cross calculation
            //    A-----------B------------C
            // (Xa,Ya)     (Xb,Yb)      (Xc,Yc)

            //    AB = sqrt( (Xb - Xa)² + (Yb - Ya)² )
            //    AC = 1000

            //    Xc = Xa + (AC * (Xb - Xa) / AB)
            //    Yc = Ya + (AC * (Yb - Ya) / AB)

            //arc lead_in startpoint calculation.. inside lead in..
            double Xa = double_cam_array[startpoint_id][6];
            double Ya = double_cam_array[startpoint_id][7];
            double Xb = double_cam_array[startpoint_id][25];
            double Yb = double_cam_array[startpoint_id][26];
            double AC = double_cam_array[startpoint_id][9]-lead_in; //radius
            double AB = double_cam_array[startpoint_id][9];
            double Xc = Xa + (AC * (Xb - Xa) / AB); //new startpoint coordinate..
            double Yc = Ya + (AC * (Yb - Ya) / AB);

            double_cam_array[temp_counter][0] = Xc;
            double_cam_array[temp_counter][1] = Yc;
            double_cam_array[temp_counter][3] = double_cam_array[startpoint_id][25];
            double_cam_array[temp_counter][4] = double_cam_array[startpoint_id][26];
        }
        temp_counter++;
    } else
    if(int_cam_array[startpoint_id][0] == 3){//id arc
        double offset = 0;
        double radius = double_cam_array[startpoint_id][9];
        double x_center = double_cam_array[startpoint_id][6];
        double y_center = double_cam_array[startpoint_id][7];

        //normal outside offset command
        if(int_cam_array[startpoint_id][12] == 1){ //cw contour
            if(int_cam_array[startpoint_id][20] == 1){ //g2
                offset = lead_in;
            }
            if(int_cam_array[startpoint_id][21] == 1){ //g3
                offset = lead_in*-1;
            }
        }
        //normal inside offset command
        if(int_cam_array[startpoint_id][13] == 1){ //ccw contour
            if(int_cam_array[startpoint_id][20] == 1){ //g2
                offset = lead_in;
            }
            if(int_cam_array[startpoint_id][21] == 1){ //g3
                offset = lead_in*-1;
            }
        }

        //keep orginal object..
        int_cam_array[temp_counter][0] = 1; //line
        //int_cam_array[temp_counter][1] = 5;
        double_cam_array[temp_counter][56] = 0; //red
        double_cam_array[temp_counter][57] = 0; //green
        double_cam_array[temp_counter][58] = 1; //blue
        double_cam_array[temp_counter][59] = 1; //alpha

        int_cam_array[temp_counter][2] = 1; //linewidth
        int_cam_array[temp_counter][5] = current_linetype;
        int_cam_array[temp_counter][12] = int_cam_array[startpoint_id][12]; //contour cw
        int_cam_array[temp_counter][13] = int_cam_array[startpoint_id][13]; //contour ccw
        int_cam_array[temp_counter][14] = int_cam_array[startpoint_id][14]; //contournumber
        int_cam_array[temp_counter][15] = int_cam_array[startpoint_id][15]; //closed contour mark
        int_cam_array[temp_counter][24] = 1; //lead in mark for i..

        //calculate new startpoint and endpoint and arc mid coordinates through given offset distance..

        //  cross calculation
        //    A-----------B------------C
        // (Xa,Ya)     (Xb,Yb)      (Xc,Yc)

        //    AB = sqrt( (Xb - Xa)² + (Yb - Ya)² )
        //    AC = 1000

        //    Xc = Xa + (AC * (Xb - Xa) / AB)
        //    Yc = Ya + (AC * (Yb - Ya) / AB)

        //arc offset startpoint calculation
        double Xa = x_center;
        double Ya = y_center;
        double Xb = double_cam_array[startpoint_id][0]; //x start
        double Yb = double_cam_array[startpoint_id][1]; //y start
        double AC = radius + offset;
        double AB = radius;
        double Xc = Xa + (AC * (Xb - Xa) / AB); //new startpoint coordinate..
        double Yc = Ya + (AC * (Yb - Ya) / AB);
        double_cam_array[temp_counter][0] = Xc;
        double_cam_array[temp_counter][1] = Yc;

        double_cam_array[temp_counter][3] = double_cam_array[startpoint_id][0];
        double_cam_array[temp_counter][4] = double_cam_array[startpoint_id][1];

        temp_counter++;
    } else
    if(int_cam_array[startpoint_id][0] == 1){//id line
        if(int_cam_array[startpoint_id][12] == 1){//cw contour
            rotate_degrees = 90;
        }
        if(int_cam_array[startpoint_id][13] == 1){//ccw contour
            rotate_degrees = 45;
        }

        //rotate orginal line..
        double temp_x = double_cam_array[startpoint_id][0];
        double temp_y = double_cam_array[startpoint_id][1];

        double rotate_dist_x_endpoint = double_cam_array[startpoint_id][3] - temp_x;
        double rotate_dist_y_endpoint = double_cam_array[startpoint_id][4] - temp_y;

        double rotate_x1 = cos(rotate_degrees * M_PI / 180.0 )* rotate_dist_x_endpoint - sin(rotate_degrees * M_PI / 180.0 ) * rotate_dist_y_endpoint;
        double rotate_y1 = sin(rotate_degrees * M_PI / 180.0 )* rotate_dist_x_endpoint + cos(rotate_degrees * M_PI / 180.0 ) * rotate_dist_y_endpoint;

        //modify line lenght to offset input..
        //calculate line length
        double object_x0 = double_cam_array[startpoint_id][0];
        double object_y0 = double_cam_array[startpoint_id][1];
        double object_x1 = rotate_x1 + temp_x;
        double object_y1 = rotate_y1 + temp_y;

        //formulat : A2 + B2 = C2
        double object_A = object_x1 - object_x0;
        double object_B = object_y1 - object_y0;
        double object_C = sqrt(pow(object_A,2)+pow(object_B,2));

        double object_radius = lead_in;
        entry_focus = 0;

        //  cross calculation
        //    A-----------B------------C
        // (Xa,Ya)     (Xb,Yb)      (Xc,Yc)

        //    AB = sqrt( (Xb - Xa)² + (Yb - Ya)² )
        //    AC = 1000

        //    Xc = Xa + (AC * (Xb - Xa) / AB)
        //    Yc = Ya + (AC * (Yb - Ya) / AB)

        double object_AB = object_C;
        double object_AC = object_radius;

        double object_x_end = object_x0 + (object_AC * (object_x1 - object_x0) / object_AB);
        double object_y_end = object_y0 + (object_AC * (object_y1 - object_y0) / object_AB);

        //calculate second line point..
        double dist_x = object_x_end - double_cam_array[startpoint_id][0];
        double dist_y = object_y_end - double_cam_array[startpoint_id][1];
        double object_x2 = double_cam_array[startpoint_id][3] + dist_x;
        double object_y2 = double_cam_array[startpoint_id][4] + dist_y;

        //keep orginal object..
        int_cam_array[temp_counter][0] = 1; //id line
        //int_cam_array[temp_counter][1] = 5; //color blue..
        double_cam_array[temp_counter][56] = 0; //red
        double_cam_array[temp_counter][57] = 0; //green
        double_cam_array[temp_counter][58] = 1; //blue
        double_cam_array[temp_counter][59] = 1; //alpha

        int_cam_array[temp_counter][2] = 1; //linewidth
        int_cam_array[temp_counter][5] = current_linetype;
        int_cam_array[temp_counter][12] = int_cam_array[startpoint_id][12]; //contour cw
        int_cam_array[temp_counter][13] = int_cam_array[startpoint_id][13]; //contour ccw
        int_cam_array[temp_counter][14] = int_cam_array[startpoint_id][14]; //contournumber
        int_cam_array[temp_counter][15] = int_cam_array[startpoint_id][15]; //closed contour mark
        int_cam_array[temp_counter][24] = 1; //lead in mark for i..
        double_cam_array[temp_counter][0] = object_x_end;
        double_cam_array[temp_counter][1] = object_y_end;
        //double_cam_array[temp_counter][2] = snap_cad_pos_z;
        double_cam_array[temp_counter][3] = double_cam_array[startpoint_id][0];
        double_cam_array[temp_counter][4] = double_cam_array[startpoint_id][1];
        //double_cam_array[temp_counter][5] = snap_cad_pos_z;
        temp_counter++;
    }
}

void line_line(int id_1, int id_2){ //id_1 = endpoint, id_2 = startpoint

    //qDebug()<< "line-line intersection id_1 : " << id_1 << "id_2 : " << id_2;
    //line 1 to compare :
    double startpoint_x0 = double_cam_array[id_1][0];
    double startpoint_y0 = double_cam_array[id_1][1];
    double endpoint_x0 = double_cam_array[id_1][3];
    double endpoint_y0 = double_cam_array[id_1][4];

    //line 2 to compare :
    double startpoint_x1 = double_cam_array[id_2][0];
    double startpoint_y1 = double_cam_array[id_2][1];
    double endpoint_x1 = double_cam_array[id_2][3];
    double endpoint_y1 = double_cam_array[id_2][4];

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

        double x = (delta_x1*c0 - delta_x0*c1)/determinant;
        double y = (delta_y0*c1 - delta_y1*c0)/determinant;
        //qDebug() << " intersection point is x : " << x << " y : " << y;

        double_cam_array[id_1][3] = x;
        double_cam_array[id_1][4] = y;
        double_cam_array[id_2][0] = x;
        double_cam_array[id_2][1] = y;
    }
}
void line_arc(int id_1, int id_2){

    double start_line_x1 = double_cam_array[id_1][0];
    double start_line_y1 = double_cam_array[id_1][1];
    double end_line_x2 = double_cam_array[id_1][3];
    double end_line_y2 = double_cam_array[id_1][4];

    double circle_center_x = double_cam_array[id_2][6];
    double circle_center_y = double_cam_array[id_2][7];
    double radius = double_cam_array[id_2][9];

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

    //find closest solution, at line endpoint..
    double c1 = sqrt(pow(double_cam_array[id_1][3]-intersection_x1,2) + pow(double_cam_array[id_1][4]-intersection_y1,2));
    double c2 = sqrt(pow(double_cam_array[id_1][3]-intersection_x2,2) + pow(double_cam_array[id_1][4]-intersection_y2,2));

    if(c1<c2){
        //line endpoint..
        double_cam_array[id_1][3] = intersection_x1;
        double_cam_array[id_1][4] = intersection_y1;
        //arc startpoint..
        double_cam_array[id_2][0] = intersection_x1;
        double_cam_array[id_2][1] = intersection_y1;
    }
    if(c1>c2){
        //line endpoint..
        double_cam_array[id_1][3] = intersection_x2;
        double_cam_array[id_1][4] = intersection_y2;
        //arc startpoint..
        double_cam_array[id_2][0] = intersection_x2;
        double_cam_array[id_2][1] = intersection_y2;
    }
    //recalculate circle angles..
    if(int_cam_array[id_2][20]==1){//g2
        double_cam_array[id_2][11] = 180/M_PI*atan2(double_cam_array[id_2][4]-double_cam_array[id_2][7], double_cam_array[id_2][3]-double_cam_array[id_2][6]);    //start angle G2
        double_cam_array[id_2][12] = 180/M_PI*atan2(double_cam_array[id_2][1]-double_cam_array[id_2][7], double_cam_array[id_2][0]-double_cam_array[id_2][6]);    //end angle G2
    }
    if(int_cam_array[id_2][21]==1){//g3
        double_cam_array[id_2][11] = 180/M_PI*atan2(double_cam_array[id_2][1]-double_cam_array[id_2][7], double_cam_array[id_2][0]-double_cam_array[id_2][6]);    //start angle G3
        double_cam_array[id_2][12] = 180/M_PI*atan2(double_cam_array[id_2][4]-double_cam_array[id_2][7], double_cam_array[id_2][3]-double_cam_array[id_2][6]);    //end angle G3
    }
}
void arc_line(int id_1, int id_2){

    double start_line_x1 = double_cam_array[id_2][0];
    double start_line_y1 = double_cam_array[id_2][1];
    double end_line_x2 = double_cam_array[id_2][3];
    double end_line_y2 = double_cam_array[id_2][4];

    double circle_center_x = double_cam_array[id_1][6];
    double circle_center_y = double_cam_array[id_1][7];
    double radius = double_cam_array[id_1][9];

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

    //find closest solution, at line startpoint..
    double c1 = sqrt(pow(double_cam_array[id_2][0]-intersection_x1,2) + pow(double_cam_array[id_2][1]-intersection_y1,2));
    double c2 = sqrt(pow(double_cam_array[id_2][0]-intersection_x2,2) + pow(double_cam_array[id_2][1]-intersection_y2,2));

    if(c1<c2){
        //arc endpoint..
        double_cam_array[id_1][3] = intersection_x1;
        double_cam_array[id_1][4] = intersection_y1;
        //line startpoint..
        double_cam_array[id_2][0] = intersection_x1;
        double_cam_array[id_2][1] = intersection_y1;
    }
    if(c1>c2){
        //arc endtpoint..
        double_cam_array[id_1][3] = intersection_x2;
        double_cam_array[id_1][4] = intersection_y2;
        //line startpoint..
        double_cam_array[id_2][0] = intersection_x2;
        double_cam_array[id_2][1] = intersection_y2;

    }
    //recalculate arc angles..
    if(int_cam_array[id_1][20]==1){//g2
        double_cam_array[id_1][11] = 180/M_PI*atan2(double_cam_array[id_1][4]-double_cam_array[id_1][7], double_cam_array[id_1][3]-double_cam_array[id_1][6]);    //start angle G2
        double_cam_array[id_1][12] = 180/M_PI*atan2(double_cam_array[id_1][1]-double_cam_array[id_1][7], double_cam_array[id_1][0]-double_cam_array[id_1][6]);    //end angle G2
    }
    if(int_cam_array[id_1][21]==1){//g3
        double_cam_array[id_1][11] = 180/M_PI*atan2(double_cam_array[id_1][1]-double_cam_array[id_1][7], double_cam_array[id_1][0]-double_cam_array[id_1][6]);    //start angle G3
        double_cam_array[id_1][12] = 180/M_PI*atan2(double_cam_array[id_1][4]-double_cam_array[id_1][7], double_cam_array[id_1][3]-double_cam_array[id_1][6]);    //end angle G3
    }
}
void arc_arc(int id_1, int id_2){

    double cx0 = double_cam_array[id_1][6];
    double cy0 = double_cam_array[id_1][7];
    double radius0 = double_cam_array[id_1][9];
    double cx1 = double_cam_array[id_2][6];
    double cy1 = double_cam_array[id_2][7];
    double radius1 = double_cam_array[id_2][9];

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

        double dist_p1 = sqrt(pow(double_cam_array[id_1][3]-px1,2)+pow(double_cam_array[id_1][4]-py1,2));
        double dist_p2 = sqrt(pow(double_cam_array[id_1][3]-px2,2)+pow(double_cam_array[id_1][4]-py2,2));

        if(dist_p1<dist_p2){
            double_cam_array[id_1][3] = px1;
            double_cam_array[id_1][4] = py1;
            double_cam_array[id_2][0] = px1;
            double_cam_array[id_2][1] = py1;
        }
        if(dist_p1>dist_p2){
            double_cam_array[id_1][3] = px2;
            double_cam_array[id_1][4] = py2;
            double_cam_array[id_2][0] = px2;
            double_cam_array[id_2][1] = py2;
        }

        //recalculate arc angles..
        if(int_cam_array[id_1][20]==1){//g2
            double_cam_array[id_1][11] = 180/M_PI*atan2(double_cam_array[id_1][4]-double_cam_array[id_1][7], double_cam_array[id_1][3]-double_cam_array[id_1][6]);    //start angle G2
            double_cam_array[id_1][12] = 180/M_PI*atan2(double_cam_array[id_1][1]-double_cam_array[id_1][7], double_cam_array[id_1][0]-double_cam_array[id_1][6]);    //end angle G2
        }
        if(int_cam_array[id_1][21]==1){//g3
            double_cam_array[id_1][11] = 180/M_PI*atan2(double_cam_array[id_1][1]-double_cam_array[id_1][7], double_cam_array[id_1][0]-double_cam_array[id_1][6]);    //start angle G3
            double_cam_array[id_1][12] = 180/M_PI*atan2(double_cam_array[id_1][4]-double_cam_array[id_1][7], double_cam_array[id_1][3]-double_cam_array[id_1][6]);    //end angle G3
        }

        //recalculate arc angles..
        if(int_cam_array[id_2][20]==1){//g2
            double_cam_array[id_2][11] = 180/M_PI*atan2(double_cam_array[id_2][4]-double_cam_array[id_2][7], double_cam_array[id_2][3]-double_cam_array[id_2][6]);    //start angle G2
            double_cam_array[id_2][12] = 180/M_PI*atan2(double_cam_array[id_2][1]-double_cam_array[id_2][7], double_cam_array[id_2][0]-double_cam_array[id_2][6]);    //end angle G2
        }
        if(int_cam_array[id_2][21]==1){//g3
            double_cam_array[id_2][11] = 180/M_PI*atan2(double_cam_array[id_2][1]-double_cam_array[id_2][7], double_cam_array[id_2][0]-double_cam_array[id_2][6]);    //start angle G3
            double_cam_array[id_2][12] = 180/M_PI*atan2(double_cam_array[id_2][4]-double_cam_array[id_2][7], double_cam_array[id_2][3]-double_cam_array[id_2][6]);    //end angle G3
        }
    }
}

























