#include "fillet.h"
#include <core_functions/variables.h>
#include <math.h>
#include <display_functions/no_highlight.h>
#include <display_functions/object_select_line_startpoint.h>
#include <display_functions/object_select_line_midpoint.h>
#include <display_functions/object_select_line_endpoint.h>
#include <display_functions/object_select_line_perpendicular.h>
#include <display_functions/object_select_line_nearest.h>
#include <display_functions/object_select_line_tangent_arc.h>
#include <display_functions/object_select_line_tangent_circle.h>
#include <display_functions/object_select_centerpoint.h>
#include <display_functions/object_select_circle_4p_intersection.h>
#include <display_functions/object_select_circle_nearest.h>
#include <display_functions/object_select_arc_nearest.h>
#include <display_functions/object_select_ellipse_nearest.h>
#include <display_functions/object_select_hermite_spline_nearest.h>
#include <display_functions/object_select_bezier_curve_nearest.h>
#include <display_functions/simple_line_select.h>

fillet::fillet()
{
    //radius edge..
    //initialiation..
    snap_cad_pos_x = mouse_cad_pos_x;
    snap_cad_pos_y = mouse_cad_pos_y;
    snap_cad_pos_z = mouse_cad_pos_z;

    //object_select_line_nearest(0);
    simple_line_select();

    if(click == 0){

        entry_focus = 1;
        fillet_mm = double_user_input; 
        messagebox_text = "<b><i>mode fillet</i></b> input fillet value <br>input value : " + QString(QString::number(double_user_input)) + ", click first corner.. ";

        id_1 = -1;
        id_2 = -1;
    }

    if(click == 1){
        if(key_enter){click = 0;}

        messagebox_text = "<b><i>mode fillet </i></b> click second corner..";
        id_1 = select_id; //see line_nearest class..

        //dist id_1 startpoint to mouse pointer..
        id_1_mouse_dist_to_startpoint = sqrt(pow(double_cad_array[id_1][0]-mouse_cad_pos_x,2)+pow(double_cad_array[id_1][1]-mouse_cad_pos_y,2));
        //qDebug() << "id_1_mouse_dist_to_startpoint " << id_1_mouse_dist_to_startpoint;

        id_1_mouse_dist_to_endpoint = sqrt(pow(double_cad_array[id_1][3]-mouse_cad_pos_x,2)+pow(double_cad_array[id_1][4]-mouse_cad_pos_y,2));
        //qDebug() << "id_1_mouse_dist_to_endpoint " << id_1_mouse_dist_to_endpoint ;

        click = 2;

    }

    if(click == 3){
        if(key_enter){click = 0;}

        messagebox_text = "<b><i>mode fillet </i></b> enter for repeat or Esc for cancel";
        id_2 = select_id;

        id_2_mouse_dist_to_startpoint = sqrt(pow(double_cad_array[id_2][0]-mouse_cad_pos_x,2)+pow(double_cad_array[id_2][1]-mouse_cad_pos_y,2));
        //qDebug() << "id_2_mouse_dist_to_startpoint " << id_2_mouse_dist_to_startpoint ;

        id_2_mouse_dist_to_endpoint = sqrt(pow(double_cad_array[id_2][3]-mouse_cad_pos_x,2)+pow(double_cad_array[id_2][4]-mouse_cad_pos_y,2));
        //qDebug() << "id_2_mouse_dist_to_endpoint " << id_2_mouse_dist_to_endpoint ;

        click = 4;
    }

    if(click == 4){
         if(key_enter){click = 0;}

        //calculate wich corners are nearest to the mouse pointer..

        if(id_1_mouse_dist_to_startpoint < id_1_mouse_dist_to_endpoint){
            id_1_chamfer_startpoint = 1;
            //qDebug() << "id_1 fillet at startpoint..";
        }
        if(id_1_mouse_dist_to_startpoint > id_1_mouse_dist_to_endpoint){
            id_1_chamfer_startpoint = 0;
            //qDebug() << "id_1 fillet at endpoint..";
        }
        if(id_2_mouse_dist_to_startpoint < id_2_mouse_dist_to_endpoint){
            id_2_chamfer_startpoint = 1;
            //qDebug() << "id_2 fillet at startpoint..";
        }
        if(id_2_mouse_dist_to_startpoint > id_2_mouse_dist_to_endpoint){
            id_2_chamfer_startpoint = 0;
            //qDebug() << "id_2 fillet at endpoint..";
        }

        //make the corner closed if open or drawed trough.... initial value : chamfer_mm = 0 mm. Intersect corner..

        //line - line intersection..
        //line 1 to compare :
        double startpoint_x0 = double_cad_array[id_1][0];
        double startpoint_y0 = double_cad_array[id_1][1];
        double endpoint_x0 = double_cad_array[id_1][3];
        double endpoint_y0 = double_cad_array[id_1][4];

        //line 2 to compare :
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

            double x = (delta_x1*c0 - delta_x0*c1)/determinant;
            double y = (delta_y0*c1 - delta_y1*c0)/determinant;
            //qDebug() << " intersection point is x : " << x << " y : " << y;

            //write the new line-line intersection to the array....

            double start_angle = 0;
            double end_angle = 0;

            //extend corner to intersection..
            if(id_1_chamfer_startpoint == 1){
                double_cad_array[id_1][0] = x;
                double_cad_array[id_1][1] = y;
                start_angle = 180/M_PI*atan2(double_cad_array[id_1][4]- y, double_cad_array[id_1][3] - x);
            }
            if(id_1_chamfer_startpoint == 0){
                double_cad_array[id_1][3] = x;
                double_cad_array[id_1][4] = y;
                start_angle = 180/M_PI*atan2(double_cad_array[id_1][1]- y, double_cad_array[id_1][0] - x);
            }
            if(id_2_chamfer_startpoint == 1){
                double_cad_array[id_2][0] = x;
                double_cad_array[id_2][1] = y;
                end_angle = 180/M_PI*atan2(double_cad_array[id_2][4]- y, double_cad_array[id_2][3] - x);
            }
            if(id_2_chamfer_startpoint == 0){
                double_cad_array[id_2][3] = x;
                double_cad_array[id_2][4] = y;
                end_angle = 180/M_PI*atan2(double_cad_array[id_2][1]- y, double_cad_array[id_2][0] - x);
            }

            //calculate corner radius and calculate chamfer dist..
            //qDebug() << "start angle : " << start_angle;
            //qDebug() << "end angle : " << end_angle;
            //qDebug() << "angle : " << start_angle-end_angle;

            double half_angle = (end_angle - start_angle)/2; //needed for corner tangent calculation..
            if(half_angle < 0){half_angle = half_angle *-1;}

            //qDebug() << "half angle : " << half_angle;

            double chamfer_radius = fillet_mm / tan(half_angle * M_PI/180) ;
            //qDebug() << "output : " << chamfer_radius; //checked ok..

            double corner_circle_radius = fillet_mm / sin(half_angle * M_PI/180) ;
            //qDebug() << "corner_circle_radius : " << corner_circle_radius; //checked ok..

            //example 22.5 degrees, output tan = 0.4142 is oke.
            //double tangens = tan(22.5 * M_PI/180);
            //qDebug() << "tangens 22.5 is :" << tangens;

            //intersection chamfer radius.. id_1 & id_2..

            //id_1 cirlce -> line intersection..
            double circle_center_x = x;
            double circle_center_y = y;
            double radius = chamfer_radius;

            double line_x1 = double_cad_array[id_1][0];
            double line_y1 = double_cad_array[id_1][1];
            double line_x2 = double_cad_array[id_1][3];
            double line_y2 = double_cad_array[id_1][4];

            double dx, dy, A, B, C, det, t;

            dx = line_x2 - line_x1;
            dy = line_y2 - line_y1;

            A = dx * dx + dy * dy;
            B = 2 * (dx * (line_x1 - circle_center_x) + dy * (line_y1 - circle_center_y));
            C = (line_x1 - circle_center_x) * (line_x1 - circle_center_x) + (line_y1 - circle_center_y) * (line_y1 - circle_center_y) - radius * radius;

            det = B * B - 4 * A * C;
            if ((A <= 0.0000001) || (det < 0))
            {

                //qDebug() << "No real solutions";

            }
            else if (det == 0)
            {

                t = -B / (2 * A);
                //double intersection_x1 = (line_x1 + t * dx);
                //double intersection_y1 = (line_y1 + t * dy);

                //qDebug() << "One solution x1 :" << intersection_x1 << "y1 :" << intersection_y1;
            }
            else
            {

                t = (-B + sqrt(det)) / (2 * A);
                double intersection_x1 = (line_x1 + t * dx);
                double intersection_y1 = (line_y1 + t * dy);

                t = (-B - sqrt(det)) / (2 * A);
                double intersection_x2 = (line_x1 + t * dx);
                double intersection_y2 = (line_y1 + t * dy);

                //qDebug() << "Two solutions x1 :" << intersection_x1 << "y1 :" << intersection_y1;
                //qDebug() << "Two solutions x2 :" << intersection_x2 << "y2 :" << intersection_y2;

                //calculate closest point..

                if(id_1_chamfer_startpoint == 1){
                    //compare opposite line point with closest intersection point.
                    double dist_1 = sqrt(pow(double_cad_array[id_1][3]-intersection_x1, 2) + pow(double_cad_array[id_1][4]-intersection_y1, 2));
                    double dist_2 = sqrt(pow(double_cad_array[id_1][3]-intersection_x2, 2) + pow(double_cad_array[id_1][4]-intersection_y2, 2));
                    if(dist_1 < dist_2){
                        double_cad_array[id_1][0] = intersection_x1;
                        double_cad_array[id_1][1] = intersection_y1;
                    } else {
                        double_cad_array[id_1][0] = intersection_x2;
                        double_cad_array[id_1][1] = intersection_y2;
                    }
                }

                if(id_1_chamfer_startpoint == 0){
                    //compare opposite line point with closest intersection point.
                    double dist_1 = sqrt(pow(double_cad_array[id_1][0]-intersection_x1, 2) + pow(double_cad_array[id_1][1]-intersection_y1, 2));
                    double dist_2 = sqrt(pow(double_cad_array[id_1][0]-intersection_x2, 2) + pow(double_cad_array[id_1][1]-intersection_y2, 2));
                    if(dist_1 < dist_2){
                        double_cad_array[id_1][3] = intersection_x1;
                        double_cad_array[id_1][4] = intersection_y1;
                    } else {
                        double_cad_array[id_1][3] = intersection_x2;
                        double_cad_array[id_1][4] = intersection_y2;
                    }
                }
            }

            //id_2 cirlce -> line intersection..
            circle_center_x = x;
            circle_center_y = y;
            radius = chamfer_radius;

            line_x1 = double_cad_array[id_2][0];
            line_y1 = double_cad_array[id_2][1];
            line_x2 = double_cad_array[id_2][3];
            line_y2 = double_cad_array[id_2][4];


            dx = line_x2 - line_x1;
            dy = line_y2 - line_y1;

            A = dx * dx + dy * dy;
            B = 2 * (dx * (line_x1 - circle_center_x) + dy * (line_y1 - circle_center_y));
            C = (line_x1 - circle_center_x) * (line_x1 - circle_center_x) + (line_y1 - circle_center_y) * (line_y1 - circle_center_y) - radius * radius;

            det = B * B - 4 * A * C;
            if ((A <= 0.0000001) || (det < 0))
            {

                //qDebug() << "No real solutions";

            }
            else if (det == 0)
            {

                t = -B / (2 * A);
                //double intersection_x1 = (line_x1 + t * dx);
                //double intersection_y1 = (line_y1 + t * dy);

                //qDebug() << "One solution x1 :" << intersection_x1 << "y1 :" << intersection_y1;
            }
            else
            {

                t = (-B + sqrt(det)) / (2 * A);
                double intersection_x1 = (line_x1 + t * dx);
                double intersection_y1 = (line_y1 + t * dy);

                t = (-B - sqrt(det)) / (2 * A);
                double intersection_x2 = (line_x1 + t * dx);
                double intersection_y2 = (line_y1 + t * dy);

                //qDebug() << "Two solutions x1 :" << intersection_x1 << "y1 :" << intersection_y1;
                //qDebug() << "Two solutions x2 :" << intersection_x2 << "y2 :" << intersection_y2;

                //calculate closest point..

                if(id_2_chamfer_startpoint == 1){
                    //compare opposite line point with closest intersection point.
                    double dist_1 = sqrt(pow(double_cad_array[id_2][3]-intersection_x1, 2) + pow(double_cad_array[id_2][4]-intersection_y1, 2));
                    double dist_2 = sqrt(pow(double_cad_array[id_2][3]-intersection_x2, 2) + pow(double_cad_array[id_2][4]-intersection_y2, 2));
                    if(dist_1 < dist_2){
                        double_cad_array[id_2][0] = intersection_x1;
                        double_cad_array[id_2][1] = intersection_y1;
                    } else {
                        double_cad_array[id_2][0] = intersection_x2;
                        double_cad_array[id_2][1] = intersection_y2;
                    }
                }

                if(id_2_chamfer_startpoint == 0){
                    //compare opposite line point with closest intersection point.
                    double dist_1 = sqrt(pow(double_cad_array[id_2][0]-intersection_x1, 2) + pow(double_cad_array[id_2][1]-intersection_y1, 2));
                    double dist_2 = sqrt(pow(double_cad_array[id_2][0]-intersection_x2, 2) + pow(double_cad_array[id_2][1]-intersection_y2, 2));
                    if(dist_1 < dist_2){
                        double_cad_array[id_2][3] = intersection_x1;
                        double_cad_array[id_2][4] = intersection_y1;
                    } else {
                        double_cad_array[id_2][3] = intersection_x2;
                        double_cad_array[id_2][4] = intersection_y2;
                    }
                }
            }


            //fillets are done at this stage. Checked okey..


            //calculate fillet circle center point..
            //middle line..
            //x, y = intersection point corner when fillet = 0;
            //second line point ..
            double p1x = 0;
            double p1y = 0;
            double p2x = 0;
            double p2y = 0;
            double cpx = 0;
            double cpy = 0;

            if(id_1_chamfer_startpoint == 1){
                p1x = double_cad_array[id_1][0];
                p1y = double_cad_array[id_1][1];
            }
            if(id_1_chamfer_startpoint == 0){
                p1x = double_cad_array[id_1][3];
                p1y = double_cad_array[id_1][4];
            }
            if(id_2_chamfer_startpoint == 1){
                p2x = double_cad_array[id_2][0];
                p2y = double_cad_array[id_2][1];
            }
            if(id_2_chamfer_startpoint == 0){
                p2x = double_cad_array[id_2][3];
                p2y = double_cad_array[id_2][4];
            }

            //midpoint to create fillet centerline..
            cpx = (p1x + p2x) / 2; //checked okey..
            cpy = (p1y + p2y) / 2; //checked okey..
            //qDebug() << "point for creating middle line x : " << cpx << " y : "<< cpy;

            //arc centerpoint..
            double arc_cpx = 0;
            double arc_cpy = 0;

            //line - circle intersection corner to middle corner line "corner_circle_radius = radius"
            circle_center_x = x;
            circle_center_y = y;
            radius = corner_circle_radius;

            line_x1 = x; //corner
            line_y1 = y;
            line_x2 = cpx; //middle line
            line_y2 = cpy;

            dx = line_x2 - line_x1;
            dy = line_y2 - line_y1;

            A = dx * dx + dy * dy;
            B = 2 * (dx * (line_x1 - circle_center_x) + dy * (line_y1 - circle_center_y));
            C = (line_x1 - circle_center_x) * (line_x1 - circle_center_x) + (line_y1 - circle_center_y) * (line_y1 - circle_center_y) - radius * radius;

            det = B * B - 4 * A * C;
            if ((A <= 0.0000001) || (det < 0))
            {

                //qDebug() << "No real solutions";

            }
            else if (det == 0)
            {

                t = -B / (2 * A);
                //double intersection_x1 = (line_x1 + t * dx);
                //double intersection_y1 = (line_y1 + t * dy);

                //qDebug() << "One solution x1 :" << intersection_x1 << "y1 :" << intersection_y1;
            }
            else
            {
                t = (-B + sqrt(det)) / (2 * A);
                double intersection_x1 = (line_x1 + t * dx);
                double intersection_y1 = (line_y1 + t * dy);

                t = (-B - sqrt(det)) / (2 * A);
                double intersection_x2 = (line_x1 + t * dx);
                double intersection_y2 = (line_y1 + t * dy);

                //qDebug() << "Two solutions x1 :" << intersection_x1 << "y1 :" << intersection_y1;
                //qDebug() << "Two solutions x2 :" << intersection_x2 << "y2 :" << intersection_y2;

                //compare opposite line point with closest intersection point.
                double dist_1 = sqrt(pow(cpx-intersection_x1, 2) + pow(cpy-intersection_y1, 2));
                double dist_2 = sqrt(pow(cpx-intersection_x2, 2) + pow(cpy-intersection_y2, 2));
                if(dist_1 < dist_2){
                    arc_cpx = intersection_x1;
                    arc_cpy = intersection_y1;
                } else {
                    arc_cpx  = intersection_x2;
                    arc_cpy  = intersection_y2;
                }
                //qDebug() << "arc cpx : " << arc_cpx;
                //qDebug() << "arc cpy : " << arc_cpy;
            }

            //draw arc from centerpoint arc_cpx, arc_cpy, radius fillet_mm
            //startpoint arc..
            //endpoint arc..
            //write the chamfer line..
            int_cad_array[cad_counter][0] = 3; //id arc
            int_cad_array[cad_counter][5] = current_linetype;
            double_cad_array[cad_counter][18] = current_linetype_scale;
            double_cad_array[cad_counter][19] = current_linewidth;

            double_cad_array[cad_counter][56] = current_gui_color_red_gl;
            double_cad_array[cad_counter][57] = current_gui_color_green_gl;
            double_cad_array[cad_counter][58] = current_gui_color_blue_gl;
            double_cad_array[cad_counter][59] = current_gui_color_alpha_gl;

            double_cad_array[cad_counter][6] = arc_cpx;
            double_cad_array[cad_counter][7] = arc_cpy;
            double_cad_array[cad_counter][9] = fillet_mm;

            //formula if arc is cw or ccw.. this is nice..
            //To determine which side of the line from A=(x1,y1) to B=(x2,y2) a point P=(x,y) falls on you need to compute the value:-
            //d=(x−x1)(y2−y1)−(y−y1)(x2−x1)
            //If d<0 then the point lies on one side of the line, and if d>0 then it lies on the other side. If d=0 then the point lies exactly line.

            double xp = arc_cpx;
            double yp = arc_cpy;
            double x1 = p1x;
            double y1 = p1y;
            double x2 = p2x;
            double y2 = p2y;
            double d = ((xp-x1)*(y2-y1))-((yp-y1)*(x2-x1));
            //qDebug() << "d :" << d;

            if(d > 0){
                double_cad_array[cad_counter][11] = 180/M_PI*atan2(p2y-arc_cpy, p2x-arc_cpx);    //start angle g2
                double_cad_array[cad_counter][12] = 180/M_PI*atan2(p1y-arc_cpy, p1x-arc_cpx);    //end angle g2

                double_cad_array[cad_counter][0] = p1x;
                double_cad_array[cad_counter][1] = p1y;
                double_cad_array[cad_counter][3] = p2x;
                double_cad_array[cad_counter][4] = p2y;

                redefine_arc_cw(cad_counter);
            }

            if(d < 0){
                double_cad_array[cad_counter][11] = 180/M_PI*atan2(p1y-arc_cpy, p1x-arc_cpx);    //start angle g2
                double_cad_array[cad_counter][12] = 180/M_PI*atan2(p2y-arc_cpy, p2x-arc_cpx);    //end angle g2

                double_cad_array[cad_counter][0] = p1x;
                double_cad_array[cad_counter][1] = p1y;
                double_cad_array[cad_counter][3] = p2x;
                double_cad_array[cad_counter][4] = p2y;

                redefine_arc_ccw(cad_counter);
            }

            cad_counter++; //write the new line to the cad_counter..

            //end function ..
            click = 5;
            no_highlight();
            id_1 = -1;
            id_2 = -1;
            select_id = -1;
            entry_focus = 0;
        }
    }

    if(click >= 5 && key_enter){
        click = 0; //repeat function..
    }
}

