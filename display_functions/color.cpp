#include "color.h"
#include <core_functions/variables.h>

color::color(int i)
{

    //red_list.at(i) 0-255
    //green_list.at(i)
    //blue_list.at(i)
    //alpha_list.at(i)
    //current_index_color

    //    int red = red_list.at(current_index_color)/255;
    //    int green = green_list.at(current_index_color)/255;
    //    int blue = blue_list.at(current_index_color)/255;
    //    int alpha = alpha_list.at(current_index_color)/255;

    //glClearColor(1,1,1,1); //white color..

    if(mode_cad){

        if(mode_background_white){
            //invert if color is black or white..
            if(double_cad_array[i][56]==1 && double_cad_array[i][57]==1 && double_cad_array[i][58]==1){ //white
                glColor4f(0, 0, 0, double_cad_array[i][59]); //to black..
            } else {
                glColor4f(double_cad_array[i][56], double_cad_array[i][57], double_cad_array[i][58], double_cad_array[i][59]);
            }
        }

        if(!mode_background_white){
            //invert if color is black or white..
            if(double_cad_array[i][56]==0 && double_cad_array[i][57]==0 && double_cad_array[i][58]==0){ //black
                glColor4f(1, 1, 1, double_cad_array[i][59]); //to white..
            } else {
                glColor4f(double_cad_array[i][56], double_cad_array[i][57], double_cad_array[i][58], double_cad_array[i][59]);
            }
        }


    }

    if(mode_cam){
        glColor4f(double_cam_array[i][56], double_cam_array[i][57], double_cam_array[i][58], double_cam_array[i][59]);
    }

}
