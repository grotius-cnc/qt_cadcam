#include "variables.h"
#include <QString>

GLdouble zoom;
GLdouble zoom_left;
GLdouble zoom_right;
GLdouble zoom_top;
GLdouble zoom_bottom;
GLdouble screen_pixel_width;
GLdouble screen_pixel_height;
GLdouble screen_cad_width;
GLdouble screen_cad_height;

GLdouble gl_rotate_x;
GLdouble gl_rotate_y;
GLdouble gl_rotate_z;

GLdouble snapshot_zoom_left;
GLdouble snapshot_zoom_right;
GLdouble snapshot_zoom_top;
GLdouble snapshot_zoom_bottom;

GLdouble distance_cad_mousepos_x;
GLdouble distance_cad_mousepos_y;
GLdouble distance_cad_mousepos_z;
GLdouble snapshot_cad_mousepos_x;
GLdouble snapshot_cad_mousepos_y;
GLdouble snapshot_cad_mousepos_z;

int gl_linewidth = 1;
int current_gui_color = 7;

double mouse_pixel_pos_x;
double mouse_pixel_pos_y;
double mouse_cad_pos_x;
double mouse_cad_pos_y;
double mouse_cad_pos_z;

double snap_cad_pos_x;
double snap_cad_pos_y;
double snap_cad_pos_z;

int click = 0;
int zoom_click = 0;
int select_click = 0;
int cad_counter = 0;
int cam_counter = 0;
int triangle_counter = 0;
int temp_counter = 0;

int int_cad_array[100000][30];
double double_cad_array[100000][60];
QString string_cad_array[100000][2];

int int_cam_array[100000][30];
double double_cam_array[100000][60];

int int_triangle_array[100000][1]; //for color
double double_triangle_array[100000][4];

int int_undo_array[100000][30];
double double_undo_array[100000][60];

int mm_points[3000][1500];

//textbox..
bool append = 0;
QString string;
int int_key;

double dist_x = 0;
double dist_y = 0;
double dist_z = 0;
double p1x_mirror = 0;
double p1y_mirror = 0;
double p1z_mirror = 0;
double p2x_mirror = 0;
double p2y_mirror = 0;
double p2z_mirror = 0;
double rotate_degrees = 0;
double scale_factor = 0;

//opengl
double object_highlight;
double aspect;
int segments = 32; //used in display class as part of the resolution..

double zoom_cad;
double zoom_cad_left;
double zoom_cad_right;
double zoom_cad_top;
double zoom_cad_bottom;
double zoom_cad_factor;
//double screen_pixel_ratio;

//draw circle
double diameter = 0;
double radius = 0;
bool bool_diameter = 0;
bool bool_radius = 0;

//draw arc
double X1 = 0;
double Y1 = 0;
double Z1 = 0;
double X2 = 0;
double Y2 = 0;
double Z2 = 0;
double X3 = 0;
double Y3 = 0;
double Z3 = 0;

//draw polygon
double x3;
double y3;
double z3;
double x4;
double y4;
double z4;
bool even;
double x_center;
double y_center;
int polygon_sides = 5;
double start_angle;

//ellipse
double x0_start;
double y0_start;
double x1_start;
double y1_start;
double x0_end;
double y0_end;
double x1_end;
double y1_end;
double midpoint_x;
double midpoint_y;
double distance_x ;
double distance_y ;
double distance_z ;
double arc_pieces = 999; //66 number += 3..
double px_top;
double py_top;

//spline
int i_spline = 0;
double Ax;
double Ay;
double Az;
double Bx;
double By;
double Bz;
double Cx;
double Cy;
double Cz;
double Dx;
double Dy;
double Dz;
double t; //value from 0 to 1..
//double s = 1-t;
double px_min = 0;
double px_max = 0;
double t_min;
double t_max;
double t_focus;


int pieces = 200;
double Radius_small = 0;
double Radius_big = 0;

//preview class
//double dist_x;
//double dist_y;
//double dist_z;

//gui
double double_user_input;
QString string_user_input;
bool clear_user_input;

QString intersection_type;
QString messagebox_text;
double g2;
double intersection_text_y;

//mouse
bool left_mouse_button;
bool middle_mouse_button;
bool right_mouse_button;

//keyboard
bool key_escape = 0;
bool key_enter = 0;
bool key_control = 0;
bool key_z = 0;
bool relative = 0;
bool keyboard = 0;
bool key_shift = 0;

//snap variables..
double snap_dist; //see opengl for value..
double red_dist = 2;

//move..
double base_x = 0;
double base_y = 0;
double base_z = 0;
double target_x = 0;
double target_y = 0;
double target_z = 0;

//chamfer & fillet..
int select_id = -1;
int fillet_id = -1;
double fillet_mm = 0;
int chamfer_id = -1;
double chamfer_mm = 0;
int trim_extend_id = -1;
int id_1 = -1;
bool id_1_chamfer_startpoint = 0;
int id_2 = -1;
bool id_2_chamfer_startpoint = 0;
double id_1_mouse_dist_to_startpoint = 0;
double id_1_mouse_dist_to_endpoint = 0;
double id_2_mouse_dist_to_startpoint = 0;
double id_2_mouse_dist_to_endpoint = 0;

int snap_startpoint = -1;
int snap_endpoint = -1;
int snap_midpoint = -1;
int snap_nearest = -1;
int snap_perpendicular = -1;
int snap_centerpoint = -1;
int snap_tangent = -1;
int snap_circle_left = -1;
int snap_circle_right = -1;
int snap_circle_top = -1;
int snap_circle_bottom = -1;

