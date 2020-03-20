#include "read_spline.h"
#include <core_functions/variables.h>

read_spline::read_spline()
{
    //QFile file_in(QDir::currentPath() + "/" + filename_in );
    int splinetrigger = 0;
    int x_start = 0;
    int y_start = 0;
    int z_start = 0;
    int x_control = 0;
    int y_control = 0;
    int z_control = 0;
    int x_control2 = 0;
    int y_control2 = 0;
    int z_control2 = 0;
    int x_end = 0;
    int y_end = 0;
    int z_end = 0;
    int count = 0;

    QFile file_in(filename_in );
    if(!file_in.open(QIODevice::ReadOnly)) {
        qDebug() << "error reading file" << file_in.errorString();
    }
    QTextStream in(&file_in);    // file to read

    while(!in.atEnd()) {
        QString line = in.readLine();

        if( (line.contains("SPLINE", Qt::CaseSensitive)) && (!line.contains("$DIMARCSYM", Qt::CaseSensitive)) && (!line.contains("$SPLINETYPE", Qt::CaseSensitive)) && (!line.contains("$SPLINESEGS", Qt::CaseSensitive)) ) //
        {
            int_cad_array[cad_counter][0] = 6;                           //id 6 = cubic hermite spline
            int_cad_array[cad_counter][2] = 1;                           //line width
            int_cad_array[cad_counter+1][0] = 6;                           //id 6 = cubic hermite spline
            int_cad_array[cad_counter+1][2] = 1;                           //line width
            splinetrigger = 1;
        }
        if(splinetrigger){
            if(line.contains(" 62", Qt::CaseSensitive)){                    //colorcode line
                colorcode_line = linenumber + 1;
            }
            if(linenumber == colorcode_line){
                int_cad_array[cad_counter][1] = line.toInt();
                int_cad_array[cad_counter+1][1] = line.toInt();
            }

            //x start
            if(line.contains(" 11", Qt::CaseSensitive)&& count==0){
                x_start = linenumber + 1;
            }
            if(linenumber == x_start){
                double_cad_array[cad_counter][0] = line.toDouble();
                double_cad_array[cad_counter][50] = line.toDouble();
                double_cad_array[cad_counter+1][0] = line.toDouble();
            }
            //y start
            if(line.contains(" 21", Qt::CaseSensitive)&& count==0){
                y_start = linenumber + 1;
            }
            if(linenumber == y_start){
                double_cad_array[cad_counter][1] = line.toDouble();
                double_cad_array[cad_counter][51] = line.toDouble();
                double_cad_array[cad_counter+1][1] = line.toDouble();
                count=1;
            }


            //x control
            if(line.contains(" 11", Qt::CaseSensitive)&& count==1){
                x_control = linenumber + 1;
            }
            if(linenumber == x_control){
                double_cad_array[cad_counter][53] = line.toDouble();
                double_cad_array[cad_counter+1][50] = line.toDouble();
            }
            //y control
            if(line.contains(" 21", Qt::CaseSensitive)&& count==1){
                y_control = linenumber + 1;
            }
            if(linenumber == y_control){
                double_cad_array[cad_counter][54] = line.toDouble();
                double_cad_array[cad_counter+1][51] = line.toDouble();
                count=3;
            }


            //x control & x end
            if(line.contains(" 11", Qt::CaseSensitive)&& count==3){
                x_end = linenumber + 1;
            }
            if(linenumber == x_end){
                double_cad_array[cad_counter][3] = line.toDouble();
                double_cad_array[cad_counter+1][53] = line.toDouble();
                double_cad_array[cad_counter+1][3] = line.toDouble();

            }
            //y control
            if(line.contains(" 21", Qt::CaseSensitive)&& count==3){
                y_end = linenumber + 1;
            }
            if(linenumber == y_end){
                double_cad_array[cad_counter][4] = line.toDouble();
                double_cad_array[cad_counter+1][54] = line.toDouble();
                double_cad_array[cad_counter+1][4] = line.toDouble();
                cad_counter+=2;
                count=0;
            }

            //end
            if(line.contains("  0", Qt::CaseSensitive)){
                splinetrigger = 0;
            }
        }

        linenumber++;
    }
    file_in.close();
}
