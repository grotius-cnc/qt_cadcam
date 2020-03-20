#include "polytree.h"
#include <iostream>
#include <core_functions/variables.h>
//#include <cam_functions/triangulation.h>
#include <cam_functions/point_in_polygon.h>

polytree::polytree()
{
    QVector<int> dept_0; //top level..
    QVector<int> dept_1;
    QVector<int> dept_2;
    QVector<int> dept_3;
    QVector<int> dept_4;
    QVector<int> dept_5;
    QVector<int> level_0_contour;
    QVector<int> level_1_contour;
    QVector<int> level_2_contour;
    QVector<int> level_3_contour;
    QVector<int> level_4_contour;
    QVector<int> level_5_contour;

    QVector<int>::iterator it;
    QVector<int>::iterator it1;

//    std::cout << endl;
//    std::cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx " << std::endl;
//    std::cout << "depth layers output " << std::endl;
//    std::cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx " << std::endl;
//    std::cout << endl;

    //1. List of contournumbers in cam array..
    for(int i = 0; i<cam_counter; i++){
        if(!contournumbers.contains(int_cam_array[i][14]) && int_cam_array[i][0] != 0){ //no emtpy id's..
            contournumbers.append(int_cam_array[i][14]);
        }
    }


    //create depth 0
    for(it = contournumbers.begin(); it != contournumbers.end(); ++it){
        dept_0.push_back(*it);
        //cout << "depth_0 : " << *it << endl;
    }

    //colorize depth 0
    for(it = dept_0.begin(); it != dept_0.end(); it++){
        for(int i = 0; i<cam_counter; i++){
            if(int_cam_array[i][14] == *it){
                double_cam_array[i][56] = 1; //red
                double_cam_array[i][57] = 0; //green
                double_cam_array[i][58] = 0; //blue
                double_cam_array[i][59] = 1; //alpha
                int_cam_array[i][16] = 0;    //depth 0
            }
        }
    }

    //create depth 1
    for(it = dept_0.begin(); it != dept_0.end(); it++){
        //check_insides(*it);
        (point_in_polygon(*it));

        for(it1 = inside.begin(); it1 != inside.end(); ++it1){
            if(dept_1.contains(*it1)){
                //do nothing
            } else {
                //cout << "depth_1 : " << *it1 << endl;
                dept_1.push_back(*it1);
            }
        }
        inside.clear();
    }

    //colorize depth 1
    for(it = dept_1.begin(); it != dept_1.end(); it++){
        for(int i = 0; i<cam_counter; i++){
            if(int_cam_array[i][14] == *it){
                double_cam_array[i][56] = 1; //red
                double_cam_array[i][57] = 1; //green (red+green=yellow)
                double_cam_array[i][58] = 0; //blue
                double_cam_array[i][59] = 1; //alpha
                int_cam_array[i][16] = 1;    //depth 1
            }
        }
    }

    //create depth 2
    for(it = dept_1.begin(); it != dept_1.end(); it++){
        (point_in_polygon(*it));

        for(int i = 0; i < inside.size(); i++){
            if(!dept_2.contains(inside.at(i))){
                dept_2.push_back(inside.at(i));
            }
        }
        inside.clear();
    }

    //colorize depth 2
    for(it = dept_2.begin(); it != dept_2.end(); it++){
        for(int i = 0; i<cam_counter; i++){
            if(int_cam_array[i][14] == *it){
                double_cam_array[i][56] = 1; //red
                double_cam_array[i][57] = 0; //green
                double_cam_array[i][58] = 0; //blue
                double_cam_array[i][59] = 1; //alpha
                int_cam_array[i][16] = 2;    //depth 2
            }
        }
    }

    //create depth 3
    for(it = dept_2.begin(); it != dept_2.end(); it++){
        //check_insides(*it);
        (point_in_polygon(*it));

        for(int i = 0; i < inside.size(); i++){
            if(!dept_3.contains(inside.at(i))){
                //cout << "depth_3 : " << inside.at(i) << endl;
                dept_3.push_back(inside.at(i));
            }
        }
        inside.clear();
    }

    //colorize depth 3
    for(it = dept_3.begin(); it != dept_3.end(); it++){
        for(int i = 0; i<cam_counter; i++){
            if(int_cam_array[i][14] == *it){
                double_cam_array[i][56] = 1; //red
                double_cam_array[i][57] = 1; //green
                double_cam_array[i][58] = 0; //blue
                double_cam_array[i][59] = 1; //alpha
                int_cam_array[i][16] = 3;    //depth 3
            }
        }
    }

    //create depth 4
    for(it = dept_3.begin(); it != dept_3.end(); it++){
        //check_insides(*it);
        (point_in_polygon(*it));

        for(int i = 0; i < inside.size(); i++){
            if(!dept_4.contains(inside.at(i))){
                //cout << "depth_4 : " << inside.at(i) << endl;
                dept_4.push_back(inside.at(i));
            }
        }
        inside.clear();
    }

    //colorize depth 4
    for(it = dept_4.begin(); it != dept_4.end(); it++){
        for(int i = 0; i<cam_counter; i++){
            if(int_cam_array[i][14] == *it){
                double_cam_array[i][56] = 1; //red
                double_cam_array[i][57] = 0; //green
                double_cam_array[i][58] = 0; //blue
                double_cam_array[i][59] = 1; //alpha
                int_cam_array[i][16] = 4;    //depth 4
            }
        }
    }

    //create depth 5
    for(it = dept_4.begin(); it != dept_4.end(); it++){
        //check_insides(*it);
        (point_in_polygon(*it));

        for(int i = 0; i < inside.size(); i++){
            if(!dept_5.contains(inside.at(i))){
                //cout << "depth_5 : " << inside.at(i) << endl;
                dept_5.push_back(inside.at(i));
            }
        }
        inside.clear();
    }

    //colorize depth 5
    for(it = dept_5.begin(); it != dept_5.end(); it++){
        for(int i = 0; i<cam_counter; i++){
            if(int_cam_array[i][14] == *it){
                //int_cam_array[i][1] = 2; //yellow
                double_cam_array[i][56] = 1; //red
                double_cam_array[i][57] = 1; //green
                double_cam_array[i][58] = 0; //blue
                double_cam_array[i][59] = 1; //alpha
                int_cam_array[i][16] = 5;    //depth 5
            }
        }
    }

    //create level 0
    for(it = dept_0.begin(); it != dept_0.end(); ++it){
        if(!dept_1.contains(*it)){
            level_0_contour.push_back(*it);
        }
    }

    //create level 1
    for(it = level_0_contour.begin(); it != level_0_contour.end(); ++it){

        (point_in_polygon(*it));
        for(it1 = inside.begin(); it1 != inside.end(); ++it1){
            if(!dept_2.contains(*it1)){
                level_1_contour.append(*it1);
            }
        }
        inside.clear();
    }

    //create level 2
    cout << " " << endl;
    for(it = contournumbers.begin(); it != contournumbers.end(); ++it){

        if(level_0_contour.contains(*it) || level_1_contour.contains(*it)){
            //do nothing..
        } else {

            if(!dept_3.contains(*it)){
                //cout << "level 2 contour : " << *it << endl;
                level_2_contour.push_back(*it);
            }
        }
    }

    //create level 3
    for(it = level_2_contour.begin(); it != level_2_contour.end(); ++it){

        //cout << "level 2 contour : " << *it << endl;

        //check_insides(*it);
        (point_in_polygon(*it));
        for(it1 = inside.begin(); it1 != inside.end(); ++it1){
            if(!dept_4.contains(*it1)){
                //cout << "   level 3 contour : " << *it1 << endl;
                level_3_contour.append(*it1);
            }
        }
        inside.clear();
    }

    //create level 4
    //cout << " " << endl;
    for(it = contournumbers.begin(); it != contournumbers.end(); ++it){

        if(level_0_contour.contains(*it) || level_1_contour.contains(*it) || level_2_contour.contains(*it) || level_3_contour.contains(*it) || dept_5.contains(*it)){
            //do nothing..
        } else {
            //cout << "level 4 contour : " << *it << endl;
            level_4_contour.push_back(*it);
        }
    }

    //create level 5
    for(it = level_4_contour.begin(); it != level_4_contour.end(); ++it){

        //cout << "level 4 contour : " << *it << endl;

        //check_insides(*it);
        (point_in_polygon(*it));
        for(it1 = inside.begin(); it1 != inside.end(); ++it1){

                //cout << "   level 5 contour : " << *it1 << endl;
                level_5_contour.append(*it1);
        }
        inside.clear();
    }
    dept_0.clear();
    dept_1.clear();
    dept_2.clear();
    dept_3.clear();
    dept_4.clear();
    dept_5.clear();
    level_0_contour.clear();
    level_1_contour.clear();
    level_2_contour.clear();
    level_3_contour.clear();
    level_4_contour.clear();
    level_5_contour.clear();


}


























