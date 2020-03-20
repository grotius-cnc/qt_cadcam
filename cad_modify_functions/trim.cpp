#include "trim.h"
#include <core_functions/variables.h>
#include <display_functions/object_select_line_nearest.h>
#include <display_functions/object_select_arc_nearest.h>
#include <display_functions/object_select_circle_nearest.h>
#include <display_functions/no_highlight.h>
#include <cad_draw_functions/redraw_arc.h>
#include <display_functions/simple_line_select.h>
#include <math.h>

#define myqDebug() qDebug() << fixed << qSetRealNumberPrecision(3)

trim::trim()
{
    //initialiation..
    snap_cad_pos_x = mouse_cad_pos_x;
    snap_cad_pos_y = mouse_cad_pos_y;
    snap_cad_pos_z = mouse_cad_pos_z;

    //overwrite initialisation if we spot a snap somewhere..
    object_select_line_nearest(0);
    //simple_line_select();
    object_select_arc_nearest(0);
    object_select_circle_nearest(0);

    if(click == 0){
        id_1 = -1;
        id_2 = -1;
        messagebox_text = "<b><i>mode trim</i></b> click boundary line";
        //mode_nearest = 1;
    }

    if(click == 1){

        id_1 = select_id; qDebug()<< "id_1 : " << id_1; //boundary line..
        messagebox_text = "<b><i>mode trim</i></b> click line piece to delete";
        click = 2;
    }

    if(click == 3){

        id_2 = select_id; qDebug()<< "id_2 : " << id_2; //line to delete..
        double x = snap_cad_pos_x;
        double y = snap_cad_pos_y;

        //calculate intersection
        if(int_cad_array[id_1][0]==1 && int_cad_array[id_2][0]==1 ){ //line - line intersection..

            double trim_snapshot_side =(snap_cad_pos_x-double_cad_array[id_1][0])*(double_cad_array[id_1][4]-double_cad_array[id_1][1]) - (snap_cad_pos_y-double_cad_array[id_1][1])*(double_cad_array[id_1][3] - double_cad_array[id_1][0]);
            double startpoint_side =(double_cad_array[id_2][0]-double_cad_array[id_1][0])*(double_cad_array[id_1][4]-double_cad_array[id_1][1]) - (double_cad_array[id_2][1]-double_cad_array[id_1][1])*(double_cad_array[id_1][3] - double_cad_array[id_1][0]);
            double endpoint_side =(double_cad_array[id_2][3]-double_cad_array[id_1][0])*(double_cad_array[id_1][4]-double_cad_array[id_1][1]) - (double_cad_array[id_2][4]-double_cad_array[id_1][1])*(double_cad_array[id_1][3] - double_cad_array[id_1][0]);

            //source line :
            double trim_x_start_source = double_cad_array[id_2][0];
            double trim_y_start_source = double_cad_array[id_2][1];
            double trim_x_end_source   = double_cad_array[id_2][3];
            double trim_y_end_source   = double_cad_array[id_2][4];
            //boundary line :
            double trim_x_start_boundary = double_cad_array[id_1][0];
            double trim_y_start_boundary = double_cad_array[id_1][1];
            double trim_x_end_boundary   = double_cad_array[id_1][3];
            double trim_y_end_boundary   = double_cad_array[id_1][4];

            double trim_x_intersect = 0;
            double trim_y_intersect = 0;

            //source line :
            double delta_y0 = trim_y_end_source - trim_y_start_source;
            double delta_x0 = trim_x_start_source - trim_x_end_source;
            double c0 = delta_y0 * trim_x_start_source + delta_x0 * trim_y_start_source;
            //boundary line :
            double delta_y1 = trim_y_end_boundary - trim_y_start_boundary;
            double delta_x1 = trim_x_start_boundary - trim_x_end_boundary;
            double c1 = delta_y1 * trim_x_start_boundary + delta_x1 * trim_y_start_boundary;

            double determinant = delta_y0*delta_x1 - delta_y1*delta_x0;
            //qDebug() << "determinant is : " << determinant;

            if (determinant == 0) // The lines are parallel.
            {
                //qDebug() << "the lines are parallel";
            }
            else  {
                trim_x_intersect = (delta_x1*c0 - delta_x0*c1)/determinant;
                trim_y_intersect = (delta_y0*c1 - delta_y1*c0)/determinant;
            }

            if(trim_snapshot_side > 0 && startpoint_side > 0 ){ //startpoint trim
                double_cad_array[id_2][0] = trim_x_intersect; //x_start_intersect
                double_cad_array[id_2][1] = trim_y_intersect; //y_start_intersect

            }

            if(trim_snapshot_side < 0 && startpoint_side < 0 ){ //startpoint trim
                double_cad_array[id_2][0] = trim_x_intersect; //x_start_intersect
                double_cad_array[id_2][1] = trim_y_intersect; //y_start_intersect

            }

            if(trim_snapshot_side > 0 && endpoint_side > 0 ){ //endpoint trim
                double_cad_array[id_2][3] = trim_x_intersect; //x_start_intersect
                double_cad_array[id_2][4] = trim_y_intersect; //y_start_intersect

            }

            if(trim_snapshot_side < 0 && endpoint_side < 0 ){ //endpoint trim
                double_cad_array[id_2][3] = trim_x_intersect; //x_start_intersect
                double_cad_array[id_2][4] = trim_y_intersect; //y_start_intersect

            }

            QList<double> list = line_midpoint(double_cad_array[id_2][0],double_cad_array[id_2][1],double_cad_array[id_2][3],double_cad_array[id_2][4]);
            if(list.size()==2){
                double_cad_array[id_2][15]=list.at(0);
                double_cad_array[id_2][16]=list.at(1);
            } list.clear();
        }

        if(int_cad_array[id_1][0]==1 && int_cad_array[id_2][0]==3 ){ //line - arc intersection.. (boundary line is line..)

            //line - arc intersection..
            double x0 = double_cad_array[id_1][0];
            double y0 = double_cad_array[id_1][1];
            double x1 = double_cad_array[id_1][3];
            double y1 = double_cad_array[id_1][4];

            double cpx = double_cad_array[id_2][6];    //array target circle center x
            double cpy = double_cad_array[id_2][7];    //array target circle center y
            double radius = double_cad_array[id_2][9]; //array target circle radius
            double cx0 = double_cad_array[id_2][0];
            double cy0 = double_cad_array[id_2][1];
            double cx1 = double_cad_array[id_2][3];
            double cy1 = double_cad_array[id_2][4];

            double dx, dy, A, B, C, det, t;
            dx = x1 - x0;
            dy = y1 - y0;
            A = dx * dx + dy * dy;
            B = 2 * (dx * (x0 - cpx) + dy * (y0 - cpy));
            C = (x0 - cpx) * (x0 - cpx) + (y0 - cpy) * (y0 - cpy) - radius * radius;
            det = B * B - 4 * A * C;

            t = (-B + sqrt(det)) / (2 * A);
            double i_x0 = (x0 + t * dx);
            double i_y0 = (y0 + t * dy);

            t = (-B - sqrt(det)) / (2 * A);
            double i_x1 = (x0 + t * dx);
            double i_y1 = (y0 + t * dy);

            int clicked_side = side_d(x0,y0,x1,y1,x,y);
            int startpoint_side = side_d(x0,y0,x1,y1,cx0,cy0);
            int endpoint_side = side_d(x0,y0,x1,y1,cx1,cy1);

            //find closest intersecion..
            double c1 = sqrt(pow(x-i_x0,2) + pow(y-i_y0,2));
            double c2 = sqrt(pow(x-i_x1,2) + pow(y-i_y1,2));

            if(c1<c2){

                if(clicked_side==startpoint_side){
                    double_cad_array[id_2][0] = i_x0;
                    double_cad_array[id_2][1] = i_y0;
                }
                if(clicked_side==endpoint_side){
                    double_cad_array[id_2][3] = i_x0;
                    double_cad_array[id_2][4] = i_y0;
                }

            } else {

                if(clicked_side==startpoint_side){
                    double_cad_array[id_2][0] = i_x1;
                    double_cad_array[id_2][1] = i_y1;
                }
                if(clicked_side==endpoint_side){
                    double_cad_array[id_2][3] = i_x1;
                    double_cad_array[id_2][4] = i_y1;
                }
            }
            calculate_midpoint(id_2);
            update_angles(id_2);
        }

        if(int_cad_array[id_1][0]==3 && int_cad_array[id_2][0]==1){ //arc - line intersection.. (boundary line is arc.. )
            //arc -line intersection..
            double cpx = double_cad_array[id_1][6];
            double cpy = double_cad_array[id_1][7];
            double radius = double_cad_array[id_1][9];

            double x0 = double_cad_array[id_2][0];
            double y0 = double_cad_array[id_2][1];
            double x1 = double_cad_array[id_2][3];
            double y1 = double_cad_array[id_2][4];

            double dx, dy, A, B, C, det, t;
            dx = x1 - x0;
            dy = y1 - y0;
            A = dx * dx + dy * dy;
            B = 2 * (dx * (x0 - cpx) + dy * (y0 - cpy));
            C = (x0 - cpx) * (x0 - cpx) + (y0 - cpy) * (y0 - cpy) - radius * radius;
            det = B * B - 4 * A * C;

            t = (-B + sqrt(det)) / (2 * A);
            double i_x0 = (x0 + t * dx);
            double i_y0 = (y0 + t * dy);

            t = (-B - sqrt(det)) / (2 * A);
            double i_x1 = (x0 + t * dx);
            double i_y1 = (y0 + t * dy);

            //find closest solution..
            double c1 = sqrt(pow(x-i_x0,2) + pow(y-i_y0,2));
            double c2 = sqrt(pow(x-i_x1,2) + pow(y-i_y1,2));

            //To determine 'd' which side of the arc is clicked we use the radius..
            double radius_click = sqrt(pow(x-cpx,2)+pow(y-cpy,2));
            double d = 0;
            double d_line_start = 0;
            double d_line_end = 0;

            //if clicked radius < arc radius..
            if(radius_click < radius){
                d=1;
            } else { d=-1;}

            //if line start pos < arc radius..
            double radius_line_start = sqrt(pow(double_cad_array[id_2][0]-cpx,2)+pow(double_cad_array[id_2][1]-cpy,2));
            if(radius_line_start < radius){
                d_line_start=1;
            } else { d_line_start=-1;}

            //if line end pos < arc radius..
            double radius_line_end = sqrt(pow(double_cad_array[id_2][3]-cpx,2)+pow(double_cad_array[id_2][4]-cpy,2));
            if(radius_line_end < radius){
                d_line_end=1;
            } else { d_line_end=-1;}

            if(c1<c2){
                if(d<0 && d_line_start<0){
                    double_cad_array[id_2][0] = i_x0;
                    double_cad_array[id_2][1] = i_y0;

                }
                if(d<0 && d_line_end<0){
                    double_cad_array[id_2][3] = i_x0;
                    double_cad_array[id_2][4] = i_y0;

                }
                if(d>0 && d_line_start>0){
                    double_cad_array[id_2][0] = i_x0;
                    double_cad_array[id_2][1] = i_y0;

                }
                if(d>0 && d_line_end>0){
                    double_cad_array[id_2][3] = i_x0;
                    double_cad_array[id_2][4] = i_y0;

                }
            } else {
                if(d<0 && d_line_start<0){
                    double_cad_array[id_2][0] = i_x1;
                    double_cad_array[id_2][1] = i_y1;

                }
                if(d<0 && d_line_end<0){
                    double_cad_array[id_2][3] = i_x1;
                    double_cad_array[id_2][4] = i_y1;

                }
                if(d>0 && d_line_start>0){
                    double_cad_array[id_2][0] = i_x1;
                    double_cad_array[id_2][1] = i_y1;

                }
                if(d>0 && d_line_end>0){
                    double_cad_array[id_2][3] = i_x1;
                    double_cad_array[id_2][4] = i_y1;

                }
            }
        }

        if(int_cad_array[id_1][0]==3 && int_cad_array[id_2][0]==3){ //arc - arc intersection.. (boundary line is id_1..)
            //arc-arc intersection..
            double cx0 = double_cad_array[id_1][6];
            double cy0 = double_cad_array[id_1][7];
            double radius0 = double_cad_array[id_1][9];
            double cx1 = double_cad_array[id_2][6];
            double cy1 = double_cad_array[id_2][7];
            double radius1 = double_cad_array[id_2][9];

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
                double dist_p1 = sqrt(pow(x-px1,2)+pow(y-py1,2));
                double dist_p2 = sqrt(pow(x-px2,2)+pow(y-py2,2));

                double d_radius_boundary = sqrt(pow(x-cx0,2)+pow(y-cy0,2));
                double d;
                double d_start;
                double d_end;

                if(d_radius_boundary<radius0){
                    d=1;
                } else {d=-1;}

                double radius_start = sqrt(pow(double_cad_array[id_2][0]-cx0,2)+pow(double_cad_array[id_2][1]-cy0,2));
                if(radius_start<radius0){
                    d_start = 1;
                } else {d_start = -1;}

                double radius_end = sqrt(pow(double_cad_array[id_2][3]-cx0,2)+pow(double_cad_array[id_2][4]-cy0,2));
                if(radius_end<radius0){
                    d_end = 1;
                } else {d_end = -1;}

                //qDebug()<< "d :" << d;
                //qDebug()<< "d start :" << d_start;
                //qDebug()<< "d end :" << d_end;

                if(dist_p1<dist_p2){
                    if(d<0 && d_start<0){
                        double_cad_array[id_2][0] = px1;
                        double_cad_array[id_2][1] = py1;
                        update_angles(id_2);
                    }
                    if(d<0 && d_end<0){
                        double_cad_array[id_2][3] = px1;
                        double_cad_array[id_2][4] = py1;
                        update_angles(id_2);
                    }
                    if(d>0 && d_start>0){
                        double_cad_array[id_2][0] = px1;
                        double_cad_array[id_2][1] = py1;
                        update_angles(id_2);
                    }
                    if(d>0 && d_end>0){
                        double_cad_array[id_2][3] = px1;
                        double_cad_array[id_2][4] = py1;
                        update_angles(id_2);
                    }
                } else {
                    if(d<0 && d_start<0){
                        double_cad_array[id_2][0] = px2;
                        double_cad_array[id_2][1] = py2;
                        update_angles(id_2);
                    }
                    if(d<0 && d_end<0){
                        double_cad_array[id_2][3] = px2;
                        double_cad_array[id_2][4] = py2;
                        update_angles(id_2);
                    }
                    if(d>0 && d_start>0){
                        double_cad_array[id_2][0] = px2;
                        double_cad_array[id_2][1] = py2;
                        update_angles(id_2);
                    }
                    if(d>0 && d_end>0){
                        double_cad_array[id_2][3] = px2;
                        double_cad_array[id_2][4] = py2;
                        update_angles(id_2);
                    }
                }
                calculate_midpoint(id_2);
                update_angles(id_2);
            }
        }

        if(int_cad_array[id_1][0]==2 && int_cad_array[id_2][0]==1){ //circle - line intersection.. (boundary line is circle.. )
            //circle-line intersection..
            double cpx = double_cad_array[id_1][6];
            double cpy = double_cad_array[id_1][7];
            double radius = double_cad_array[id_1][9];

            double x0 = double_cad_array[id_2][0];
            double y0 = double_cad_array[id_2][1];
            double x1 = double_cad_array[id_2][3]; double temp_x_end = double_cad_array[id_2][3];
            double y1 = double_cad_array[id_2][4]; double temp_y_end = double_cad_array[id_2][4];

            double dx, dy, A, B, C, det, t;
            dx = x1 - x0;
            dy = y1 - y0;
            A = dx * dx + dy * dy;
            B = 2 * (dx * (x0 - cpx) + dy * (y0 - cpy));
            C = (x0 - cpx) * (x0 - cpx) + (y0 - cpy) * (y0 - cpy) - radius * radius;
            det = B * B - 4 * A * C;

            t = (-B + sqrt(det)) / (2 * A);
            double i_x0 = (x0 + t * dx);
            double i_y0 = (y0 + t * dy);

            t = (-B - sqrt(det)) / (2 * A);
            double i_x1 = (x0 + t * dx);
            double i_y1 = (y0 + t * dy);

            //find closest solution..
            double c1 = sqrt(pow(x-i_x0,2) + pow(y-i_y0,2));
            double c2 = sqrt(pow(x-i_x1,2) + pow(y-i_y1,2));

            double radius_click = sqrt(pow(x-cpx,2)+pow(y-cpy,2));
            if(radius_click<radius){
                //qDebug()<< "transform into 2 seperate lines..";

                //look closest by intersection for existing startpoint..
                double dist_0 = sqrt(pow(double_cad_array[id_2][0]-i_x0,2)+pow(double_cad_array[id_2][1]-i_y0,2));
                double dist_1 = sqrt(pow(double_cad_array[id_2][0]-i_x1,2)+pow(double_cad_array[id_2][1]-i_y1,2));
                if(dist_0 < dist_1){
                    //modify line endpoint..
                    double_cad_array[id_2][3] = i_x0;
                    double_cad_array[id_2][4] = i_y0;

                    //create new line..
                    int_cad_array[cad_counter][0] = 1; //id line
                    int_cad_array[cad_counter][5] = int_cad_array[id_2][5]; //linetype
                    double_cad_array[cad_counter][56] = double_cad_array[id_2][56]; //colors
                    double_cad_array[cad_counter][57] = double_cad_array[id_2][57];
                    double_cad_array[cad_counter][58] = double_cad_array[id_2][58];
                    double_cad_array[cad_counter][59] = double_cad_array[id_2][59];
                    double_cad_array[cad_counter][18] = double_cad_array[id_2][18]; //scale
                    double_cad_array[cad_counter][19] = double_cad_array[id_2][19]; //linewidth
                    double_cad_array[cad_counter][0] = i_x1;
                    double_cad_array[cad_counter][1] = i_y1;
                    double_cad_array[cad_counter][3] = temp_x_end;
                    double_cad_array[cad_counter][4] = temp_y_end;
                    cad_counter++;

                } else {
                    //modify line endpoint..
                    double_cad_array[id_2][3] = i_x1;
                    double_cad_array[id_2][4] = i_y1;

                    //create new line..
                    int_cad_array[cad_counter][0] = 1; //id line
                    int_cad_array[cad_counter][5] = int_cad_array[id_2][5]; //linetype
                    double_cad_array[cad_counter][56] = double_cad_array[id_2][56]; //colors
                    double_cad_array[cad_counter][57] = double_cad_array[id_2][57];
                    double_cad_array[cad_counter][58] = double_cad_array[id_2][58];
                    double_cad_array[cad_counter][59] = double_cad_array[id_2][59];
                    double_cad_array[cad_counter][18] = double_cad_array[id_2][18]; //scale
                    double_cad_array[cad_counter][19] = double_cad_array[id_2][19]; //linewidth
                    double_cad_array[cad_counter][0] = i_x0;
                    double_cad_array[cad_counter][1] = i_y0;
                    double_cad_array[cad_counter][3] = temp_x_end;
                    double_cad_array[cad_counter][4] = temp_y_end;
                    cad_counter++;

                }




            } else if(c1<c2){

                //is start or end closest to pxy?
                double d_start = sqrt(pow(double_cad_array[id_2][0]-x,2)+pow(double_cad_array[id_2][1]-y,2));
                double d_end = sqrt(pow(double_cad_array[id_2][3]-x,2)+pow(double_cad_array[id_2][4]-y,2));

                if(d_start<d_end){
                    double_cad_array[id_2][0] = i_x0;
                    double_cad_array[id_2][1] = i_y0;
                } else {
                    double_cad_array[id_2][3] = i_x0;
                    double_cad_array[id_2][4] = i_y0;
                }
            } else {

                //is start or end closest to pxy?
                double d_start = sqrt(pow(double_cad_array[id_2][0]-x,2)+pow(double_cad_array[id_2][1]-y,2));
                double d_end = sqrt(pow(double_cad_array[id_2][3]-x,2)+pow(double_cad_array[id_2][4]-y,2));

                if(d_start<d_end){
                    double_cad_array[id_2][0] = i_x1;
                    double_cad_array[id_2][1] = i_y1;
                } else {
                    double_cad_array[id_2][3] = i_x1;
                    double_cad_array[id_2][4] = i_y1;
                }
            }
        }

        no_highlight();
        mode_trim = 0;
        click = 0;
        key_enter = 0;
        int_key = 0 ;
        mode_nearest = 0;
        id_1 = -1;
        id_2 = -1;
        messagebox_text = "<b><i>mode trim </i></b> enter for repeat or Esc for cancel";
    }
}

