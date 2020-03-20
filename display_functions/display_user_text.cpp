#include "display_user_text.h"
#include <core_functions/variables.h>
#include <display_functions/color.h>
#include <display_functions/linetype.h>
#include <display_functions/highlight.h>

double pos_x = 0;
double pos_y = 0;
double scale = 0;
QString text;
int stringlenght = 0;
double char_offset = 0;

//text to cam..
double cam_x_offset = 0;
double cam_y_offset = 0;

display_user_text::display_user_text(int i, double x_displacement, double y_displacement)
{
    if(int_cad_array[i][0] == 10){ // id = text

        (color(i)); (highlight(i)); (linetype(i));

        pos_x = double_cad_array[i][0];       //text pos x
        pos_y = double_cad_array[i][1];       //text pos y
        scale = double_cad_array[i][13];      //text height
        text = string_cad_array[i][0];   //text string

        text.replace("new_line","\n",Qt::CaseSensitive);
        //qDebug()<< "text : " << text;

        if(!text.contains("\n")){ //single line..
            //cam_x_offset=0; //start new line..
            glPushMatrix(); //new matrix, start with clean offset values..
            draw_text(text, x_displacement,y_displacement);
            glPopMatrix(); //end matrix..
        } else { //multiline text..

            QString line;
            int factor = 1;

            while(text.size() != 0){
                line.append(text.at(0));
                if(line.contains("\n")){
                    line.chop(1);
                    //qDebug()<< "line : " << line;

                    //cam
                    cam_x_offset=pos_x; //start new line..
                    cam_y_offset=pos_y-(factor*scale*1.5);
                    //end cam

                    glPushMatrix();
                    draw_text(line, x_displacement,y_displacement-(factor*scale*1.5));
                    glPopMatrix();
                    factor++;
                    line.clear();
                }
                text.remove(0,1);
            }
        }
    }
}

void display_user_text::draw_text(QString text, double x_displacement, double y_displacement)
{
    stringlenght = text.size();
    char_offset = scale;

    glTranslated(pos_x+x_displacement, pos_y+y_displacement, 0);

    for(int i=0; i<stringlenght; i++){
        //lower characters..
        if(text.at(i)=="a"){
            draw_a(scale);
            char_offset = scale;
        }
        if(text.at(i)=="b"){
            draw_b(scale);
            char_offset = scale;
        }
        if(text.at(i)=="c"){
            draw_c(scale);
            char_offset = scale;
        }
        if(text.at(i)=="d"){
            draw_d(scale);
            char_offset = scale;
        }
        if(text.at(i)=="e"){
            draw_e(scale);
            char_offset = scale;
        }
        if(text.at(i)=="f"){
            draw_f(scale);
            char_offset = scale;
        }
        if(text.at(i)=="g"){
            draw_g(scale);
            char_offset = scale;
        }
        if(text.at(i)=="h"){
            draw_h(scale);
            char_offset = scale;
        }
        if(text.at(i)=="i"){
            draw_i(scale);
            char_offset = 0.2*scale;
        }
        if(text.at(i)=="j"){
            draw_j(scale);
            char_offset = 0.7*scale;
        }
        if(text.at(i)=="k"){
            draw_k(scale);
            char_offset = scale;
        }
        if(text.at(i)=="l"){
            draw_l(scale);
            char_offset = scale;
        }
        if(text.at(i)=="m"){
            draw_m(scale);
            char_offset = scale;
        }
        if(text.at(i)=="n"){
            draw_n(scale);
            char_offset = scale;
        }
        if(text.at(i)=="o"){
            draw_o(scale);
            char_offset = scale;
        }
        if(text.at(i)=="p"){
            draw_p(scale);
            char_offset = scale;
        }
        if(text.at(i)=="q"){
            draw_q(scale);
            char_offset = scale;
        }
        if(text.at(i)=="r"){
            draw_r(scale);
            char_offset = scale;
        }
        if(text.at(i)=="s"){
            draw_s(scale);
            char_offset = scale;
        }
        if(text.at(i)=="t"){
            draw_t(scale);
            char_offset = scale;
        }
        if(text.at(i)=="u"){
            draw_u(scale);
            char_offset = scale;
        }
        if(text.at(i)=="v"){
            draw_v(scale);
            char_offset = scale;
        }
        if(text.at(i)=="w"){
            draw_w(scale);
            char_offset = scale;
        }
        if(text.at(i)=="x"){
            draw_x(scale);
            char_offset = scale;
        }
        if(text.at(i)=="y"){
            draw_y(scale);
            char_offset = scale;
        }
        if(text.at(i)=="z"){
            draw_z(scale);
            char_offset = scale;
        }

        //upper characters..
        if(text.at(i)=="A"){
            draw_A(scale);
            char_offset = scale;
        }
        if(text.at(i)=="B"){
            draw_B(scale);
            char_offset = scale;
        }
        if(text.at(i)=="C"){
            draw_C(scale);
            char_offset = scale;
        }
        if(text.at(i)=="D"){
            draw_D(scale);
            char_offset = scale;
        }
        if(text.at(i)=="E"){
            draw_E(scale);
            char_offset = scale;
        }
        if(text.at(i)=="F"){
            draw_F(scale);
            char_offset = scale;
        }
        if(text.at(i)=="G"){
            draw_G(scale);
            char_offset = scale;
        }
        if(text.at(i)=="H"){
            draw_H(scale);
            char_offset = scale;
        }
        if(text.at(i)=="I"){
            draw_I(scale);
            char_offset = scale;
        }
        if(text.at(i)=="J"){
            draw_J(scale);
            char_offset = scale;
        }
        if(text.at(i)=="K"){
            draw_K(scale);
            char_offset = scale;
        }
        if(text.at(i)=="L"){
            draw_L(scale);
            char_offset = scale;
        }
        if(text.at(i)=="M"){
            draw_M(scale);
            char_offset = scale;
        }
        if(text.at(i)=="N"){
            draw_N(scale);
            char_offset = scale;
        }
        if(text.at(i)=="O"){
            draw_O(scale);
            char_offset = scale;
        }
        if(text.at(i)=="P"){
            draw_P(scale);
            char_offset = scale;
        }
        if(text.at(i)=="Q"){
            draw_Q(scale);
            char_offset = scale;
        }
        if(text.at(i)=="R"){
            draw_R(scale);
            char_offset = scale;
        }
        if(text.at(i)=="S"){
            draw_S(scale);
            char_offset = scale;
        }
        if(text.at(i)=="T"){
            draw_T(scale);
            char_offset = scale;
        }
        if(text.at(i)=="U"){
            draw_U(scale);
            char_offset = scale;
        }
        if(text.at(i)=="V"){
            draw_V(scale);
            char_offset = scale;
        }
        if(text.at(i)=="W"){
            draw_W(scale);
            char_offset = scale;
        }
        if(text.at(i)=="X"){
            draw_X(scale);
            char_offset = scale;
        }
        if(text.at(i)=="Y"){
            draw_Y(scale);
            char_offset = scale;
        }
        if(text.at(i)=="Z"){
            draw_Z(scale);
            char_offset = scale;
        }

        //digits..
        if(text.at(i)=="1"){
            draw_1(scale);
            char_offset = scale;
        }
        if(text.at(i)=="2"){
            draw_2(scale);
            char_offset = scale;
        }
        if(text.at(i)=="3"){
            draw_3(scale);
            char_offset = scale;
        }
        if(text.at(i)=="4"){
            draw_4(scale);
            char_offset = scale;
        }
        if(text.at(i)=="5"){
            draw_5(scale);
            char_offset = scale;
        }
        if(text.at(i)=="6"){
            draw_6(scale);
            char_offset = scale;
        }
        if(text.at(i)=="7"){
            draw_7(scale);
            char_offset = scale;
        }
        if(text.at(i)=="8"){
            draw_8(scale);
            char_offset = scale;
        }
        if(text.at(i)=="9"){
            draw_9(scale);
            char_offset = scale;
        }
        if(text.at(i)=="0"){
            draw_0(scale);
            char_offset = scale;
        }
        if(text.at(i)=="."){
            draw_dot(scale);
            char_offset = scale;
        }
        if(text.at(i)==":"){
            draw_doubledot(scale);
            char_offset = scale;
        }
        if(text.at(i)=="-"){
            draw_min(scale);
            char_offset = scale;
        }
        if(text.at(i)=="_"){
            draw_underscore(scale);
            char_offset = scale;
        }
        if(text.at(i)=="!"){
            draw_exclamation(scale);
            char_offset = scale;
        }

        if(text.at(i)=="="){
            draw_is(scale);
            char_offset = scale;
        }
        if(text.at(i)=="+"){
            draw_plus(scale);
            char_offset = scale;
        }
        if(text.at(i)=="/"){
            draw_divide(scale);
            char_offset = scale;
        }
        if(text.at(i)=="|"){
            draw_or(scale);
            char_offset = scale;
        }
        if(text.at(i)=="*"){
            draw_star(scale);
            char_offset = scale;
        }
        if(text.at(i)=="?"){
            draw_question(scale);
            char_offset = scale;
        }
        if(text.at(i)=="{"){
            draw_curly_open(scale);
            char_offset = scale;
        }
        if(text.at(i)=="}"){
            draw_curly_close(scale);
            char_offset = scale;
        }
        if(text.at(i)=="%"){
            draw_procent(scale);
            char_offset = scale;
        }
        if(text.at(i)=="["){
            draw_square_open_bracket(scale);
            char_offset = scale;
        }
        if(text.at(i)=="]"){
            draw_square_close_bracket(scale);
            char_offset = scale;
        }
        if(text.at(i)=="("){
            draw_open_bracket(scale);
            char_offset = scale;
        }
        if(text.at(i)==")"){
            draw_close_bracket(scale);
            char_offset = scale;
        }
        if(text.at(i)=="<"){
            draw_angle_open_bracket(scale);
            char_offset = scale;
        }
        if(text.at(i)==">"){
            draw_angle_close_bracket(scale);
            char_offset = scale;
        }
        if(text.at(i)=="^"){
            draw_roof(scale);
            char_offset = scale;
        }
        glTranslated(char_offset, 0, 0);
        cam_x_offset+=char_offset;

    }

}

