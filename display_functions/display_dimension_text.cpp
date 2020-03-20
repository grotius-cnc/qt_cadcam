#include "display_dimension_text.h"
#include <core_functions/variables.h>
#include <display_functions/color.h>
#include <display_functions/linetype.h>
#include <display_functions/highlight.h>

#define myqDebug() qDebug() << fixed << qSetRealNumberPrecision(3)

void text_horizontal(int i);
void text_vertical(int i);
void draw_1(double scale);
void draw_2(double scale);
void draw_3(double scale);
void draw_4(double scale);
void draw_5(double scale);
void draw_6(double scale);
void draw_7(double scale);
void draw_8(double scale);
void draw_9(double scale);
void draw_0(double scale);
void draw_dot(double scale);
void draw_diameter(double scale);
void draw_R(double scale);
void draw_degrees(double scale);
double dimension_value = 0;

display_dimension_text::display_dimension_text(int i)
{
        glPushMatrix(); //new matrix, start with clean offset values..
        dimension_value = 0;

        if(int_cad_array[i][9] == 1){ // flag = 1
            text_horizontal(i);
        }
        if(int_cad_array[i][9] == 2){
            text_vertical(i);
        }
        if(int_cad_array[i][9] == 3){
            text_non_ortho(i);
        }
        if(int_cad_array[i][9] == 4){
                text_diameter(i);
        }
        if(int_cad_array[i][9] == 5){
                text_radius(i);
        }
        if(int_cad_array[i][9] == 6){
                text_angle_2p(i);
        }

        glPopMatrix(); //end matrix..
}

void display_dimension_text::text_angle_2p(int i)
{
    //double angle = atan2(p0y - p1y, p0x - p1x)*180/M_PI; qDebug()<< "angle degrees : " << angle;

    double angle_start_radians = (double_cad_array[i][11]/360)*(2*M_PI);/*start angle*/
    if(double_cad_array[i][12]==360){double_cad_array[i][12]=0;} //autocad degree problem..

    double angle_end_radians = (double_cad_array[i][12]/360)*(2*M_PI);

    if (angle_end_radians < angle_start_radians){  //this to avoid the start angle is bigger then the end angle value
        angle_end_radians += 2*M_PI;
    }

    double angle_rad = angle_end_radians-angle_start_radians;

    dimension_value = angle_rad*180/M_PI;

    int stringsize = QString::number(dimension_value).size();
    double scale = double_cad_array[i][13]; //dimension text height..
    double offset = double_cad_array[i][13]; //text is build from a grid layour of 1x1mm.. see file : drawings/dimension_characters.dxf

    glDisable(GL_LINE_STIPPLE);
    glLineWidth(1);

    if(mode_background_white){
        glColor4f(0, 0, 0, 1); //black..
    } else {glColor4f(1, 1, 1, 1);} //white..

    glTranslated( double_cad_array[i][15],  double_cad_array[i][16], 0);

    for(int k=0; k<stringsize; k++){

        if(QString::number(dimension_value).at(k)=="1"){
            draw_1(scale);
        }
        if(QString::number(dimension_value).at(k)=="2"){
            draw_2(scale);
        }
        if(QString::number(dimension_value).at(k)=="3"){
            draw_3(scale);
        }
        if(QString::number(dimension_value).at(k)=="4"){
            draw_4(scale);
        }
        if(QString::number(dimension_value).at(k)=="5"){
           draw_5(scale);
        }
        if(QString::number(dimension_value).at(k)=="6"){
           draw_6(scale);
        }
        if(QString::number(dimension_value).at(k)=="7"){
           draw_7(scale);
        }
        if(QString::number(dimension_value).at(k)=="8"){
           draw_8(scale);
        }
        if(QString::number(dimension_value).at(k)=="9"){
           draw_9(scale);
        }
        if(QString::number(dimension_value).at(k)=="0"){
           draw_0(scale);
        }
        if(QString::number(dimension_value).at(k)=="."){
           draw_dot(scale);
        }
        glTranslated(offset, 0, 0);
    }
    draw_degrees(scale); glTranslated(offset, 0, 0);

    glEnable(GL_LINE_STIPPLE);
}

