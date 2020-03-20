#include "read_gro.h"
#include <core_functions/variables.h>

read_gro::read_gro(QString filename)
{
    //cad_counter = 0;
    int i = 0;

    QFile file_in(filename);
    if(!file_in.open(QIODevice::ReadOnly)) {
        qDebug() << "error reading file" << file_in.errorString();
    }
    QTextStream in(&file_in);    // file to read

    while(!in.atEnd()) {

        QString line = in.readLine();

            if(i==90){cad_counter++; i=0;}
            if(i<29){
                int_cad_array[cad_counter][i] = line.toInt();
            }
            if(i==29){
                string_cad_array[cad_counter][0] = line;
            }
            if(i>=30 && i < 90){
                double_cad_array[cad_counter][i-30] = line.toDouble();
            }
        i++;

    }
    file_in.close();
    cad_counter++;

}