void display_user_text::draw_A(double scale){
    if(mode_cad){
        glBegin(GL_LINE_STRIP);
        glVertex2d((0.1*scale), (0.0*scale));
        glVertex2d((0.5*scale), (1.0*scale));
        glVertex2d((0.9*scale), (0.0*scale));
        glEnd();

        glBegin(GL_LINE_STRIP);
        glVertex2d((0.23*scale), (0.3*scale));
        glVertex2d((0.77*scale), (0.3*scale));
        glEnd();
    }

    if(mode_cam){
//        double_cad_array[cad_counter][0] = cam_x_offset+0.1*scale;
//        double_cad_array[cad_counter][1] = cam_y_offset+0.0*scale;
//        double_cad_array[cad_counter][3] = cam_x_offset+0.5*scale;
//        double_cad_array[cad_counter][4] = cam_y_offset+1.0*scale;
//        end_function();

//        double_cad_array[cad_counter][0] = cam_x_offset+0.5*scale;
//        double_cad_array[cad_counter][1] = cam_y_offset+1.0*scale;
//        double_cad_array[cad_counter][3] = cam_x_offset+0.9*scale;
//        double_cad_array[cad_counter][4] = cam_y_offset+0.0*scale;
//        end_function();

//        double_cad_array[cad_counter][0] = cam_x_offset+0.9*scale;
//        double_cad_array[cad_counter][1] = cam_y_offset+0.0*scale;
//        double_cad_array[cad_counter][3] = cam_x_offset+0.77*scale;
//        double_cad_array[cad_counter][4] = cam_y_offset+0.3*scale;
//        end_function();

//        double_cad_array[cad_counter][0] = cam_x_offset+0.77*scale;
//        double_cad_array[cad_counter][1] = cam_y_offset+0.3*scale;
//        double_cad_array[cad_counter][3] = cam_x_offset+0.23*scale;
//        double_cad_array[cad_counter][4] = cam_y_offset+0.3*scale;
//        end_function();
    }

}

