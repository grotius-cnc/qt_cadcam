#include "extend.h"
#include <core_functions/variables.h>
#include <display_functions/object_select_line_nearest.h>
#include <display_functions/object_select_arc_nearest.h>
#include <display_functions/object_select_circle_nearest.h>
#include <display_functions/simple_line_select.h>
#include <display_functions/no_highlight.h>
#include <cad_draw_functions/redraw_arc.h>
#include <math.h>

#define myqDebug() qDebug() << fixed << qSetRealNumberPrecision(3)

QList<double> rotate_point(double cx,double cy,double angle_rad, double x, double y);

double xx=0;
double yy=0;

extend::extend()
{
    //initialiation..
    snap_cad_pos_x = mouse_cad_pos_x;
    snap_cad_pos_y = mouse_cad_pos_y;
    snap_cad_pos_z = mouse_cad_pos_z;

    //overwrite initialisation if we spot a snap somewhere..
    //object_select_line_nearest(0);
    simple_line_select();
    object_select_arc_nearest(0);
    object_select_circle_nearest(0);

    if(click == 0){
        id_1 = -1;
        id_2 = -1;
        //qDebug() << "click = 0";
        messagebox_text = "<b><i>mode extend</i></b> click boundary line";
        mode_nearest = 1;
    }

    if(click == 1){

        id_1 = select_id;
        //qDebug() << "target id : " << id_2;
        messagebox_text = "<b><i>mode extend</i></b> click line to extend";
        xx = snap_cad_pos_x;
        yy = snap_cad_pos_y;
        click = 2;

    }

    if(click == 3){

        id_2 = select_id;
        //qDebug() << "source id : " << extend_id_source;
        double x = snap_cad_pos_x;
        double y = snap_cad_pos_y;

        //calculate intersection

        if(int_cad_array[id_1][0] == 1 && int_cad_array[id_2][0] == 1 ){ //line - line intersection..

            //bounderay line :
            double p1_x0 = double_cad_array[id_1][0];
            double p1_y0 = double_cad_array[id_1][1];
            double p1_x1 = double_cad_array[id_1][3];
            double p1_y1 = double_cad_array[id_1][4];
            //line to extend :
            double p2_x0 = double_cad_array[id_2][0];
            double p2_y0 = double_cad_array[id_2][1];
            double p2_x1 = double_cad_array[id_2][3];
            double p2_y1 = double_cad_array[id_2][4];

            //source line :
            double delta_y0 = p1_y1 - p1_y0;
            double delta_x0 = p1_x0 - p1_x1;
            double c0 = delta_y0 * p1_x0 + delta_x0 * p1_y0;
            //target line :
            double delta_y1 = p2_y1 - p2_y0;
            double delta_x1 = p2_x0 - p2_x1;
            double c1 = delta_y1 * p2_x0 + delta_x1 * p2_y0;

            double determinant = delta_y0*delta_x1 - delta_y1*delta_x0;
            //qDebug() << "determinant is : " << determinant;

            if (determinant == 0) // The lines are parallel.
            {
                //qDebug() << "the lines are parallel";
            }
            else  {
                double ix = (delta_x1*c0 - delta_x0*c1)/determinant;
                double iy = (delta_y0*c1 - delta_y1*c0)/determinant;

                double dist_start = sqrt(pow(p2_x0-ix,2)+pow(p2_y0-iy,2));
                double dist_end = sqrt(pow(p2_x1-ix,2)+pow(p2_y1-iy,2));

                if(dist_start<dist_end){
                    double_cad_array[id_2][0] = ix;
                    double_cad_array[id_2][1] = iy;
                } else {
                    double_cad_array[id_2][3] = ix;
                    double_cad_array[id_2][4] = iy;
                }
            }
        }

        if(int_cad_array[id_1][0] == 1 && int_cad_array[id_2][0] == 3 ){ //line - arc intersection.. arc extend to line..

            //line - arc intersection..
            double x0 = double_cad_array[id_1][0];
            double y0 = double_cad_array[id_1][1];
            double x1 = double_cad_array[id_1][3];
            double y1 = double_cad_array[id_1][4];

            double cpx = double_cad_array[id_2][6];    //array target circle center x
            double cpy = double_cad_array[id_2][7];    //array target circle center y
            double radius = double_cad_array[id_2][9];             //array target circle radius
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

            //declare clostest intersection at first click..
            double c1 = sqrt(pow(xx-i_x0,2) + pow(yy-i_y0,2));
            double c2 = sqrt(pow(xx-i_x1,2) + pow(yy-i_y1,2));

            if(c1<c2){

                //is startpoint or endpoint closest at second click..
                double dist_start = sqrt(pow(x-cx0,2)+pow(y-cy0,2));
                double dist_end = sqrt(pow(x-cx1,2)+pow(y-cy1,2));
                if(dist_start<dist_end){
                    double_cad_array[id_2][0] = i_x0; qDebug()<<"x" << i_x0;
                    double_cad_array[id_2][1] = i_y0; qDebug()<<"y" << i_y0;
                    update_angles(id_2);
                    qDebug()<<"1";
                } else {
                    double_cad_array[id_2][3] = i_x0; qDebug()<<"x" << i_x0;
                    double_cad_array[id_2][4] = i_y0; qDebug()<<"y" << i_y0;
                    update_angles(id_2);
                    qDebug()<<"2";
                }

            } else {

                //is startpoint closest or is endpoint closest..
                double dist_start = sqrt(pow(x-cx0,2)+pow(y-cy0,2));
                double dist_end = sqrt(pow(x-cx1,2)+pow(y-cy1,2));
                if(dist_start<dist_end){
                    double_cad_array[id_2][0] = i_x1; qDebug()<<"x" << i_x1;
                    double_cad_array[id_2][1] = i_y1; qDebug()<<"y" << i_y1;
                    update_angles(id_2);
                    qDebug()<<"3";
                } else {
                    double_cad_array[id_2][3] = i_x1; qDebug()<<"x" << i_x1;
                    double_cad_array[id_2][4] = i_y1; qDebug()<<"y" << i_y1;
                    update_angles(id_2);
                    qDebug()<<"4";
                }
            }
            calculate_midpoint(id_2);
            update_angles(id_2);
        }

        if((int_cad_array[id_1][0] == 3 && int_cad_array[id_2][0] == 1) || (int_cad_array[id_1][0] == 2 && int_cad_array[id_2][0] == 1)  ){ //arc - line intersection.. line extend to arc.. line extend to circle..

            //line - arc intersection..
            double cpx = double_cad_array[id_1][6];
            double cpy = double_cad_array[id_1][7];
            double radius = double_cad_array[id_1][9];
            double cx0 = double_cad_array[id_1][0];
            double cy0 = double_cad_array[id_1][1];
            double cx1 = double_cad_array[id_1][3];
            double cy1 = double_cad_array[id_1][4];

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
            double c1 = sqrt(pow(xx-i_x0,2) + pow(yy-i_y0,2));
            double c2 = sqrt(pow(xx-i_x1,2) + pow(yy-i_y1,2));

            if(c1<c2){

                //is startpoint closest or is endpoint closest..
                double dist_start = sqrt(pow(i_x0-x0,2)+pow(i_y0-y0,2));
                double dist_end = sqrt(pow(i_x0-x1,2)+pow(i_y0-y1,2));
                if(dist_start<dist_end){
                    double_cad_array[id_2][0] = i_x0;
                    double_cad_array[id_2][1] = i_y0;
                } else {
                    double_cad_array[id_2][3] = i_x0;
                    double_cad_array[id_2][4] = i_y0;
                }
            } else {
                //is startpoint closest or is endpoint closest..
                double dist_start = sqrt(pow(i_x1-x0,2)+pow(i_y1-y0,2));
                double dist_end = sqrt(pow(i_x1-x1,2)+pow(i_y1-y1,2));
                if(dist_start<dist_end){
                    double_cad_array[id_2][0] = i_x1;
                    double_cad_array[id_2][1] = i_y1;
                } else {
                    double_cad_array[id_2][3] = i_x1;
                    double_cad_array[id_2][4] = i_y1;
                }

            }
        }

        if((int_cad_array[id_1][0] == 3 && int_cad_array[id_2][0] == 3) || (int_cad_array[id_1][0] == 2 && int_cad_array[id_2][0] == 3)){ //arc to arc extend //extend arc to circle..

            double cx0 = double_cad_array[id_1][6];
            double cy0 = double_cad_array[id_1][7];
            double radius0 = double_cad_array[id_1][9];

            double cx1 = double_cad_array[id_2][6];
            double cy1 = double_cad_array[id_2][7];
            double radius1 = double_cad_array[id_2][9];
            double x0 = double_cad_array[id_2][0];
            double y0 = double_cad_array[id_2][1];
            double x1 = double_cad_array[id_2][3];
            double y1 = double_cad_array[id_2][4];

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
                double a = (radius0 * radius0 - radius1 * radius1 + dist * dist) / (2 * dist);
                double h = sqrt(radius0 * radius0 - a * a);
                double cx2 = cx0 + a * (cx1 - cx0) / dist;
                double cy2 = cy0 + a * (cy1 - cy0) / dist;
                //intersection 1
                double px0 = ((cx2 + h * (cy1 - cy0) / dist));
                double py0 = ((cy2 - h * (cx1 - cx0) / dist));
                //intersection 2
                double px1 = (cx2 - h * (cy1 - cy0) / dist);
                double py1 = ((cy2 + h * (cx1 - cx0) / dist));
                //closest intersection to mouse snap pos..
                double c0 = sqrt(pow(px0-xx,2)+pow(py0-yy,2));
                double c1 = sqrt(pow(px1-xx,2)+pow(py1-yy,2));

                if(c0<c1){
                    double dist_start = sqrt(pow(x0-px0,2)+pow(y0-py0,2));
                    double dist_end = sqrt(pow(x1-px0,2)+pow(y1-py0,2));
                    if(dist_start<dist_end){
                        double_cad_array[id_2][0] = px0;
                        double_cad_array[id_2][1] = py0;

                    } else {
                        double_cad_array[id_2][3] = px0;
                        double_cad_array[id_2][4] = py0;
                    }
                } else {
                    double dist_start = sqrt(pow(x0-px1,2)+pow(y0-py1,2));
                    double dist_end = sqrt(pow(x1-px1,2)+pow(y1-py1,2));
                    if(dist_start<dist_end){
                        double_cad_array[id_2][0] = px1;
                        double_cad_array[id_2][1] = py1;

                    } else {
                        double_cad_array[id_2][3] = px1;
                        double_cad_array[id_2][4] = py1;
                    }
                }
                calculate_midpoint(id_2);
                update_angles(id_2);
            }
        }

        no_highlight();
        mode_extend = 0;
        click = 0;
        key_enter = 0;
        int_key = 0 ;
        mode_nearest = 0;
        id_1 = -1;
        id_2 = -1;
        messagebox_text = "<b><i>mode extend </i></b> press enter for repeat";
    }
}

QList<double> rotate_point(double cx,double cy,double angle_rad, double x, double y)
{
  QList<double> list;
  double s = sin(angle_rad);
  double c = cos(angle_rad);

  // translate point back to origin:
  x -= cy;
  y -= cy;

  // rotate point
  double xnew = x * c - y * s;
  double ynew = x * s + y * c;

  // translate point back:
  x = xnew + cx;
  y = ynew + cy;

  list.append(x);
  list.append(y);
  return list;
}

void extend::calculate_midpoint(int i)
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

QList<double> extend::rotate_point(double cx ,double cy, double angle, double x, double y)
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

void extend::update_angles(int i)
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
