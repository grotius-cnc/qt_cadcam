#include "write_gro.h"
#include <core_functions/variables.h>

write_gro::write_gro(QString filename)
{
    qDebug()<< "file to write : " << filename;

    QFile file_out(filename);
    if(!file_out.open(QIODevice::ReadWrite)) { //| QIODevice::Append
        qDebug() << "error writing file" << file_out.errorString();
    }

    file_out.resize(0); //empty file

    QTextStream stream(&file_out);

    for(int i = 0; i < cad_counter; i++){

        for(int j = 0; j < 29; j++){
                stream << int_cad_array[i][j] << endl;
        }

        stream << string_cad_array[i][0] << endl;

        for(int j = 0; j < 60; j++){
                stream << double_cad_array[i][j] << endl;
        }
    }
    file_out.close();
}