void display_user_text::draw_B(double scale){
    if(mode_cad){
        glBegin(GL_LINE_STRIP);
        glVertex2d((0.1*scale), (0.0*scale));
        glVertex2d((0.1*scale), (1.0*scale));
        glVertex2d((0.8*scale), (1.0*scale));
        glVertex2d((0.9*scale), (0.9*scale));
        glVertex2d((0.9*scale), (0.6*scale));
        glVertex2d((0.8*scale), (0.5*scale));
        glVertex2d((0.9*scale), (0.4*scale));
        glVertex2d((0.9*scale), (0.1*scale));
        glVertex2d((0.8*scale), (0.0*scale));
        glVertex2d((0.1*scale), (0.0*scale));
        glEnd();

        glBegin(GL_LINE_STRIP);
        glVertex2d((0.1*scale), (0.5*scale));
        glVertex2d((0.8*scale), (0.5*scale));
        glEnd();
    }

    if(mode_cam){
//        double_cad_array[cad_counter][0] = cam_x_offset+0.1*scale;
//        double_cad_array[cad_counter][1] = cam_y_offset+0.0*scale;
//        double_cad_array[cad_counter][3] = cam_x_offset+0.1*scale;
//        double_cad_array[cad_counter][4] = cam_y_offset+1.0*scale;
//        end_function();

//        double_cad_array[cad_counter][0] = cam_x_offset+0.1*scale;
//        double_cad_array[cad_counter][1] = cam_y_offset+1.0*scale;
//        double_cad_array[cad_counter][3] = cam_x_offset+0.8*scale;
//        double_cad_array[cad_counter][4] = cam_y_offset+1.0*scale;
//        end_function();

//        double_cad_array[cad_counter][0] = cam_x_offset+0.8*scale;
//        double_cad_array[cad_counter][1] = cam_y_offset+1.0*scale;
//        double_cad_array[cad_counter][3] = cam_x_offset+0.9*scale;
//        double_cad_array[cad_counter][4] = cam_y_offset+0.9*scale;
//        end_function();

//        double_cad_array[cad_counter][0] = cam_x_offset+0.9*scale;
//        double_cad_array[cad_counter][1] = cam_y_offset+0.9*scale;
//        double_cad_array[cad_counter][3] = cam_x_offset+0.9*scale;
//        double_cad_array[cad_counter][4] = cam_y_offset+0.6*scale;
//        end_function();

//        double_cad_array[cad_counter][0] = cam_x_offset+0.9*scale;
//        double_cad_array[cad_counter][1] = cam_y_offset+0.6*scale;
//        double_cad_array[cad_counter][3] = cam_x_offset+0.8*scale;
//        double_cad_array[cad_counter][4] = cam_y_offset+0.5*scale;
//        end_function();

//        double_cad_array[cad_counter][0] = cam_x_offset+0.8*scale;
//        double_cad_array[cad_counter][1] = cam_y_offset+0.5*scale;
//        double_cad_array[cad_counter][3] = cam_x_offset+0.9*scale;
//        double_cad_array[cad_counter][4] = cam_y_offset+0.4*scale;
//        end_function();

//        double_cad_array[cad_counter][0] = cam_x_offset+0.9*scale;
//        double_cad_array[cad_counter][1] = cam_y_offset+0.4*scale;
//        double_cad_array[cad_counter][3] = cam_x_offset+0.9*scale;
//        double_cad_array[cad_counter][4] = cam_y_offset+0.1*scale;
//        end_function();

//        double_cad_array[cad_counter][0] = cam_x_offset+0.9*scale;
//        double_cad_array[cad_counter][1] = cam_y_offset+0.1*scale;
//        double_cad_array[cad_counter][3] = cam_x_offset+0.8*scale;
//        double_cad_array[cad_counter][4] = cam_y_offset+0.0*scale;
//        end_function();
    }
}

void display_user_text::draw_C(double scale){
    if(mode_cad){
        glBegin(GL_LINE_STRIP);
        glVertex2d((0.9*scale), (0.0*scale));
        glVertex2d((0.2*scale), (0.0*scale));
        glVertex2d((0.1*scale), (0.1*scale));
        glVertex2d((0.1*scale), (0.9*scale));
        glVertex2d((0.2*scale), (1.0*scale));
        glVertex2d((0.9*scale), (1.0*scale));
        glEnd();
    }

    if(mode_cam){
//        double_cad_array[cad_counter][0] = cam_x_offset+0.9*scale;
//        double_cad_array[cad_counter][1] = cam_y_offset+0.0*scale;
//        double_cad_array[cad_counter][3] = cam_x_offset+0.2*scale;
//        double_cad_array[cad_counter][4] = cam_y_offset+0.0*scale;
//        end_function();

//        double_cad_array[cad_counter][0] = cam_x_offset+0.2*scale;
//        double_cad_array[cad_counter][1] = cam_y_offset+0.0*scale;
//        double_cad_array[cad_counter][3] = cam_x_offset+0.1*scale;
//        double_cad_array[cad_counter][4] = cam_y_offset+0.1*scale;
//        end_function();

//        double_cad_array[cad_counter][0] = cam_x_offset+0.1*scale;
//        double_cad_array[cad_counter][1] = cam_y_offset+0.1*scale;
//        double_cad_array[cad_counter][3] = cam_x_offset+0.1*scale;
//        double_cad_array[cad_counter][4] = cam_y_offset+0.9*scale;
//        end_function();

//        double_cad_array[cad_counter][0] = cam_x_offset+0.1*scale;
//        double_cad_array[cad_counter][1] = cam_y_offset+0.9*scale;
//        double_cad_array[cad_counter][3] = cam_x_offset+0.2*scale;
//        double_cad_array[cad_counter][4] = cam_y_offset+1.0*scale;
//        end_function();

//        double_cad_array[cad_counter][0] = cam_x_offset+0.9*scale;
//        double_cad_array[cad_counter][1] = cam_y_offset+1.0*scale;
//        double_cad_array[cad_counter][3] = cam_x_offset+0.2*scale;
//        double_cad_array[cad_counter][4] = cam_y_offset+1.0*scale;
//        end_function();
    }
}

void display_user_text::draw_D(double scale){
    glBegin(GL_LINE_STRIP);
    glVertex2d((0.1*scale), (0.0*scale));
    glVertex2d((0.1*scale), (1.0*scale));
    glVertex2d((0.8*scale), (1.0*scale));
    glVertex2d((0.9*scale), (0.9*scale));
    glVertex2d((0.9*scale), (0.1*scale));
    glVertex2d((0.8*scale), (0.0*scale));
    glVertex2d((0.1*scale), (0.0*scale));
    glEnd();
}

void display_user_text::draw_E(double scale){
    glBegin(GL_LINE_STRIP);
    glVertex2d((0.9*scale), (0.0*scale));
    glVertex2d((0.2*scale), (0.0*scale));
    glVertex2d((0.1*scale), (0.1*scale));
    glVertex2d((0.1*scale), (0.9*scale));
    glVertex2d((0.2*scale), (1.0*scale));
    glVertex2d((0.9*scale), (1.0*scale));
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2d((0.1*scale), (0.5*scale));
    glVertex2d((0.9*scale), (0.5*scale));
    glEnd();
}

void display_user_text::draw_F(double scale){
    glBegin(GL_LINE_STRIP);
    glVertex2d((0.1*scale), (0.0*scale));
    glVertex2d((0.1*scale), (0.9*scale));
    glVertex2d((0.2*scale), (1.0*scale));
    glVertex2d((0.9*scale), (1.0*scale));
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2d((0.1*scale), (0.5*scale));
    glVertex2d((0.9*scale), (0.5*scale));
    glEnd();
}

void display_user_text::draw_G(double scale){
    glBegin(GL_LINE_STRIP);
    glVertex2d((0.4*scale), (0.5*scale));
    glVertex2d((0.8*scale), (0.5*scale));
    glVertex2d((0.9*scale), (0.4*scale));
    glVertex2d((0.9*scale), (0.1*scale));
    glVertex2d((0.8*scale), (0.0*scale));
    glVertex2d((0.2*scale), (0.0*scale));
    glVertex2d((0.1*scale), (0.1*scale));
    glVertex2d((0.1*scale), (0.9*scale));
    glVertex2d((0.2*scale), (1.0*scale));
    glVertex2d((0.9*scale), (1.0*scale));
    glEnd();
}

