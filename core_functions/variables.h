#ifndef VARIABLES_H
#define VARIABLES_H

#include <QMainWindow>
#include <QtWidgets>
#include <QString>
#include <QtDebug>

extern GLdouble zoom;
extern GLdouble zoom_left;
extern GLdouble zoom_right;
extern GLdouble zoom_top;
extern GLdouble zoom_bottom;
extern GLdouble screen_pixel_width;
extern GLdouble screen_pixel_height;
extern GLdouble screen_cad_width;
extern GLdouble screen_cad_height;

extern GLdouble gl_rotate_x;
extern GLdouble gl_rotate_y;
extern GLdouble gl_rotate_z;

extern GLdouble snapshot_zoom_left;
extern GLdouble snapshot_zoom_right;
extern GLdouble snapshot_zoom_top;
extern GLdouble snapshot_zoom_bottom;

extern GLdouble distance_cad_mousepos_x;
extern GLdouble distance_cad_mousepos_y;
extern GLdouble distance_cad_mousepos_z;
extern GLdouble snapshot_cad_mousepos_x;
extern GLdouble snapshot_cad_mousepos_y;
extern GLdouble snapshot_cad_mousepos_z;

extern int gl_linewidth;
extern int current_gui_color;

extern double mouse_pixel_pos_x;
extern double mouse_pixel_pos_y;
extern double mouse_cad_pos_x;
extern double mouse_cad_pos_y;
extern double mouse_cad_pos_z;

extern double snap_cad_pos_x;
extern double snap_cad_pos_y;
extern double snap_cad_pos_z;

//extern double dist_x;
//extern double dist_y;
//extern double dist_z;

extern bool leftbutton;
extern bool middlebutton;
extern bool rightbutton;

extern int click;
extern int zoom_click;
extern int select_click;
extern int cad_counter;
extern int triangle_counter;
extern int cam_counter;
extern int temp_counter;

//cad modify..
extern double dist_x;
extern double dist_y;
extern double dist_z;
extern double p1x_mirror;
extern double p1y_mirror;
extern double p1z_mirror;
extern double p2x_mirror;
extern double p2y_mirror;
extern double p2z_mirror;
extern double rotate_degrees;
extern double scale_factor;

//array's
extern int int_cad_array[100000][30];
extern double double_cad_array[100000][60];
extern QString string_cad_array[100000][2];

extern int int_cam_array[100000][30];
extern double double_cam_array[100000][60];

extern int int_undo_array[100000][30];
extern double double_undo_array[100000][60];

extern int int_triangle_array[100000][1];
extern double double_triangle_array[100000][4];

extern int mm_points[3000][1500];

//textbox..
extern bool append;
extern QString string;
extern int int_key;

//opengl
extern double object_highlight;
extern double aspect;
extern int segments;
extern double zoom_cad;
extern double zoom_cad_left;
extern double zoom_cad_right;
extern double zoom_cad_top;
extern double zoom_cad_bottom;
extern double zoom_cad_factor;

//move..
extern double base_x;
extern double base_y;
extern double base_z;
extern double target_x;
extern double target_y;
extern double target_z;

//draw circle
extern double diameter;
extern double radius;
extern bool bool_diameter;
extern bool bool_radius;

//draw arc
extern double X1;
extern double Y1;
extern double Z1;
extern double X2;
extern double Y2;
extern double Z2;
extern double X3;
extern double Y3;
extern double Z3;

//draw polygon
extern double x3;
extern double y3;
extern double z3;
extern double x4;
extern double y4;
extern double z4;
extern bool even;
extern double x_center;
extern double y_center;
extern int polygon_sides;
extern double start_angle;

//ellipse
extern double x0_start;
extern double y0_start;
extern double x1_start;
extern double y1_start;
extern double x0_end;
extern double y0_end;
extern double x1_end;
extern double y1_end;
extern double midpoint_x;
extern double midpoint_y;
extern double distance_x;
extern double distance_y;
extern double distance_z;
extern double arc_pieces;
extern double px_top;
extern double py_top;

extern int pieces;
extern double Radius_small;
extern double Radius_big;

