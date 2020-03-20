#include "cam_text.h"
#include <core_functions/variables.h>

double pos_x1 = 0;
double pos_y1 = 0;
double scale1 = 0;
QString text1;
int stringlenght1 = 0;
double char_offset1 = 0;

//text to cam..
double cam_x_offset1 = 0;
double cam_y_offset1 = 0;

cam_text::cam_text()
{
    pos_x1 = 0;
    pos_y1 = 0;
    scale1 = 0;
    stringlenght1 = 0;
    char_offset1 = 0;

    //text to cam..
    cam_x_offset1 = 0;
    cam_y_offset1 = 0;

    for(int i=0; i<cad_counter; i++){
        if(int_cad_array[i][0] == 10){ // id = text

            pos_x1 = double_cad_array[i][0];       //text pos x
            pos_y1 = double_cad_array[i][1];       //text pos y
            scale1 = double_cad_array[i][13];      //text height
            text1 = string_cad_array[i][0];   //text string

            text1.replace("new_line","\n",Qt::CaseSensitive);
            //qDebug()<< "text : " << text;

            if(!text1.contains("\n")){ //single line..

                cam_x_offset1=pos_x1;
                cam_y_offset1=pos_y1;
                draw_text(text1);

            } else { //multiline text..

                QString line;
                int factor = 1;

                while(text1.size() != 0){
                    line.append(text1.at(0));
                    if(line.contains("\n")){
                        line.chop(1);
                        //qDebug()<< "line : " << line;

                        //cam
                        cam_x_offset1=pos_x1; //start new line..
                        cam_y_offset1=pos_y1-(factor*scale1*1.5);
                        //end cam

                        draw_text(line);
                        factor++;
                        line.clear();
                    }
                    text1.remove(0,1);
                }
            }
        }
    }
}