void display_user_text::draw_H(double scale){
    glBegin(GL_LINE_STRIP);
    glVertex2d((0.1*scale), (0.0*scale));
    glVertex2d((0.1*scale), (1.0*scale));
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2d((0.1*scale), (0.5*scale));
    glVertex2d((0.9*scale), (0.5*scale));
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2d((0.9*scale), (0.0*scale));
    glVertex2d((0.9*scale), (1.0*scale));
    glEnd();
}

void display_user_text::draw_I(double scale){
    glBegin(GL_LINE_STRIP);
    glVertex2d((0.5*scale), (0.0*scale));
    glVertex2d((0.5*scale), (1.0*scale));
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2d((0.1*scale), (0.0*scale));
    glVertex2d((0.9*scale), (0.0*scale));
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2d((0.1*scale), (1.0*scale));
    glVertex2d((0.9*scale), (1.0*scale));
    glEnd();
}

void display_user_text::draw_J(double scale){
    glBegin(GL_LINE_STRIP);
    glVertex2d((0.1*scale), (0.0*scale));
    glVertex2d((0.8*scale), (0.0*scale));
    glVertex2d((0.9*scale), (0.1*scale));
    glVertex2d((0.9*scale), (1.0*scale));
    glVertex2d((0.5*scale), (1.0*scale));
    glEnd();
}

void display_user_text::draw_K(double scale){
    glBegin(GL_LINE_STRIP);
    glVertex2d((0.1*scale), (0.0*scale));
    glVertex2d((0.1*scale), (1.0*scale));
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2d((0.1*scale), (0.4*scale));
    glVertex2d((0.9*scale), (1.0*scale));
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2d((0.24*scale), (0.5*scale));
    glVertex2d((0.9*scale), (0.0*scale));
    glEnd();
}

void display_user_text::draw_L(double scale){
    glBegin(GL_LINE_STRIP);
    glVertex2d((0.9*scale), (0.0*scale));
    glVertex2d((0.2*scale), (0.0*scale));
    glVertex2d((0.1*scale), (0.1*scale));
    glVertex2d((0.1*scale), (1.0*scale));
    glEnd();
}

void display_user_text::draw_M(double scale){
    glBegin(GL_LINE_STRIP);
    glVertex2d((0.1*scale), (0.0*scale));
    glVertex2d((0.1*scale), (1.0*scale));
    glVertex2d((0.5*scale), (0.5*scale));
    glVertex2d((0.9*scale), (1.0*scale));
    glVertex2d((0.9*scale), (0.0*scale));
    glEnd();
}

void display_user_text::draw_N(double scale){
    glBegin(GL_LINE_STRIP);
    glVertex2d((0.1*scale), (0.0*scale));
    glVertex2d((0.1*scale), (1.0*scale));
    glVertex2d((0.9*scale), (0.0*scale));
    glVertex2d((0.9*scale), (1.0*scale));
    glEnd();
}

void display_user_text::draw_O(double scale){
    glBegin(GL_LINE_STRIP);
    glVertex2d((0.1*scale), (0.1*scale));
    glVertex2d((0.1*scale), (0.9*scale));
    glVertex2d((0.2*scale), (1.0*scale));
    glVertex2d((0.8*scale), (1.0*scale));
    glVertex2d((0.9*scale), (0.9*scale));
    glVertex2d((0.9*scale), (0.1*scale));
    glVertex2d((0.8*scale), (0.0*scale));
    glVertex2d((0.2*scale), (0.0*scale));
    glVertex2d((0.1*scale), (0.1*scale));
    glEnd();
}

void display_user_text::draw_P(double scale){
    glBegin(GL_LINE_STRIP);
    glVertex2d((0.1*scale), (0.0*scale));
    glVertex2d((0.1*scale), (1.0*scale));
    glVertex2d((0.8*scale), (1.0*scale));
    glVertex2d((0.9*scale), (0.9*scale));
    glVertex2d((0.9*scale), (0.6*scale));
    glVertex2d((0.8*scale), (0.5*scale));
    glVertex2d((0.1*scale), (0.5*scale));
    glEnd();
}

void display_user_text::draw_Q(double scale){
    glBegin(GL_LINE_STRIP);
    glVertex2d((0.1*scale), (0.1*scale));
    glVertex2d((0.1*scale), (0.9*scale));
    glVertex2d((0.2*scale), (1.0*scale));
    glVertex2d((0.8*scale), (1.0*scale));
    glVertex2d((0.9*scale), (0.9*scale));
    glVertex2d((0.9*scale), (0.1*scale));
    glVertex2d((0.8*scale), (0.0*scale));
    glVertex2d((0.2*scale), (0.0*scale));
    glVertex2d((0.1*scale), (0.1*scale));
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2d((0.7*scale), (0.1*scale));
    glVertex2d((0.7*scale), (-0.1*scale));
    glEnd();
}

void display_user_text::draw_R(double scale){
    glBegin(GL_LINE_STRIP);
    glVertex2d((0.1*scale), (0.0*scale));
    glVertex2d((0.1*scale), (0.9*scale));
    glVertex2d((0.2*scale), (1.0*scale));
    glVertex2d((0.8*scale), (1.0*scale));
    glVertex2d((0.9*scale), (0.9*scale));
    glVertex2d((0.9*scale), (0.6*scale));
    glVertex2d((0.8*scale), (0.5*scale));
    glVertex2d((0.1*scale), (0.5*scale));
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2d((0.6*scale), (0.5*scale));
    glVertex2d((0.9*scale), (0.0*scale));
    glEnd();
}

void display_user_text::draw_S(double scale){
    glBegin(GL_LINE_STRIP);
    glVertex2d((0.1*scale), (0.0*scale));
    glVertex2d((0.8*scale), (0.0*scale));
    glVertex2d((0.9*scale), (0.1*scale));
    glVertex2d((0.9*scale), (0.4*scale));
    glVertex2d((0.8*scale), (0.5*scale));
    glVertex2d((0.2*scale), (0.5*scale));
    glVertex2d((0.1*scale), (0.6*scale));
    glVertex2d((0.1*scale), (0.9*scale));
    glVertex2d((0.2*scale), (1.0*scale));
    glVertex2d((0.9*scale), (1.0*scale));
    glEnd();
}

void display_user_text::draw_T(double scale){
    glBegin(GL_LINE_STRIP);
    glVertex2d((0.5*scale), (0.0*scale));
    glVertex2d((0.5*scale), (1.0*scale));
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2d((0.1*scale), (1.0*scale));
    glVertex2d((0.9*scale), (1.0*scale));
    glEnd();
}

void display_user_text::draw_U(double scale){
    glBegin(GL_LINE_STRIP);
    glVertex2d((0.1*scale), (1.0*scale));
    glVertex2d((0.1*scale), (0.1*scale));
    glVertex2d((0.2*scale), (0.0*scale));
    glVertex2d((0.8*scale), (0.0*scale));
    glVertex2d((0.9*scale), (0.1*scale));
    glVertex2d((0.9*scale), (1.0*scale));
    glEnd();
}

