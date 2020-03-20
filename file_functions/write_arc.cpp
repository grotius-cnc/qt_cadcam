#include "write_arc.h"
#include <core_functions/variables.h>

write_arc::write_arc()
{
    //QFile file_out(QDir::currentPath() + "/" + filename_out);

    QFile file_out(filename_out);
    if(!file_out.open(QIODevice::WriteOnly | QIODevice::Append)) {
        qDebug() << "error writing file" << file_out.errorString();
    }
    QTextStream stream(&file_out);

    for(int i = 0; i < cad_counter; i++){

        if(int_cad_array[i][0] == 3){ //id arc

            stream  << endl; //empty line
            stream << "ARC" << endl; //id
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
            stream << " 50" << endl; //start angle
            stream << double_cad_array[i][11] << endl;
            stream << " 51" << endl; //end angle
            stream << double_cad_array[i][12] << endl;
        }
    }
    file_out.close();
}