void display_dimension_text::text_radius(int i)
{
    dimension_value = double_cad_array[i][9];

    double p1x = double_cad_array[i][21];
    double p1y = double_cad_array[i][22];
    double p0x = double_cad_array[i][23];
    double p0y = double_cad_array[i][24];

    double angle = atan2(p0y - p1y, p0x - p1x)*180/M_PI; //qDebug()<< "angle : " << angle;
    //Of course the return type is in radians, if you need it in degrees just do angle * 180 / PI

    int stringsize = QString::number(dimension_value).size();
    double scale = double_cad_array[i][13]; //dimension text height..
    double offset = double_cad_array[i][13]; //text is build from a grid layour of 1x1mm.. see file : drawings/dimension_characters.dxf

    //text bottom space.. offset baseline 1mm and calculate midpoint..
    double text_spacing = 1;
    QList<double> list;
    list = offset_line(double_cad_array[i][0],double_cad_array[i][1],double_cad_array[i][3],double_cad_array[i][4],text_spacing,90);
    //calculate midpoint..
    double text_mid_x =  (list.at(0) + list.at(2))/2;
    double text_start_y = (list.at(1) + list.at(3))/2;
    list.clear();


    glDisable(GL_LINE_STIPPLE);
    glLineWidth(1);

    if(mode_background_white){
        glColor4f(0, 0, 0, 1); //black..
    } else {glColor4f(1, 1, 1, 1);} //white..

    //glTranslated(x_mid, y_start,0);

    glTranslated(text_mid_x, text_start_y,0);
    glRotated(angle,0,0,1);
    glTranslated(((stringsize*offset)/2)*-1, 0,0);

    draw_R(scale); glTranslated(offset, 0, 0);

    for(int k=0; k<stringsize; k++){

        if(QString::number(dimension_value).at(k)=="1"){
            draw_1(scale);
        }
        if(QString::number(dimension_value).at(k)=="2"){
            draw_2(scale);
        }
        if(QString::number(dimension_value).at(k)=="3"){
            draw_3(scale);
        }
        if(QString::number(dimension_value).at(k)=="4"){
            draw_4(scale);
        }
        if(QString::number(dimension_value).at(k)=="5"){
           draw_5(scale);
        }
        if(QString::number(dimension_value).at(k)=="6"){
           draw_6(scale);
        }
        if(QString::number(dimension_value).at(k)=="7"){
           draw_7(scale);
        }
        if(QString::number(dimension_value).at(k)=="8"){
           draw_8(scale);
        }
        if(QString::number(dimension_value).at(k)=="9"){
           draw_9(scale);
        }
        if(QString::number(dimension_value).at(k)=="0"){
           draw_0(scale);
        }
        if(QString::number(dimension_value).at(k)=="."){
           draw_dot(scale);
        }
        glTranslated(offset, 0, 0);
    }
    glEnable(GL_LINE_STIPPLE);
}