void display_user_text::draw_V(double scale){
    glBegin(GL_LINE_STRIP);
    glVertex2d((0.1*scale), (1.0*scale));
    glVertex2d((0.5*scale), (0.0*scale));
    glVertex2d((0.9*scale), (1.0*scale));
    glEnd();
}

void display_user_text::draw_W(double scale){
    glBegin(GL_LINE_STRIP);
    glVertex2d((0.1*scale), (1.0*scale));
    glVertex2d((0.3*scale), (0.0*scale));
    glVertex2d((0.5*scale), (1.0*scale));
    glVertex2d((0.7*scale), (0.0*scale));
    glVertex2d((0.9*scale), (1.0*scale));
    glEnd();
}

void display_user_text::draw_X(double scale){
    glBegin(GL_LINE_STRIP);
    glVertex2d((0.1*scale), (0.0*scale));
    glVertex2d((0.9*scale), (1.0*scale));
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2d((0.1*scale), (1.0*scale));
    glVertex2d((0.9*scale), (0.0*scale));
    glEnd();
}

void display_user_text::draw_Y(double scale){
    glBegin(GL_LINE_STRIP);
    glVertex2d((0.1*scale), (0.0*scale));
    glVertex2d((0.8*scale), (0.0*scale));
    glVertex2d((0.9*scale), (0.1*scale));
    glVertex2d((0.9*scale), (1.0*scale));
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2d((0.1*scale), (1.0*scale));
    glVertex2d((0.1*scale), (0.6*scale));
    glVertex2d((0.2*scale), (0.5*scale));
    glVertex2d((0.9*scale), (0.5*scale));
    glEnd();
}

void display_user_text::draw_Z(double scale){
    glBegin(GL_LINE_STRIP);
    glVertex2d((0.9*scale), (0.0*scale));
    glVertex2d((0.1*scale), (0.0*scale));
    glVertex2d((0.9*scale), (1.0*scale));
    glVertex2d((0.1*scale), (1.0*scale));
    glEnd();
}

void display_user_text::draw_a(double scale){
    glBegin(GL_LINE_STRIP);
    glVertex2d((0.9*scale), (0.0*scale));
    glVertex2d((0.2*scale), (0.0*scale));
    glVertex2d((0.1*scale), (0.1*scale));
    glVertex2d((0.1*scale), (0.2*scale));
    glVertex2d((0.2*scale), (0.3*scale));
    glVertex2d((0.9*scale), (0.3*scale));
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2d((0.9*scale), (0.0*scale));
    glVertex2d((0.9*scale), (0.5*scale));
    glVertex2d((0.8*scale), (0.6*scale));
    glVertex2d((0.3*scale), (0.6*scale));
    glVertex2d((0.1*scale), (0.5*scale));
    glVertex2d((0.1*scale), (0.4*scale));
    glEnd();
}

void display_user_text::draw_b(double scale){
    glBegin(GL_LINE_STRIP);
    glVertex2d((0.1*scale), (0.0*scale));
    glVertex2d((0.8*scale), (0.0*scale));
    glVertex2d((0.9*scale), (0.1*scale));
    glVertex2d((0.9*scale), (0.5*scale));
    glVertex2d((0.8*scale), (0.6*scale));
    glVertex2d((0.1*scale), (0.6*scale));
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2d((0.1*scale), (0.0*scale));
    glVertex2d((0.1*scale), (1.0*scale));
    glEnd();
}

void display_user_text::draw_c(double scale){
    glBegin(GL_LINE_STRIP);
    glVertex2d((0.9*scale), (0.0*scale));
    glVertex2d((0.2*scale), (0.0*scale));
    glVertex2d((0.1*scale), (0.1*scale));
    glVertex2d((0.1*scale), (0.5*scale));
    glVertex2d((0.2*scale), (0.6*scale));
    glVertex2d((0.9*scale), (0.6*scale));
    glEnd();
}

void display_user_text::draw_d(double scale){
    glBegin(GL_LINE_STRIP);
    glVertex2d((0.9*scale), (1.0*scale));
    glVertex2d((0.9*scale), (0.0*scale));
    glVertex2d((0.2*scale), (0.0*scale));
    glVertex2d((0.1*scale), (0.1*scale));
    glVertex2d((0.1*scale), (0.5*scale));
    glVertex2d((0.2*scale), (0.6*scale));
    glVertex2d((0.9*scale), (0.6*scale));
    glEnd();
}

void display_user_text::draw_e(double scale){
    glBegin(GL_LINE_STRIP);
    glVertex2d((0.9*scale), (0.0*scale));
    glVertex2d((0.2*scale), (0.0*scale));
    glVertex2d((0.1*scale), (0.1*scale));
    glVertex2d((0.1*scale), (0.5*scale));
    glVertex2d((0.2*scale), (0.6*scale));
    glVertex2d((0.8*scale), (0.6*scale));
    glVertex2d((0.9*scale), (0.5*scale));
    glVertex2d((0.9*scale), (0.3*scale));
    glVertex2d((0.1*scale), (0.3*scale));
    glEnd();
}

void display_user_text::draw_f(double scale){
    glBegin(GL_LINE_STRIP);
    glVertex2d((0.9*scale), (1.0*scale));
    glVertex2d((0.3*scale), (1.0*scale));
    glVertex2d((0.2*scale), (0.9*scale));
    glVertex2d((0.2*scale), (0.0*scale));
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2d((0.5*scale), (0.6*scale));
    glVertex2d((0.1*scale), (0.6*scale));
    glEnd();
}

void display_user_text::draw_g(double scale){
    glBegin(GL_LINE_STRIP);
    glVertex2d((0.1*scale), (-0.4*scale));
    glVertex2d((0.8*scale), (-0.4*scale));
    glVertex2d((0.9*scale), (-0.3*scale));
    glVertex2d((0.9*scale), (0.5*scale));
    glVertex2d((0.8*scale), (0.6*scale));
    glVertex2d((0.2*scale), (0.6*scale));
    glVertex2d((0.1*scale), (0.5*scale));
    glVertex2d((0.1*scale), (0.1*scale));
    glVertex2d((0.2*scale), (0.0*scale));
    glVertex2d((0.9*scale), (0.0*scale));
    glEnd();
}

void display_user_text::draw_h(double scale){
    glBegin(GL_LINE_STRIP);
    glVertex2d((0.1*scale), (0.0*scale));
    glVertex2d((0.1*scale), (1.0*scale));
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2d((0.9*scale), (0.0*scale));
    glVertex2d((0.9*scale), (0.5*scale));
    glVertex2d((0.8*scale), (0.6*scale));
    glVertex2d((0.1*scale), (0.6*scale));
    glEnd();
}

