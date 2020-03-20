#include "preview_displacement_line_stretch.h"
#include <core_functions/variables.h>
#include <display_functions/color.h>
#include <display_functions/highlight.h>
#include <display_functions/linetype.h>
#include <display_functions/show_midpoint.h>
#include <cad_draw_functions/arc_stretch.h>
#define DEG2RAD M_PI/180;

bool startpoint = 0;
bool endpoint = 0;

preview_displacement_line_stretch::preview_displacement_line_stretch(int i, bool startpoint, bool endpoint, bool full_object, double dist_x, double dist_y, double dist_z)
{
    //draw objects from cad array..
    if(int_cad_array[i][0] == 1){ // id line..

        (color(i)); (highlight(i)); (linetype(i));
        //draw line

        if(full_object){
            glBegin(GL_LINES);
            glVertex3d(double_cad_array[i][0]+dist_x, double_cad_array[i][1]+dist_y, double_cad_array[i][2]+dist_z);  //xyz start
            //glColor3f(1.0f, 0.0f, 1.0f);
            glVertex3d(double_cad_array[i][3]+dist_x, double_cad_array[i][4]+dist_y, double_cad_array[i][5]+dist_z);  //xyz end
            glEnd();
            glDisable(GL_LINE_STIPPLE);
        }
        if(startpoint){
            glBegin(GL_LINES);
            glVertex3d(double_cad_array[i][0]+dist_x, double_cad_array[i][1]+dist_y, double_cad_array[i][2]+dist_z);  //xyz start
            //glColor3f(1.0f, 0.0f, 1.0f);
            glVertex3d(double_cad_array[i][3], double_cad_array[i][4], double_cad_array[i][5]);  //xyz end
            glEnd();
            glDisable(GL_LINE_STIPPLE);
        }
        if(endpoint){
            glBegin(GL_LINES);
            glVertex3d(double_cad_array[i][0], double_cad_array[i][1], double_cad_array[i][2]);  //xyz start
            //glColor3f(1.0f, 0.0f, 1.0f);
            glVertex3d(double_cad_array[i][3]+dist_x, double_cad_array[i][4]+dist_y, double_cad_array[i][5]+dist_z);  //xyz end
            glEnd();
            glDisable(GL_LINE_STIPPLE);
        }

    }
}
