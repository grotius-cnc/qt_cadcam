#-------------------------------------------------
#
# Project created by QtCreator 2019-07-01T10:08:48
#
#-------------------------------------------------

QT       += core gui opengl printsupport svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Cad
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#CONFIG += c++11 console


SOURCES += \
    array_functions/cad_array.cpp \
    array_functions/cam_array.cpp \
    array_functions/copy_cad_to_cam_array.cpp \
    array_functions/copy_mirror_array.cpp \
    array_functions/copy_move_array.cpp \
    array_functions/copy_move_cam_array.cpp \
    array_functions/copy_rotate_array.cpp \
    array_functions/copy_scale_array.cpp \
    array_functions/delete_selected_cad_array_objects.cpp \
    array_functions/deselect_all_cad_array.cpp \
    array_functions/deselect_highlight_hovering.cpp \
    array_functions/empty_cad_array.cpp \
    array_functions/empty_cam_array.cpp \
    array_functions/empty_triangle_array.cpp \
    array_functions/emtpy_current_cad_counter.cpp \
    array_functions/purge_array.cpp \
    array_functions/restore_undo_array.cpp \
    array_functions/select_all_cad_array.cpp \
    array_functions/stretch_arc_array.cpp \
    array_functions/stretch_line_array.cpp \
    array_functions/swap_cam_array.cpp \
    array_functions/triangle_array.cpp \
    array_functions/update_undo_array.cpp \
    cad_draw_functions/arc.cpp \
    cad_draw_functions/arc_stretch.cpp \
    cad_draw_functions/circle_2p.cpp \
    cad_draw_functions/circle_3p.cpp \
    cad_draw_functions/cubic_hermite_spline.cpp \
    cad_draw_functions/ellipse.cpp \
    cad_draw_functions/keyboard_endpoint.cpp \
    cad_draw_functions/keyboard_startpoint.cpp \
    cad_draw_functions/line.cpp \
    cad_draw_functions/linestrip.cpp \
    cad_draw_functions/point.cpp \
    cad_draw_functions/polygon.cpp \
    cad_draw_functions/qubic_bezier_curve.cpp \
    cad_draw_functions/rectangular.cpp \
    cad_draw_functions/redraw_arc.cpp \
    cad_draw_functions/text.cpp \
    cad_modify_functions/chamfer.cpp \
    cad_modify_functions/copy.cpp \
    cad_modify_functions/del.cpp \
    cad_modify_functions/extend.cpp \
    cad_modify_functions/fillet.cpp \
    cad_modify_functions/match_properties.cpp \
    cad_modify_functions/mirror.cpp \
    cad_modify_functions/move.cpp \
    cad_modify_functions/offset.cpp \
    cad_modify_functions/preview_displacement.cpp \
    cad_modify_functions/preview_displacement_arc_stretch.cpp \
    cad_modify_functions/preview_displacement_line_stretch.cpp \
    cad_modify_functions/rotate.cpp \
    cad_modify_functions/scale.cpp \
    cad_modify_functions/stretch.cpp \
    cad_modify_functions/text_edit.cpp \
    cad_modify_functions/trim.cpp \
    cam_functions/cam_text.cpp \
    cam_functions/contour_offset.cpp \
    cam_functions/contour_recognize.cpp \
    cam_functions/contour_reverse.cpp \
    cam_functions/final_direction.cpp \
    cam_functions/g_code.cpp \
    cam_functions/nearest.cpp \
    cam_functions/offset_intersection.cpp \
    cam_functions/point_in_polygon.cpp \
    cam_functions/polytree.cpp \
    cam_functions/polytree_triangulation.cpp \
    cam_functions/triangulation.cpp \
    core_functions/variables.cpp \
    dialog_functions/dialog_axis.cpp \
    dialog_functions/dialog_color.cpp \
    dialog_functions/dialog_dimension_edit.cpp \
    dialog_functions/dialog_file.cpp \
    dialog_functions/dialog_linetype.cpp \
    dialog_functions/dialog_linewidth.cpp \
    dialog_functions/dialog_postprocessor.cpp \
    dialog_functions/dialog_print.cpp \
    dialog_functions/dialog_textedit.cpp \
    dialog_functions/dialog_tools.cpp \
    dimension/dimension.cpp \
    display_functions/color.cpp \
    display_functions/display.cpp \
    display_functions/display_cad.cpp \
    display_functions/display_cam.cpp \
    display_functions/display_dimension_text.cpp \
    display_functions/display_user_text.cpp \
    display_functions/highlight.cpp \
    display_functions/linetype.cpp \
    display_functions/no_highlight.cpp \
    display_functions/no_selection.cpp \
    display_functions/object_select_arc_nearest.cpp \
    display_functions/object_select_bezier_curve_nearest.cpp \
    display_functions/object_select_centerpoint.cpp \
    display_functions/object_select_circle_4p_intersection.cpp \
    display_functions/object_select_circle_nearest.cpp \
    display_functions/object_select_ellipse_nearest.cpp \
    display_functions/object_select_hermite_spline_nearest.cpp \
    display_functions/object_select_line_endpoint.cpp \
    display_functions/object_select_line_intersection.cpp \
    display_functions/object_select_line_midpoint.cpp \
    display_functions/object_select_line_nearest.cpp \
    display_functions/object_select_line_perpendicular.cpp \
    display_functions/object_select_line_startpoint.cpp \
    display_functions/object_select_line_tangent_arc.cpp \
    display_functions/object_select_line_tangent_circle.cpp \
    display_functions/origin.cpp \
    display_functions/preview_selection.cpp \
    display_functions/print.cpp \
    display_functions/show_centerpoint.cpp \
    display_functions/show_endpoint.cpp \
    display_functions/show_midpoint.cpp \
    display_functions/show_startpoint.cpp \
    display_functions/simple_line_select.cpp \
    display_functions/window_select.cpp \
    display_functions/window_select_stretch.cpp \
    file_functions/read_arc.cpp \
    file_functions/read_circle.cpp \
    file_functions/read_gro.cpp \
    file_functions/read_line.cpp \
    file_functions/read_spline.cpp \
    file_functions/write_arc.cpp \
    file_functions/write_circle.cpp \
    file_functions/write_gro.cpp \
    file_functions/write_line.cpp \
    interface_functions/cw_ccw.cpp \
    interface_functions/distance.cpp \
    interface_functions/snapshot.cpp \
    interface_functions/zoom_accelerator.cpp \
    interface_functions/zoom_extends.cpp \
    interface_functions/zoom_in.cpp \
    interface_functions/zoom_move.cpp \
    interface_functions/zoom_out.cpp \
    interface_functions/zoom_rotate.cpp \
    interface_functions/zoom_window.cpp \
    keyboard/keyboard_interaction.cpp \
    main.cpp \
    mainwindow.cpp \
    opengl.cpp \
    text_functions/read_arc_text.cpp \
    text_functions/read_circle_text.cpp \
    text_functions/read_line_text.cpp \

