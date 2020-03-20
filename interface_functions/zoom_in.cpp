#include "zoom_in.h"
#include <core_functions/variables.h>
#include <interface_functions/zoom_accelerator.h>

zoom_in::zoom_in()
{
    zoom_accelerator();

    zoom_cad = zoom_cad + zoom_cad_factor;
    zoom_cad_left = zoom_cad_left + zoom_cad_factor;
    zoom_cad_right = zoom_cad_right - zoom_cad_factor;
    zoom_cad_top = zoom_cad_top - zoom_cad_factor;
    zoom_cad_bottom = zoom_cad_bottom + zoom_cad_factor;

//    qDebug() << "zoom_cad" << zoom_cad;
//    qDebug() << "zoom_cad_factor" << zoom_cad_factor;
//    qDebug() << "zoom_cad_left" << zoom_cad_left;
//    qDebug() << "zoom_cad_right" << zoom_cad_right;
//    qDebug() << "zoom_cad_bottom" << zoom_cad_bottom;
//    qDebug() << "zoom_cad_top" << zoom_cad_top;

//    qDebug() << "zoom delta x :" << zoom_cad_right - zoom_cad_left;
//    qDebug() << "zoom delta y :" << zoom_cad_top - zoom_cad_bottom;
//    qDebug() << "zoom delta ratio :" << (zoom_cad_right - zoom_cad_left) / (zoom_cad_top - zoom_cad_bottom);
//    qDebug() << "" ;

}