void display_dimension_text::text_diameter(int i)
{
    dimension_value = double_cad_array[i][9]*2; //diameter = radius*2..

    double p1x = double_cad_array[i][21];
    double p1y = double_cad_array[i][22];
    double p0x = double_cad_array[i][23];
    double p0y = double_cad_array[i][24];

    double angle = atan2(p0y - p1y, p0x - p1x)*180/M_PI; //qDebug()<< "angle : " << angle;
    //Of course the return type is in radians, if you need it in degrees just do angle * 180 / PI

    int stringsize = QString::number(dimension_value).size();
    double scale = double_cad_array[i][13]; //dimension text height..
    double offset = double_cad_array[i][13]; //text is build from a grid layour of 1x1mm.. see file : drawings/dimension_characters.dxf

    //text bottom space.. offset baseline 1mm and calculate midpoint..
    double text_spacing = 1;
    QList<double> list;
    list = offset_line(double_cad_array[i][0],double_cad_array[i][1],double_cad_array[i][3],double_cad_array[i][4],text_spacing,90);
    //calculate midpoint..
    double text_mid_x =  (list.at(0) + list.at(2))/2;
    double text_start_y = (list.at(1) + list.at(3))/2;
    list.clear();


    glDisable(GL_LINE_STIPPLE);
    glLineWidth(1);

    if(mode_background_white){
        glColor4f(0, 0, 0, 1); //black..
    } else {glColor4f(1, 1, 1, 1);} //white..

    //glTranslated(x_mid, y_start,0);

    glTranslated(text_mid_x, text_start_y,0);
    glRotated(angle,0,0,1);
    glTranslated(((stringsize*offset)/2)*-1, 0,0);

    //add diameter sign..
    draw_diameter(scale); glTranslated(offset, 0, 0);

    for(int k=0; k<stringsize; k++){

        if(QString::number(dimension_value).at(k)=="1"){
            draw_1(scale);
        }
        if(QString::number(dimension_value).at(k)=="2"){
            draw_2(scale);
        }
        if(QString::number(dimension_value).at(k)=="3"){
            draw_3(scale);
        }
        if(QString::number(dimension_value).at(k)=="4"){
            draw_4(scale);
        }
        if(QString::number(dimension_value).at(k)=="5"){
           draw_5(scale);
        }
        if(QString::number(dimension_value).at(k)=="6"){
           draw_6(scale);
        }
        if(QString::number(dimension_value).at(k)=="7"){
           draw_7(scale);
        }
        if(QString::number(dimension_value).at(k)=="8"){
           draw_8(scale);
        }
        if(QString::number(dimension_value).at(k)=="9"){
           draw_9(scale);
        }
        if(QString::number(dimension_value).at(k)=="0"){
           draw_0(scale);
        }
        if(QString::number(dimension_value).at(k)=="."){
           draw_dot(scale);
        }
        glTranslated(offset, 0, 0);
    }
    glEnable(GL_LINE_STIPPLE);
}

void display_dimension_text::text_non_ortho(int i)
{
    dimension_value = sqrt(pow(double_cad_array[i][23]-double_cad_array[i][21],2)+pow(double_cad_array[i][24]-double_cad_array[i][22],2)); //has the dimension text value..

    double p1x = double_cad_array[i][21];
    double p1y = double_cad_array[i][22];
    double p0x = double_cad_array[i][23];
    double p0y = double_cad_array[i][24];

    double angle = atan2(p0y - p1y, p0x - p1x)*180/M_PI; //qDebug()<< "angle : " << angle;
    //Of course the return type is in radians, if you need it in degrees just do angle * 180 / PI

    int stringsize = QString::number(dimension_value).size();
    double scale = double_cad_array[i][13]; //dimension text height..
    double offset = double_cad_array[i][13]; //text is build from a grid layour of 1x1mm.. see file : drawings/dimension_characters.dxf

    //text bottom space.. offset baseline 1mm and calculate midpoint..
    double text_spacing = 1;
    QList<double> list;
    list = offset_line(double_cad_array[i][0],double_cad_array[i][1],double_cad_array[i][3],double_cad_array[i][4],text_spacing,90);
    //calculate midpoint..
    double text_mid_x =  (list.at(0) + list.at(2))/2;
    double text_start_y = (list.at(1) + list.at(3))/2;
    list.clear();


    glDisable(GL_LINE_STIPPLE);
    glLineWidth(1);

    if(mode_background_white){
        glColor4f(0, 0, 0, 1); //black..
    } else {glColor4f(1, 1, 1, 1);} //white..

    //glTranslated(x_mid, y_start,0);

    glTranslated(text_mid_x, text_start_y,0);
    glRotated(angle,0,0,1);
    glTranslated(((stringsize*offset)/2)*-1, 0,0);

    for(int k=0; k<stringsize; k++){

        if(QString::number(dimension_value).at(k)=="1"){
            draw_1(scale);
        }
        if(QString::number(dimension_value).at(k)=="2"){
            draw_2(scale);
        }
        if(QString::number(dimension_value).at(k)=="3"){
            draw_3(scale);
        }
        if(QString::number(dimension_value).at(k)=="4"){
            draw_4(scale);
        }
        if(QString::number(dimension_value).at(k)=="5"){
           draw_5(scale);
        }
        if(QString::number(dimension_value).at(k)=="6"){
           draw_6(scale);
        }
        if(QString::number(dimension_value).at(k)=="7"){
           draw_7(scale);
        }
        if(QString::number(dimension_value).at(k)=="8"){
           draw_8(scale);
        }
        if(QString::number(dimension_value).at(k)=="9"){
           draw_9(scale);
        }
        if(QString::number(dimension_value).at(k)=="0"){
           draw_0(scale);
        }
        if(QString::number(dimension_value).at(k)=="."){
           draw_dot(scale);
        }
        glTranslated(offset, 0, 0);
    }
    glEnable(GL_LINE_STIPPLE);
}

