#include "g_code.h"
#include <core_functions/variables.h>
#define myqDebug() qDebug() << fixed << qSetRealNumberPrecision(3)

void calculate_i_j();

g_code::g_code()
{
    calculate_i_j();

    double feedrate = extern_cutspeed.toDouble();
    double power = extern_power_rpm.toDouble();
    double startheight = extern_start_height.toDouble();
    double cutheight = extern_cut_height.toDouble();
    double piercespeed = extern_plunge_speed.toDouble();
    int temp = 0;
    bool bool_temp = 0;
    int first_line = 0;
    double temp_lead_in_x = 0; //for circle i and j calculation..
    double temp_lead_in_y = 0;
    bool open_contour = 0;

    QFile file_out(QDir::currentPath() + "/cadcam/" + gcode_filename);
    if(!file_out.open(QIODevice::WriteOnly /*| QIODevice::Append*/)) {
        qDebug() << "error writing file" << file_out.errorString();
    }
    QTextStream stream(&file_out);
    stream.setRealNumberNotation(QTextStream::FixedNotation);
    stream.setRealNumberPrecision(3); //avoid sientific notations..

    file_out.resize(0); //empty file

    //gcode intro :
    stream << gcode_intro << endl;
    stream << "G0 Z" << travelheight << endl;
    stream << "" << endl;

    for(int k=5; k>-1; k--){ //dept layers..

        for(int i =0; i<cam_counter; i++){

            if(int_cam_array[i][16] == k){    //depth

                if(double_cam_array[i][56] == 0.6 && double_cam_array[i][57] == 0.6 && double_cam_array[i][58] == 0.6 && int_cam_array[i][0] != 0){//color grey, open contour, no empty id..

                    if(!open_contour){
                        open_contour=1;
                        stream<< "(Open Contour id : " << int_cam_array[i][14] << " Depth:" << k << ")" << endl;
                        stream<< "G0" << " X" << double_cam_array[i][0] << " Y" << double_cam_array[i][1] << " Z" << travelheight << endl;
                        stream << "M3" << " S" << power << endl;
                        stream << gcode_startblock << endl;
                        stream<< "G1" << " Z" << cutheight << " F" << piercespeed <<endl;
                    }
                    if(open_contour){
                        if(int_cam_array[i][0] == 1){ //line
                            stream<< "G1" << " X" << double_cam_array[i][3] << " Y" << double_cam_array[i][4] << " F" << feedrate << endl;
                        }
                        if(int_cam_array[i][0] == 3){ //arc
                            if(int_cam_array[i][20] ==1){ //g2
                                stream << "G2" << " X" << double_cam_array[i][3] << " Y" << double_cam_array[i][4] << " Z" << cutheight << " I" << double_cam_array[i][22] << " J" << double_cam_array[i][23] << " F" << feedrate << endl;
                            }
                            if(int_cam_array[i][21] ==1){ //g3
                                stream << "G3" << " X" << double_cam_array[i][3] << " Y" << double_cam_array[i][4] << " Z" << cutheight << " I" << double_cam_array[i][22] << " J" << double_cam_array[i][23] << " F" << feedrate << endl;
                            }
                        }
                    }
                    if(int_cam_array[i][11]==-1){
                        open_contour=0;
                        stream << gcode_offblock << endl;
                        stream<< "G0"<< " Z" << travelheight << endl;
                        stream << "" << endl;
                    }
                }

                if(double_cam_array[i][56] == 0 && double_cam_array[i][57] == 0 && double_cam_array[i][58] == 1 && int_cam_array[i][24] != 1  && int_cam_array[i][0] != 0){//color blue, do not use the lead in lines at this stage.. no emtpy id..
                    //qDebug()<< "blue found at i : " << i;

                    if(!bool_temp){
                        //first line of g-code at each contour..
                        temp = int_cam_array[i][14];
                        first_line = i;
                        bool_temp = 1;

                        stream<< "(Closed contour id : " << int_cam_array[i][14] << " Depth:" << k << ")" << endl;

                        //find the lead in of this contour..
                        for(int i =0; i<cam_counter; i++){
                            if(temp == int_cam_array[i][14] && int_cam_array[i][24] == 1){ //lead in line at pos i..  24 is lead in..
                                stream<< "G0" << " X" << double_cam_array[i][0] << " Y" << double_cam_array[i][1] << " Z" << travelheight << endl; //rapid to object at travelheight..
                                stream<< "G0" << " Z" << startheight << endl;
                                stream<< "M3" << " S" << power << endl;
                                stream<< gcode_startblock << endl;
                                stream<< "G1" << " Z"<< cutheight << " F" << piercespeed << endl;
                                stream<< "G1" << " X" << double_cam_array[i][3] << " Y" << double_cam_array[i][4] << " Z"  << cutheight << " F" << extern_cutspeed << endl; //lead in move..
                                temp_lead_in_x = double_cam_array[i][3]; //lead in endpoint is circle startpoint..
                                temp_lead_in_y = double_cam_array[i][4];
                            }
                        }
                    }

                    if(bool_temp && int_cam_array[i+1][14]!=temp){
                        bool_temp=0;

                        //intersect last line with first line
                        if(int_cam_array[i][0] == 1){ //line
                            stream<< "G1"<< " X" << double_cam_array[i][3] << " Y" << double_cam_array[i][4] << " Z" << cutheight << " F" << feedrate << endl;
                            stream<< gcode_offblock << endl;
                            stream<< "G0" << " Z" << travelheight << endl;
                            stream<< "" << endl;
                        }
                        if(int_cam_array[i][0] == 3){ //arc
                            if(int_cam_array[i][20] ==1){ //g2
                                stream<< "G2" << " X" << double_cam_array[i][3] << " Y" << double_cam_array[i][4] << " Z" << cutheight << " I" << double_cam_array[i][22] << " J" << double_cam_array[i][23] << " F" << feedrate << endl;
                                stream<< gcode_offblock << endl;
                                stream<< extern_rapid_move_sign << " Z" << travelheight << endl;
                                stream<< "" << endl;
                            }
                            if(int_cam_array[i][21] ==1){ //g3
                                stream<< "G3" << " X" << double_cam_array[i][3] << " Y" << double_cam_array[i][4] << " Z" << cutheight << " I" << double_cam_array[i][22] << " J" << double_cam_array[i][23] << " F" << feedrate  << endl;
                                stream<< gcode_offblock << endl;
                                stream<< "G0"<< " Z" << travelheight << endl;
                                stream<< "" << endl;
                            }
                        }
                        if(int_cam_array[i][0] == 2){ //circle, no endpoint means full circle..
                            double I = double_cam_array[i][6] - temp_lead_in_x; //lead in x - center x
                            double J = double_cam_array[i][7] - temp_lead_in_y; //lead in y - center y, check if this must be a +

                            if(int_cam_array[i][20] ==1){ //g2

                                //myqDebug()<< "G2 I" << double_cam_array[i][22]*-1 << " J " << double_cam_array[i][23] << " F" << feedrate << "(Circle)";
                                stream<< "G2" << " I" << I << " J" << J << " F" << feedrate << endl;
                                stream<< gcode_offblock << endl;
                                stream<< "G0" << " Z" << travelheight << endl;
                                stream<< "" << endl;
                            }
                            if(int_cam_array[i][21] ==1){ //g3
                                stream<< "G3" << " I" << I << " J" << J << " F" << feedrate << endl;
                                stream<< gcode_offblock << endl;
                                stream<< "G0" << " Z" << travelheight << endl;
                                stream<< "" << endl;
                            }
                        }
                    }

                    if(bool_temp && int_cam_array[i+1][14]==temp){

                        //intersect next item
                        if(int_cam_array[i][0] == 1){ //line
                            stream<< "G1" << " X" << double_cam_array[i][3] << " Y" << double_cam_array[i][4] << " Z" << cutheight << " F" << feedrate << endl;
                        }
                        if(int_cam_array[i][0] == 3){ //arc
                            if(int_cam_array[i][20] ==1){ //g2
                                stream<< "G2" << " X" << double_cam_array[i][3] << " Y" << double_cam_array[i][4] << " Z" << cutheight << " I" << double_cam_array[i][22] << " J" << double_cam_array[i][23] << " F" << feedrate << endl;
                            }
                            if(int_cam_array[i][21] ==1){ //g3
                                stream<< "G3" << " X" << double_cam_array[i][3] << " Y" << double_cam_array[i][4] << " Z" << cutheight << " I" << double_cam_array[i][22] << " J" << double_cam_array[i][23] << " F" << feedrate << endl;
                            }
                        }

                    }
                }
            }
        }
    }

    //gcode outtro :
    stream << gcode_outtro << endl;

    file_out.close();
}

