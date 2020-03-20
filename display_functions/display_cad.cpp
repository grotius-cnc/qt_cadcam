#include "display_cad.h"
#include <core_functions/variables.h>
#include <display_functions/color.h>
#include <display_functions/linetype.h>
#include <display_functions/highlight.h>
#define DEG2RAD M_PI/180;

display_cad::display_cad()
{
    for(int i=0 ; i < cad_counter+100 ; i++) {

        //temponairy linewidth..
        glLineWidth(int_cad_array[i][2] = 1);

        //draw objects from cad array..
        if(int_cad_array[i][0] == 1){ // id = line..

            (color(i)); (highlight(i)); (linetype(i));  //highlight includes linewidth..
            //draw line

            glBegin(GL_LINES);
            glVertex3d(double_cad_array[i][0], double_cad_array[i][1], double_cad_array[i][2]);  //xyz start
            //glColor3f(1.0f, 0.0f, 1.0f);
            glVertex3d(double_cad_array[i][3], double_cad_array[i][4], double_cad_array[i][5]);  //xyz end
            glEnd();
            //glDisable(GL_LINE_STIPPLE);
        }

        if(int_cad_array[i][0] == 2){ // id = circle
            ///********** NOTE: if a circle is flickering, then there are too many segments...

            (color(i)); (highlight(i)); (linetype(i));
            //draw circle

            glBegin(GL_LINE_LOOP);
            for (int ii = 0; ii < segments; ii++)   {
                double theta = 2.0 * M_PI * int(ii) / int(segments );                                                               //get the current angle
                double x = double_cad_array[i][9]/*radius*/ * cosf(theta);                                                             //calculate the x component
                double y = double_cad_array[i][9]/*radius*/ * sinf(theta);                                                             //calculate the y component
                glVertex3d(x + double_cad_array[i][6]/*x center*/, y + double_cad_array[i][7]/*y center*/, double_cad_array[i][8]/*z center*/);      //output vertex
            }
            glEnd();
            //glDisable(GL_LINE_STIPPLE);

        }

        if(int_cad_array[i][0] == 3){ // id = arc

            double angle_start = (double_cad_array[i][11]/360)*(2*M_PI);/*start angle*/

            if(double_cad_array[i][12]==360){double_cad_array[i][12]=0;} //autocad degree problem..

            double angle_end = (double_cad_array[i][12]/360)*(2*M_PI);

            if (angle_end < angle_start){  //this to avoid the start angle is bigger then the end angle value
                angle_end += 2*M_PI;
            }

            //temp
            //            (color(i)); (highlight(i)); (linetype(i));
            //            glBegin(GL_LINE_STRIP);

            //            //double max_angle = 2 * M_PI; //6.28
            //            double angle_increment = M_PI/200; //resolution
            //            for(double theta = angle_start/*start angle*/; theta < angle_end/*end angle*/; theta += angle_increment ){
            //                glVertex2d(double_cad_array[i][6]/*x center*/+ double_cad_array[i][9]/*radius*/* cosf(theta),double_cad_array[i][7]/*y center*/+ double_cad_array[i][9]/*radius*/* sinf(theta) );
            //            }
            //            glEnd();

            float arc_angle = angle_end - angle_start;
            float theta = arc_angle / float(segments - 1);//theta is now calculated from the arc angle instead, the - 1 bit comes from the fact that the arc is open
            float tangetial_factor = tanf(theta);
            float radial_factor = cosf(theta);
            float x = double_cad_array[i][9] * cosf(angle_start);//we now start at the start angle
            float y = double_cad_array[i][9] * sinf(angle_start);

            (color(i)); (highlight(i)); (linetype(i));

            glBegin(GL_LINE_STRIP);//since the arc is not a closed curve, this is a strip now
            for(int ii = 0; ii < segments; ii++)
            {
                glVertex2f(x + double_cad_array[i][6], y + double_cad_array[i][7]); //x center, y center..

                float tx = -y;
                float ty = x;

                x += tx * tangetial_factor;
                y += ty * tangetial_factor;

                x *= radial_factor;
                y *= radial_factor;
            }
            glEnd();
            //glDisable(GL_LINE_STIPPLE);


        }

        if(int_cad_array[i][0] == 4){ // id = ellipse

            double center_x = double_cad_array[i][6];
            double center_y = double_cad_array[i][7];
            double radius_x = double_cad_array[i][9];
            double radius_y = double_cad_array[i][10];

            double rotate_degrees = double_cad_array[i][11];
            double rotate_x0;
            double rotate_y0;

            (color(i)); (highlight(i)); (linetype(i));

            glBegin(GL_LINE_LOOP);

            for(int i = 0; i<360; i++){

                //non rotated ellipse..
                double rad = i*DEG2RAD
                double non_rotated_x = /*center_x +*/ cos(rad)*radius_x;
                double non_rotated_y = /*center_y +*/ sin(rad)*radius_y;
                //glVertex2d(center_x + cos(rad)*radius_x, center_y + sin(rad)*radius_y);

                //rotated ellipse..
                rotate_x0 = center_x  + cos(rotate_degrees * M_PI / 180.0 )* non_rotated_x - sin(rotate_degrees * M_PI / 180.0 ) * non_rotated_y;
                rotate_y0 = center_y  + sin(rotate_degrees * M_PI / 180.0 )* non_rotated_x + cos(rotate_degrees * M_PI / 180.0 ) * non_rotated_y;
                glVertex2d(rotate_x0, rotate_y0);
            }
            glEnd();
            //glDisable(GL_LINE_STIPPLE);

        }

        if(int_cad_array[i][0] == 5){ // id = qubic bezier curve

            (color(i)); (highlight(i)); (linetype(i));

            glBegin(GL_LINE_STRIP);

            for(double t = 0; t < 1; t+=0.001){ //choose a different resolution for t ..
                //qDebug() << "t = " << t;

                //start point A..
                Ax = double_cad_array[i][0];
                Ay = double_cad_array[i][1];
                Az = double_cad_array[i][2];

                //control point B..
                Bx = double_cad_array[i][50];
                By = double_cad_array[i][51];
                Bz = double_cad_array[i][52];

                //control point C..
                Cx = double_cad_array[i][53];
                Cy = double_cad_array[i][54];
                Cz = double_cad_array[i][55];

                //end point D..
                Dx = double_cad_array[i][3];
                Dy = double_cad_array[i][4];
                Dz = double_cad_array[i][5];

                //at this stage we have defined all the points and de lines of the cubic bezier curve..
                //Calculate Point E, on the line AB
                double Ex = ((1-t) * Ax) + (t * Bx);
                double Ey = ((1-t) * Ay) + (t * By);
                double Ez = ((1-t) * Az) + (t * Bz);

                //Calculate Point F, on the line BC
                double Fx = ((1-t) * Bx) + (t * Cx);
                double Fy = ((1-t) * By) + (t * Cy);
                double Fz = ((1-t) * Bz) + (t * Cz);

                //Calculate Point G, on the line CD
                double Gx = ((1-t) * Cx) + (t * Dx);
                double Gy = ((1-t) * Cy) + (t * Dy);
                double Gz = ((1-t) * Cz) + (t * Dz);

                //Calculate Point Q, on the line EF
                double Qx = ((1-t) * Ex) + (t * Fx);
                double Qy = ((1-t) * Ey) + (t * Fy);
                double Qz = ((1-t) * Ez) + (t * Fz);

                //Calculate Point R, on the line FG
                double Rx = ((1-t) * Fx) + (t * Gx);
                double Ry = ((1-t) * Fy) + (t * Gy);
                double Rz = ((1-t) * Fz) + (t * Gz);

                //Calculate Point P, on the line QR
                double Px = ((1-t) * Qx) + (t * Rx);
                double Py = ((1-t) * Qy) + (t * Ry);
                double Pz = ((1-t) * Qz) + (t * Rz);

                glVertex3d(Px, Py, Pz);  //draw linestrip..
            }
            glEnd();
            //glDisable(GL_LINE_STIPPLE);

        }

        if(int_cad_array[i][0] == 6){ // id = cubic hermite spline

            (color(i)); (highlight(i)); (linetype(i));

            glBegin(GL_LINE_STRIP);

            for(double t = 0; t <= 1; t+=0.001){ //choose a different resolution for t ..
                //qDebug() << "t = " << t;

                //start point A..
                Ax = double_cad_array[i][0];
                Ay = double_cad_array[i][1];
                Az = double_cad_array[i][2];

                //control point B..
                Bx = double_cad_array[i][50];
                By = double_cad_array[i][51];
                Bz = double_cad_array[i][52];

                //control point C..
                Cx = double_cad_array[i][53];
                Cy = double_cad_array[i][54];
                Cz = double_cad_array[i][55];

                //end point D..
                Dx = double_cad_array[i][3];
                Dy = double_cad_array[i][4];
                Dz = double_cad_array[i][5];

                double ax = -Ax/2 + (3*Bx)/2 - (3*Cx)/2 + Dx/2;
                double bx = Ax - (5*Bx)/2 + 2*Cx - Dx / 2;
                double cx = -Ax/2 + Cx/2;
                double dx = Bx;
                double Px = ax*t*t*t + bx*t*t + cx*t + dx;

                double ay = -Ay/2 + (3*By)/2 - (3*Cy)/2 + Dy/2;
                double by = Ay - (5*By)/2 + 2*Cy - Dy / 2;
                double cy = -Ay/2 + Cy/2;
                double dy = By;
                double Py = ay*t*t*t + by*t*t + cy*t + dy;

                double az = -Az/2 + (3*Bz)/2 - (3*Cz)/2 + Dz/2;
                double bz = Az - (5*Bz)/2 + 2*Cz - Dz / 2;
                double cz = -Az/2 + Cz/2;
                double dz = Bz;
                double Pz = az*t*t*t + bz*t*t + cz*t + dz;

                glVertex3d(Px, Py, Pz);  //draw linestrip..
            }
            glEnd();
            //glDisable(GL_LINE_STIPPLE);
        }

        if(int_cad_array[i][0] == 7){ // id = points..

            (color(i)); (highlight(i)); (linetype(i));  //highlight includes linewidth..
            //glPointSize(float(double_cad_array[i][19]));

            glBegin(GL_POINTS);
            glVertex3d(double_cad_array[i][0], double_cad_array[i][1], double_cad_array[i][2]);  //xyz start
            glEnd();

        }
    }
}






















