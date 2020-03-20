#include "final_direction.h"
#include <core_functions/variables.h>
#include <cam_functions/contour_reverse.h>

final_direction::final_direction()
{
    //change preprocessed contour direction into final contour direction
    QList<int> contour;
    for(int i=0; i<cam_counter; i++){
        if(int_cam_array[i][12] == 1 && double_cam_array[i][56] == 1 && double_cam_array[i][57] == 0 && double_cam_array[i][58] == 0){  //cw - colorcode red
            //do nothing
        }
        if(int_cam_array[i][13] == 1 && double_cam_array[i][56] == 1 && double_cam_array[i][57] == 1 && double_cam_array[i][58] == 0){  //ccw - colorcode yellow
            //do nothing
        }
        if(int_cam_array[i][13] == 1 && double_cam_array[i][56] == 1 && double_cam_array[i][57] == 0 && double_cam_array[i][58] == 0){  //ccw - colorcode red
            //change polygon direction
            if(!contour.contains(int_cam_array[i][14])){ //contour nr.
                contour.push_back(int_cam_array[i][14]);
            }
            //qDebug() << "must be reversed into cw.. : " << i;
        }
        if(int_cam_array[i][12] == 1 && double_cam_array[i][56] == 1 && double_cam_array[i][57] == 1 && double_cam_array[i][58] == 0){  //cw - colorcode yellow
            //change polygon direction
            if(!contour.contains(int_cam_array[i][14])){
                contour.push_back(int_cam_array[i][14]);
            }
            //qDebug() << "must be reversed into ccw.. : " << i;
        }
    }
    //contour reverse function..
    (contour_reverse(contour));
    contour.clear();

    //calculate if arc's are g2 or g3..
    for(int i=0; i<cam_counter; i++){

        if(int_cam_array[i][0]==3){ //id arc

            double x1 = double_cam_array[i][0]; //startpoint
            double y1 = double_cam_array[i][1];
            double x2 = double_cam_array[i][15]; //midpoint on arc circumfence
            double y2 = double_cam_array[i][16];
            double x = double_cam_array[i][3];
            double y = double_cam_array[i][4]; //endpoint

            double d=(x-x1)*(y2-y1)-(y-y1)*(x2-x1);
            if(d>0){
                int_cam_array[i][20] = 1; //g2
            }
            if(d<0){
                int_cam_array[i][21] = 1; //g3
            }
        }
    }

    //colorize open path's grey..
    QList<int> list;
    QList<int> open_contour;
    QList<int>::iterator it;
    for(int i = 0; i < cam_counter; i++){
        if(!list.contains(int_cad_array[i][14])){
            list.append(int_cad_array[i][14]);
            //qDebug()<< "contournumbers : " << int_cad_array[i][14];
        }
    }
    //look in the list if there are open contours..
    for(it = list.begin(); it != list.end(); it++){
        for(int i = 0; i<cam_counter; i++){
            if(int_cam_array[i][14] == *it){
                if((int_cam_array[i][10]==-1 || int_cam_array[i][11]==-1) &&  int_cam_array[i][0]!=2){ //no startmatch, no endmatch, no circle..

                    if(!open_contour.contains(int_cam_array[i][14])){
                        open_contour.append(int_cam_array[i][14]);
                        //qDebug()<< "open contournumbers : " << int_cad_array[i][14];
                    }
                }

            }
        }
    }

    //color open contours grey, excluding circles..
    for(it = open_contour.begin(); it != open_contour.end(); it++){
        for(int i = 0; i<cam_counter; i++){
            if(int_cam_array[i][14] == *it){

                double_cam_array[i][56] = 0.6;
                double_cam_array[i][57] = 0.6;
                double_cam_array[i][58] = 0.6; //blue
                double_cam_array[i][59] = 1;
            }
        }
    }

    list.clear(); open_contour.clear();
}