//spline
extern int i_spline;
extern double Ax;
extern double Ay;
extern double Az;
extern double Bx;
extern double By;
extern double Bz;
extern double Cx;
extern double Cy;
extern double Cz;
extern double Dx;
extern double Dy;
extern double Dz;
extern double t; //value from 0 to 1..
//double s = 1-t;
extern double px_min;
extern double px_max;
extern double t_min;
extern double t_max;
extern double t_focus;

//gui
extern double double_user_input;
extern QString string_user_input;
extern QString intersection_type;
extern QString messagebox_text;
extern double g2;
extern double intersection_text_y;
extern bool clear_user_input;

//mouse
extern bool left_mouse_button;
extern bool middle_mouse_button;
extern bool right_mouse_button;

//keyboard
extern bool key_escape;
extern bool key_enter;
extern bool key_control;
extern bool key_z;
extern bool relative;
extern bool keyboard;
extern bool key_shift;

//chamfer & fillet..
extern int select_id;
extern int fillet_id;
extern double fillet_mm;
extern int chamfer_id;
extern double chamfer_mm;
extern int trim_extend_id;
extern int id_1;
extern bool id_1_chamfer_startpoint;
extern int id_2;
extern bool id_2_chamfer_startpoint;
extern double id_1_mouse_dist_to_startpoint;
extern double id_1_mouse_dist_to_endpoint;
extern double id_2_mouse_dist_to_startpoint;
extern double id_2_mouse_dist_to_endpoint;

//snap variables..
extern double snap_dist;
extern double red_dist;
extern int snap_startpoint;
extern int snap_midpoint;
extern int snap_endpoint;
extern int snap_nearest;
extern int snap_perpendicular;
extern int snap_centerpoint;
extern int snap_tangent;
extern int snap_circle_left;
extern int snap_circle_right;
extern int snap_circle_top;
extern int snap_circle_bottom;
//extern int snap_nearest_one_cycle;

//mode variables..
extern bool mode_select;
//extern bool mode_enter;
//extern bool mode_escape;
extern bool mode_point;
extern bool mode_line;
extern bool mode_linestrip;
extern bool mode_circle_2p;
extern bool mode_circle_3p;
extern bool mode_arc;
extern bool mode_rectangular;
extern bool mode_polygon;
extern bool mode_ellipse;
extern bool mode_cubic_hermite_spline;
extern bool mode_cubic_bezier_curve;
extern bool mode_ortho;
extern bool mode_midpoint;
extern bool mode_endpoint;
extern bool mode_nearest;
extern bool mode_snap_intersection;
extern bool mode_perpendicular;
extern bool mode_centerpoint;
extern bool mode_tangent;
extern bool mode_snap_circle_4p;
extern bool mode_zoom_window;
extern bool mode_text;
extern bool mode_text_edit;
extern bool mode_define_cw_ccw;
extern bool mode_chamfer;
extern bool mode_copy;
extern bool mode_extend;
extern bool mode_fillet;
extern bool mode_mirror;
extern bool mode_move;
extern bool mode_offset;
extern bool mode_rotate;
extern bool mode_scale;
extern bool mode_stretch;
extern bool mode_trim;
extern bool mode_delete;
extern bool mode_print;
extern bool mode_background_white;
extern bool mode_grid;
extern bool mode_dimension;
extern bool mode_match_properties;
extern QString dimension_type;

extern bool mode_cad;
extern bool mode_cam;
extern bool mode_solid;
extern bool mode_show_triangles;
extern bool mode_cull_face;

//grid
extern double gridsize;
extern double gridspace;

//cam
extern bool mode_contour_recognize;
extern bool mode_contour_offset;
extern bool mode_contour_autonest;
extern QVector<int> contournumbers;
extern QVector<int> object_list;
extern QVector<int> master;
extern QVector<int> slave;
extern QVector<int> inside;
extern QVector<int> templist;
extern QVector<int> templist1;
extern bool loop_times;
extern int temp;
extern int depth;
extern int inside_count;

extern QVector<int> solid_outside;
extern QVector<int> solid_inside;

extern double solid_color_red;
extern double solid_color_green;
extern double solid_color_blue;
extern double solid_color_alpha;

extern QString gcode_startblock;
extern QString gcode_offblock;
extern QString gcode_intro;
extern QString gcode_outtro;

