#include "read_line_text.h"
#include <core_functions/variables.h>

read_line_text::read_line_text(double x, double y, double z)
{
    //QFile file_in(QDir::currentPath() + "/" + filename_in);

    QFile file_in(filename_in);
    if(!file_in.open(QIODevice::ReadOnly)) {
        qDebug() << "error reading file" << file_in.errorString();
    }
    QTextStream in(&file_in);    // file to read

    while(!in.atEnd()) {
        QString line = in.readLine();

        //Search for "LINE", the ! means exclude this...
            if(line.contains("LINE", Qt::CaseSensitive) && (!line.contains("LWPOLYLINE", Qt::CaseSensitive)) && (!line.contains("$PLINEWID", Qt::CaseSensitive)) &&
                (!line.contains("$SPLINETYPE", Qt::CaseSensitive)) && (!line.contains("$SPLINESEGS", Qt::CaseSensitive)) && (!line.contains("$PLINEGEN", Qt::CaseSensitive)) &&
                (!line.contains("ACAD_MLINESTYLE", Qt::CaseSensitive)) && (!line.contains("MLINESTYLE", Qt::CaseSensitive) && (!line.contains("SPLINE", Qt::CaseSensitive))
                ))
            {
                int_cad_array[cad_counter][0] = 1;                              //id
                //int_cad_array[cad_counter][1] = color;                          //color
                int_cad_array[cad_counter][2] = 1;                              //line width
                int_cad_array[cad_counter][3] = 1;                              //select
                linetrigger = 1;
            }
            if(linetrigger){
                if(line.contains(" 62", Qt::CaseSensitive)){                    //colorcode line
                    colorcode_line = linenumber + 1;
                }
                if(linenumber == colorcode_line){                               //fill array
                    int_cad_array[cad_counter][1] = line.toInt();
                }
                if(line.contains(" 10", Qt::CaseSensitive)){
                    x_start_line = linenumber + 1;                              //x start line
                }
                if(linenumber == x_start_line){
                    double_cad_array[cad_counter][0] = line.toDouble() + x;      //fill array
                }
                if(line.contains(" 20", Qt::CaseSensitive)){
                    y_start_line = linenumber + 1;
                }
                if(linenumber == y_start_line){
                    double_cad_array[cad_counter][1] = line.toDouble() + y;
                }
                if(line.contains(" 30", Qt::CaseSensitive)){
                    z_start_line = linenumber + 1;
                }
                if(linenumber == z_start_line){
                    double_cad_array[cad_counter][2] = line.toDouble() + z;
                }
                if(line.contains(" 11", Qt::CaseSensitive)){
                    x_end_line = linenumber + 1;
                }
                if(linenumber == x_end_line){
                    double_cad_array[cad_counter][3] = line.toDouble() + x;
                }

                if(line.contains(" 21", Qt::CaseSensitive)){
                    y_end_line = linenumber + 1;
                }
                if(linenumber == y_end_line){
                    double_cad_array[cad_counter][4] = line.toDouble() + y;
                }

                if(line.contains(" 31", Qt::CaseSensitive)){
                    z_end_line = linenumber + 1;
                }
                if(linenumber == z_end_line){
                    double_cad_array[cad_counter][5] = line.toDouble() + z;
                    linetrigger = 0;
                    cad_counter++;
                }
            }

    linenumber++;
    }
    file_in.close();
}
