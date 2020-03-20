#include "opengl.h"
#include <math.h>
#include <QToolTip>
#include <QKeyEvent>
#include <QCursor>
#include <QString>
#include <mainwindow.h>
#include <display_functions/display.h>
#include <interface_functions/zoom_in.h>
#include <interface_functions/zoom_out.h>
#include <interface_functions/zoom_move.h>
#include <interface_functions/zoom_rotate.h>
#include <interface_functions/snapshot.h>
#include <interface_functions/distance.h>
#include <array_functions/deselect_highlight_hovering.h>
#include <interface_functions/zoom_window.h>
#include <display_functions/object_select_line_nearest.h>
#include <interface_functions/zoom_accelerator.h>

#include <GL/glut.h>

int value = 1;

//#define checkImageWidth 64
//#define checkImageHeight 64
//GLubyte checkImage[checkImageHeight][checkImageWidth][3];

#define myqDebug() qDebug() << fixed << qSetRealNumberPrecision(4)

opengl::opengl(QWidget *parent)
    : QOpenGLWidget(parent)
{
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    //timer->start(25);
    timer->start(25);
}

opengl::~opengl()
{

}

void opengl::initializeGL()
{
    setMouseTracking(true);
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LINE_STIPPLE);
    glEnable(GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glClearColor(0, 0, 0, 1);
    glLineWidth(1);

    zoom_cad_factor = 50;
    zoom_cad_left = -500;
    zoom_cad_right = 500;
    zoom_cad_bottom = -500;
    zoom_cad_top = 500;

    zoom_accelerator();
}

void opengl::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    screen_pixel_height = h;
    screen_pixel_width = w;
    aspect = screen_pixel_width / screen_pixel_height;
}

void opengl::paintGL()
{  
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(mode_background_white){
        glClearColor(1,1,1,1); //white background color..
    } else {glClearColor(0,0,0,1);} //black..


    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glOrtho(zoom_cad_left, zoom_cad_right, zoom_cad_bottom/aspect, zoom_cad_top/aspect, -100000.0, 100000.0);

    //snap_dist = screen_cad_width/300; //smaller
    snap_dist = screen_cad_width/150; //bigger

    glRotated(gl_rotate_x,1,0,0); //qDebug() << "gl_rotate_x : " << gl_rotate_x;
    glRotated(gl_rotate_y,0,1,0); //qDebug() << "gl_rotate_y : " << gl_rotate_y;
    glRotated(gl_rotate_z,0,0,1); //qDebug() << "gl_rotate_z : " << gl_rotate_z;

    //https://www.glprogramming.com/red/chapter08.html

    display();

}

void opengl::wheelEvent(QWheelEvent *event)
{
    if(event->delta() > 0 && zoom_cad_right - zoom_cad_left > 5 && zoom_cad_top - zoom_cad_bottom > 5){ //prevent zooming trough the plane.
        zoom_in();
        value++;
    }

    if(event->delta() < 0 ){
        zoom_out();
        value--;
    }
}

void opengl::mouseMoveEvent(QMouseEvent *event)
{
    //    for(int i = 0; i < cad_counter; i++){

    //        (object_select_line(i));
    //    }


    screen_cad_width = zoom_cad_right - zoom_cad_left;
    screen_cad_height = (zoom_cad_top - zoom_cad_bottom)/aspect;

    mouse_pixel_pos_x = event->x();
    mouse_pixel_pos_y = screen_pixel_height - event->y();
    printer_pixel_pos_y = int(screen_pixel_height)-int(mouse_pixel_pos_y); //print class needs inverted y..

    //qDebug()<<"pixel pos x : " << mouse_pixel_pos_x;
    //qDebug()<<"pixel pos y : " << mouse_pixel_pos_y;
    //qDebug()<<"printer pixel pos y : " << printer_pixel_pos_y;

    mouse_cad_pos_x = ((mouse_pixel_pos_x / screen_pixel_width) * screen_cad_width) + zoom_cad_left;
    mouse_cad_pos_y = ((mouse_pixel_pos_y / screen_pixel_height) * screen_cad_height) + (zoom_cad_bottom/aspect);

    if (this->rect().contains(event->pos())) {
        QPixmap cursor_pixmap = QPixmap(":/icons/cad_mouse_pointer.svg");
        QCursor cursor_default = QCursor(cursor_pixmap, -10, -10);
        setCursor(cursor_default);
    }
    if (!this->rect().contains(event->pos())) {
        setCursor(Qt::ArrowCursor);
    }

    if(event->buttons() == Qt::LeftButton){
        //distance_cad_mousepos_x = mouse_cad_pos_x - snapshot_cad_mousepos_x;
        //distance_cad_mousepos_y = mouse_cad_pos_y - snapshot_cad_mousepos_y;
        //distance_cad_mousepos_z = mouse_cad_pos_z - snapshot_cad_mousepos_z;
    }

    if(event->buttons() == Qt::MiddleButton){
        distance_cad_mousepos_x = snapshot_cad_mousepos_x - mouse_cad_pos_x;
        distance_cad_mousepos_y = snapshot_cad_mousepos_y - mouse_cad_pos_y;
        distance_cad_mousepos_z = snapshot_cad_mousepos_z - mouse_cad_pos_z;

        zoom_cad_left = zoom_cad_left + distance_cad_mousepos_x;
        zoom_cad_right = zoom_cad_right + distance_cad_mousepos_x;
        zoom_cad_top = zoom_cad_top + distance_cad_mousepos_y;
        zoom_cad_bottom = zoom_cad_bottom + distance_cad_mousepos_y;

        //qDebug() << "zoom left : " << zoom_cad_left;
        //qDebug() << "zoom right : " << zoom_cad_right;
        //qDebug() << "zoom top : " << zoom_cad_top;
        //qDebug() << "zoom bottom : " << zoom_cad_bottom;
    }

    if(event->buttons() == Qt::RightButton){
        zoom_rotate();
    }
}

void opengl::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::LeftButton){
        left_mouse_button = 1;

        select_click++;

        if(!mode_zoom_window){
            click++;
        }

        if(mode_zoom_window){
            zoom_click++;
        }

    }

    if(event->buttons() == Qt::MiddleButton){
        middle_mouse_button = 1;
        snapshot();
    }

    if(event->button() == Qt::RightButton){
        right_mouse_button = 1;
    }
}

void opengl::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        left_mouse_button = 0;
    }

    if(event->button() == Qt::MiddleButton){
        middle_mouse_button = 0;
    }

    if(event->button() == Qt::RightButton){
        right_mouse_button = 0;
    }
}





