void text_vertical(int i)
{
    if(double_cad_array[i][22]>double_cad_array[i][24]){ //p0y, p1y..
        dimension_value = double_cad_array[i][22]-double_cad_array[i][24]; //qDebug()<< "dimension value : " << dimension_value;
    }
    if(double_cad_array[i][22]<double_cad_array[i][24]){
        dimension_value = double_cad_array[i][24]-double_cad_array[i][22]; //qDebug()<< "dimension value : " << dimension_value;
    }

    int stringsize = QString::number(dimension_value).size();
    double x_mid = double_cad_array[i][0] - 1; //text spacing
    double y_start = (double_cad_array[i][1] + double_cad_array[i][4])/2;
    double scale = double_cad_array[i][13]; //dimension text height..
    double offset = double_cad_array[i][13]; //text is build from a grid layour of 1x1mm.. see file : drawings/dimension_characters.dxf

    glDisable(GL_LINE_STIPPLE);
    glLineWidth(1);

    if(mode_background_white){
        glColor4f(0, 0, 0, 1); //black..
    } else {glColor4f(1, 1, 1, 1);} //white..

    glRotated(90,0,0,1);
    glTranslated(((stringsize*offset)/2)*-1,0,0); //center text in origin..
    //glTranslated(100, 0, 0);
    glTranslated(y_start, x_mid*-1,0);

    for(int k=0; k<stringsize; k++){

        if(QString::number(dimension_value).at(k)=="1"){
            draw_1(scale);
        }
        if(QString::number(dimension_value).at(k)=="2"){
            draw_2(scale);
        }
        if(QString::number(dimension_value).at(k)=="3"){
            draw_3(scale);
        }
        if(QString::number(dimension_value).at(k)=="4"){
            draw_4(scale);
        }
        if(QString::number(dimension_value).at(k)=="5"){
           draw_5(scale);
        }
        if(QString::number(dimension_value).at(k)=="6"){
           draw_6(scale);
        }
        if(QString::number(dimension_value).at(k)=="7"){
           draw_7(scale);
        }
        if(QString::number(dimension_value).at(k)=="8"){
           draw_8(scale);
        }
        if(QString::number(dimension_value).at(k)=="9"){
           draw_9(scale);
        }
        if(QString::number(dimension_value).at(k)=="0"){
           draw_0(scale);
        }
        if(QString::number(dimension_value).at(k)=="."){
           draw_dot(scale);
        }
        glTranslated(offset, 0, 0);
    }
    glEnable(GL_LINE_STIPPLE);
}