void display_user_text::draw_i(double scale){
    glBegin(GL_LINE_STRIP);
    glVertex2d((0.1*scale), (0.0*scale));
    glVertex2d((0.1*scale), (0.6*scale));
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2d((0.1*scale), (0.8*scale));
    glVertex2d((0.1*scale), (1.0*scale));
    glEnd();
}

void display_user_text::draw_j(double scale){
    glBegin(GL_LINE_STRIP);
    glVertex2d((0.0*scale), (-0.4*scale));
    glVertex2d((0.4*scale), (-0.4*scale));
    glVertex2d((0.5*scale), (-0.3*scale));
    glVertex2d((0.5*scale), (0.6*scale));
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2d((0.5*scale), (0.8*scale));
    glVertex2d((0.5*scale), (1.0*scale));
    glEnd();
}

void display_user_text::draw_k(double scale){
    glBegin(GL_LINE_STRIP);
    glVertex2d((0.1*scale), (0.0*scale));
    glVertex2d((0.1*scale), (1.0*scale));
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2d((0.1*scale), (0.3*scale));
    glVertex2d((0.9*scale), (0.6*scale));
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2d((0.5*scale), (0.45*scale));
    glVertex2d((0.9*scale), (0.0*scale));
    glEnd();
}

void display_user_text::draw_l(double scale){
    glBegin(GL_LINE_STRIP);
    glVertex2d((0.1*scale), (1.0*scale));
    glVertex2d((0.1*scale), (0.1*scale));
    glVertex2d((0.2*scale), (0.0*scale));
    glVertex2d((0.9*scale), (0.0*scale));
    glEnd();
}

void display_user_text::draw_m(double scale){
    glBegin(GL_LINE_STRIP);
    glVertex2d((0.1*scale), (0.0*scale));
    glVertex2d((0.1*scale), (0.5*scale));
    glVertex2d((0.2*scale), (0.6*scale));
    glVertex2d((0.8*scale), (0.6*scale));
    glVertex2d((0.9*scale), (0.5*scale));
    glVertex2d((0.9*scale), (0.0*scale));
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2d((0.5*scale), (0.0*scale));
    glVertex2d((0.5*scale), (0.6*scale));
    glEnd();
}

void display_user_text::draw_n(double scale){
    glBegin(GL_LINE_STRIP);
    glVertex2d((0.1*scale), (0.0*scale));
    glVertex2d((0.1*scale), (0.5*scale));
    glVertex2d((0.2*scale), (0.6*scale));
    glVertex2d((0.8*scale), (0.6*scale));
    glVertex2d((0.9*scale), (0.5*scale));
    glVertex2d((0.9*scale), (0.0*scale));
    glEnd();
}

void display_user_text::draw_o(double scale){
    glBegin(GL_LINE_STRIP);
    glVertex2d((0.1*scale), (0.1*scale));
    glVertex2d((0.1*scale), (0.5*scale));
    glVertex2d((0.2*scale), (0.6*scale));
    glVertex2d((0.8*scale), (0.6*scale));
    glVertex2d((0.9*scale), (0.5*scale));
    glVertex2d((0.9*scale), (0.1*scale));
    glVertex2d((0.8*scale), (0.0*scale));
    glVertex2d((0.2*scale), (0.0*scale));
    glVertex2d((0.1*scale), (0.1*scale));
    glEnd();
}

void display_user_text::draw_p(double scale){
    glBegin(GL_LINE_STRIP);
    glVertex2d((0.1*scale), (-0.4*scale));
    glVertex2d((0.1*scale), (0.5*scale));
    glVertex2d((0.2*scale), (0.6*scale));
    glVertex2d((0.8*scale), (0.6*scale));
    glVertex2d((0.9*scale), (0.5*scale));
    glVertex2d((0.9*scale), (0.1*scale));
    glVertex2d((0.8*scale), (0.0*scale));
    glVertex2d((0.1*scale), (0.0*scale));
    glEnd();
}

void display_user_text::draw_q(double scale){
    glBegin(GL_LINE_STRIP);
    glVertex2d((0.9*scale), (0.0*scale));
    glVertex2d((0.2*scale), (0.0*scale));
    glVertex2d((0.1*scale), (0.1*scale));
    glVertex2d((0.1*scale), (0.5*scale));
    glVertex2d((0.2*scale), (0.6*scale));
    glVertex2d((0.8*scale), (0.6*scale));
    glVertex2d((0.9*scale), (0.5*scale));
    glVertex2d((0.9*scale), (-0.4*scale));
    glEnd();
}

void display_user_text::draw_r(double scale){
    glBegin(GL_LINE_STRIP);
    glVertex2d((0.1*scale), (0.0*scale));
    glVertex2d((0.1*scale), (0.5*scale));
    glVertex2d((0.2*scale), (0.6*scale));
    glVertex2d((0.8*scale), (0.6*scale));
    glVertex2d((0.9*scale), (0.5*scale));
    glEnd();
}

void display_user_text::draw_s(double scale){
    glBegin(GL_LINE_STRIP);
    glVertex2d((0.1*scale), (0.0*scale));
    glVertex2d((0.8*scale), (0.0*scale));
    glVertex2d((0.9*scale), (0.1*scale));
    glVertex2d((0.8*scale), (0.3*scale));
    glVertex2d((0.2*scale), (0.3*scale));
    glVertex2d((0.1*scale), (0.4*scale));
    glVertex2d((0.1*scale), (0.5*scale));
    glVertex2d((0.2*scale), (0.6*scale));
    glVertex2d((0.9*scale), (0.6*scale));
    glEnd();
}

void display_user_text::draw_t(double scale){
    glBegin(GL_LINE_STRIP);
    glVertex2d((0.2*scale), (1.0*scale));
    glVertex2d((0.2*scale), (0.1*scale));
    glVertex2d((0.3*scale), (0.0*scale));
    glVertex2d((0.9*scale), (0.0*scale));
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2d((0.1*scale), (0.6*scale));
    glVertex2d((0.5*scale), (0.6*scale));
    glEnd();
}

void display_user_text::draw_u(double scale){
    glBegin(GL_LINE_STRIP);
    glVertex2d((0.1*scale), (0.6*scale));
    glVertex2d((0.1*scale), (0.1*scale));
    glVertex2d((0.2*scale), (0.0*scale));
    glVertex2d((0.8*scale), (0.0*scale));
    glVertex2d((0.9*scale), (0.1*scale));
    glVertex2d((0.9*scale), (0.6*scale));
    glEnd();
}

void display_user_text::draw_v(double scale){
    glBegin(GL_LINE_STRIP);
    glVertex2d((0.1*scale), (0.6*scale));
    glVertex2d((0.5*scale), (0.0*scale));
    glVertex2d((0.9*scale), (0.6*scale));
    glEnd();
}

