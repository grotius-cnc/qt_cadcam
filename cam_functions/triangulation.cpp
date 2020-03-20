#include "triangulation.h"
#include <core_functions/variables.h>
#include <cstdlib>

triangulation::triangulation(int id_outside, QVector<int> id_inside, bool outside, bool inside)
{

    int facing = 24;
    //qDebug()<< "triangulation active..";
    if(outside){
        for(int i=0; i<cam_counter; i++){
            if(int_cam_array[i][14] == id_outside){
                if(int_cam_array[i][0]==1){ //id line..
                    outside_contour.push_back(new p2t::Point(double_cam_array[i][0],double_cam_array[i][1]));
                } else
                if(int_cam_array[i][0]==2){ //id circle
//                    outside_contour.push_back(new p2t::Point(double_cam_array[i][25],double_cam_array[i][26]));
//                    outside_contour.push_back(new p2t::Point(double_cam_array[i][31],double_cam_array[i][32]));
//                    outside_contour.push_back(new p2t::Point(double_cam_array[i][28],double_cam_array[i][29]));
//                    outside_contour.push_back(new p2t::Point(double_cam_array[i][34],double_cam_array[i][35]));

                    for (int ii = 0; ii < facing; ii++)   {
                        double theta = 1.99 * M_PI * int(ii) / int(facing);
                        double x = double_cam_array[i][9]/*radius*/ * cosf(theta);
                        double y = double_cam_array[i][9]/*radius*/ * sinf(theta);
                        outside_contour.push_back(new p2t::Point(x + double_cam_array[i][6],y + double_cam_array[i][7]));
                    }

                } else
                if(int_cam_array[i][0]==3){ //id arc..
                    //outside_contour.push_back(new p2t::Point(double_cam_array[i][0],double_cam_array[i][1]));

                    double angle_end = 0;
                    double angle_start = 0;
                    float arc_angle = 0;
                    float tangetial_factor = 0;
                    float radial_factor = 0;
                    float x =0;
                    float y =0;

                    if(int_cam_array[i][20]==1){ //g2
                        angle_start = (double_cam_array[i][11]/360)*(2*M_PI);/*start angle*/
                        angle_end = (double_cam_array[i][12]/360)*(2*M_PI);

                        if (angle_end < angle_start){  //this to avoid the start angle is bigger then the end angle value
                            angle_end += 2*M_PI;
                        }

                        arc_angle = angle_start - angle_end ;
                        float theta = arc_angle / float(facing - 1);//theta is now calculated from the arc angle instead, the - 1 bit comes from the fact that the arc is open
                        tangetial_factor = tanf(theta);
                        radial_factor = cosf(theta);
                        x = double_cam_array[i][9] * cosf(angle_end);//we now start at the start angle
                        y = double_cam_array[i][9] * sinf(angle_end);


                        //glBegin(GL_LINE_STRIP);//since the arc is not a closed curve, this is a strip now
                        for(int ii = 0; ii < facing; ii++)
                        {
                            //glVertex2f(x + double_cam_array[i][6], y + double_cam_array[i][7]);
                            outside_contour.push_back(new p2t::Point(x + double_cam_array[i][6], y + double_cam_array[i][7]));

                            float tx = -y;
                            float ty = x;
                            x += tx * tangetial_factor;
                            y += ty * tangetial_factor;
                            x *= radial_factor;
                            y *= radial_factor;
                        }
                    } else
                    if(int_cam_array[i][21]==1){ //g3
                        angle_start = (double_cam_array[i][11]/360)*(2*M_PI);/*start angle*/
                        angle_end = (double_cam_array[i][12]/360)*(2*M_PI);

                        if (angle_end < angle_start){  //this to avoid the start angle is bigger then the end angle value
                            angle_end += 2*M_PI;
                        }

                        arc_angle = angle_end - angle_start;
                        float theta = arc_angle / float(facing - 1);//theta is now calculated from the arc angle instead, the - 1 bit comes from the fact that the arc is open
                        tangetial_factor = tanf(theta);
                        radial_factor = cosf(theta);
                        x = double_cam_array[i][9] * cosf(angle_start);//we now start at the start angle
                        y = double_cam_array[i][9] * sinf(angle_start);


                        //glBegin(GL_LINE_STRIP);//since the arc is not a closed curve, this is a strip now
                        for(int ii = 0; ii < facing; ii++)
                        {
                            //glVertex2f(x + double_cam_array[i][6], y + double_cam_array[i][7]);
                            outside_contour.push_back(new p2t::Point(x + double_cam_array[i][6], y + double_cam_array[i][7]));

                            float tx = -y;
                            float ty = x;
                            x += tx * tangetial_factor;
                            y += ty * tangetial_factor;
                            x *= radial_factor;
                            y *= radial_factor;
                        }
                    }
                }
            }
        }
    }

    p2t::CDT cdt(outside_contour);

    if(inside){
        while(!id_inside.empty()){
            //for(it = id_inside.begin(); it != id_inside.end(); it++){
            for(int i=0; i<cam_counter; i++){
                if(int_cam_array[i][14] == id_inside.first()){ //contournumber..
                    if(int_cam_array[i][0]==1){ //id line..
                        inside_contour.push_back(new p2t::Point(double_cam_array[i][0],double_cam_array[i][1]));
                    } else
                    if(int_cam_array[i][0]==2){ //id circle
//                        inside_contour.push_back(new p2t::Point(double_cam_array[i][25],double_cam_array[i][26]));
//                        inside_contour.push_back(new p2t::Point(double_cam_array[i][31],double_cam_array[i][32]));
//                        inside_contour.push_back(new p2t::Point(double_cam_array[i][28],double_cam_array[i][29]));
//                        inside_contour.push_back(new p2t::Point(double_cam_array[i][34],double_cam_array[i][35]));

                        for (int ii = 0; ii < facing; ii++)   {
                            double theta = 2.0 * M_PI * int(ii) / int(facing);
                            double x = double_cam_array[i][9]/*radius*/ * cosf(theta);
                            double y = double_cam_array[i][9]/*radius*/ * sinf(theta);
                            inside_contour.push_back(new p2t::Point(x + double_cam_array[i][6],y + double_cam_array[i][7]));
                        }
                    } else
                    if(int_cam_array[i][0]==3){ //id arc..
                        //inside_contour.push_back(new p2t::Point(double_cam_array[i][0],double_cam_array[i][1]));

                        double angle_end = 0;
                        double angle_start = 0;
                        float arc_angle = 0;
                        float tangetial_factor = 0;
                        float radial_factor = 0;
                        float x =0;
                        float y =0;

                        if(int_cam_array[i][20]==1){ //g2
                            angle_start = (double_cam_array[i][11]/360)*(2*M_PI);/*start angle*/
                            angle_end = (double_cam_array[i][12]/360)*(2*M_PI);

                            if (angle_end < angle_start){  //this to avoid the start angle is bigger then the end angle value
                                angle_end += 2*M_PI;
                            }

                            arc_angle = angle_start - angle_end ;
                            float theta = arc_angle / float(facing - 1);//theta is now calculated from the arc angle instead, the - 1 bit comes from the fact that the arc is open
                            tangetial_factor = tanf(theta);
                            radial_factor = cosf(theta);
                            x = double_cam_array[i][9] * cosf(angle_end);//we now start at the start angle
                            y = double_cam_array[i][9] * sinf(angle_end);

                            //glBegin(GL_LINE_STRIP);//since the arc is not a closed curve, this is a strip now
                            for(int ii = 0; ii < facing; ii++)
                            {
                                //glVertex2f(x + double_cam_array[i][6], y + double_cam_array[i][7]);
                                inside_contour.push_back(new p2t::Point(x + double_cam_array[i][6], y + double_cam_array[i][7]));

                                float tx = -y;
                                float ty = x;
                                x += tx * tangetial_factor;
                                y += ty * tangetial_factor;
                                x *= radial_factor;
                                y *= radial_factor;
                            }
                        } else
                        if(int_cam_array[i][21]==1){ //g3
                            angle_start = (double_cam_array[i][11]/360)*(2*M_PI);/*start angle*/
                            angle_end = (double_cam_array[i][12]/360)*(2*M_PI);

                            if (angle_end < angle_start){  //this to avoid the start angle is bigger then the end angle value
                                angle_end += 2*M_PI;
                            }

                            arc_angle = angle_end - angle_start;
                            float theta = arc_angle / float(facing - 1);//theta is now calculated from the arc angle instead, the - 1 bit comes from the fact that the arc is open
                            tangetial_factor = tanf(theta);
                            radial_factor = cosf(theta);
                            x = double_cam_array[i][9] * cosf(angle_start);//we now start at the start angle
                            y = double_cam_array[i][9] * sinf(angle_start);

                            //glBegin(GL_LINE_STRIP);//since the arc is not a closed curve, this is a strip now
                            for(int ii = 0; ii < facing; ii++)
                            {
                                //glVertex2f(x + double_cam_array[i][6], y + double_cam_array[i][7]);
                                inside_contour.push_back(new p2t::Point(x + double_cam_array[i][6], y + double_cam_array[i][7]));

                                float tx = -y;
                                float ty = x;
                                x += tx * tangetial_factor;
                                y += ty * tangetial_factor;
                                x *= radial_factor;
                                y *= radial_factor;
                            }
                        }

                    }

                }
            }
            id_inside.removeFirst();
            cdt.AddHole(inside_contour);
            inside_contour.clear();
        }
    }

    cdt.Triangulate();

    triangles = cdt.GetTriangles();
    map = cdt.GetMap();

    //qDebug()<< "triangles.size : "  << triangles.size();
    for (unsigned int i = 0; i < triangles.size(); i++) {
        p2t::Triangle& t = *triangles[i];
        p2t::Point& a = *t.GetPoint(0);
        p2t::Point& b = *t.GetPoint(1);
        p2t::Point& c = *t.GetPoint(2);

        //        qDebug()<< " a.x : " << a.x;
        //        qDebug()<< " a.y : " << a.y;
        //        qDebug()<< " b.x : " << b.x;
        //        qDebug()<< " b.y : " << b.y;
        //        qDebug()<< " c.x : " << c.x;
        //        qDebug()<< " c.y : " << c.y;

        double_triangle_array[triangle_counter][0] = a.x;
        double_triangle_array[triangle_counter][1] = a.y;
        double_triangle_array[triangle_counter+1][0] = b.x;
        double_triangle_array[triangle_counter+1][1] = b.y;
        double_triangle_array[triangle_counter+2][0] = c.x;
        double_triangle_array[triangle_counter+2][1] = c.y;
        int_triangle_array[triangle_counter][0] = current_gui_color;
        int_triangle_array[triangle_counter+1][0] = current_gui_color;
        int_triangle_array[triangle_counter+2][0] = current_gui_color;

        triangle_counter+=3;
    }

    //clean extern variable..
    outside_contour.clear();
    inside_contour.clear();
    triangles.clear();
    //outside_contour.shrink_to_fit();
    //inside_contour.shrink_to_fit();
    //triangles.shrink_to_fit();

}



//double radian_start = atan2(double_cam_array[i][1]-double_cam_array[i][7], double_cam_array[i][0]-double_cam_array[i][6]); //qDebug() << "radian_start : " << radian_start;
//double radian_end = atan2(double_cam_array[i][4]-double_cam_array[i][7], double_cam_array[i][3]-double_cam_array[i][6]);   //qDebug() << "radian_end : " << radian_end;
//if (radian_end < radian_start){  //this to avoid the start angle is bigger then the end angle value
//    radian_end += 2*M_PI;
//}

//double arc_radians = radian_end-radian_start;


////rotate startpoint...
//double rotate_dist_x = double_cam_array[i][0] - double_cam_array[i][6];
//double rotate_dist_y = double_cam_array[i][1] - double_cam_array[i][7];
//double rotate_x = cos(rotate_degrees * M_PI / 180.0 )* rotate_dist_x - sin(rotate_degrees * M_PI / 180.0 ) * rotate_dist_y;
//double rotate_y = sin(rotate_degrees * M_PI / 180.0 )* rotate_dist_x + cos(rotate_degrees * M_PI / 180.0 ) * rotate_dist_y;
//double x = rotate_x + double_cam_array[i][6];
//double y = rotate_y + double_cam_array[i][7];






