QList<double> trim::line_midpoint(double x0, double y0, double x1, double y1)
{
    QList<double> list;
    list.append((x0+x1)/2);
    list.append((y0+y1)/2);
    return list;
}

void trim::calculate_midpoint(int i)
{
    double x0 = double_cad_array[i][0]; //startpoint
    double y0 = double_cad_array[i][1];
    double x1 = double_cad_array[i][3]; //endpoint
    double y1 = double_cad_array[i][4];
    double cx = double_cad_array[i][6];
    double cy = double_cad_array[i][7]; //center
    double radius = double_cad_array[i][9];
    double xmid = 0;
    double ymid = 0;

    //midpoint at line..
    xmid = (x0+x1)/2; qDebug()<<"xmid :" << xmid;
    ymid = (y0+y1)/2; qDebug()<<"ymid :" << ymid;
    //angle midpoint - arc center..
    double angle_mid = 180/M_PI*atan2(ymid-cy, xmid-cx);  qDebug()<<"angle_mid :" << angle_mid;
    double angle_mid_rad = atan2(ymid-cy, xmid-cx);
    //to coordinate..
    QList<double> list =rotate_point(cx,cy,angle_mid_rad,radius,0);

    if(list.size()==2){
        double_cad_array[i][15] = list.at(0); qDebug()<<"midpoint arc x :" << list.at(0);
        double_cad_array[i][16] = list.at(1); qDebug()<<"midpoint arc y :" << list.at(1);
    }
    list.clear();
}

