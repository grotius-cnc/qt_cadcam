#include "write_circle.h"
#include <core_functions/variables.h>

write_circle::write_circle()
{
    //QFile file_out(QDir::currentPath() + "/" + filename_out);

    QFile file_out(filename_out);
    if(!file_out.open(QIODevice::WriteOnly | QIODevice::Append)) {
        qDebug() << "error writing file" << file_out.errorString();
    }
    QTextStream stream(&file_out);

    for(int i = 0; i < cad_counter; i++){

        if(int_cad_array[i][0] == 2){ //id circle

            stream  << endl; //empty line
            stream << "CIRCLE" << endl; //id
            stream  << endl; //empty line
            stream << " 62" << endl; //colorcode
            stream << int_cad_array[i][1] << endl;
            stream << " 10" << endl; //x center
            stream << double_cad_array[i][6] << endl;
            stream << " 20" << endl; //y center
            stream << double_cad_array[i][7] << endl;
            stream << " 30" << endl; //z center
            stream << double_cad_array[i][8] << endl;
            stream << " 40" << endl; //radius
            stream << double_cad_array[i][9] << endl;
        }
    }
    file_out.close();
}

