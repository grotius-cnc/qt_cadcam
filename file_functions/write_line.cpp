#include "write_line.h"
#include <core_functions/variables.h>

write_line::write_line()
{
    //QFile file_out(QDir::currentPath() + "/" + filename_out);

    //if cad color is bylayer then lines turn to blue..

    QFile file_out(filename_out);
    if(!file_out.open(QIODevice::WriteOnly | QIODevice::Append)) {
        qDebug() << "error writing file" << file_out.errorString();
    }

    file_out.resize(0); //empty file

    QTextStream stream(&file_out);

    for(int i = 0; i < cad_counter; i++){

        if(int_cad_array[i][0] == 1){ //id line

            stream  << endl; //empty line
            stream << "LINE" << endl; //id
            stream  << endl; //empty line
            stream << " 62" << endl; //colorcode
            stream << int_cad_array[i][1] << endl;
            stream << " 10" << endl; //x start
            stream << double_cad_array[i][0] << endl;
            stream << " 20" << endl; //y start
            stream << double_cad_array[i][1] << endl;
            stream << " 30" << endl; //z start
            stream << double_cad_array[i][2] << endl;
            stream << " 11" << endl; //x end
            stream << double_cad_array[i][3] << endl;
            stream << " 21" << endl; //y end
            stream << double_cad_array[i][4] << endl;
            stream << " 31" << endl; //z end
            stream << double_cad_array[i][5] << endl;

        }
    }
    file_out.close();
}
