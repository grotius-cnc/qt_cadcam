#include "point_in_polygon.h"
#include <core_functions/variables.h>


point_in_polygon::point_in_polygon(int object_id)
{
    QVector<int> contours;
    QVector<int>::iterator it;
    QVector<QVector<int>> path;
    int child = 0;
    int result = 0;
    int circle_points = 20;

    //1. List of contournumbers in cam array..
    contours.append(object_id);

    //2. Add paths..
    for(it = contours.begin(); it != contours.end(); ++it){
        for(int i = 0; i<cam_counter; i++){
            if(*it == int_cam_array[i][14]){
                if(int_cam_array[i][0]==1 || int_cam_array[i][0]==3 ){//id line, id arc
                    path.push_back({int(double_cam_array[i][0]),int(double_cam_array[i][1])});

                    if(int_cam_array[i][0]==3){ //if arc, push back extra arc midpoint to be more accurate..
                        path.push_back({int(double_cam_array[i][15]),int(double_cam_array[i][16])});
                    }

                } else
                    if(int_cam_array[i][0]==2){//id circle
                        //path.push_back({int(double_cam_array[i][6]),int(double_cam_array[i][7])});

                        //update 30-11-2019
                        //path.push_back({int(double_cam_array[i][25]),int(double_cam_array[i][26])}); //left
                        //path.push_back({int(double_cam_array[i][31]),int(double_cam_array[i][32])}); //top
                        //path.push_back({int(double_cam_array[i][28]),int(double_cam_array[i][29])}); //right
                        //path.push_back({int(double_cam_array[i][34]),int(double_cam_array[i][35])}); //bottom

                        //we need more points...
                        for(int k=0; k<360; k+=10){
                            //rotate circle left up to 360 degrees
                            double rotate_dist_x = double_cam_array[i][25] - double_cam_array[i][6];
                            double rotate_dist_y = double_cam_array[i][26] - double_cam_array[i][7];
                            double rotate_x = cos(k * M_PI / 180.0 )* rotate_dist_x - sin(k * M_PI / 180.0 ) * rotate_dist_y;
                            double rotate_y = sin(k * M_PI / 180.0 )* rotate_dist_x + cos(k * M_PI / 180.0 ) * rotate_dist_y;
                            double result_x = rotate_x + double_cam_array[i][6];
                            double result_y = rotate_y + double_cam_array[i][7];

                            path.push_back({int(result_x),int(result_y)}); //bottom
                        }

                    }

            }
        }

        //3. Check points inside paths..
        for(int i = 0; i<cam_counter; i++){
            if(*it != int_cam_array[i][14]){
                if(int_cam_array[i][0]==1 || int_cam_array[i][0]==3 ){//id line, id arc
                    result = pip(path.size(), path, int(double_cam_array[i][0]) ,int(double_cam_array[i][1]));
                } else
                    if(int_cam_array[i][0]==2){//id circle
                        result = pip(path.size(), path, int(double_cam_array[i][25]) ,int(double_cam_array[i][26]));
                    }

                child = int_cam_array[i][14];

                if(result==1){
                    //qDebug() << "parent" << *it << "child : " << child;
                    if(!inside.contains(child)){
                        inside.push_back(child);
                    }
                }
            }
        }
        path.clear();
    }
    contours.clear();
}

int point_in_polygon::pip(int n, QVector<QVector<int>> pos, int x, int y)
{
    int i, j, c = 0;
    for (i = 0, j = n-1; i < n; j = i++) {
        if ( ((pos[i][1]>y) != (pos[j][1]>y)) && (x < (pos[j][0]-pos[i][0]) * (y-pos[i][1]) / (pos[j][1]-pos[i][1]) + pos[i][0]) ){
            c = !c;
        }
    }
    return c;
}