//tools
extern QString extern_tool_description;
extern QString extern_diameter;
extern QString extern_power_rpm;
extern QString extern_cutspeed;
extern QString extern_start_delay;
extern QString extern_start_height;
extern QString extern_cut_height;
extern QString extern_end_delay;
extern QString extern_plunge_speed;

//postprocessor
extern QString extern_post_description;
extern bool extern_display_line_nr;
extern QString extern_rapid_move_sign;
extern QString extern_lineair_move_sign;
extern QString extern_circle_cw_sign;
extern QString extern_circle_ccw_sign;
extern QString extern_quadratic_spline_sign;
extern QString extern_spindle_delay_sign;
extern QString extern_tool_sign;
extern QString extern_feedrate_sign;

//base axis + head axis config
extern QString extern_axis_base_description;
extern QString extern_x_axis_sign;
extern QString extern_y_axis_sign;
extern QString extern_x_home_pos;
extern QString extern_y_home_pos;

extern QString extern_axis_head_description;
extern QString extern_z_axis_sign;
extern QString extern_z_travelheight;
extern QString extern_z_home_pos;
extern QString extern_x_offset;
extern QString extern_y_offset;
extern QString extern_z_offset;

extern double travelheight;
extern double leadin;

//gcode
extern QString gcode_filename;

//file variables..
extern QString filename_in;
extern QString filename_out;

//color diaglog extern toolbar variables..
extern QList<int> red_list; //colors 0-255
extern QList<int> green_list;
extern QList<int> blue_list;
extern QList<int> alpha_list;
extern QList<QString> comments;

extern QList<double> red_list_gl; //colors 0-1
extern QList<double> green_list_gl;
extern QList<double> blue_list_gl;
extern QList<double> alpha_list_gl;

extern double current_gui_color_red_gl;
extern double current_gui_color_green_gl;
extern double current_gui_color_blue_gl;
extern double current_gui_color_alpha_gl;

extern bool update_mainwindow;
extern int current_color;

//linetype
extern int current_linetype_index;
extern GLushort current_linetype;
extern double current_linetype_scale;
extern QList<double> linetype_scale_list;
extern QList<QString> linetype_pattern_list;
extern QList<QString> linetype_comment_list;

//linewidth
extern double current_linewidth;
extern int current_linewidth_index;
extern QList<double> linewidth_list;
extern QList<QString> linewidth_comment_list;

//treewidget
extern bool bool_load_treewidget;

extern int colorcode_line;
extern int x_start_line;
extern int y_start_line;
extern int z_start_line;
extern int x_end_line;
extern int y_end_line;
extern int z_end_line;

extern int x_center_line;
extern int y_center_line;
extern int z_center_line;
extern int radius_line;
extern int start_angle_line;
extern int end_angle_line;

extern bool color_trigger;
extern bool x_start_line_trigger;
extern bool y_start_line_trigger;
extern bool z_start_line_trigger;
extern bool x_end_line_trigger;
extern bool y_end_line_trigger;
extern bool z_end_line_trigger;

extern bool linetrigger;
extern bool circletrigger;
extern bool arctrigger;
extern bool polytrigger;

extern int linenumber;

extern int id;                             //LINE = 1, CIRCLE = 2, ARC = 3, LWPOLYLINE = 4, SPLINE = 5
extern int colorcode;                      //colorcode 62, red = 1, yellow = 2, green = 3, cyan = 4, blue = 5, magenta = 6, white = 7, dark_grey = 8, light_grey = 9
extern int arrayline_to_int_number;        //after start and end point's are recognized, we number the array lines.
extern int contournumber;

//stretch
extern double x_start;
extern double y_start;
extern double x_end;
extern double y_end;

//text edit
extern QString text_edit_string;
extern double text_height;
extern int trigger;
extern QString x;
extern QString y;
extern QString z;
extern QString left_tekst;

//focus policy
extern bool entry_focus;
extern bool opengl_focus;

//dimension
extern double arrow_lenght;
extern double arrow_height;
extern double dimension_text_height;

//print pixel pos
extern int print_x0;
extern int print_y0;
extern int print_x1;
extern int print_y1;
extern bool print_now;
extern int printer_pixel_pos_y;
extern int margin_top;
extern int margin_left;
extern int margin_right;
extern int margin_bottom;
extern QString file_type;
extern QList<int> papersize;

class variables
{
public:
    variables();
};

#endif // VARIABLES_H



