void fillet::redefine_arc_cw(int i){

    double X1 = double_cad_array[i][0]; //qDebug() << "X1: " << X1;
    double Y1 = double_cad_array[i][1]; //qDebug() << "Y1: " << Y1;
    double Z1 = double_cad_array[i][2];
    double X3 = double_cad_array[i][3]; //qDebug() << "X3: " << X3;
    double Y3 = double_cad_array[i][4]; //qDebug() << "Y3: " << Y3;
    double Z3 = double_cad_array[i][5];
    double x_center = double_cad_array[i][6]; //qDebug() << "x_center " << x_center;
    double y_center = double_cad_array[i][7]; //qDebug() << "y_center " << y_center;
    double radius =  double_cad_array[i][9];

    //calculate arc midpoint..
    //calculate arc midpoint..
    double radian_start = atan2(Y3-y_center, X3-x_center); //qDebug() << "radian_start : " << radian_start;
    double radian_end = atan2(Y1-y_center, X1-x_center);   //qDebug() << "radian_end : " << radian_end;
    if (radian_end < radian_start){  //this to avoid the start angle is bigger then the end angle value
        radian_end += 2*M_PI;
    }
    double radian_mid = (radian_start+radian_end)/2;       //qDebug() << "radian_mid : " << radian_mid;
    double rotate_x = cos(radian_mid)* radius - sin(radian_mid) * 0;
    double rotate_y = sin(radian_mid)* radius + cos(radian_mid) * 0;
    double_cad_array[i][15] = rotate_x + double_cad_array[i][6]; //qDebug() << "arc midpoint x : " << double_cad_array[i][15];
    double_cad_array[i][16] = rotate_y + double_cad_array[i][7]; //qDebug() << "arc midpoint y : " << double_cad_array[i][16];
}