void calculate_i_j(){

    for(int i =0; i<cam_counter; i++){

        if(((double_cam_array[i][56] == 0 && double_cam_array[i][57] == 0 && double_cam_array[i][58] == 1)||(double_cam_array[i][56] == 0.6 && double_cam_array[i][57] == 0.6 && double_cam_array[i][58] == 0.6)) && (int_cam_array[i][0] == 3 || int_cam_array[i][0] == 2)){//color blue.. id = arc or circle..

            //old code from dxf2gcode program..
            //calcutation arc startpoint adjacent side
            double degree_start = 180 - double_cam_array[i][12];/*end angle*/
            double adjacent_start_side = cos(degree_start*(M_PI/180)) * double_cam_array[i][9];
            double opposite_start_side = sin(degree_start*(M_PI/180)) * double_cam_array[i][9];

            //calcutation arc endpoint adjacent side
            double degree_end = 90 - double_cam_array[i][11];/*start angle*/
            double adjacent_end_side = cos(degree_end*(M_PI/180)) * double_cam_array[i][9]; /*radius*/
            double opposite_end_side = sin(degree_end*(M_PI/180)) * double_cam_array[i][9];

            double g2_arc_i = adjacent_start_side;
            double g2_arc_j = opposite_start_side*-1;

            double g3_arc_i = opposite_end_side*-1;
            double g3_arc_j = adjacent_end_side*-1;

            //qDebug()<< "G00 - G02 arc start (Gcode arc : G00 XYZ)";
            //qDebug()<< "g2_x_start : " << g2_x_start << " g2_y_start : " << g2_y_start;;
            //qDebug()<< "g2_x_end : " << g2_x_end << " g2_y_end : " << g2_y_end << "g2_arc_i : " << g2_arc_i << " g2_arc_j : " << g2_arc_j;

            //qDebug()<< "G00 - G03 arc start (Gcode arc : G00 XYZ)";
            //qDebug()<< "g3_x_start : " << g3_x_start << " g3_y_start : " << g3_y_start;;
            //qDebug()<< "g3_x_end : " << g3_x_end << " g3_y_end : " << g3_y_end << "g3_arc_i : " << g3_arc_i << " g3_arc_j : " << g3_arc_j;

            //write to array..
            if(int_cam_array[i][0] == 3 ){//id arc..
                if(int_cam_array[i][20] == 1){ //g2
                    double_cam_array[i][22] = g2_arc_i;// I
                    double_cam_array[i][23] = g2_arc_j;// J
                }
                if(int_cam_array[i][21] == 1){ //g3
                    double_cam_array[i][22] = g3_arc_i;// I
                    double_cam_array[i][23] = g3_arc_j;// J
                }
            }
        }
    }
}
























