#include "contour_recognize.h"
#include <core_functions/variables.h>
#include <array_functions/empty_cam_array.h>
#include <array_functions/copy_cad_to_cam_array.h>


void find_match();
void single_contours();
void open_contours();
void closed_contours();
void area_calculation();

contour_recognize::contour_recognize()
{
    for(int i = 0; i<cad_counter; i++){
        int_cad_array[i][3] = 0; //no select
    }

    find_match();
    single_contours();
    open_contours();
    closed_contours();
    area_calculation();
}

void find_match(){

    for(int k = 0; k<cad_counter; k++){
        int_cad_array[k][10] = -1;
        int_cad_array[k][11] = -1;
    }

    //define open ends..
    for(int k = 0; k<cad_counter; k++){
        for(int l = 0; l<cad_counter; l++){

            //end-end match
            if((double_cad_array[k][3]) == (double_cad_array[l][3]) && (double_cad_array[k][4]) == (double_cad_array[l][4]) && k!=l){
                int_cad_array[k][11] = l;
            } else
                //end-start match
                if((double_cad_array[k][3]) == (double_cad_array[l][0]) && (double_cad_array[k][4]) == (double_cad_array[l][1]) && k!=l){
                    int_cad_array[k][11] = l;
                } else
                    //start-start match
                    if((double_cad_array[k][0]) == (double_cad_array[l][0]) && (double_cad_array[k][1]) == (double_cad_array[l][1]) && k!=l){
                        int_cad_array[k][10] = l;
                    } else
                        //start-end match
                        if((double_cad_array[k][0]) == (double_cad_array[l][3]) && (double_cad_array[k][1]) == (double_cad_array[l][4]) && k!=l){
                            int_cad_array[k][10] = l;
                        }
        }
    }

    //make sure with one side open path's the end match is not -1..
    for(int k = 0; k<cad_counter; k++){
        if(int_cad_array[k][11] == -1 && int_cad_array[k][10] != -1){

            //flip
            double temp_x = double_cad_array[k][0];
            double temp_y = double_cad_array[k][1];
            int start_match = int_cad_array[k][10];
            int end_match = int_cad_array[k][11];
            double_cad_array[k][0] = double_cad_array[k][3];
            double_cad_array[k][1] = double_cad_array[k][4];
            double_cad_array[k][3] = temp_x;
            double_cad_array[k][4] = temp_y;
            int_cad_array[k][10] = end_match;
            int_cad_array[k][11] = start_match;
        }
    }

    //print match output..
    for(int i = 0; i<cad_counter; i++){
        //qDebug()<< "id : " << i << " start match : " << int_cad_array[i][10] << " end match : " << int_cad_array[i][11];
    }
}

void single_contours(){
    //circles are open ends..
    for(int i = 0; i<cad_counter; i++){
        if(int_cad_array[i][0] == 2 || int_cad_array[i][0] == 7 ){ //id circle, id point
            int_cad_array[i][10] = -1;
            int_cad_array[i][11] = -1;
        }
    }

    //text string item, exclude from contour recognize algoritme..
    for(int i = 0; i<cad_counter; i++){
        if(int_cad_array[i][0] == 10){ //id text
            int_cad_array[i][10] = -1;
            int_cad_array[i][11] = -1;
            int_cad_array[i][3] = 1; //select
        }
    }

    //print stand alone objects..
    for(int i = 0; i<cad_counter; i++){
        if(int_cad_array[i][10]==-1 && int_cad_array[i][11]==-1 && int_cad_array[i][0] != 10){ //no startmatch, no endmatch, no text string item..
            int_cad_array[i][14] = contournumber;
            int_cad_array[i][15] = 0; //closed contour mark
            int_cad_array[i][3] = 1; //select

            if(int_cad_array[i][0] == 2){ //id circle
                int_cad_array[i][15] = 1; //closed contour mark
            }

            copy_cad_to_cam_array(i,cam_counter);
            cam_counter++;
            contournumber++;
            qDebug()<< "single contour id : " << i;
            qDebug()<< "contournumber     : " << contournumber;
        }
    }
}