void cam_text::draw_text(QString text)
{
    stringlenght1 = text.size();
    char_offset1 = scale1;

    for(int i=0; i<stringlenght1; i++){

//        QString sign = text.at(i);
//        load_text(scale1, sign + ".gro");
//        char_offset1 = scale1;
//        cam_x_offset1+=char_offset1;

        //lower characters..
        if(text.at(i)=="a"){
            load_text(scale1, "a.gro");
            cam_x_offset1+=char_offset1;
        }
        if(text.at(i)=="b"){
            load_text(scale1, "b.gro");
            cam_x_offset1+=char_offset1;
        }
        if(text.at(i)=="c"){
            load_text(scale1, "c.gro");
            cam_x_offset1+=char_offset1;
        }
        if(text.at(i)=="d"){
            load_text(scale1, "d.gro");
            cam_x_offset1+=char_offset1;
        }
        if(text.at(i)=="e"){
            load_text(scale1, "e.gro");
            cam_x_offset1+=char_offset1;
        }
        if(text.at(i)=="f"){
            load_text(scale1, "f.gro");
            cam_x_offset1+=char_offset1;
        }
        if(text.at(i)=="g"){
            load_text(scale1, "g.gro");
            cam_x_offset1+=char_offset1;
        }
        if(text.at(i)=="h"){
            load_text(scale1, "h.gro");
            cam_x_offset1+=char_offset1;
        }
        if(text.at(i)=="i"){
            load_text(scale1, "i.gro");
            cam_x_offset1+=0.2*char_offset1;
        }
        if(text.at(i)=="j"){
            load_text(scale1, "j.gro");
            cam_x_offset1+=0.7*char_offset1;
        }
        if(text.at(i)=="k"){
            load_text(scale1, "k.gro");
            cam_x_offset1+=char_offset1;
        }
        if(text.at(i)=="l"){
            load_text(scale1, "l.gro");
            cam_x_offset1+=char_offset1;
        }
        if(text.at(i)=="m"){
            load_text(scale1, "m.gro");
            cam_x_offset1+=char_offset1;
        }
        if(text.at(i)=="n"){
            load_text(scale1, "n.gro");
            cam_x_offset1+=char_offset1;
        }
        if(text.at(i)=="o"){
            load_text(scale1, "o.gro");
            cam_x_offset1+=char_offset1;
        }
        if(text.at(i)=="p"){
            load_text(scale1, "p.gro");
            cam_x_offset1+=char_offset1;
        }
        if(text.at(i)=="q"){
            load_text(scale1, "q.gro");
            cam_x_offset1+=char_offset1;
        }
        if(text.at(i)=="r"){
            load_text(scale1, "r.gro");
            cam_x_offset1+=char_offset1;
        }
        if(text.at(i)=="s"){
            load_text(scale1, "s.gro");
            cam_x_offset1+=char_offset1;
        }
        if(text.at(i)=="t"){
            load_text(scale1, "t.gro");
            cam_x_offset1+=char_offset1;
        }
        if(text.at(i)=="u"){
            load_text(scale1, "u.gro");
            cam_x_offset1+=char_offset1;
        }
        if(text.at(i)=="v"){
            load_text(scale1, "v.gro");
            cam_x_offset1+=char_offset1;
        }
        if(text.at(i)=="w"){
            load_text(scale1, "w.gro");
            cam_x_offset1+=char_offset1;
        }
        if(text.at(i)=="x"){
            load_text(scale1, "x.gro");
            cam_x_offset1+=char_offset1;
        }
        if(text.at(i)=="y"){
            load_text(scale1, "y.gro");
            cam_x_offset1+=char_offset1;
        }
        if(text.at(i)=="z"){
            load_text(scale1, "z.gro");
            cam_x_offset1+=char_offset1;
        }


        //upper characters..
        if(text.at(i)=="A"){
            load_text(scale1, "A.gro");
            cam_x_offset1+=char_offset1;
        }
        if(text.at(i)=="B"){
            load_text(scale1, "B.gro");
            cam_x_offset1+=char_offset1;
        }
        if(text.at(i)=="C"){
            load_text(scale1, "C.gro");
            cam_x_offset1+=char_offset1;
        }
        if(text.at(i)=="D"){
            load_text(scale1, "D.gro");
            cam_x_offset1+=char_offset1;
        }
        if(text.at(i)=="E"){
            load_text(scale1, "E.gro");
            cam_x_offset1+=char_offset1;
        }
        if(text.at(i)=="F"){
            load_text(scale1, "F.gro");
            cam_x_offset1+=char_offset1;
        }
        if(text.at(i)=="G"){
            load_text(scale1, "G.gro");
            cam_x_offset1+=char_offset1;
        }
        if(text.at(i)=="H"){
            load_text(scale1, "H.gro");
            cam_x_offset1+=char_offset1;
        }
        if(text.at(i)=="I"){
            load_text(scale1, "I.gro");
            cam_x_offset1+=char_offset1;
        }
        if(text.at(i)=="J"){
            load_text(scale1, "J.gro");
            cam_x_offset1+=char_offset1;
        }
        if(text.at(i)=="K"){
            load_text(scale1, "K.gro");
            cam_x_offset1+=char_offset1;
        }
        if(text.at(i)=="L"){
            load_text(scale1, "L.gro");
            cam_x_offset1+=char_offset1;
        }
        if(text.at(i)=="M"){
            load_text(scale1, "M.gro");
            cam_x_offset1+=char_offset1;
        }
        if(text.at(i)=="N"){
            load_text(scale1, "N.gro");
            cam_x_offset1+=char_offset1;
        }
        if(text.at(i)=="O"){
            load_text(scale1, "O.gro");
            cam_x_offset1+=char_offset1;
        }
        if(text.at(i)=="P"){
            load_text(scale1, "P.gro");
            cam_x_offset1+=char_offset1;
        }
        if(text.at(i)=="Q"){
            load_text(scale1, "Q.gro");
            cam_x_offset1+=char_offset1;
        }
        if(text.at(i)=="R"){
            load_text(scale1, "R.gro");
            cam_x_offset1+=char_offset1;
        }
        if(text.at(i)=="S"){
            load_text(scale1, "S.gro");
            cam_x_offset1+=char_offset1;
        }
        if(text.at(i)=="T"){
            load_text(scale1, "T.gro");
            cam_x_offset1+=char_offset1;
        }
        if(text.at(i)=="U"){
            load_text(scale1, "U.gro");
            cam_x_offset1+=char_offset1;
        }
        if(text.at(i)=="V"){
            load_text(scale1, "V.gro");
            cam_x_offset1+=char_offset1;
        }
        if(text.at(i)=="W"){
            load_text(scale1, "W.gro");
            cam_x_offset1+=char_offset1;
        }
        if(text.at(i)=="X"){
            load_text(scale1, "X.gro");
            cam_x_offset1+=char_offset1;
        }
        if(text.at(i)=="Y"){
            load_text(scale1, "Y.gro");
            cam_x_offset1+=char_offset1;
        }
        if(text.at(i)=="Z"){
            load_text(scale1, "Z.gro");
            cam_x_offset1+=char_offset1;
        }

        //digits..
        if(text.at(i)=="1"){
            load_text(scale1, "1.gro");
            cam_x_offset1+=char_offset1;
        }
        if(text.at(i)=="2"){
            load_text(scale1, "2.gro");
            cam_x_offset1+=char_offset1;
        }
        if(text.at(i)=="3"){
            load_text(scale1, "3.gro");
            cam_x_offset1+=char_offset1;
        }
        if(text.at(i)=="4"){
            load_text(scale1, "4.gro");
            cam_x_offset1+=char_offset1;
        }
        if(text.at(i)=="5"){
            load_text(scale1, "5.gro");
            cam_x_offset1+=char_offset1;
        }
        if(text.at(i)=="6"){
            load_text(scale1, "6.gro");
            cam_x_offset1+=char_offset1;
        }
        if(text.at(i)=="7"){
            load_text(scale1, "7.gro");
            cam_x_offset1+=char_offset1;
        }
        if(text.at(i)=="8"){
            load_text(scale1, "8.gro");
            cam_x_offset1+=char_offset1;
        }
        if(text.at(i)=="9"){
            load_text(scale1, "9.gro");
            cam_x_offset1+=char_offset1;
        }
        if(text.at(i)=="0"){
            load_text(scale1, "0.gro");
            cam_x_offset1+=char_offset1;
        }

        //special characters
        if(text.at(i)=="."){
            load_text(scale1, "char_dot.gro");
            cam_x_offset1+=char_offset1;
        }
        if(text.at(i)==":"){
            load_text(scale1, "char_doublepoint.gro");
            cam_x_offset1+=char_offset1;
        }
        if(text.at(i)=="-"){
            load_text(scale1, "char_min.gro");
            cam_x_offset1+=char_offset1;
        }
        if(text.at(i)=="_"){
            load_text(scale1, "char_undescore.gro");
            cam_x_offset1+=char_offset1;
        }
        if(text.at(i)=="!"){
            load_text(scale1, "char_exclamation.gro");
            cam_x_offset1+=char_offset1;
        }
        if(text.at(i)=="="){
            load_text(scale1, "char_equal.gro");
            cam_x_offset1+=char_offset1;
        }
        if(text.at(i)=="+"){
            load_text(scale1, "char_plus.gro");
            cam_x_offset1+=char_offset1;
        }
        if(text.at(i)=="/"){
            load_text(scale1, "char_forwardslash.gro");
            cam_x_offset1+=char_offset1;
        }
        if(text.at(i)=="|"){
            load_text(scale1, "char_or.gro");
            cam_x_offset1+=char_offset1;
        }
        if(text.at(i)=="*"){
            load_text(scale1, "char_star.gro");
            cam_x_offset1+=char_offset1;
        }
        if(text.at(i)=="?"){
            load_text(scale1, "char_question.gro");
            cam_x_offset1+=char_offset1;
        }
        if(text.at(i)=="{"){
            load_text(scale1, "char_curly_open.gro");
            cam_x_offset1+=char_offset1;
        }
        if(text.at(i)=="}"){
            load_text(scale1, "char_curly_close.gro");
            cam_x_offset1+=char_offset1;
        }
        if(text.at(i)=="%"){
            load_text(scale1, "char_procent.gro");
            cam_x_offset1+=char_offset1;
        }
        if(text.at(i)=="["){
            load_text(scale1, "char_square_bracket_open.gro");
            cam_x_offset1+=char_offset1;
        }
        if(text.at(i)=="]"){
            load_text(scale1, "char_square_bracket_close.gro");
            cam_x_offset1+=char_offset1;
        }
        if(text.at(i)=="("){
            load_text(scale1, "char_open_bracket.gro");
            cam_x_offset1+=char_offset1;
        }
        if(text.at(i)==")"){
            load_text(scale1, "char_close_bracket.gro");
            cam_x_offset1+=char_offset1;
        }
        if(text.at(i)=="<"){
            load_text(scale1, "char_angle_open_bracket.gro");
            cam_x_offset1+=char_offset1;
        }
        if(text.at(i)==">"){
            load_text(scale1, "char_angle_close_bracket.gro");
            cam_x_offset1+=char_offset1;
        }
        if(text.at(i)=="^"){
            load_text(scale1, "char_roof.gro");
            cam_x_offset1+=char_offset1;
        }
    }
}

void cam_text::load_text(double scale, QString filename){

    int i = 0;

    QFile file_in(QDir::currentPath() + "cadcam/fonts/" + filename );
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

            //text data
            if(i==26){
                int_cad_array[cad_counter][i] = 1; //text flag
            }
            if(i==30){
                double_cad_array[cad_counter][i-30] = cam_x_offset1+double_cad_array[cad_counter][i-30]*scale;
            }
            if(i==31){
                double_cad_array[cad_counter][i-30] = cam_y_offset1+double_cad_array[cad_counter][i-30]*scale;
            }
            if(i==33){
                double_cad_array[cad_counter][i-30] = cam_x_offset1+double_cad_array[cad_counter][i-30]*scale;
            }
            if(i==34){
                double_cad_array[cad_counter][i-30] = cam_y_offset1+double_cad_array[cad_counter][i-30]*scale;
            }
        i++;

    }
    file_in.close();
    cad_counter++;
}

