HEADERS += \
    array_functions/cad_array.h \
    array_functions/cam_array.h \
    array_functions/copy_cad_to_cam_array.h \
    array_functions/copy_mirror_array.h \
    array_functions/copy_move_array.h \
    array_functions/copy_move_cam_array.h \
    array_functions/copy_rotate_array.h \
    array_functions/copy_scale_array.h \
    array_functions/delete_selected_cad_array_objects.h \
    array_functions/deselect_all_cad_array.h \
    array_functions/deselect_highlight_hovering.h \
    array_functions/empty_cad_array.h \
    array_functions/empty_cam_array.h \
    array_functions/empty_triangle_array.h \
    array_functions/emtpy_current_cad_counter.h \
    array_functions/purge_array.h \
    array_functions/restore_undo_array.h \
    array_functions/select_all_cad_array.h \
    array_functions/stretch_arc_array.h \
    array_functions/stretch_line_array.h \
    array_functions/swap_cam_array.h \
    array_functions/triangle_array.h \
    array_functions/update_undo_array.h \
    cad_draw_functions/arc.h \
    cad_draw_functions/arc_stretch.h \
    cad_draw_functions/circle_2p.h \
    cad_draw_functions/circle_3p.h \
    cad_draw_functions/cubic_bezier_curve.h \
    cad_draw_functions/cubic_hermite_spline.h \
    cad_draw_functions/ellipse.h \
    cad_draw_functions/keyboard_endpoint.h \
    cad_draw_functions/keyboard_startpoint.h \
    cad_draw_functions/line.h \
    cad_draw_functions/linestrip.h \
    cad_draw_functions/point.h \
    cad_draw_functions/polygon.h \
    cad_draw_functions/rectangular.h \
    cad_draw_functions/redraw_arc.h \
    cad_draw_functions/text.h \
    cad_modify_functions/chamfer.h \
    cad_modify_functions/copy.h \
    cad_modify_functions/del.h \
    cad_modify_functions/extend.h \
    cad_modify_functions/fillet.h \
    cad_modify_functions/match_properties.h \
    cad_modify_functions/mirror.h \
    cad_modify_functions/move.h \
    cad_modify_functions/offset.h \
    cad_modify_functions/preview_displacement.h \
    cad_modify_functions/preview_displacement_arc_stretch.h \
    cad_modify_functions/preview_displacement_line_stretch.h \
    cad_modify_functions/rotate.h \
    cad_modify_functions/scale.h \
    cad_modify_functions/stretch.h \
    cad_modify_functions/text_edit.h \
    cad_modify_functions/trim.h \
    cam_functions/cam_text.h \
    cam_functions/contour_offset.h \
    cam_functions/contour_recognize.h \
    cam_functions/contour_reverse.h \
    cam_functions/final_direction.h \
    cam_functions/g_code.h \
    cam_functions/nearest.h \
    cam_functions/offset_intersection.h \
    cam_functions/point_in_polygon.h \
    cam_functions/polytree.h \
    cam_functions/polytree_triangulation.h \
    cam_functions/triangulation.h \
    core_functions/variables.h \
    dialog_functions/dialog_axis.h \
    dialog_functions/dialog_color.h \
    dialog_functions/dialog_dimension_edit.h \
    dialog_functions/dialog_file.h \
    dialog_functions/dialog_linetype.h \
    dialog_functions/dialog_linewidth.h \
    dialog_functions/dialog_postprocessor.h \
    dialog_functions/dialog_print.h \
    dialog_functions/dialog_textedit.h \
    dialog_functions/dialog_tools.h \
    dimension/dimension.h \
    display_functions/color.h \
    display_functions/display.h \
    display_functions/display_cad.h \
    display_functions/display_cam.h \
    display_functions/display_dimension_text.h \
    display_functions/display_user_text.h \
    display_functions/highlight.h \
    display_functions/linetype.h \
    display_functions/no_highlight.h \
    display_functions/no_selection.h \
    display_functions/object_select_arc_nearest.h \
    display_functions/object_select_bezier_curve_nearest.h \
    display_functions/object_select_centerpoint.h \
    display_functions/object_select_circle_4p_intersection.h \
    display_functions/object_select_circle_nearest.h \
    display_functions/object_select_ellipse_nearest.h \
    display_functions/object_select_hermite_spline_nearest.h \
    display_functions/object_select_line_endpoint.h \
    display_functions/object_select_line_intersection.h \
    display_functions/object_select_line_midpoint.h \
    display_functions/object_select_line_nearest.h \
    display_functions/object_select_line_perpendicular.h \
    display_functions/object_select_line_startpoint.h \
    display_functions/object_select_line_tangent_arc.h \
    display_functions/object_select_line_tangent_circle.h \
    display_functions/origin.h \
    display_functions/preview_selection.h \
    display_functions/print.h \
    display_functions/show_centerpoint.h \
    display_functions/show_endpoint.h \
    display_functions/show_midpoint.h \
    display_functions/show_startpoint.h \
    display_functions/simple_line_select.h \
    display_functions/window_select.h \
    display_functions/window_select_stretch.h \
    file_functions/read_arc.h \
    file_functions/read_circle.h \
    file_functions/read_gro.h \
    file_functions/read_line.h \
    file_functions/read_spline.h \
    file_functions/write_arc.h \
    file_functions/write_circle.h \
    file_functions/write_gro.h \
    file_functions/write_line.h \
    interface_functions/cw_ccw.h \
    interface_functions/distance.h \
    interface_functions/snapshot.h \
    interface_functions/zoom_accelerator.h \
    interface_functions/zoom_extends.h \
    interface_functions/zoom_in.h \
    interface_functions/zoom_move.h \
    interface_functions/zoom_out.h \
    interface_functions/zoom_rotate.h \
    interface_functions/zoom_window.h \
    keyboard/keyboard_interaction.h \
    mainwindow.h \
    opengl.h \
    text_functions/read_arc_text.h \
    text_functions/read_circle_text.h \
    text_functions/read_line_text.h \ \

