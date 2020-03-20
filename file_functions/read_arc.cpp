#include "read_arc.h"
#include <core_functions/variables.h>

read_arc::read_arc()
{
    //QFile file_in(QDir::currentPath() + "/" + filename_in );

    QFile file_in(filename_in );
    if(!file_in.open(QIODevice::ReadOnly)) {
        qDebug() << "error reading file" << file_in.errorString();
    }
    QTextStream in(&file_in);    // file to read

    while(!in.atEnd()) {
        QString line = in.readLine();

            if( (line.contains("ARC", Qt::CaseSensitive)) && (!line.contains("$DIMARCSYM", Qt::CaseSensitive)) )
            {
                int_cad_array[cad_counter][0] = 3;                           //id
                int_cad_array[cad_counter][5] = 65535;                       //line type (decimal value for solid line)
                double_cad_array[cad_counter][18] = 0;                       //line scale
                double_cad_array[cad_counter][19] = 1;                       //line width
                arctrigger = 1;
            }
            if(arctrigger){
                if(line.contains(" 62", Qt::CaseSensitive)){                    //colorcode line
                    colorcode_line = linenumber + 1;
                }
                if(linenumber == colorcode_line){                               //fill array
                    int value = line.toInt();

                    if(value == 1){ //red
                        double_cad_array[cad_counter][56] = 255; //red
                        double_cad_array[cad_counter][57] = 0; //green
                        double_cad_array[cad_counter][58] = 0; //blue
                        double_cad_array[cad_counter][59] = 255; //alpha
                        double_cad_array[cad_counter][19] = 2;
                    }
                    if(value == 2){ //yellow
                        double_cad_array[cad_counter][56] = 255; //red
                        double_cad_array[cad_counter][57] = 255; //green
                        double_cad_array[cad_counter][58] = 0; //blue
                        double_cad_array[cad_counter][59] = 255; //alpha
                    }
                    if(value == 3){ //green
                        double_cad_array[cad_counter][56] = 0; //red
                        double_cad_array[cad_counter][57] = 255; //green
                        double_cad_array[cad_counter][58] = 0; //blue
                        double_cad_array[cad_counter][59] = 255; //alpha
                    }
                    if(value == 4){ //cyan
                        double_cad_array[cad_counter][56] = 255; //red
                        double_cad_array[cad_counter][57] = 0; //green
                        double_cad_array[cad_counter][58] = 255; //blue
                        double_cad_array[cad_counter][59] = 255; //alpha
                    }
                    if(value == 5){ //blue
                        double_cad_array[cad_counter][56] = 49; //red
                        double_cad_array[cad_counter][57] = 112; //green
                        double_cad_array[cad_counter][58] = 206; //blue
                        double_cad_array[cad_counter][59] = 255; //alpha
                    }
                    if(value == 6){ //magenta
                        double_cad_array[cad_counter][56] = 0; //red
                        double_cad_array[cad_counter][57] = 255; //green
                        double_cad_array[cad_counter][58] = 255; //blue
                        double_cad_array[cad_counter][59] = 255; //alpha
                    }
                    if(value == 7){ //white
                        double_cad_array[cad_counter][56] = 255; //red
                        double_cad_array[cad_counter][57] = 255; //green
                        double_cad_array[cad_counter][58] = 255; //blue
                        double_cad_array[cad_counter][59] = 255; //alpha
                    }
                    if(value == 8){ //grey
                        double_cad_array[cad_counter][56] = 106; //red
                        double_cad_array[cad_counter][57] = 106; //green
                        double_cad_array[cad_counter][58] = 106; //blue
                        double_cad_array[cad_counter][59] = 255; //alpha
                    }
                    if(value == 9){ //orange/brown
                        double_cad_array[cad_counter][56] = 255; //red
                        double_cad_array[cad_counter][57] = 170; //green
                        double_cad_array[cad_counter][58] = 0; //blue
                        double_cad_array[cad_counter][59] = 255; //alpha
                    }
                }
                if(line.contains(" 10", Qt::CaseSensitive)){
                    x_center_line = linenumber + 1;                             //x start line
                }
                if(linenumber == x_center_line){
                    double_cad_array[cad_counter][6] = line.toDouble();      //fill array
                }
                if(line.contains(" 20", Qt::CaseSensitive)){
                    y_center_line  = linenumber + 1;
                }
                if(linenumber == y_center_line){
                    double_cad_array[cad_counter][7] = line.toDouble();
                }
                if(line.contains(" 30", Qt::CaseSensitive)){
                    z_center_line  = linenumber + 1;
                }
                if(linenumber == z_center_line){
                    double_cad_array[cad_counter][8] = line.toDouble();
                }
                if(line.contains(" 40", Qt::CaseSensitive)){
                    radius_line = linenumber + 1;
                }
                if(linenumber == radius_line){
                    double_cad_array[cad_counter][9] = line.toDouble();
                }

                if(line.contains(" 50", Qt::CaseSensitive)){
                    start_angle_line = linenumber + 1;
                }
                if(linenumber == start_angle_line){
                    double_cad_array[cad_counter][11] = line.toDouble();
                }

                if(line.contains(" 51", Qt::CaseSensitive)){
                    end_angle_line = linenumber + 1;
                }
                if(linenumber == end_angle_line){
                    double_cad_array[cad_counter][12] = line.toDouble();
                    arctrigger = 0;
                    cad_counter++;
                }
            }

    linenumber++;
    }
    file_in.close();
}