void text_horizontal(int i)
{
        if(double_cad_array[i][21]>double_cad_array[i][23]){ //p0x, p1x..
            dimension_value = double_cad_array[i][21]-double_cad_array[i][23]; //qDebug()<< "dimension value : " << dimension_value;
        }
        if(double_cad_array[i][21]<double_cad_array[i][23]){
            dimension_value = double_cad_array[i][23]-double_cad_array[i][21]; //qDebug()<< "dimension value : " << dimension_value;
        }

        int stringsize = QString::number(dimension_value).size();
        double x_mid = (double_cad_array[i][0] + double_cad_array[i][3])/2;
        double y_start = double_cad_array[i][1] + 1; //text spacing
        double scale = double_cad_array[i][13]; //dimension text height..
        double offset = double_cad_array[i][13]; //text is build from a grid layour of 1x1mm.. see file : drawings/dimension_characters.dxf

        glDisable(GL_LINE_STIPPLE);
        glLineWidth(1);

        if(mode_background_white){
            glColor4f(0, 0, 0, 1); //black..
        } else {glColor4f(1, 1, 1, 1);} //white..

        glTranslated(x_mid-((stringsize*offset)/2), y_start, 0);

        for(int k=0; k<stringsize; k++){

            if(QString::number(dimension_value).at(k)=="1"){
                draw_1(scale);
            }
            if(QString::number(dimension_value).at(k)=="2"){
                draw_2(scale);
            }
            if(QString::number(dimension_value).at(k)=="3"){
                draw_3(scale);
            }
            if(QString::number(dimension_value).at(k)=="4"){
                draw_4(scale);
            }
            if(QString::number(dimension_value).at(k)=="5"){
               draw_5(scale);
            }
            if(QString::number(dimension_value).at(k)=="6"){
               draw_6(scale);
            }
            if(QString::number(dimension_value).at(k)=="7"){
               draw_7(scale);
            }
            if(QString::number(dimension_value).at(k)=="8"){
               draw_8(scale);
            }
            if(QString::number(dimension_value).at(k)=="9"){
               draw_9(scale);
            }
            if(QString::number(dimension_value).at(k)=="0"){
               draw_0(scale);
            }
            if(QString::number(dimension_value).at(k)=="."){
               draw_dot(scale);
            }
            glTranslated(offset, 0, 0);
        }
        glEnable(GL_LINE_STIPPLE);
}

void draw_1(double scale){
    glBegin(GL_LINES);
    glVertex2d((0.1*scale), (0.0*scale));
    glVertex2d((0.9*scale), (0.0*scale));
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex2d((0.5*scale), (0.0*scale));
    glVertex2d((0.5*scale), (1.0*scale));
    glVertex2d((0.4*scale), (1.0*scale));
    glVertex2d((0.1*scale), (0.8*scale));
    glEnd();
}

void draw_2(double scale){
    glBegin(GL_LINE_STRIP);
    glVertex2d((0.9*scale), (0.0*scale));
    glVertex2d((0.1*scale), (0.0*scale));
    glVertex2d((0.9*scale), (0.7*scale));
    glVertex2d((0.9*scale), (0.8*scale));
    glVertex2d((0.6*scale), (1.0*scale));
    glVertex2d((0.4*scale), (1.0*scale));
    glVertex2d((0.1*scale), (0.8*scale));
    glEnd();
}

void draw_3(double scale){
    glBegin(GL_LINE_STRIP);
    glVertex2d((0.1*scale), (0.2*scale));
    glVertex2d((0.4*scale), (0.0*scale));
    glVertex2d((0.6*scale), (0.0*scale));
    glVertex2d((0.9*scale), (0.2*scale));
    glVertex2d((0.9*scale), (0.4*scale));
    glVertex2d((0.7*scale), (0.6*scale));
    glVertex2d((0.5*scale), (0.6*scale));
    glVertex2d((0.8*scale), (1.0*scale));
    glVertex2d((0.2*scale), (1.0*scale));
    glEnd();
}

void draw_4(double scale){
    glBegin(GL_LINE_STRIP);
    glVertex2d((0.7*scale), (0.0*scale));
    glVertex2d((0.7*scale), (1.0*scale));
    glVertex2d((0.6*scale), (1.0*scale));
    glVertex2d((0.1*scale), (0.5*scale));
    glVertex2d((0.1*scale), (0.4*scale));
    glVertex2d((0.9*scale), (0.4*scale));
    glEnd();
}

