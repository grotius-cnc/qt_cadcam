#include "circle_3p.h"
#include <core_functions/variables.h>
#include <array_functions/emtpy_current_cad_counter.h>
#include <display_functions/no_selection.h>
#include <display_functions/object_select_line_startpoint.h>
#include <display_functions/object_select_line_midpoint.h>
#include <display_functions/object_select_line_endpoint.h>
#include <display_functions/object_select_line_perpendicular.h>
#include <display_functions/object_select_line_nearest.h>
#include <display_functions/object_select_line_tangent_arc.h>
#include <display_functions/object_select_line_tangent_circle.h>
#include <display_functions/object_select_centerpoint.h>
#include <display_functions/object_select_circle_4p_intersection.h>
#include <display_functions/object_select_circle_nearest.h>
#include <display_functions/object_select_arc_nearest.h>
#include <display_functions/object_select_ellipse_nearest.h>
#include <display_functions/object_select_hermite_spline_nearest.h>
#include <display_functions/object_select_bezier_curve_nearest.h>
#include <array_functions/restore_undo_array.h>
#include <cad_draw_functions/keyboard_startpoint.h>
#include <cad_draw_functions/keyboard_endpoint.h>
#include <display_functions/object_select_line_intersection.h>

circle_3p::circle_3p()
{
    //initialiation..
    snap_cad_pos_x = mouse_cad_pos_x;
    snap_cad_pos_y = mouse_cad_pos_y;
    snap_cad_pos_z = mouse_cad_pos_z;

    //overwrite initialisation if we spot a snap somewhere..
    if(mode_snap_intersection){
        object_select_line_intersection();
    }
    if(mode_endpoint){
        object_select_line_startpoint();
        object_select_line_endpoint();
    }
    if(mode_midpoint){
        object_select_line_midpoint();
    }
    if(mode_centerpoint){
        object_select_centerpoint();
    }
    if(mode_perpendicular){
        object_select_line_perpendicular();
    }
    if(mode_snap_circle_4p){
        object_select_circle_4p_intersection();
    }
    if(mode_tangent){
        object_select_line_tangent_arc();
        object_select_line_tangent_circle();
    }
    if(mode_nearest){
        object_select_line_nearest(1);
        object_select_arc_nearest(1);
        object_select_circle_nearest(1);
        object_select_ellipse_nearest(1);
        object_select_hermite_spline_nearest(1);
        object_select_bezier_curve_nearest(1);
    }

    if(click == 0){
        messagebox_text = "<b><i>mode circle </i></b> click first point";
    }

    if(click == 1){
        int_cad_array[cad_counter][0] = 2; //id circle
        //int_cad_array[cad_counter][1] = current_gui_color;
        double_cad_array[cad_counter][56] = current_gui_color_red_gl;
        double_cad_array[cad_counter][57] = current_gui_color_green_gl;
        double_cad_array[cad_counter][58] = current_gui_color_blue_gl;
        double_cad_array[cad_counter][59] = current_gui_color_alpha_gl;

        int_cad_array[cad_counter][5] = current_linetype;
        double_cad_array[cad_counter][18] = current_linetype_scale;
        double_cad_array[cad_counter][19] = current_linewidth;

        //<< "\t" << "linetype scale      "   << "\t"     << double_cad_array[i][18]   <<"\n"
        //<< "\t" << "linewidth           "   << "\t"     << double_cad_array[i][19]   <<"\n"

        X1 = snap_cad_pos_x;
        Y1 = snap_cad_pos_y;
        Z1 = mouse_cad_pos_z;
        qDebug() << "X1" << X1;
        qDebug() << "Y1" << Y1;
        qDebug() << "Z1" << Z1;
        click = 2;
    }

    if(click == 2){
        messagebox_text = "<b><i>mode circle </i></b> click second point";

        //preview stipple line..
        glColor4f(1.0f, 1.0f, 1.0f, 0.0f);  //white
        glLineStipple(1, 0xAAAA); //1-2-3-4
        glEnable(GL_LINE_STIPPLE);
        glLineWidth(1);
        glBegin(GL_LINES);
        glVertex3d(X1, Y1, Z1);                                         //xy start
        glVertex3d(snap_cad_pos_x, snap_cad_pos_y, snap_cad_pos_z);     //xy end
        glEnd();
        glLineWidth(gl_linewidth);
        glDisable(GL_LINE_STIPPLE);
    }

    if(click == 3){

        X2 = snap_cad_pos_x;
        Y2 = snap_cad_pos_y;
        Z2 = mouse_cad_pos_z;
        qDebug() << "X2" << X2;
        qDebug() << "Y2" << Y2;
        qDebug() << "Z2" << Z2;
        click = 4;
    }

    if(click == 4){
        messagebox_text = "<b><i>mode circle </i></b> click last point";

        //preview function..
        X3 = snap_cad_pos_x;
        Y3 = snap_cad_pos_y;
        Z3 = mouse_cad_pos_z;
        qDebug() << "X3" << X3;
        qDebug() << "Y3" << Y3;
        qDebug() << "Z3" << Z3;

        //calculate 3 point circle... calculate xy center and radius..
        // Get the perpendicular bisector of (x1, y1) and (x2, y2).
        double x1 = (X2 + X1) / 2;
        double y1 = (Y2 + Y1) / 2;
        double dy1 = X2 - X1;
        double dx1 = -(Y2 - Y1);

        // Get the perpendicular bisector of (x2, y2) and (x3, y3).
        double x2 = (X3 + X2) / 2;
        double y2 = (Y3 + Y2) / 2;
        double dy2 = X3 - X2;
        double dx2 = -(Y3 - Y2);

        double endpoint_x0 = x1 + dx1;
        double endpoint_y0 = y1 + dy1;
        double endpoint_x1 = x2 + dx2;
        double endpoint_y1 = y2 + dy2;

        //line 1
        double delta_y0 = endpoint_y0 - y1;
        double delta_x0 = x1 - endpoint_x0;
        double c0 = delta_y0 * x1 + delta_x0 * y1;
        //line 2
        double delta_y1 = endpoint_y1 - y2;
        double delta_x1 = x2 - endpoint_x1;
        double c1 = delta_y1 * x2 + delta_x1 * y2;

        double determinant = delta_y0*delta_x1 - delta_y1*delta_x0;
        //qDebug() << "determinant is : " << determinant;

        if (determinant == 0) // The lines are parallel.
        {
            //qDebug() << "the lines are parallel";
        }
        else  {
            double x_center = (delta_x1*c0 - delta_x0*c1)/determinant;
            double y_center = (delta_y0*c1 - delta_y1*c0)/determinant;
            double dx = x_center - X1;
            double dy = y_center - Y1;
            double radius = sqrt(dx * dx + dy * dy);
            //qDebug() << " intersection point is x : " << x_center << " y : " << y_center << " radius : " << radius;

            double_cad_array[cad_counter][6] = x_center;
            double_cad_array[cad_counter][7] = y_center;
            double_cad_array[cad_counter][9] = radius;

            //write the four intersection points..
            //left point :
            double_cad_array[cad_counter][25] = double_cad_array[cad_counter][6] - double_cad_array[cad_counter][9] ; //radius - center x..
            double_cad_array[cad_counter][26] = double_cad_array[cad_counter][7]; //is centerheight..
            double_cad_array[cad_counter][27] = Z3;
            //right point :
            double_cad_array[cad_counter][28] = double_cad_array[cad_counter][6] + double_cad_array[cad_counter][9] ; //radius + center x..
            double_cad_array[cad_counter][29] = double_cad_array[cad_counter][7]; //is centerheight..
            double_cad_array[cad_counter][30] = Z3;
            //top point :
            double_cad_array[cad_counter][31] = double_cad_array[cad_counter][6]; //center x..
            double_cad_array[cad_counter][32] = double_cad_array[cad_counter][7] + double_cad_array[cad_counter][9] ; //is centerheight..
            double_cad_array[cad_counter][33] = Z3;
            //bottom point :
            double_cad_array[cad_counter][34] = double_cad_array[cad_counter][6]; //center x..
            double_cad_array[cad_counter][35] = double_cad_array[cad_counter][7] - double_cad_array[cad_counter][9] ; //is centerheight..
            double_cad_array[cad_counter][36] = Z3;
        }

    }

    if(click == 5){
        no_selection();
        cad_counter++;
        mode_circle_3p = 0;
        click = 0;

        messagebox_text = "<b><i>mode circle </i></b> enter for repeat";
    }
}

