//mode variables..
bool mode_select = 1;
bool mode_point;
bool mode_line;
bool mode_linestrip;
bool mode_circle_2p;
bool mode_circle_3p;
bool mode_arc;
bool mode_rectangular;
bool mode_polygon;
bool mode_ellipse;
bool mode_cubic_hermite_spline;
bool mode_cubic_bezier_curve;
bool mode_ortho;
bool mode_midpoint;
bool mode_endpoint;
bool mode_nearest;
bool mode_snap_intersection;
bool mode_perpendicular;
bool mode_centerpoint;
bool mode_tangent;
bool mode_snap_circle_4p;
bool mode_zoom_window;
bool mode_text;
bool mode_text_edit;
bool mode_define_cw_ccw;

bool mode_chamfer;
bool mode_copy;
bool mode_extend;
bool mode_fillet;
bool mode_mirror;
bool mode_move;
bool mode_offset;
bool mode_rotate;
bool mode_scale;
bool mode_stretch;
bool mode_trim;
bool mode_delete;

bool mode_print;
bool mode_background_white = 0;
bool mode_grid;
bool mode_dimension;
bool mode_match_properties;
QString dimension_type;

bool mode_cad;
bool mode_cam;
bool mode_solid;
bool mode_show_triangles;
bool mode_cull_face;

//grid
double gridsize = 100;
double gridspace = 10;

//cam
bool mode_contour_recognize;
bool mode_contour_offset;
bool mode_contour_autonest;
QVector<int> contournumbers;
QVector<int> object_list;
QVector<int> master;
QVector<int> slave;
QVector<int> inside;
QVector<int> templist;
QVector<int> templist1;
bool loop_times;
int temp = 0;
int depth = 0;
int inside_count;

double solid_color_red;
double solid_color_green;
double solid_color_blue;
double solid_color_alpha;

QString gcode_startblock;
QString gcode_offblock;
QString gcode_intro;
QString gcode_outtro;

//tools
QString extern_tool_description;
QString extern_diameter;
QString extern_power_rpm;
QString extern_cutspeed;
QString extern_start_delay;
QString extern_start_height;
QString extern_cut_height;
QString extern_end_delay;
QString extern_plunge_speed;

//postprocessor
QString extern_post_description;
bool extern_display_line_nr;
QString extern_rapid_move_sign;
QString extern_lineair_move_sign;
QString extern_circle_cw_sign;
QString extern_circle_ccw_sign;
QString extern_quadratic_spline_sign;
QString extern_spindle_delay_sign;
QString extern_tool_sign;
QString extern_feedrate_sign;

//base axis + head axis config
QString extern_axis_base_description;
QString extern_x_axis_sign;
QString extern_y_axis_sign;
QString extern_x_home_pos;
QString extern_y_home_pos;

QString extern_axis_head_description;
QString extern_z_axis_sign;
QString extern_z_travelheight;
QString extern_z_home_pos;
QString extern_x_offset;
QString extern_y_offset;
QString extern_z_offset;

double travelheight;
double leadin;

//gcode
QString gcode_filename;

QVector<int> solid_outside;
QVector<int> solid_inside;

//file variables..
QString filename_in;
QString filename_out;

//color diaglog extern toolbar variables..
QList<int> red_list;
QList<int> green_list;
QList<int> blue_list;
QList<int> alpha_list;
QList<QString> comments;
QList<double> red_list_gl;
QList<double> green_list_gl;
QList<double> blue_list_gl;
QList<double> alpha_list_gl;

double current_gui_color_red_gl;
double current_gui_color_green_gl;
double current_gui_color_blue_gl;
double current_gui_color_alpha_gl;

bool update_mainwindow;
int current_color=-1;

//linetype
int current_linetype_index = -1;
GLushort current_linetype;
double current_linetype_scale = 0;// = 10;
QList<double> linetype_scale_list;
QList<QString> linetype_pattern_list;
QList<QString> linetype_comment_list;

//linewidth
double current_linewidth;
int current_linewidth_index = -1;
QList<double> linewidth_list;
QList<QString> linewidth_comment_list;

//treewidget
bool bool_load_treewidget;

int colorcode_line;
int x_start_line;
int y_start_line;
int z_start_line;
int x_end_line;
int y_end_line;
int z_end_line;

int x_center_line;
int y_center_line;
int z_center_line;
int radius_line;
int start_angle_line;
int end_angle_line;

bool color_trigger;
bool x_start_line_trigger;
bool y_start_line_trigger;
bool z_start_line_trigger;
bool x_end_line_trigger;
bool y_end_line_trigger;
bool z_end_line_trigger;

bool linetrigger;
bool circletrigger;
bool arctrigger;
bool polytrigger;

int linenumber;

int id;                             //LINE = 1, CIRCLE = 2, ARC = 3, LWPOLYLINE = 4, SPLINE = 5
int colorcode;                      //colorcode 62, red = 1, yellow = 2, green = 3, cyan = 4, blue = 5, magenta = 6, white = 7, dark_grey = 8, light_grey = 9
int arrayline_to_int_number;        //after start and end point's are recognized, we number the array lines.
int contournumber = 0;

//stretch
double x_start;
double y_start;
double x_end;
double y_end;

//text edit
QString text_edit_string;
double text_height = 0;
int trigger = 0;
QString x; //string input at command line..
QString y;
QString z;
QString left_tekst;

//dimension
double arrow_lenght = 10; //see dimension dialog with the same settings..
double arrow_height = 5;
double dimension_text_height = 5;

//focus policy
bool entry_focus = 0;
bool opengl_focus = 0;

//print pixel pos
int print_x0 = 0;
int print_y0 = 0;
int print_x1 = 0;
int print_y1 = 0;
bool print_now = 0;
int printer_pixel_pos_y =0;
int margin_top=0;
int margin_left=0;
int margin_right=0;
int margin_bottom=0;
QString file_type;
QList<int> papersize;

variables::variables()
{
}



