void draw_5(double scale){
    glBegin(GL_LINE_STRIP);
    glVertex2d((0.1*scale), (0.1*scale));
    glVertex2d((0.4*scale), (0.0*scale));
    glVertex2d((0.6*scale), (0.0*scale));
    glVertex2d((0.9*scale), (0.1*scale));
    glVertex2d((0.9*scale), (0.4*scale));
    glVertex2d((0.6*scale), (0.6*scale));
    glVertex2d((0.4*scale), (0.6*scale));
    glVertex2d((0.1*scale), (0.5*scale));
    glVertex2d((0.1*scale), (1.0*scale));
    glVertex2d((0.9*scale), (1.0*scale));
    glEnd();
}

void draw_6(double scale){
    glBegin(GL_LINE_STRIP);
    glVertex2d((0.9*scale), (0.8*scale));
    glVertex2d((0.6*scale), (1.0*scale));
    glVertex2d((0.4*scale), (1.0*scale));
    glVertex2d((0.1*scale), (0.8*scale));
    glVertex2d((0.1*scale), (0.2*scale));
    glVertex2d((0.4*scale), (0.0*scale));
    glVertex2d((0.6*scale), (0.0*scale));
    glVertex2d((0.9*scale), (0.2*scale));
    glVertex2d((0.9*scale), (0.4*scale));
    glVertex2d((0.6*scale), (0.6*scale));
    glVertex2d((0.4*scale), (0.6*scale));
    glVertex2d((0.1*scale), (0.4*scale));
    glEnd();
}

void draw_7(double scale){
    glBegin(GL_LINE_STRIP);
    glVertex2d((0.3*scale), (0.0*scale));
    glVertex2d((0.9*scale), (0.9*scale));
    glVertex2d((0.9*scale), (1.0*scale));
    glVertex2d((0.1*scale), (1.0*scale));
    glEnd();
}

void draw_8(double scale){
    glBegin(GL_LINE_STRIP);
    glVertex2d((0.4*scale), (0.0*scale));
    glVertex2d((0.6*scale), (0.0*scale));
    glVertex2d((0.9*scale), (0.2*scale));
    glVertex2d((0.9*scale), (0.4*scale));
    glVertex2d((0.1*scale), (0.6*scale));
    glVertex2d((0.1*scale), (0.8*scale));
    glVertex2d((0.4*scale), (1.0*scale));
    glVertex2d((0.6*scale), (1.0*scale));
    glVertex2d((0.9*scale), (0.8*scale));
    glVertex2d((0.9*scale), (0.6*scale));
    glVertex2d((0.1*scale), (0.4*scale));
    glVertex2d((0.1*scale), (0.2*scale));
    glVertex2d((0.4*scale), (0.0*scale));
    glEnd();
}

void draw_9(double scale){
    glBegin(GL_LINE_STRIP);
    glVertex2d((0.1*scale), (0.2*scale));
    glVertex2d((0.4*scale), (0.0*scale));
    glVertex2d((0.6*scale), (0.0*scale));
    glVertex2d((0.9*scale), (0.2*scale));
    glVertex2d((0.9*scale), (0.8*scale));
    glVertex2d((0.6*scale), (1.0*scale));
    glVertex2d((0.4*scale), (1.0*scale));
    glVertex2d((0.1*scale), (0.8*scale));
    glVertex2d((0.1*scale), (0.6*scale));
    glVertex2d((0.2*scale), (0.5*scale));
    glVertex2d((0.9*scale), (0.5*scale));
    glEnd();
}

void draw_0(double scale){
    glBegin(GL_LINE_STRIP);
    glVertex2d((0.4*scale), (0.0*scale));
    glVertex2d((0.6*scale), (0.0*scale));
    glVertex2d((0.9*scale), (0.2*scale));
    glVertex2d((0.9*scale), (0.8*scale));
    glVertex2d((0.6*scale), (1.0*scale));
    glVertex2d((0.4*scale), (1.0*scale));
    glVertex2d((0.1*scale), (0.8*scale));
    glVertex2d((0.1*scale), (0.2*scale));
    glVertex2d((0.4*scale), (0.0*scale));
    glEnd();
}