void fillet::redefine_arc_ccw(int i){

    double X1 = double_cad_array[i][0]; //qDebug() << "X1: " << X1;
    double Y1 = double_cad_array[i][1]; //qDebug() << "Y1: " << Y1;
    double Z1 = double_cad_array[i][2];
    double X3 = double_cad_array[i][3]; //qDebug() << "X3: " << X3;
    double Y3 = double_cad_array[i][4]; //qDebug() << "Y3: " << Y3;
    double Z3 = double_cad_array[i][5];
    double x_center = double_cad_array[i][6]; //qDebug() << "x_center " << x_center;
    double y_center = double_cad_array[i][7]; //qDebug() << "y_center " << y_center;
    double radius =  double_cad_array[i][9];

    //calculate arc midpoint..
    //calculate arc midpoint..
    double radian_start = atan2(Y1-y_center, X1-x_center); //qDebug() << "radian_start : " << radian_start;
    double radian_end = atan2(Y3-y_center, X3-x_center);   //qDebug() << "radian_end : " << radian_end;
    if (radian_end < radian_start){  //this to avoid the start angle is bigger then the end angle value
        radian_end += 2*M_PI;
    }
    double radian_mid = (radian_start+radian_end)/2;       //qDebug() << "radian_mid : " << radian_mid;
    double rotate_x = cos(radian_mid)* radius - sin(radian_mid) * 0;
    double rotate_y = sin(radian_mid)* radius + cos(radian_mid) * 0;
    double_cad_array[i][15] = rotate_x + double_cad_array[i][6]; //qDebug() << "arc midpoint x : " << double_cad_array[i][15];
    double_cad_array[i][16] = rotate_y + double_cad_array[i][7]; //qDebug() << "arc midpoint y : " << double_cad_array[i][16];
}
