void display_user_text::draw_w(double scale){
    glBegin(GL_LINE_STRIP);
    glVertex2d((0.1*scale), (0.6*scale));
    glVertex2d((0.3*scale), (0.0*scale));
    glVertex2d((0.5*scale), (0.6*scale));
    glVertex2d((0.7*scale), (0.0*scale));
    glVertex2d((0.9*scale), (0.6*scale));
    glEnd();
}

void display_user_text::draw_x(double scale){
    glBegin(GL_LINE_STRIP);
    glVertex2d((0.1*scale), (0.6*scale));
    glVertex2d((0.9*scale), (0.0*scale));
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2d((0.1*scale), (0.0*scale));
    glVertex2d((0.9*scale), (0.6*scale));
    glEnd();
}

void display_user_text::draw_y(double scale){
    glBegin(GL_LINE_STRIP);
    glVertex2d((0.1*scale), (0.6*scale));
    glVertex2d((0.1*scale), (0.1*scale));
    glVertex2d((0.2*scale), (0.0*scale));
    glVertex2d((0.9*scale), (0.0*scale));
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2d((0.1*scale), (-0.4*scale));
    glVertex2d((0.8*scale), (-0.4*scale));
    glVertex2d((0.9*scale), (-0.3*scale));
    glVertex2d((0.9*scale), (0.6*scale));
    glEnd();
}

void display_user_text::draw_z(double scale){
    glBegin(GL_LINE_STRIP);
    glVertex2d((0.1*scale), (0.6*scale));
    glVertex2d((0.9*scale), (0.6*scale));
    glVertex2d((0.1*scale), (0.0*scale));
    glVertex2d((0.9*scale), (0.0*scale));
    glEnd();
}