QList<double> trim::rotate_point(double cx ,double cy, double angle, double x, double y)
{
  QList<double> list;
  // rotate point
  //x=ratius
  //y=0
  double xnew = x * cos(angle) - y * sin(angle);
  double ynew = x * sin(angle) + y * cos(angle);
  // translate point back:
  xnew=xnew+cx;
  ynew=ynew+cy;
  list.append(xnew);
  list.append(ynew);
  return list;
}


void trim::update_angles(int i)
{
    //only to determine d.. g2 or g3..
    double x0 = double_cad_array[i][0]; //startpoint
    double y0 = double_cad_array[i][1];
    double x1 = double_cad_array[i][15]; //midpoint circumfence
    double y1 = double_cad_array[i][16];
    double x2 = double_cad_array[i][3];
    double y2 = double_cad_array[i][4]; //endpoint
    double cx = double_cad_array[i][6];
    double cy = double_cad_array[i][7]; //center

    double d=(x2-x0)*(y1-y0)-(y2-y0)*(x1-x0);

    if(d>0){ //g2..
        double_cad_array[i][11] = 180/M_PI*atan2(y2-cy, x2-cx);   myqDebug()<<"start angle : " << double_cad_array[i][11];
        double_cad_array[i][12] = 180/M_PI*atan2(y0-cy, x0-cx);   myqDebug()<<"end angle   : " << double_cad_array[i][12];
    }
    if(d<0){ //g3..
        double_cad_array[i][11] = 180/M_PI*atan2(y0-cy, x0-cx);   myqDebug()<<"start angle : " << double_cad_array[i][11];
        double_cad_array[i][12] = 180/M_PI*atan2(y2-cy, x2-cx);   myqDebug()<<"end angle   : " << double_cad_array[i][12];
    }

}

int trim::side_d(double x0, double y0, double x1, double y1, double px, double py) //line x0,y0, x1,y1, point px,py..
{
    double d=(px-x0)*(y1-y0)-(py-y0)*(x1-x0);
    if(d>0){
        return 1;
    }
    if(d<0){
        return -1;
    }
}

//opengl matrix :
//                90
//                |
//                |
//     135        |       45
//                |
//                |
//180----------------------------0
//                |
//                |
//                |
//     -135       |       -45
//                |
//                -90





























