#include "chamfer.h"
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

chamfer::chamfer()
{
    //line edge
    //initialiation..
    snap_cad_pos_x = mouse_cad_pos_x;
    snap_cad_pos_y = mouse_cad_pos_y;
    snap_cad_pos_z = mouse_cad_pos_z;

    //overwrite initialisation if we spot a snap somewhere..
    //object_select_line_startpoint();
    //object_select_line_midpoint();
    //object_select_line_endpoint();
    //object_select_centerpoint();
    //object_select_line_nearest(0);
    simple_line_select();
    //object_select_line_perpendicular();
    //object_select_arc_nearest(0);
    //object_select_circle_nearest(0);
    //object_select_circle_4p_intersection();
    //object_select_line_tangent_arc();
    //object_select_line_tangent_circle();
    //object_select_ellipse_nearest(0);
    //object_select_hermite_spline_nearest(0);
    //object_select_bezier_curve_nearest(0);


    if(click == 0){

        entry_focus = 1;
        chamfer_mm = double_user_input;
        messagebox_text = "<b><i>mode chamfer</i></b> input chamfer value <br>input value : " + QString(QString::number(double_user_input)) + ", click first corner.. ";

        id_1 = -1;
        id_2 = -1;
    }

    if(click == 1){

        if(key_enter){click = 0;}

        messagebox_text = "<b><i>mode chamfer</i></b> click second corner..";
        id_1 = select_id; //see line_nearest class..

        id_1_mouse_dist_to_startpoint = sqrt(pow(double_cad_array[id_1][0] - mouse_cad_pos_x,2)+pow(double_cad_array[id_1][1] - mouse_cad_pos_y,2));
        //qDebug() << "id_1_mouse_dist_to_startpoint" << id_1_mouse_dist_to_startpoint;

        id_1_mouse_dist_to_endpoint = sqrt(pow(double_cad_array[id_1][3] - mouse_cad_pos_x,2)+pow(double_cad_array[id_1][4] - mouse_cad_pos_y,2));
        //qDebug() << "id_1_mouse_dist_to_endpoint" << id_1_mouse_dist_to_endpoint;

        click = 2;
    }

    if(click == 3){
        if(key_enter){click = 0;}

        messagebox_text = "<b><i>mode chamfer </i></b> enter for repeat or Esc for cancel";
        id_2 = select_id;

        id_2_mouse_dist_to_startpoint = sqrt(pow(double_cad_array[id_2][0] - mouse_cad_pos_x,2)+pow(double_cad_array[id_2][1] - mouse_cad_pos_y,2));
        //qDebug() << "id_2_mouse_dist_to_startpoint" << id_2_mouse_dist_to_startpoint;

        id_2_mouse_dist_to_endpoint = sqrt(pow(double_cad_array[id_2][3] - mouse_cad_pos_x,2)+pow(double_cad_array[id_2][4] - mouse_cad_pos_y,2));
        //qDebug() << "id_2_mouse_dist_to_endpoint" << id_2_mouse_dist_to_endpoint;

        click = 4;
    }

    if(click == 4){
        if(key_enter){click = 0;}
        //calculate wich corners are nearest to the mouse pointer..

        if(id_1_mouse_dist_to_startpoint < id_1_mouse_dist_to_endpoint){
            id_1_chamfer_startpoint = 1;
            //qDebug() << "id_1 chamfer at startpoint..";
        }
        if(id_1_mouse_dist_to_startpoint > id_1_mouse_dist_to_endpoint){
            id_1_chamfer_startpoint = 0;
            //qDebug() << "id_1 chamfer at endpoint..";
        }
        if(id_2_mouse_dist_to_startpoint < id_2_mouse_dist_to_endpoint){
            id_2_chamfer_startpoint = 1;
            //qDebug() << "id_2 chamfer at startpoint..";
        }
        if(id_2_mouse_dist_to_startpoint > id_2_mouse_dist_to_endpoint){
            id_2_chamfer_startpoint = 0;
            //qDebug() << "id_2 chamfer at endpoint..";
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
            if(chamfer_mm == 0){
                if(id_1_chamfer_startpoint == 1){
                    double_cad_array[id_1][0] = x;
                    double_cad_array[id_1][1] = y;
                }
                if(id_1_chamfer_startpoint == 0){
                    double_cad_array[id_1][3] = x;
                    double_cad_array[id_1][4] = y;
                }
                if(id_2_chamfer_startpoint == 1){
                    double_cad_array[id_2][0] = x;
                    double_cad_array[id_2][1] = y;
                }
                if(id_2_chamfer_startpoint == 0){
                    double_cad_array[id_2][3] = x;
                    double_cad_array[id_2][4] = y;
                }
            }


            if(chamfer_mm > 0){  //add an extra chamfer line to the array..

                //interpolate the chamfer distance back over the corners trough the lines..
                //cirlce - line intersection..

                //first chamfer line id_1..
                if(id_1_chamfer_startpoint == 1){
                    double_cad_array[id_1][0] = x;
                    double_cad_array[id_1][1] = y;
                }
                if(id_1_chamfer_startpoint == 0){
                    double_cad_array[id_1][3] = x;
                    double_cad_array[id_1][4] = y;
                }

                double circle_center_x = x;
                double circle_center_y = y;
                double radius = chamfer_mm;
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
                    double intersection_x1 = (line_x1 + t * dx);
                    double intersection_y1 = (line_y1 + t * dy);
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


                //second chamfer line id_2..
                if(id_2_chamfer_startpoint == 1){
                    double_cad_array[id_2][0] = x;
                    double_cad_array[id_2][1] = y;
                }
                if(id_2_chamfer_startpoint == 0){
                    double_cad_array[id_2][3] = x;
                    double_cad_array[id_2][4] = y;
                }

                circle_center_x = x;
                circle_center_y = y;
                radius = chamfer_mm;
                line_x1 = double_cad_array[id_2][0];
                line_y1 = double_cad_array[id_2][1];
                line_x2 = double_cad_array[id_2][3];
                line_y2 = double_cad_array[id_2][4];

                //dx, dy, A, B, C, det, t;

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
                    double intersection_x1 = (line_x1 + t * dx);
                    double intersection_y1 = (line_y1 + t * dy);
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
            }

            //write the chamfer line..
            int_cad_array[cad_counter][0] = 1; //id line

            int_cad_array[cad_counter][5] = current_linetype;
            double_cad_array[cad_counter][18] = current_linetype_scale;
            double_cad_array[cad_counter][19] = current_linewidth;

            double_cad_array[cad_counter][56] = current_gui_color_red_gl;
            double_cad_array[cad_counter][57] = current_gui_color_green_gl;
            double_cad_array[cad_counter][58] = current_gui_color_blue_gl;
            double_cad_array[cad_counter][59] = current_gui_color_alpha_gl;

            if(id_1_chamfer_startpoint == 1){
                double_cad_array[cad_counter][0] = double_cad_array[id_1][0];
                double_cad_array[cad_counter][1] = double_cad_array[id_1][1];
            }
            if(id_1_chamfer_startpoint == 0){
                double_cad_array[cad_counter][0] = double_cad_array[id_1][3];
                double_cad_array[cad_counter][1] = double_cad_array[id_1][4];
            }
            if(id_2_chamfer_startpoint == 1){
                double_cad_array[cad_counter][3] = double_cad_array[id_2][0];
                double_cad_array[cad_counter][4] = double_cad_array[id_2][1];
            }
            if(id_2_chamfer_startpoint == 0){
                double_cad_array[cad_counter][3] = double_cad_array[id_2][3];
                double_cad_array[cad_counter][4] = double_cad_array[id_2][4];
            }

            //write midpoint for chamfer line..
            double_cad_array[cad_counter][15] =  (double_cad_array[cad_counter][0] +  double_cad_array[cad_counter][3]) / 2; //x midpoint..
            double_cad_array[cad_counter][16] =  (double_cad_array[cad_counter][1] +  double_cad_array[cad_counter][4]) / 2; //y midpoint..
            double_cad_array[cad_counter][17] =  (double_cad_array[cad_counter][2] +  double_cad_array[cad_counter][5]) / 2; //z midpoint..

            cad_counter++; //write the new line to the cad_counter..

            //end function ..
            click = 0;
            mode_chamfer = 0;
            entry_focus = 0;
            no_highlight();
            id_1 = -1;
            id_2 = -1;
        }
    }
}


