void display_user_text::draw_1(double scale){
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

void display_user_text::draw_2(double scale){
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

void display_user_text::draw_3(double scale){
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

void display_user_text::draw_4(double scale){
    glBegin(GL_LINE_STRIP);
    glVertex2d((0.7*scale), (0.0*scale));
    glVertex2d((0.7*scale), (1.0*scale));
    glVertex2d((0.6*scale), (1.0*scale));
    glVertex2d((0.1*scale), (0.5*scale));
    glVertex2d((0.1*scale), (0.4*scale));
    glVertex2d((0.9*scale), (0.4*scale));
    glEnd();
}

void display_user_text::draw_5(double scale){
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

void display_user_text::draw_6(double scale){
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

void display_user_text::draw_7(double scale){
    glBegin(GL_LINE_STRIP);
    glVertex2d((0.3*scale), (0.0*scale));
    glVertex2d((0.9*scale), (0.9*scale));
    glVertex2d((0.9*scale), (1.0*scale));
    glVertex2d((0.1*scale), (1.0*scale));
    glEnd();
}

void display_user_text::draw_8(double scale){
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

void display_user_text::draw_9(double scale){
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

void display_user_text::draw_0(double scale){
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

void display_user_text::draw_dot(double scale){ //.
    glBegin(GL_LINE_STRIP);
    glVertex2d((0.4*scale), (0.0*scale));
    glVertex2d((0.6*scale), (0.0*scale));
    glVertex2d((0.6*scale), (0.1*scale));
    glVertex2d((0.4*scale), (0.1*scale));
    glVertex2d((0.4*scale), (0.0*scale));
    glEnd();
}

void display_user_text::draw_comma(double scale){ //,
    glBegin(GL_LINE_STRIP);
    glVertex2d((0.4*scale), (0.0*scale));
    glVertex2d((0.4*scale), (0.1*scale));
    glVertex2d((0.6*scale), (0.1*scale));
    glVertex2d((0.6*scale), (-0.1*scale));
    glVertex2d((0.5*scale), (-0.1*scale));
    glVertex2d((0.5*scale), (0.0*scale));
    glVertex2d((0.4*scale), (0.0*scale));
    glEnd();
}

void display_user_text::draw_doubledot(double scale){ //:
    glBegin(GL_LINE_STRIP);
    glVertex2d((0.45*scale), (0.2*scale));
    glVertex2d((0.45*scale), (0.4*scale));
    glVertex2d((0.55*scale), (0.4*scale));
    glVertex2d((0.55*scale), (0.2*scale));
    glVertex2d((0.45*scale), (0.2*scale));
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2d((0.45*scale), (0.6*scale));
    glVertex2d((0.45*scale), (0.8*scale));
    glVertex2d((0.55*scale), (0.8*scale));
    glVertex2d((0.55*scale), (0.6*scale));
    glVertex2d((0.45*scale), (0.6*scale));
    glEnd();
}

void display_user_text::draw_min(double scale){ //-
    glBegin(GL_LINE_STRIP);
    glVertex2d((0.1*scale), (0.5*scale));
    glVertex2d((0.9*scale), (0.5*scale));
    glEnd();
}

void display_user_text::draw_underscore(double scale){ //_
    glBegin(GL_LINE_STRIP);
    glVertex2d((0.1*scale), (0.0*scale));
    glVertex2d((0.9*scale), (0.0*scale));
    glEnd();
}

void display_user_text::draw_exclamation(double scale){ //!
    glBegin(GL_LINE_STRIP);
    glVertex2d((0.5*scale), (0.0*scale));
    glVertex2d((0.5*scale), (0.1*scale));
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2d((0.5*scale), (0.2*scale));
    glVertex2d((0.5*scale), (1.0*scale));
    glEnd();
}

void display_user_text::draw_is(double scale){ //=
    glBegin(GL_LINE_STRIP);
    glVertex2d((0.1*scale), (0.4*scale));
    glVertex2d((0.9*scale), (0.4*scale));
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2d((0.1*scale), (0.6*scale));
    glVertex2d((0.9*scale), (0.6*scale));
    glEnd();
}

void display_user_text::draw_roof(double scale){ //^
    glBegin(GL_LINE_STRIP);
    glVertex2d((0.2*scale), (0.7*scale));
    glVertex2d((0.5*scale), (1.0*scale));
    glVertex2d((0.8*scale), (0.7*scale));
    glEnd();
}


void display_user_text::draw_plus(double scale){ //+
    glBegin(GL_LINE_STRIP);
    glVertex2d((0.5*scale), (0.1*scale));
    glVertex2d((0.5*scale), (0.9*scale));
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2d((0.1*scale), (0.5*scale));
    glVertex2d((0.9*scale), (0.5*scale));
    glEnd();
}

void display_user_text::draw_star(double scale){ //*
    glBegin(GL_LINE_STRIP);
    glVertex2d((0.5*scale), (0.1*scale));
    glVertex2d((0.5*scale), (0.9*scale));
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2d((0.1*scale), (0.5*scale));
    glVertex2d((0.9*scale), (0.5*scale));
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2d((0.2*scale), (0.8*scale));
    glVertex2d((0.8*scale), (0.2*scale));
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2d((0.2*scale), (0.2*scale));
    glVertex2d((0.8*scale), (0.8*scale));
    glEnd();
}

void display_user_text::draw_divide(double scale){ // /
    glBegin(GL_LINE_STRIP);
    glVertex2d((0.2*scale), (0.0*scale));
    glVertex2d((0.8*scale), (1.0*scale));
    glEnd();
}

void display_user_text::draw_slash_back(double scale){ /* \ */
    glBegin(GL_LINE_STRIP);
    glVertex2d((0.8*scale), (0.0*scale));
    glVertex2d((0.2*scale), (1.0*scale));
    glEnd();
}

void display_user_text::draw_or(double scale){ // |
    glBegin(GL_LINE_STRIP);
    glVertex2d((0.5*scale), (0.0*scale));
    glVertex2d((0.5*scale), (1.0*scale));
    glEnd();
}

void display_user_text::draw_curly_open(double scale){ //{
    glBegin(GL_LINE_STRIP);
    glVertex2d((0.6*scale), (1.0*scale));
    glVertex2d((0.5*scale), (1.0*scale));
    glVertex2d((0.4*scale), (0.9*scale));
    glVertex2d((0.4*scale), (0.6*scale));
    glVertex2d((0.3*scale), (0.5*scale));
    glVertex2d((0.4*scale), (0.4*scale));
    glVertex2d((0.4*scale), (0.1*scale));
    glVertex2d((0.5*scale), (0.0*scale));
    glVertex2d((0.6*scale), (0.0*scale));
    glEnd();
}

void display_user_text::draw_curly_close(double scale){ //}
    glBegin(GL_LINE_STRIP);
    glVertex2d((0.4*scale), (1.0*scale));
    glVertex2d((0.5*scale), (1.0*scale));
    glVertex2d((0.6*scale), (0.9*scale));
    glVertex2d((0.6*scale), (0.6*scale));
    glVertex2d((0.7*scale), (0.5*scale));
    glVertex2d((0.6*scale), (0.4*scale));
    glVertex2d((0.6*scale), (0.1*scale));
    glVertex2d((0.5*scale), (0.0*scale));
    glVertex2d((0.4*scale), (0.0*scale));
    glEnd();
}

void display_user_text::draw_open_bracket(double scale){ //(
    glBegin(GL_LINE_STRIP);
    glVertex2d((0.6*scale), (0.0*scale));
    glVertex2d((0.4*scale), (0.2*scale));
    glVertex2d((0.4*scale), (0.8*scale));
    glVertex2d((0.6*scale), (1.0*scale));
    glEnd();
}

void display_user_text::draw_close_bracket(double scale){ //)
    glBegin(GL_LINE_STRIP);
    glVertex2d((0.4*scale), (0.0*scale));
    glVertex2d((0.6*scale), (0.2*scale));
    glVertex2d((0.6*scale), (0.8*scale));
    glVertex2d((0.4*scale), (1.0*scale));
    glEnd();
}

void display_user_text::draw_square_open_bracket(double scale){ //[
    glBegin(GL_LINE_STRIP);
    glVertex2d((0.7*scale), (0.0*scale));
    glVertex2d((0.3*scale), (0.0*scale));
    glVertex2d((0.3*scale), (1.0*scale));
    glVertex2d((0.7*scale), (1.0*scale));
    glEnd();
}

void display_user_text::draw_square_close_bracket(double scale){ //]
    glBegin(GL_LINE_STRIP);
    glVertex2d((0.3*scale), (1.0*scale));
    glVertex2d((0.7*scale), (1.0*scale));
    glVertex2d((0.7*scale), (0.0*scale));
    glVertex2d((0.3*scale), (0.0*scale));
    glEnd();
}

void display_user_text::draw_angle_open_bracket(double scale){ //<
    glBegin(GL_LINE_STRIP);
    glVertex2d((0.8*scale), (0.0*scale));
    glVertex2d((0.2*scale), (0.3*scale));
    glVertex2d((0.8*scale), (0.6*scale));
    glEnd();
}

void display_user_text::draw_angle_close_bracket(double scale){ //>
    glBegin(GL_LINE_STRIP);
    glVertex2d((0.2*scale), (0.0*scale));
    glVertex2d((0.8*scale), (0.3*scale));
    glVertex2d((0.2*scale), (0.6*scale));
    glEnd();
}

void display_user_text::draw_question(double scale){ //?
    glBegin(GL_LINE_STRIP);
    glVertex2d((0.1*scale), (0.9*scale));
    glVertex2d((0.2*scale), (1.0*scale));
    glVertex2d((0.8*scale), (1.0*scale));
    glVertex2d((0.9*scale), (0.9*scale));
    glVertex2d((0.9*scale), (0.6*scale));
    glVertex2d((0.8*scale), (0.5*scale));
    glVertex2d((0.6*scale), (0.5*scale));
    glVertex2d((0.5*scale), (0.4*scale));
    glVertex2d((0.5*scale), (0.2*scale));
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2d((0.5*scale), (0.1*scale));
    glVertex2d((0.5*scale), (0.0*scale));
    glEnd();
}

void display_user_text::draw_procent(double scale){ //%
    glBegin(GL_LINE_STRIP);
    glVertex2d((0.7*scale), (0.0*scale));
    glVertex2d((0.6*scale), (0.1*scale));
    glVertex2d((0.6*scale), (0.2*scale));
    glVertex2d((0.7*scale), (0.3*scale));
    glVertex2d((0.8*scale), (0.3*scale));
    glVertex2d((0.9*scale), (0.2*scale));
    glVertex2d((0.9*scale), (0.1*scale));
    glVertex2d((0.8*scale), (0.0*scale));
    glVertex2d((0.7*scale), (0.0*scale));
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2d((0.2*scale), (0.7*scale));
    glVertex2d((0.1*scale), (0.8*scale));
    glVertex2d((0.1*scale), (0.9*scale));
    glVertex2d((0.2*scale), (1.0*scale));
    glVertex2d((0.3*scale), (1.0*scale));
    glVertex2d((0.4*scale), (0.9*scale));
    glVertex2d((0.4*scale), (0.8*scale));
    glVertex2d((0.3*scale), (0.7*scale));
    glVertex2d((0.2*scale), (0.7*scale));
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2d((0.1*scale), (0.0*scale));
    glVertex2d((0.9*scale), (1.0*scale));
    glEnd();
}

void display_user_text::draw_diameter(double scale){
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

void display_user_text::draw_degrees(double scale){
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

void display_user_text::end_function(){
    int_cad_array[cad_counter][0] = 1; //id line
    int_cad_array[cad_counter][26] = 1; //gcode text
    double_cad_array[cad_counter][56] = 1;
    double_cad_array[cad_counter][57] = 1;
    double_cad_array[cad_counter][58] = 1;
    double_cad_array[cad_counter][59] = 1;
    int_cad_array[cad_counter][5] = current_linetype;
    double_cad_array[cad_counter][18] = current_linetype_scale;
    double_cad_array[cad_counter][19] = current_linewidth;
    cad_counter++;
}



















