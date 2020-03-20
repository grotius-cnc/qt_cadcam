#include "contour_reverse.h"
#include <core_functions/variables.h>
#include <array_functions/swap_cam_array.h>

contour_reverse::contour_reverse(QList<int> contour_nr)
{
    QList<int>::iterator it;
    QList<int>::iterator it1;
    QList<int> items;
    bool stop=0;

    //swap array items..
    for(it=contour_nr.begin(); it!=contour_nr.end(); it++){

        for(int i=0; i<cam_counter; i++){

            if(*it == int_cam_array[i][14]){
                items.push_back(i);
            }
        }
        while(items.size()!=0 && stop==0){

            if(items.size()%2 == 0){ //done for even contour lists..
                swap_cam_array(items.first(), items.last());
                items.removeFirst();
                items.removeLast();
            }
            if(items.size()%2 != 0){ //done for odd contour lists..
                swap_cam_array(items.first(), items.last());
                items.removeFirst();
                items.removeLast();

                if(items.size()==1){
                    stop = 1;
                }
            }
        }
        items.clear();
        stop=0;
    }

    //inverse path coordinates..
    for(it=contour_nr.begin(); it!=contour_nr.end(); it++){

        for(int i=0; i<cam_counter; i++){

            if(*it == int_cam_array[i][14]){
                items.push_back(i);
                //qDebug()<< "item path reversed : " << i;
            }
        }
        for(it1 = items.begin(); it1!=items.end(); it1++){

            int temp_cw = int_cam_array[*it1][12];
            int temp_ccw = int_cam_array[*it1][13];
            double temp_x_start = double_cam_array[*it1][0];
            double temp_y_start = double_cam_array[*it1][1];
            double temp_x_end = double_cam_array[*it1][3];
            double temp_y_end = double_cam_array[*it1][4];

            int_cam_array[*it1][12] = temp_ccw;
            int_cam_array[*it1][13] = temp_cw;
            double_cam_array[*it1][3] = temp_x_start;
            double_cam_array[*it1][4] = temp_y_start;
            double_cam_array[*it1][0] = temp_x_end;
            double_cam_array[*it1][1] = temp_y_end;
        }
        items.clear();
    }
    contour_nr.clear();
}






















