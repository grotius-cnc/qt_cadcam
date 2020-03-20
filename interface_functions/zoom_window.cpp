#include "zoom_window.h"
#include <core_functions/variables.h>
#include <interface_functions/snapshot.h>
#include <interface_functions/zoom_in.h>
#include <interface_functions/zoom_out.h>

zoom_window::zoom_window()
{
    if(zoom_click == 1){
        snapshot();
        zoom_click = 2;
    }

    if(zoom_click == 2){

        glColor4f(1.0f, 1.0f, 1.0f, 0.0f);  //white
        glLineStipple(1, 0xAAAA); //1-2-3-4
        glEnable(GL_LINE_STIPPLE);

        glLineWidth(1);
        glBegin(GL_LINES);

        glVertex2d(snapshot_cad_mousepos_x, snapshot_cad_mousepos_y);   //xy start
        glVertex2d(mouse_cad_pos_x, snapshot_cad_mousepos_y);           //xy end

        glVertex2d(mouse_cad_pos_x, snapshot_cad_mousepos_y);           //xy start
        glVertex2d(mouse_cad_pos_x, mouse_cad_pos_y);                   //xy end

        glVertex2d(mouse_cad_pos_x, mouse_cad_pos_y);                   //xy start
        glVertex2d(snapshot_cad_mousepos_x, mouse_cad_pos_y);           //xy end

        glVertex2d(snapshot_cad_mousepos_x, mouse_cad_pos_y);           //xy start
        glVertex2d(snapshot_cad_mousepos_x, snapshot_cad_mousepos_y);   //xy start
        glEnd();

        glLineWidth(gl_linewidth);
        glDisable(GL_LINE_STIPPLE);

    }

    if(zoom_click == 3){

        double x_min;
        double x_max;
        double x_dist;
        double y_min;
        double y_max;
        double y_dist;

        if(snapshot_cad_mousepos_x < mouse_cad_pos_x){
            x_min = snapshot_cad_mousepos_x;
            x_max = mouse_cad_pos_x;
        } else {
            x_min = mouse_cad_pos_x;
            x_max = snapshot_cad_mousepos_x;
        }

        if(snapshot_cad_mousepos_y > mouse_cad_pos_y){
            y_max = snapshot_cad_mousepos_y;
            y_min = mouse_cad_pos_y;
        } else {
            y_max = mouse_cad_pos_y;
            y_min = snapshot_cad_mousepos_y;
        }

        x_dist = x_max - x_min;
        y_dist = y_max - y_min;

        if(x_dist < y_dist){
            x_dist = y_dist;
        }

        double y_mid = (y_max + y_min)/2;
        double x_mid = (x_max + x_min)/2;

        zoom_cad_left = (x_mid - (0.5*x_dist) *aspect) ; //-
        zoom_cad_right = (x_mid + (0.5*x_dist) *aspect) ; //+
        zoom_cad_bottom = (y_mid - (0.5*x_dist)) * aspect;
        zoom_cad_top = (y_mid + (0.5*x_dist)) * aspect;

//        qDebug() << "zoom_cad_left" << zoom_cad_left;
//        qDebug() << "zoom_cad_right" << zoom_cad_right;
//        qDebug() << "zoom_cad_bottom" << zoom_cad_bottom;
//        qDebug() << "zoom_cad_top" << zoom_cad_top;

        //finish :
        zoom_click = 0;
        mode_zoom_window = 0;
    }
}



