FORMS += \
    dialog_functions/dialog_axis.ui \
    dialog_functions/dialog_color.ui \
    dialog_functions/dialog_dimension_edit.ui \
    dialog_functions/dialog_file.ui \
    dialog_functions/dialog_linetype.ui \
    dialog_functions/dialog_linewidth.ui \
    dialog_functions/dialog_postprocessor.ui \
    dialog_functions/dialog_print.ui \
    dialog_functions/dialog_textedit.ui \
    dialog_functions/dialog_tools.ui \
    mainwindow.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


CONFIG(release, debug|release): DEFINES += QT_NO_DEBUG_OUTPUT

#release: DESTDIR = $$PWD/Release
#debug:   DESTDIR = $$PWD/Debug

#OBJECTS_DIR = $$DESTDIR/obj
#MOC_DIR = $$DESTDIR/moc
#RCC_DIR = $$DESTDIR/qrc
#UI_DIR = $$DESTDIR/ui

RESOURCES += \
    icons.qrc

DISTFILES += \
    area_partition.txt \
    area_partition_scanner_slow \
    binary_to_hex.txt \
    cam_functions/check_point_inside.txt \
    cam_functions/contour_recognize.txt \
    cam_functions/contour_recognize_h.txt \
    cam_functions/scan_nearest_arc.txt \
    cam_functions/scan_nearest_circle.txt \
    cam_functions/scan_nearest_line.txt \
    clipper.txt \
    color/alphaback.png \
    color/buttonbox_with_two_pixmaps.txt \
    connect_slots.txt \
    delaunator.txt \
    drawings/empty_template.dxf \
    drawings/test.dxf \ \ \
    earcut.txt \
    poly2tri.txt \
    scan_depth_0.txt \
    vector_example.txt

unix: LIBS += -lglut -lGLU

INCLUDEPATH +=	$$PWD/clipper/include \
                $$PWD/poly2tri/include/poly2tri

DEPENDPATH +=	$$PWD/clipper/include \
                $$PWD/poly2tri/include/poly2tri

unix:!macx: {
    contains(QT_ARCH, i386) {
        message("32-bit libs not built, you can build it manually")
    } else {
        LIBS +=	-L$$PWD/poly2tri/lib/linux_x86_64/ -lpoly2tri
    }
}

win32 {
    !contains(QMAKE_TARGET.arch, x86_64) {
        message("32-bit libs not built, you can build it manually")
    } else {
        LIBS += -L$$PWD/poly2tri/lib/win_x86_64/ -lpoly2tri
    }
}


#win32: LIBS += -lGlU32 -lglut -lOpenGL32
#INCLUDEPATH += $$PWD/'../../../../../Program Files (x86)/Windows Kits/10/Lib/10.0.18362.0/um/x64'
#DEPENDPATH += $$PWD/'../../../../../Program Files (x86)/Windows Kits/10/Lib/10.0.18362.0/um/x64'