void open_contours(){

    bool stop=0;
    int source=0;
    int target=0;
    bool trigger=0;
    QList<int> list;

    while(!stop){

        //done to prevent writing first line for closed contour..
        for(int i = 0; i<cad_counter; i++){
            if(int_cad_array[i][10]==-1 && int_cad_array[i][11]!=-1 ){ //don't append circles or stand alone objects..
                list.append(i);
            }
        }
        if(list.size()==0){
            qDebug()<< "list=0";
            stop=1;
            list.clear();
            goto label;
        }

        //find first non selected..
        if(!trigger){
            for(int i = 0; i<cad_counter; i++){
                if(int_cad_array[i][10]==-1 && int_cad_array[i][3]==0){
                    source=i;
                    break;
                }
            }
        }

        for(target=0; target<cad_counter; target++){
            //end-end match
            if((double_cad_array[source][3]) == (double_cad_array[target][3]) && (double_cad_array[source][4]) == (double_cad_array[target][4]) && source!=target){
                //flip
                double temp_x = double_cad_array[target][0];
                double temp_y = double_cad_array[target][1];
                int start_match = int_cad_array[target][10];
                int end_match = int_cad_array[target][11];
                double_cad_array[target][0] = double_cad_array[target][3];
                double_cad_array[target][1] = double_cad_array[target][4];
                double_cad_array[target][3] = temp_x;
                double_cad_array[target][4] = temp_y;
                int_cad_array[target][10] = end_match;
                int_cad_array[target][11] = start_match;
            }
        }

        for(target=0; target<cad_counter; target++){
            //end-start match
            if((double_cad_array[source][3]) == (double_cad_array[target][0]) && (double_cad_array[source][4]) == (double_cad_array[target][1]) && source!=target){

                int_cad_array[source][3] = 1;//select
                int_cad_array[source][14] = contournumber;
                int_cad_array[source][15] = 0; //open contour mark..
                copy_cad_to_cam_array(source,cam_counter);
                qDebug()<< "open contour id   : " << source;
                cam_counter++;

                trigger=1;
                source = target;

                if(int_cad_array[target][11]==-1){

                    int_cad_array[target][3] = 1;//select
                    int_cad_array[target][14] = contournumber;
                    int_cad_array[target][15] = 0; //closed contour mark
                    copy_cad_to_cam_array(target,cam_counter);
                    qDebug()<< "open contour id   : " << target;
                    cam_counter++;
                    contournumber++;
                    qDebug()<< "contournumber     : " << contournumber;
                    trigger=0;
                }
            }
        }

        label:

        //check if all -1 items are done..
        int select=1;
        for(int i = 0; i<cad_counter; i++){
            if(int_cad_array[i][11]==-1 && int_cad_array[i][3]==0){
                select=0;
                break;
            }
            if(int_cad_array[i][10]==-1 && int_cad_array[i][3]==0){
                select=0;
                break;
            }
        }
        if(select == 1){stop = 1;}
    }
}

void closed_contours(){

    bool stop=0;
    int source=0;
    int target=0;
    bool trigger=0;

    while(!stop){

        //find first non selected..
        if(!trigger){
            for(int i = 0; i<cad_counter; i++){
                if(int_cad_array[i][3]==0){
                    source=i;
                    break;
                }
            }
        }

        for(target=0; target<cad_counter; target++){
            //end-end match
            if(int(double_cad_array[source][3]) == int(double_cad_array[target][3]) && int(double_cad_array[source][4]) == int(double_cad_array[target][4]) && source!=target){
                //flip
                double temp_x = double_cad_array[target][0];
                double temp_y = double_cad_array[target][1];
                int start_match = int_cad_array[target][10];
                int end_match = int_cad_array[target][11];
                double_cad_array[target][0] = double_cad_array[target][3];
                double_cad_array[target][1] = double_cad_array[target][4];
                double_cad_array[target][3] = temp_x;
                double_cad_array[target][4] = temp_y;
                int_cad_array[target][10] = end_match;
                int_cad_array[target][11] = start_match;
            }
        }

        for(target=0; target<cad_counter; target++){
            //end-start match
            if(int(double_cad_array[source][3]) == int(double_cad_array[target][0]) && int(double_cad_array[source][4]) == int(double_cad_array[target][1]) && source!=target && int_cad_array[source][3]==0){

                int_cad_array[source][3] = 1;//select
                int_cad_array[source][14] = contournumber;
                int_cad_array[source][15] = 1; //closed contour mark..
                copy_cad_to_cam_array(source,cam_counter);
                qDebug()<< "closed contour id   : " << source;
                cam_counter++;

                trigger=1;
                source = target;

                if(int_cad_array[target][3]==1){
                    contournumber++;
                    qDebug()<< "contournumber     : " << contournumber;
                    trigger=0;
                }
            }
        }

        //check if all -1 items are done..
        int select=1;
        for(int i = 0; i<cad_counter; i++){

            if(int_cad_array[i][3]==0){
                select=0;
                break;
            }
        }
        if(select == 1){stop = 1;}
    }

}

void area_calculation(){

    //deselect all..
    for(int k = 0; k<cad_counter; k++){
        int_cad_array[k][3] = 0;
    }
    for(int k = 0; k<cam_counter; k++){
        int_cam_array[k][3] = 0;
    }

    //calculate object area's..
    double sum = 0;
    int contournr = 0;
    int startnr = 0;
    bool start = 0;
    double area = 0;
    for(int k = 0; k<cam_counter; k++){

        if(int_cam_array[k][15] == 1){ //closed contour mark
            if(!start){
                contournr = int_cam_array[k][14];
                startnr = k;
                start = 1;}

            if(start && (int_cam_array[k+1][14] == contournr)){
                sum+=((double_cam_array[k+1][0] - double_cam_array[k][0])) * ((double_cam_array[k+1][1] + double_cam_array[k][1]));
            }
            if(start && (int_cam_array[k+1][14] != contournr)){ //at last line..
                sum+=((double_cam_array[startnr][0] - double_cam_array[k][0])) * ((double_cam_array[startnr][1] + double_cam_array[k][1]));
                area = sum/2;
                //qDebug() << "area mm2 :" << area;

                //write area to contournr items..
                for(int l = 0; l<cam_counter; l++){
                    if(int_cam_array[l][14] == contournr){
                        double_cam_array[l][20] = area;

                        if(area > 0){
                            int_cam_array[l][12] = 1; //predefined cw..
                        }
                        if(area < 0){
                            int_cam_array[l][13] = 1; //predefined ccw..
                        }
                    }
                }
                start = 0;
                sum = 0;
                area = 0;
            }
        }
    }

}






















