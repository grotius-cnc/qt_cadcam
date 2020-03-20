#include "contour_offset.h"
#include <core_functions/variables.h>
#include <array_functions/empty_cam_array.h>
#include <array_functions/empty_triangle_array.h>
#include <cam_functions/polytree.h>
#include <cam_functions/polytree_triangulation.h>
#include <array_functions/cad_array.h>
#include <array_functions/cam_array.h>
#include <ctime>
#include <cam_functions/point_in_polygon.h>
#include <cam_functions/contour_recognize.h>
#include <cam_functions/offset_intersection.h>
#include <cam_functions/g_code.h>
#include <dialog_functions/dialog_tools.h>
#include <dialog_functions/dialog_postprocessor.h>
#include <dialog_functions/dialog_axis.h>
#include <mainwindow.h>
#include <array_functions/purge_array.h>
#include <cam_functions/nearest.h>
#include <cam_functions/final_direction.h>
#include <cam_functions/cam_text.h>
#include <array_functions/emtpy_current_cad_counter.h>


contour_offset::contour_offset()
{
    if(click == 0){

        //clear array text lines..
        for(int i=0; i<cad_counter; i++){
            if(int_cad_array[i][26] == 1){
                (emtpy_current_cad_counter(i));
            }
        }

        purge_array();

        std::clock_t start;
        double duration;
        start = std::clock();

        empty_cam_array();
        contournumber=1;
        cam_counter=0;

        cam_text();

        contour_recognize();
        polytree(); //2.8 seconds..
        final_direction();

        Dialog_tools().load_selected_data();

        auto_offset(extern_diameter.toDouble()/2);
        offset_intersection();

        gcode_filename = "gcode_preview.txt";
        g_code();

        duration = ( std::clock() - start ) / double CLOCKS_PER_SEC;
        std::cout<<"duration : "<< duration <<'\n';
        messagebox_text = "<b><i>mode cam </i></b> ";

        bool_load_treewidget = 1;
        click = 1;
    }

    //nearest line..
    //nearest();
    //qDebug()<< "click : " << click;
    //qDebug()<< "select id : " << select_id;

}