void draw_dot(double scale){
    glBegin(GL_LINE_STRIP);
    glVertex2d((0.4*scale), (0.0*scale));
    glVertex2d((0.6*scale), (0.0*scale));
    glVertex2d((0.6*scale), (0.1*scale));
    glVertex2d((0.4*scale), (0.1*scale));
    glVertex2d((0.4*scale), (0.0*scale));
    glEnd();
}

void draw_diameter(double scale){
    glBegin(GL_LINE_STRIP);
    glVertex2d((0.1*scale), (0.0*scale));
    glVertex2d((0.9*scale), (0.9*scale));
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex2d((0.4*scale), (0.1*scale));
    glVertex2d((0.6*scale), (0.1*scale));
    glVertex2d((0.9*scale), (0.3*scale));
    glVertex2d((0.9*scale), (0.7*scale));
    glVertex2d((0.6*scale), (0.9*scale));
    glVertex2d((0.4*scale), (0.9*scale));
    glVertex2d((0.1*scale), (0.7*scale));
    glVertex2d((0.1*scale), (0.3*scale));
    glVertex2d((0.4*scale), (0.1*scale));
    glEnd();
}

void draw_R(double scale){
    glBegin(GL_LINE_STRIP);
    glVertex2d((0.1*scale), (0.5*scale));
    glVertex2d((0.6*scale), (0.5*scale));
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex2d((0.1*scale), (0.0*scale));
    glVertex2d((0.1*scale), (1.0*scale));
    glVertex2d((0.6*scale), (1.0*scale));
    glVertex2d((0.9*scale), (0.8*scale));
    glVertex2d((0.9*scale), (0.7*scale));
    glVertex2d((0.6*scale), (0.5*scale));
    glVertex2d((0.9*scale), (0.0*scale));
    glEnd();
}

void draw_degrees(double scale){
    glBegin(GL_LINE_STRIP);
    glVertex2d((0.4*scale), (0.6*scale));
    glVertex2d((0.6*scale), (0.6*scale));
    glVertex2d((0.7*scale), (0.7*scale));
    glVertex2d((0.7*scale), (0.8*scale));
    glVertex2d((0.6*scale), (0.9*scale));
    glVertex2d((0.4*scale), (0.9*scale));
    glVertex2d((0.3*scale), (0.8*scale));
    glVertex2d((0.3*scale), (0.7*scale));
    glVertex2d((0.4*scale), (0.6*scale));
    glEnd();
}

QList<double>display_dimension_text::offset_line(double p0x, double p0y, double p1x, double p1y, double offset, double rotate_degrees) //rotate degrees 90 or -90
{

    QList<double> list;

    //rotate orginal line..
    double dx = p1x - p0x;
    double dy = p1y - p0y;
    double rotate_x1 = cos(rotate_degrees * M_PI / 180.0 )* dx - sin(rotate_degrees * M_PI / 180.0 ) * dy;
    double rotate_y1 = sin(rotate_degrees * M_PI / 180.0 )* dx + cos(rotate_degrees * M_PI / 180.0 ) * dy;

    //modify line lenght to offset input..
    //calculate line length
    double object_x1 = rotate_x1 + p0x;
    double object_y1 = rotate_y1 + p0y;

    //formulat : A2 + B2 = C2
    double lenght = sqrt(pow(object_x1 - p0x,2)+pow(object_y1 - p0y,2));
    double p0x_out = p0x + (offset * (object_x1 - p0x) / lenght);
    double p0y_out = p0y + (offset * (object_y1 - p0y) / lenght);

    //calculate second line point..
    double p1x_out = p1x + (p0x_out - p0x);
    double p1y_out = p1y + (p0y_out - p0y);

    //fill list with line offset values..
    list.append(p0x_out);
    list.append(p0y_out);
    list.append(p1x_out);
    list.append(p1y_out);
    return list;
}