void contour_offset::auto_offset(double kerf)
{
    //qDebug() << "cam counter : " <<  cam_counter;
    int temp_counter = cam_counter;

    for(int i = 0; i < cam_counter; i++){

        if(int_cam_array[i][15] == 1){//offset only if closed contour mark..

            if(int_cam_array[i][0] == 2){//id circle
                int_cam_array[temp_counter][0] = 2; //id circle
                if(double_cam_array[i][56] == 1 && double_cam_array[i][57] == 0 && double_cam_array[i][58] == 0){//color red cw
                    int_cam_array[i][20] = 1; //g2
                    int_cam_array[i][12] = 1; //write cw to array
                    int_cam_array[temp_counter][20] = 1;
                }
                if(double_cam_array[i][56] == 1 && double_cam_array[i][57] == 1 && double_cam_array[i][58] == 0){//color yellow ccw
                    int_cam_array[i][21] = 1; //g3
                    int_cam_array[i][13] = 1; //write ccw to array
                    int_cam_array[temp_counter][21] = 1;
                }

                //int_cam_array[temp_counter][1] = 5; //blue
                double_cam_array[temp_counter][56] = 0; //red
                double_cam_array[temp_counter][57] = 0; //green
                double_cam_array[temp_counter][58] = 1; //blue
                double_cam_array[temp_counter][59] = 1; //alpha

                //int_cam_array[temp_counter][2] = 1; //linewidth
                double_cam_array[temp_counter][19] = double_cam_array[i][19];//linewidth

                int_cam_array[temp_counter][5] = current_linetype;
                int_cam_array[temp_counter][12] = int_cam_array[i][12]; //contour cw
                int_cam_array[temp_counter][13] = int_cam_array[i][13]; //contour ccw
                int_cam_array[temp_counter][14] = int_cam_array[i][14]; //contournumber
                int_cam_array[temp_counter][15] = int_cam_array[i][15]; //closed contour mark
                int_cam_array[temp_counter][16] = int_cam_array[i][16]; //depth
                double_cam_array[temp_counter][6] = double_cam_array[i][6];
                double_cam_array[temp_counter][7] = double_cam_array[i][7];
                double_cam_array[temp_counter][8] = double_cam_array[i][8];

                if(int_cam_array[i][20] == 1){//g2

                    double Xa = double_cam_array[i][6];
                    double Ya = double_cam_array[i][7];
                    double Xb = double_cam_array[i][25];
                    double Yb = double_cam_array[i][26];
                    double AC = double_cam_array[i][9]+kerf; //radius
                    double AB = double_cam_array[i][9];
                    double Xc = Xa + (AC * (Xb - Xa) / AB); //new startpoint coordinate..
                    double Yc = Ya + (AC * (Yb - Ya) / AB);

                    double_cam_array[temp_counter][25] = Xc;
                    double_cam_array[temp_counter][26] = Yc;
                    double_cam_array[temp_counter][9] = double_cam_array[i][9]+kerf; //radius

                }
                if(int_cam_array[i][21] == 1){//g3

                    //left contour point, inside offset :
                    double Xa = double_cam_array[i][6];
                    double Ya = double_cam_array[i][7];
                    double Xb = double_cam_array[i][25];
                    double Yb = double_cam_array[i][26];
                    double AC = double_cam_array[i][9]-kerf; //radius
                    double AB = double_cam_array[i][9];
                    double Xc = Xa + (AC * (Xb - Xa) / AB); //new startpoint coordinate..
                    double Yc = Ya + (AC * (Yb - Ya) / AB);

                    double_cam_array[temp_counter][25] = Xc;
                    double_cam_array[temp_counter][26] = Yc;
                    double_cam_array[temp_counter][9] = double_cam_array[i][9]-kerf; //radius

                }
                temp_counter++;

            }


            if(int_cam_array[i][0] == 3){//id arc

                double offset = 0;
                double radius = double_cam_array[i][9];
                double x_center = double_cam_array[i][6];
                double y_center = double_cam_array[i][7];

                //normal outside offset command
                if(int_cam_array[i][12] == 1){ //cw contour
                    if(int_cam_array[i][20] == 1){ //g2
                        offset = kerf;
                    }
                    if(int_cam_array[i][21] == 1){ //g3
                        offset = kerf*-1;
                    }
                }
                //normal inside offset command
                if(int_cam_array[i][13] == 1){ //ccw contour
                    if(int_cam_array[i][20] == 1){ //g2
                        offset = kerf;
                    }
                    if(int_cam_array[i][21] == 1){ //g3
                        offset = kerf*-1;
                    }
                }

                //keep orginal object..
                int_cam_array[temp_counter][0] = 3; //arc
                //int_cam_array[temp_counter][1] = 5;
                double_cam_array[temp_counter][56] = 0; //red
                double_cam_array[temp_counter][57] = 0; //green
                double_cam_array[temp_counter][58] = 1; //blue
                double_cam_array[temp_counter][59] = 1; //alpha

                //int_cam_array[temp_counter][2] = 1; //linewidth
                double_cam_array[temp_counter][19] = double_cam_array[i][19];//linewidth

                int_cam_array[temp_counter][5] = current_linetype;
                int_cam_array[temp_counter][12] = int_cam_array[i][12]; //contour cw
                int_cam_array[temp_counter][13] = int_cam_array[i][13]; //contour ccw
                int_cam_array[temp_counter][14] = int_cam_array[i][14]; //contournumber
                int_cam_array[temp_counter][15] = int_cam_array[i][15]; //closed contour mark
                int_cam_array[temp_counter][16] = int_cam_array[i][16]; //depth

                int_cam_array[temp_counter][20] = int_cam_array[i][20]; //g2
                int_cam_array[temp_counter][21] = int_cam_array[i][21]; //g3

                double_cam_array[temp_counter][6] = x_center;
                double_cam_array[temp_counter][7] = y_center;
                double_cam_array[temp_counter][9] = radius + offset;
                double_cam_array[temp_counter][11] = double_cam_array[i][11]; //keep the same start angle..
                double_cam_array[temp_counter][12] = double_cam_array[i][12];

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
                double Xb = double_cam_array[i][0]; //x start
                double Yb = double_cam_array[i][1]; //y start
                double AC = radius + offset;
                double AB = radius;
                double Xc = Xa + (AC * (Xb - Xa) / AB); //new startpoint coordinate..
                double Yc = Ya + (AC * (Yb - Ya) / AB);
                double_cam_array[temp_counter][0] = Xc;
                double_cam_array[temp_counter][1] = Yc;

                //arc offset endpoint calculation
                Xb = double_cam_array[i][3]; //x end
                Yb = double_cam_array[i][4]; //y end
                Xc = Xa + (AC * (Xb - Xa) / AB); //new endpoint coordinate..
                Yc = Ya + (AC * (Yb - Ya) / AB);
                double_cam_array[temp_counter][3] = Xc;
                double_cam_array[temp_counter][4] = Yc;

                //arc offset mid on curve calculation
                Xb = double_cam_array[i][15]; //x mid
                Yb = double_cam_array[i][16]; //y mid
                Xc = Xa + (AC * (Xb - Xa) / AB); //new midpoint coordinate..
                Yc = Ya + (AC * (Yb - Ya) / AB);
                double_cam_array[temp_counter][15] = Xc;
                double_cam_array[temp_counter][16] = Yc;

                temp_counter++;
            }



            if(int_cam_array[i][0] == 1){//id line


                //qDebug()<< "write line.. ";
                rotate_degrees = 90;

                //rotate orginal line..
                double temp_x = double_cam_array[i][0];
                double temp_y = double_cam_array[i][1];

                double rotate_dist_x_endpoint = double_cam_array[i][3] - temp_x;
                double rotate_dist_y_endpoint = double_cam_array[i][4] - temp_y;

                double rotate_x1 = cos(rotate_degrees * M_PI / 180.0 )* rotate_dist_x_endpoint - sin(rotate_degrees * M_PI / 180.0 ) * rotate_dist_y_endpoint;
                double rotate_y1 = sin(rotate_degrees * M_PI / 180.0 )* rotate_dist_x_endpoint + cos(rotate_degrees * M_PI / 180.0 ) * rotate_dist_y_endpoint;

                //modify line lenght to offset input..
                //calculate line length
                double object_x0 = double_cam_array[i][0];
                double object_y0 = double_cam_array[i][1];
                double object_x1 = rotate_x1 + temp_x;
                double object_y1 = rotate_y1 + temp_y;

                //formulat : A2 + B2 = C2
                double object_A = object_x1 - object_x0;
                double object_B = object_y1 - object_y0;
                double object_C = sqrt(pow(object_A,2)+pow(object_B,2));

                double object_radius = kerf;
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
                double dist_x = object_x_end - double_cam_array[i][0];
                double dist_y = object_y_end - double_cam_array[i][1];
                double object_x2 = double_cam_array[i][3] + dist_x;
                double object_y2 = double_cam_array[i][4] + dist_y;

                //keep orginal object..
                int_cam_array[temp_counter][0] = 1; //id line
                //int_cam_array[temp_counter][1] = 5; //color blue..
                double_cam_array[temp_counter][56] = 0; //red
                double_cam_array[temp_counter][57] = 0; //green
                double_cam_array[temp_counter][58] = 1; //blue
                double_cam_array[temp_counter][59] = 1; //alpha

                //int_cam_array[temp_counter][2] = 1; //linewidth
                double_cam_array[temp_counter][19] = double_cam_array[i][19];//linewidth

                int_cam_array[temp_counter][5] = current_linetype;
                int_cam_array[temp_counter][12] = int_cam_array[i][12]; //contour cw
                int_cam_array[temp_counter][13] = int_cam_array[i][13]; //contour ccw
                int_cam_array[temp_counter][14] = int_cam_array[i][14]; //contournumber
                int_cam_array[temp_counter][15] = int_cam_array[i][15]; //closed contour mark
                int_cam_array[temp_counter][16] = int_cam_array[i][16]; //depth
                double_cam_array[temp_counter][0] = object_x_end;
                double_cam_array[temp_counter][1] = object_y_end;
                //double_cam_array[temp_counter][2] = snap_cad_pos_z;
                double_cam_array[temp_counter][3] = object_x2;
                double_cam_array[temp_counter][4] = object_y2;
                //double_cam_array[temp_counter][5] = snap_cad_pos_z;

                temp_counter++;
            }
        }


    }
    //qDebug() << "cam counter after offset : " <<  cam_counter;
    cam_counter = temp_counter;
}









