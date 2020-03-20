#include <mainwindow.h>
#include "ui_mainwindow.h"
#include <core_functions/variables.h>
#include <opengl.h>
#include <QString>
#include <QCursor>
#include <QIcon>
#include <cad_draw_functions/line.h>
#include <dialog_functions/dialog_file.h>
#include <dialog_functions/dialog_postprocessor.h>
#include <dialog_functions/dialog_tools.h>
#include <array_functions/cad_array.h>
#include <array_functions/cam_array.h>
#include <array_functions/triangle_array.h>
#include <array_functions/empty_cad_array.h>
#include <array_functions/empty_cam_array.h>
#include <array_functions/empty_triangle_array.h>
#include <array_functions/purge_array.h>
#include <array_functions/deselect_all_cad_array.h>
#include <array_functions/delete_selected_cad_array_objects.h>
#include <array_functions/restore_undo_array.h>
#include <interface_functions/zoom_extends.h>
#include <interface_functions/zoom_window.h>
#include <interface_functions/zoom_in.h>
#include <interface_functions/zoom_out.h>
#include <cad_draw_functions/line.h>
#include <array_functions/emtpy_current_cad_counter.h>
#include <display_functions/no_highlight.h>
#include <display_functions/no_selection.h>
#include <array_functions/copy_move_array.h>
#include <dialog_functions/dialog_tools.h>
#include <dialog_functions/dialog_axis.h>
#include <dialog_functions/dialog_color.h>
#include <dialog_functions/dialog_linetype.h>
#include <dialog_functions/dialog_linewidth.h>
#include <dialog_functions/dialog_textedit.h>

#include <file_functions/read_line.h>
#include <file_functions/read_circle.h>
#include <file_functions/read_arc.h>

#include <cam_functions/g_code.h>
#include <QColorDialog>

#include <QPrinter>
#include <QObject>

//#include <QFileInfo>

#include <file_functions/write_gro.h>
#include <file_functions/read_gro.h>

//text edit dialog
#include <QStringList>

//dimension edit dialog
#include <dialog_functions/dialog_dimension_edit.h>

//printer dialog
#include <dialog_functions/dialog_print.h>

#include <keyboard/keyboard_interaction.h>

#define MyQLineEdit() << QLineEdit() << fixed << qSetRealNumberPrecision(3)

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timerId = startTimer(25);
    setWindowIcon(QIcon(":icons/mainwindow.svg"));

    ui->toolBar_text->addWidget(textheight_LineEdit);
    textheight_LineEdit->setMinimumSize(50,20);
    textheight_LineEdit->setMaximumSize(75,20);

    textheight_LineEdit->setText("5.00");
    textheight_LineEdit->setMaxLength(10);
    textheight_LineEdit->setValidator(new QDoubleValidator(0,10000,3,this));
    text_height = textheight_LineEdit->text().toDouble();

    mode_cad = 1;

    Dialog_tools().load_table(); //initialise tool library at program startup..
    Dialog_tools().load_selected_data();

    Dialog_postprocessor().load_table();

    //combobox layer.. (see header for setting up widget)
    Dialog_color().load_table();
    ui->toolBar_color->addWidget(colors);
    colors->setMinimumWidth(250);

    //combobox linetype.. (see header for setting up widget)
    Dialog_linetype().load_table();
    ui->toolBar_linetype->addWidget(linetype);
    linetype->setMinimumWidth(250);

    //combobox linewidth.. (see header for setting up widget)
    Dialog_linewidth().load_table();
    ui->toolBar_linewidth->addWidget(linewidth);
    linewidth->setMinimumWidth(250);

    //grid.. (see header for setting up widget)
    ui->toolBar_grid->addWidget(LineEdit_gridsize);
    LineEdit_gridsize->setText(QString::number(gridsize));
    LineEdit_gridsize->setMaximumWidth(50);
    //LineEdit_gridsize->setValidator(new QDoubleValidator(0,1000,1,this));
    ui->toolBar_grid->addWidget(LineEdit_gridspace);
    LineEdit_gridspace->setText(QString::number(gridspace));
    LineEdit_gridspace->setMaximumWidth(30);
    //LineEdit_gridspace->setValidator(new QDoubleValidator(0,100,1,this));

    ui->dockWidget->hide();
    ui->openGLWidget->setFocus();
    //linetype_scale->setFocusPolicy(Qt::FocusPolicy::ClickFocus);
    //textheight_LineEdit->setFocusPolicy(Qt::FocusPolicy::ClickFocus);

    mode_grid=1;
    ui->action_grid->setChecked(1);
}

MainWindow::~MainWindow()
{
    killTimer(timerId);
    delete ui;
}

void MainWindow::timerEvent(QTimerEvent *)
{
    if(mode_grid){
        mode_endpoint = 1; //snap to grid..
        ui->action_snap_endpoint->setChecked(true);

        gridsize = LineEdit_gridsize->text().toDouble();
        gridspace = LineEdit_gridspace->text().toDouble();

        //bottom
        if(gridsize<1){
            gridsize = 1;
        }
        if(gridspace<0.1){
            gridspace=0.1;
        }

        //top
//        if(gridsize>1000){
//            gridsize = 1000;
//        }
//        if(gridspace>100){
//            gridspace=100;
//        }
    }


    if(print_now){

        qDebug()<< "file type : " << file_type;

        if(file_type == "pdf"){
            QPrinter printer(QPrinter::HighResolution); //https://stackoverflow.com/questions/45467942/how-can-i-print-a-qwidget-in-qt
            printer.setOutputFormat(QPrinter::PdfFormat);
            printer.setOutputFileName(QDir::currentPath() + "/cadcam/" + filename_out + ".pdf");
            printer.setPageMargins(margin_left, margin_top, margin_right, margin_bottom, QPrinter::Millimeter);
            if(papersize.size()==2){ //avoid errors..
                printer.setPaperSize(QSizeF(papersize.at(0), papersize.at(1)), QPrinter::Millimeter);   //a4 210x297 //a1 594x841
            }
            printer.setFullPage(true);

            QPainter painter(&printer);
            double b = 0; double h=0;

            if(print_x0<print_x1){
                b = print_x1-print_x0;
            } else {b = print_x0-print_x1;}

            if(print_x0>print_x1){ //startpoint x
                print_x0 = print_x1;
            }

            if(print_y0<print_y1){
                h = print_y1-print_y0;
            } else {h = print_y0-print_y1;}

            if(print_y0>print_y1){ //startpoint y
                print_y0 = print_y1;
            }

            double xscale = printer.pageRect().width() / b;
            double yscale = printer.pageRect().height() / h;
            double scale = qMin(xscale, yscale);
            painter.translate(printer.paperRect().center());
            painter.scale(scale, scale);
            painter.translate(-b/ 2, -h/2);
            ui->openGLWidget->render(&painter,QPoint(0,0),QRegion(print_x0,print_y0,int(b),int(h),QRegion::Rectangle));
        } else if(file_type == "png"){
            double b = 0; double h=0;

            if(print_x0<print_x1){
                b = print_x1-print_x0;
            } else {b = print_x0-print_x1;}

            if(print_x0>print_x1){ //startpoint x
                print_x0 = print_x1;
            }

            if(print_y0<print_y1){
                h = print_y1-print_y0;
            } else {h = print_y0-print_y1;}

            if(print_y0>print_y1){ //startpoint y
                print_y0 = print_y1;
            }

            // render QWidget to QImage:
            QImage bitmap(int(b),int(h), QImage::Format_ARGB32);
            bitmap.fill(Qt::transparent);
            QPainter painter(&bitmap);
            ui->openGLWidget->render(&painter,QPoint(0,0),QRegion(print_x0,print_y0,int(b),int(h),QRegion::Rectangle),QWidget::DrawChildren);
            //this->render(&painter, QPoint(), QRegion(), QWidget::DrawChildren);

            // save QImage to png file:
            QImageWriter writer(QDir::currentPath() + "/" + filename_out + ".png", "png");
            writer.write(bitmap);


        }

        mode_background_white = 0;
        ui->action_background_color->setChecked(0);
        print_now = 0;
    }

    if(bool_load_treewidget){
        load_treewidget();
        gcode_preview();
        bool_load_treewidget = 0;
    }

    if(update_mainwindow == 1){
        //combobox color, update data..
        colors->clear();
        Dialog_color().extern_toolbar_load();
        QPixmap pixmap(15,15);
        for(int i = 0; i<red_list.size(); i++){
            pixmap.fill(QColor (red_list.at(i),green_list.at(i),blue_list.at(i),alpha_list.at(i)));
            colors->addItem(pixmap, QString("layer : ") + comments.at(i));

            //qDebug()<< "red list at i : " << red_list.at(i);
        }

        //combobox linetype, update data..
        linetype->clear();
        Dialog_linetype().extern_toolbar_load();
        for(int i = 0; i<linetype_scale_list.size(); i++){
            linetype->addItem("type : " + linetype_comment_list.at(i) + ", scale : " + QString::number(linetype_scale_list.at(i)));
        }

        //combobox linewidth, update data..
        linewidth->clear();
        Dialog_linewidth().extern_toolbar_load();
        for(int i = 0; i<linewidth_list.size(); i++){

            linewidth->addItem("width : " + QString::number(linewidth_list.at(i)) + "mm, type : " + linewidth_comment_list.at(i));
        }

        update_mainwindow = 0;
    }

    if(current_color != colors->currentIndex()){
        //load current color combobox into current gui color..
        //qDebug()<< "current color index : " << colors->currentIndex();
        current_gui_color_red_gl = red_list_gl.at(colors->currentIndex());
        current_gui_color_green_gl = green_list_gl.at(colors->currentIndex());
        current_gui_color_blue_gl = blue_list_gl.at(colors->currentIndex());
        current_gui_color_alpha_gl = alpha_list_gl.at(colors->currentIndex());

        //close this function..
        current_color = colors->currentIndex();
    }

    if(current_linetype_index != linetype->currentIndex()){
        current_linetype = Dialog_linetype().binaryToDecimal(linetype_pattern_list.at(linetype->currentIndex()).toLong());
        current_linetype_scale = linetype_scale_list.at(linetype->currentIndex());

        //close this function..
        current_linetype_index = linetype->currentIndex();
        //qDebug()<< "current linetype index : " << linetype->currentIndex();
    }


    if(current_linewidth_index != linewidth->currentIndex()){
        //segmentsx interface..
        current_linewidth = linewidth_list.at(linewidth->currentIndex());

        //close this function..
        current_linewidth_index = linewidth->currentIndex();
        //qDebug()<< "current linewidth : " << current_linewidth;
    }

    if(mode_zoom_window){
        if(zoom_click == 0){
            ui->textBrowser->setText("click first window point");
        }
        if(zoom_click == 2){
            ui->textBrowser->setText("click second window point");
        }
        if(zoom_click == 3){
            ui->textBrowser->setText("");
        }
    }

    ui->lineEdit_mousecadpos_x->setText(QString::number(mouse_cad_pos_x, 'f', 6));
    ui->lineEdit_mousecadpos_y->setText(QString::number(mouse_cad_pos_y, 'f', 6));

    text_height = textheight_LineEdit->text().toDouble();

    ui->textBrowser->setText(messagebox_text);

    if(entry_focus){
        ui->lineEdit_insertbox->setFocus();
    }
    if(opengl_focus){
        ui->openGLWidget->setFocus();
        opengl_focus=0;
    }
    if(clear_user_input){
        ui->lineEdit_insertbox->clear();
        clear_user_input = 0;
    }




}

void MainWindow::on_lineEdit_insertbox_returnPressed()
{

}

void MainWindow::on_lineEdit_insertbox_textChanged(const QString &arg1)
{
    double_user_input = ui->lineEdit_insertbox->text().toDouble();
    string_user_input = ui->lineEdit_insertbox->text();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Enter)
    {
        key_enter = 1;
    }
    if(event->key() == Qt::Key_Return)
    {
        key_enter = 1;
    }

    int_key = event->key();
    (keyboard_interaction(int_key));

    if(event->key() == Qt::Key_F8)
    {
        if(mode_ortho == 0){
            mode_ortho = 1;
            ui->action_ortho->setChecked(1);
        } else if(mode_ortho == 1){
            mode_ortho = 0;
            ui->action_ortho->setChecked(0);
        }
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape)
    {
        key_escape = 0;
    }
    if(event->key() == Qt::Key_Enter)
    {
        key_enter = 0;
    }
    if(event->key() == Qt::Key_Return)
    {
        key_enter = 0;
    }
    if(event->key() == Qt::Key_Control)
    {
        key_control = 0;
    }
    if(event->key() == Qt::Key_Z)
    {
        key_z = 0;
    }
    if(event->key() == Qt::Key_Shift){
        key_shift = 0;
    }
}

void MainWindow::on_action_view_3d_toggled(bool arg1)
{
    if(arg1){
        ui->action_view_top->setChecked(0);
        gl_rotate_x = -70;
        gl_rotate_y = 0;
        gl_rotate_z = 30;
    }

}

void MainWindow::on_action_view_top_toggled(bool arg1)
{
    if(arg1){
        ui->action_view_3d->setChecked(0);
        gl_rotate_x = 0;
        gl_rotate_y = 0;
        gl_rotate_z = 0;
    }
}

void MainWindow::on_action_line_triggered()
{
    click = 0;
    select_click = 0;

    mode_arc = 0;
    mode_circle_2p = 0;
    mode_circle_3p = 0;
    mode_cubic_hermite_spline = 0;
    mode_ellipse = 0;
    mode_point = 0;
    mode_line = 1;
    mode_linestrip = 0;
    mode_polygon = 0;
    mode_cubic_bezier_curve = 0;
    mode_rectangular = 0;
    mode_text = 0;
    mode_text_edit = 0;
    mode_chamfer = 0;
    mode_copy = 0;
    mode_delete = 0;
    mode_extend = 0;
    mode_fillet = 0;
    mode_mirror = 0;
    mode_move = 0;
    mode_offset = 0;
    mode_rotate = 0;
    mode_scale = 0;
    mode_stretch = 0;
    mode_trim = 0;
    mode_dimension = 0;
    mode_contour_recognize = 0;
    mode_contour_offset = 0;
    mode_contour_autonest = 0;
    mode_print = 0;
    mode_match_properties = 0;
}

void MainWindow::on_action_linestrip_triggered()
{
    click = 0;
    select_click = 0;

    mode_arc = 0;
    mode_circle_2p = 0;
    mode_circle_3p = 0;
    mode_cubic_hermite_spline = 0;
    mode_ellipse = 0;
    mode_point = 0;
    mode_line = 0;
    mode_linestrip = 1;
    mode_polygon = 0;
    mode_cubic_bezier_curve = 0;
    mode_rectangular = 0;
    mode_text = 0;
    mode_text_edit = 0;
    mode_chamfer = 0;
    mode_copy = 0;
    mode_delete = 0;
    mode_extend = 0;
    mode_fillet = 0;
    mode_mirror = 0;
    mode_move = 0;
    mode_offset = 0;
    mode_rotate = 0;
    mode_scale = 0;
    mode_stretch = 0;
    mode_trim = 0;
    mode_dimension = 0;
    mode_contour_recognize = 0;mode_print = 0;
    mode_contour_offset = 0;
    mode_contour_autonest = 0;
    mode_print = 0;
    mode_match_properties = 0;
}

void MainWindow::on_action_rectangular_triggered()
{
    click = 0;
    select_click = 0;

    mode_arc = 0;
    mode_circle_2p = 0;
    mode_circle_3p = 0;
    mode_cubic_hermite_spline = 0;
    mode_ellipse = 0;
    mode_point = 0;
    mode_line = 0;
    mode_linestrip = 0;
    mode_polygon = 0;
    mode_cubic_bezier_curve = 0;
    mode_rectangular = 1;
    mode_text = 0;
    mode_text_edit = 0;
    mode_chamfer = 0;
    mode_copy = 0;
    mode_delete = 0;
    mode_extend = 0;
    mode_fillet = 0;
    mode_mirror = 0;
    mode_move = 0;
    mode_offset = 0;
    mode_rotate = 0;
    mode_scale = 0;
    mode_stretch = 0;
    mode_trim = 0;
    mode_dimension = 0;
    mode_contour_recognize = 0;
    mode_contour_offset = 0;
    mode_contour_autonest = 0;
    mode_print = 0;
    mode_match_properties = 0;
}

void MainWindow::on_action_arc_triggered()
{
    click = 0;
    select_click = 0;

    mode_arc = 1;
    mode_circle_2p = 0;
    mode_circle_3p = 0;
    mode_cubic_hermite_spline = 0;
    mode_ellipse = 0;
    mode_point = 0;
    mode_line = 0;
    mode_linestrip = 0;
    mode_polygon = 0;
    mode_cubic_bezier_curve = 0;
    mode_rectangular = 0;
    mode_text = 0;
    mode_text_edit = 0;
    mode_chamfer = 0;
    mode_copy = 0;
    mode_delete = 0;
    mode_extend = 0;
    mode_fillet = 0;
    mode_mirror = 0;
    mode_move = 0;
    mode_offset = 0;
    mode_rotate = 0;
    mode_scale = 0;
    mode_stretch = 0;
    mode_trim = 0;
    mode_dimension = 0;
    mode_contour_recognize = 0;
    mode_contour_offset = 0;
    mode_contour_autonest = 0;
    mode_print = 0;
    mode_match_properties = 0;
}

void MainWindow::on_action_2p_circle_triggered()
{
    click = 0;
    select_click = 0;

    mode_arc = 0;
    mode_circle_2p = 1;
    mode_circle_3p = 0;
    mode_cubic_hermite_spline = 0;
    mode_ellipse = 0;
    mode_point = 0;
    mode_line = 0;
    mode_linestrip = 0;
    mode_polygon = 0;
    mode_cubic_bezier_curve = 0;
    mode_rectangular = 0;
    mode_text = 0;
    mode_text_edit = 0;
    mode_chamfer = 0;
    mode_copy = 0;
    mode_delete = 0;
    mode_extend = 0;
    mode_fillet = 0;
    mode_mirror = 0;
    mode_move = 0;
    mode_offset = 0;
    mode_rotate = 0;
    mode_scale = 0;
    mode_stretch = 0;
    mode_trim = 0;
    mode_dimension = 0;
    mode_contour_recognize = 0;
    mode_contour_offset = 0;
    mode_contour_autonest = 0;
    mode_print = 0;
    mode_match_properties = 0;
}

void MainWindow::on_action_3p_circle_triggered()
{
    click = 0;
    select_click = 0;

    mode_arc = 0;
    mode_circle_2p = 0;
    mode_circle_3p = 1;
    mode_cubic_hermite_spline = 0;
    mode_ellipse = 0;
    mode_point = 0;
    mode_line = 0;
    mode_linestrip = 0;
    mode_polygon = 0;
    mode_cubic_bezier_curve = 0;
    mode_rectangular = 0;
    mode_text = 0;
    mode_text_edit = 0;
    mode_chamfer = 0;
    mode_copy = 0;
    mode_delete = 0;
    mode_extend = 0;
    mode_fillet = 0;
    mode_mirror = 0;
    mode_move = 0;
    mode_offset = 0;
    mode_rotate = 0;
    mode_scale = 0;
    mode_stretch = 0;
    mode_trim = 0;
    mode_dimension = 0;
    mode_contour_recognize = 0;
    mode_contour_offset = 0;
    mode_contour_autonest = 0;
    mode_print = 0;
    mode_match_properties = 0;
}

void MainWindow::on_action_polygon_triggered()
{
    click = 0;
    select_click = 0;

    mode_arc = 0;
    mode_circle_2p = 0;
    mode_circle_3p = 0;
    mode_cubic_hermite_spline = 0;
    mode_ellipse = 0;
    mode_point = 0;
    mode_line = 0;
    mode_linestrip = 0;
    mode_polygon = 1;
    mode_cubic_bezier_curve = 0;
    mode_rectangular = 0;
    mode_text = 0;
    mode_text_edit = 0;
    mode_chamfer = 0;
    mode_copy = 0;
    mode_delete = 0;
    mode_extend = 0;
    mode_fillet = 0;
    mode_mirror = 0;
    mode_move = 0;
    mode_offset = 0;
    mode_rotate = 0;
    mode_scale = 0;
    mode_stretch = 0;
    mode_trim = 0;
    mode_dimension = 0;
    mode_contour_recognize = 0;
    mode_contour_offset = 0;
    mode_contour_autonest = 0;
    mode_print = 0;
    mode_match_properties = 0;
}

void MainWindow::on_action_ellipse_triggered()
{
    click = 0;
    select_click = 0;

    mode_arc = 0;
    mode_circle_2p = 0;
    mode_circle_3p = 0;
    mode_cubic_hermite_spline = 0;
    mode_ellipse = 1;
    mode_point = 0;
    mode_line = 0;
    mode_linestrip = 0;
    mode_polygon = 0;
    mode_cubic_bezier_curve = 0;
    mode_rectangular = 0;
    mode_text = 0;
    mode_text_edit = 0;
    mode_chamfer = 0;
    mode_copy = 0;
    mode_delete = 0;
    mode_extend = 0;
    mode_fillet = 0;
    mode_mirror = 0;
    mode_move = 0;
    mode_offset = 0;
    mode_rotate = 0;
    mode_scale = 0;
    mode_stretch = 0;
    mode_trim = 0;
    mode_dimension = 0;
    mode_contour_recognize = 0;
    mode_contour_offset = 0;
    mode_contour_autonest = 0;
    mode_print = 0;
    mode_match_properties = 0;
}

void MainWindow::on_action_cubic_bezier_curve_triggered()
{
    click = 0;
    select_click = 0;

    mode_arc = 0;
    mode_circle_2p = 0;
    mode_circle_3p = 0;
    mode_cubic_hermite_spline = 0;
    mode_ellipse = 0;
    mode_point = 0;
    mode_line = 0;
    mode_linestrip = 0;
    mode_polygon = 0;
    mode_cubic_bezier_curve = 1;
    mode_rectangular = 0;
    mode_text = 0;
    mode_text_edit = 0;
    mode_chamfer = 0;
    mode_copy = 0;
    mode_delete = 0;
    mode_extend = 0;
    mode_fillet = 0;
    mode_mirror = 0;
    mode_move = 0;
    mode_offset = 0;
    mode_rotate = 0;
    mode_scale = 0;
    mode_stretch = 0;
    mode_trim = 0;
    mode_dimension = 0;
    mode_contour_recognize = 0;
    mode_contour_offset = 0;
    mode_contour_autonest = 0;
    mode_print = 0;
    mode_match_properties = 0;
}

void MainWindow::on_action_spline_triggered()
{
    click = 0;
    select_click = 0;

    mode_arc = 0;
    mode_circle_2p = 0;
    mode_circle_3p = 0;
    mode_cubic_hermite_spline = 1;
    mode_ellipse = 0;
    mode_point = 0;
    mode_line = 0;
    mode_linestrip = 0;
    mode_polygon = 0;
    mode_cubic_bezier_curve = 0;
    mode_rectangular = 0;
    mode_text = 0;
    mode_text_edit = 0;
    mode_chamfer = 0;
    mode_copy = 0;
    mode_delete = 0;
    mode_extend = 0;
    mode_fillet = 0;
    mode_mirror = 0;
    mode_move = 0;
    mode_offset = 0;
    mode_rotate = 0;
    mode_scale = 0;
    mode_stretch = 0;
    mode_trim = 0;
    mode_dimension = 0;
    mode_contour_recognize = 0;
    mode_contour_offset = 0;
    mode_contour_autonest = 0;
    mode_print = 0;
    mode_match_properties = 0;
}

void MainWindow::on_action_chamfer_triggered()
{
    click = 0;
    select_click = 0;

    mode_arc = 0;
    mode_circle_2p = 0;
    mode_circle_3p = 0;
    mode_cubic_hermite_spline = 0;
    mode_ellipse = 0;
    mode_point = 0;
    mode_line = 0;
    mode_linestrip = 0;
    mode_polygon = 0;
    mode_cubic_bezier_curve = 0;
    mode_rectangular = 0;
    mode_text = 0;
    mode_text_edit = 0;
    mode_chamfer = 1;
    mode_copy = 0;
    mode_delete = 0;
    mode_extend = 0;
    mode_fillet = 0;
    mode_mirror = 0;
    mode_move = 0;
    mode_offset = 0;
    mode_rotate = 0;
    mode_scale = 0;
    mode_stretch = 0;
    mode_trim = 0;
    mode_dimension = 0;
    mode_contour_recognize = 0;
    mode_contour_offset = 0;
    mode_contour_autonest = 0;
    mode_print = 0;
    mode_match_properties = 0;
}

void MainWindow::on_action_fillet_triggered()
{
    click = 0;
    select_click = 0;

    mode_arc = 0;
    mode_circle_2p = 0;
    mode_circle_3p = 0;
    mode_cubic_hermite_spline = 0;
    mode_ellipse = 0;
    mode_point = 0;
    mode_line = 0;
    mode_linestrip = 0;
    mode_polygon = 0;
    mode_cubic_bezier_curve = 0;
    mode_rectangular = 0;
    mode_text = 0;
    mode_text_edit = 0;
    mode_chamfer = 0;
    mode_copy = 0;
    mode_delete = 0;
    mode_extend = 0;
    mode_fillet = 1;
    mode_mirror = 0;
    mode_move = 0;
    mode_offset = 0;
    mode_rotate = 0;
    mode_scale = 0;
    mode_stretch = 0;
    mode_trim = 0;
    mode_dimension = 0;
    mode_contour_recognize = 0;
    mode_contour_offset = 0;
    mode_contour_autonest = 0;
    mode_print = 0;
    mode_match_properties = 0;
}

void MainWindow::on_action_text_triggered()
{
    click = 0;
    select_click = 0;

    mode_arc = 0;
    mode_circle_2p = 0;
    mode_circle_3p = 0;
    mode_cubic_hermite_spline = 0;
    mode_ellipse = 0;
    mode_point = 0;
    mode_line = 0;
    mode_linestrip = 0;
    mode_polygon = 0;
    mode_cubic_bezier_curve = 0;
    mode_rectangular = 0;
    mode_text = 1;
    mode_text_edit = 0;
    mode_chamfer = 0;
    mode_copy = 0;
    mode_delete = 0;
    mode_extend = 0;
    mode_fillet = 0;
    mode_mirror = 0;
    mode_move = 0;
    mode_offset = 0;
    mode_rotate = 0;
    mode_scale = 0;
    mode_stretch = 0;
    mode_trim = 0;
    mode_dimension = 0;
    mode_contour_recognize = 0;
    mode_contour_offset = 0;
    mode_contour_autonest = 0;
    mode_print = 0;
    mode_match_properties = 0;
}

void MainWindow::on_action_delete_triggered()
{
    click = 0;
    select_click = 0;

    mode_arc = 0;
    mode_circle_2p = 0;
    mode_circle_3p = 0;
    mode_cubic_hermite_spline = 0;
    mode_ellipse = 0;
    mode_point = 0;
    mode_line = 0;
    mode_linestrip = 0;
    mode_polygon = 0;
    mode_cubic_bezier_curve = 0;
    mode_rectangular = 0;
    mode_text = 0;
    mode_text_edit = 0;
    mode_chamfer = 0;
    mode_copy = 0;
    mode_delete = 1;
    mode_extend = 0;
    mode_fillet = 0;
    mode_mirror = 0;
    mode_move = 0;
    mode_offset = 0;
    mode_rotate = 0;
    mode_scale = 0;
    mode_stretch = 0;
    mode_trim = 0;
    mode_dimension = 0;
    mode_contour_recognize = 0;
    mode_contour_offset = 0;
    mode_contour_autonest = 0;
    mode_print = 0;
    mode_match_properties = 0;
}

void MainWindow::on_action_move_triggered()
{
    click = 0;
    select_click = 0;

    mode_arc = 0;
    mode_circle_2p = 0;
    mode_circle_3p = 0;
    mode_cubic_hermite_spline = 0;
    mode_ellipse = 0;
    mode_point = 0;
    mode_line = 0;
    mode_linestrip = 0;
    mode_polygon = 0;
    mode_cubic_bezier_curve = 0;
    mode_rectangular = 0;
    mode_text = 0;
    mode_text_edit = 0;
    mode_chamfer = 0;
    mode_copy = 0;
    mode_delete = 0;
    mode_extend = 0;
    mode_fillet = 0;
    mode_mirror = 0;
    mode_move = 1;
    mode_offset = 0;
    mode_rotate = 0;
    mode_scale = 0;
    mode_stretch = 0;
    mode_trim = 0;
    mode_dimension = 0;
    mode_contour_recognize = 0;
    mode_contour_offset = 0;
    mode_contour_autonest = 0;
    mode_print = 0;
    mode_match_properties = 0;
}

void MainWindow::on_action_copy_triggered()
{
    click = 0;
    select_click = 0;

    mode_arc = 0;
    mode_circle_2p = 0;
    mode_circle_3p = 0;
    mode_cubic_hermite_spline = 0;
    mode_ellipse = 0;
    mode_point = 0;
    mode_line = 0;
    mode_linestrip = 0;
    mode_polygon = 0;
    mode_cubic_bezier_curve = 0;
    mode_rectangular = 0;
    mode_text = 0;
    mode_text_edit = 0;
    mode_chamfer = 0;
    mode_copy = 1;
    mode_delete = 0;
    mode_extend = 0;
    mode_fillet = 0;
    mode_mirror = 0;
    mode_move = 0;
    mode_offset = 0;
    mode_rotate = 0;
    mode_scale = 0;
    mode_stretch = 0;
    mode_trim = 0;
    mode_dimension = 0;
    mode_contour_recognize = 0;
    mode_contour_offset = 0;
    mode_contour_autonest = 0;
    mode_print = 0;
    mode_match_properties = 0;
}

void MainWindow::on_action_rotate_triggered()
{
    click = 0;
    select_click = 0;

    mode_arc = 0;
    mode_circle_2p = 0;
    mode_circle_3p = 0;
    mode_cubic_hermite_spline = 0;
    mode_ellipse = 0;
    mode_point = 0;
    mode_line = 0;
    mode_linestrip = 0;
    mode_polygon = 0;
    mode_cubic_bezier_curve = 0;
    mode_rectangular = 0;
    mode_text = 0;
    mode_text_edit = 0;
    mode_chamfer = 0;
    mode_copy = 0;
    mode_delete = 0;
    mode_extend = 0;
    mode_fillet = 0;
    mode_mirror = 0;
    mode_move = 0;
    mode_offset = 0;
    mode_rotate = 1;
    mode_scale = 0;
    mode_stretch = 0;
    mode_trim = 0;
    mode_dimension = 0;
    mode_contour_recognize = 0;
    mode_contour_offset = 0;
    mode_contour_autonest = 0;
    mode_print = 0;
    mode_match_properties = 0;
}

void MainWindow::on_action_mirror_triggered()
{
    click = 0;
    select_click = 0;

    mode_arc = 0;
    mode_circle_2p = 0;
    mode_circle_3p = 0;
    mode_cubic_hermite_spline = 0;
    mode_ellipse = 0;
    mode_point = 0;
    mode_line = 0;
    mode_linestrip = 0;
    mode_polygon = 0;
    mode_cubic_bezier_curve = 0;
    mode_rectangular = 0;
    mode_text = 0;
    mode_text_edit = 0;
    mode_chamfer = 0;
    mode_copy = 0;
    mode_delete = 0;
    mode_extend = 0;
    mode_fillet = 0;
    mode_mirror = 1;
    mode_move = 0;
    mode_offset = 0;
    mode_rotate = 0;
    mode_scale = 0;
    mode_stretch = 0;
    mode_trim = 0;
    mode_dimension = 0;
    mode_contour_recognize = 0;
    mode_contour_offset = 0;
    mode_contour_autonest = 0;
    mode_print = 0;
    mode_match_properties = 0;
}

void MainWindow::on_action_scale_triggered()
{
    click = 0;
    select_click = 0;

    mode_arc = 0;
    mode_circle_2p = 0;
    mode_circle_3p = 0;
    mode_cubic_hermite_spline = 0;
    mode_ellipse = 0;
    mode_point = 0;
    mode_line = 0;
    mode_linestrip = 0;
    mode_polygon = 0;
    mode_cubic_bezier_curve = 0;
    mode_rectangular = 0;
    mode_text = 0;
    mode_text_edit = 0;
    mode_chamfer = 0;
    mode_copy = 0;
    mode_delete = 0;
    mode_extend = 0;
    mode_fillet = 0;
    mode_mirror = 0;
    mode_move = 0;
    mode_offset = 0;
    mode_rotate = 0;
    mode_scale = 1;
    mode_stretch = 0;
    mode_trim = 0;
    mode_dimension = 0;
    mode_contour_recognize = 0;
    mode_contour_offset = 0;
    mode_contour_autonest = 0;
    mode_print = 0;
    mode_match_properties = 0;
}

void MainWindow::on_action_stretch_triggered()
{
    click = 0;
    select_click = 0;

    mode_arc = 0;
    mode_circle_2p = 0;
    mode_circle_3p = 0;
    mode_cubic_hermite_spline = 0;
    mode_ellipse = 0;
    mode_point = 0;
    mode_line = 0;
    mode_linestrip = 0;
    mode_polygon = 0;
    mode_cubic_bezier_curve = 0;
    mode_rectangular = 0;
    mode_text = 0;
    mode_text_edit = 0;
    mode_chamfer = 0;
    mode_copy = 0;
    mode_delete = 0;
    mode_extend = 0;
    mode_fillet = 0;
    mode_mirror = 0;
    mode_move = 0;
    mode_offset = 0;
    mode_rotate = 0;
    mode_scale = 0;
    mode_stretch = 1;
    mode_trim = 0;
    mode_dimension = 0;
    mode_contour_recognize = 0;
    mode_contour_offset = 0;
    mode_contour_autonest = 0;
    mode_print = 0;
    mode_match_properties = 0;
}

void MainWindow::on_action_offset_triggered()
{
    click = 0;
    select_click = 0;

    mode_arc = 0;
    mode_circle_2p = 0;
    mode_circle_3p = 0;
    mode_cubic_hermite_spline = 0;
    mode_ellipse = 0;
    mode_point = 0;
    mode_line = 0;
    mode_linestrip = 0;
    mode_polygon = 0;
    mode_cubic_bezier_curve = 0;
    mode_rectangular = 0;
    mode_text = 0;
    mode_text_edit = 0;
    mode_chamfer = 0;
    mode_copy = 0;
    mode_delete = 0;
    mode_extend = 0;
    mode_fillet = 0;
    mode_mirror = 0;
    mode_move = 0;
    mode_offset = 1;
    mode_rotate = 0;
    mode_scale = 0;
    mode_stretch = 0;
    mode_trim = 0;
    mode_dimension = 0;
    mode_contour_recognize = 0;
    mode_contour_offset = 0;
    mode_contour_autonest = 0;
    mode_print = 0;
    mode_match_properties = 0;
}

void MainWindow::on_action_extend_triggered()
{
    click = 0;
    select_click = 0;

    mode_arc = 0;
    mode_circle_2p = 0;
    mode_circle_3p = 0;
    mode_cubic_hermite_spline = 0;
    mode_ellipse = 0;
    mode_point = 0;
    mode_line = 0;
    mode_linestrip = 0;
    mode_polygon = 0;
    mode_cubic_bezier_curve = 0;
    mode_rectangular = 0;
    mode_text = 0;
    mode_text_edit = 0;
    mode_chamfer = 0;
    mode_copy = 0;
    mode_delete = 0;
    mode_extend = 1;
    mode_fillet = 0;
    mode_mirror = 0;
    mode_move = 0;
    mode_offset = 0;
    mode_rotate = 0;
    mode_scale = 0;
    mode_stretch = 0;
    mode_trim = 0;
    mode_dimension = 0;
    mode_contour_recognize = 0;
    mode_contour_offset = 0;
    mode_contour_autonest = 0;
    mode_print = 0;
    mode_match_properties = 0;
}

void MainWindow::on_action_trim_triggered()
{
    click = 0;
    select_click = 0;

    mode_arc = 0;
    mode_circle_2p = 0;
    mode_circle_3p = 0;
    mode_cubic_hermite_spline = 0;
    mode_ellipse = 0;
    mode_point = 0;
    mode_line = 0;
    mode_linestrip = 0;
    mode_polygon = 0;
    mode_cubic_bezier_curve = 0;
    mode_rectangular = 0;
    mode_text = 0;
    mode_text_edit = 0;
    mode_chamfer = 0;
    mode_copy = 0;
    mode_delete = 0;
    mode_extend = 0;
    mode_fillet = 0;
    mode_mirror = 0;
    mode_move = 0;
    mode_offset = 0;
    mode_rotate = 0;
    mode_scale = 0;
    mode_stretch = 0;
    mode_trim = 1;
    mode_dimension = 0;
    mode_contour_recognize = 0;
    mode_contour_offset = 0;
    mode_contour_autonest = 0;
    mode_print = 0;
    mode_match_properties = 0;
}

void MainWindow::on_action_undo_triggered()
{
    restore_undo_array();
}

void MainWindow::on_action_open_file_triggered()
{
    //    Dialog_file dialog;
    //    dialog.setModal(true);
    //    dialog.exec();

#define GRO_FILES "gro files (*.gro)"
#define DXF_FILES "dxf files (*.dxf)"

    QFileDialog *dialog = new QFileDialog;
    dialog->resize(500,250);
    QString selectedFilter;

    QString filename_open = QFileDialog::getOpenFileName(
                dialog,
                "Open",
                QDir::currentPath(),
                GRO_FILES ";;" DXF_FILES,
                &selectedFilter);

    if(selectedFilter == GRO_FILES){
        //qDebug()<< "filename_open : " << filename_open;
        (read_gro(filename_open));

    }
    if(selectedFilter == DXF_FILES){
        //qDebug()<< "filename_open : " << filename_open;

        filename_in = filename_open;
        read_line();
        read_circle();
        read_arc();
        //read_spline();

        //calculate line midpoints for the whole imported array..
        for(int i=0 ; i < cad_counter ; i++) {

            double_cad_array[i][15] = (double_cad_array[i][0] + double_cad_array[i][3])/2;
            double_cad_array[i][16] = (double_cad_array[i][1] + double_cad_array[i][4])/2;
            double_cad_array[i][17] = (double_cad_array[i][2] + double_cad_array[i][5])/2;
        }

        zoom_extends();
    }

}

void MainWindow::on_action_save_as_triggered()
{
    //    old file dialog..
    //    Dialog_file dialog;
    //    dialog.setModal(true);
    //    dialog.exec();

#define GRO_FILES "gro files (*.gro)"

    QFileDialog *dialog = new QFileDialog;
    dialog->resize(500,250);
    QString selectedFilter;

    QString filename_save = QFileDialog::getSaveFileName(
                dialog,
                "Save as",
                QDir::currentPath(),
                //GRO_FILES ";;" DXF_FILES, //multiple extensions..
                GRO_FILES,
                &selectedFilter);

    if(selectedFilter == GRO_FILES){
        //qDebug()<< "filename_save : " << filename_save + ".gro";
        if(filename_save.contains(".gro")){
            (write_gro(filename_save));
        } else {
            (write_gro(filename_save+".gro"));
        }
    }
}

void MainWindow::on_action_debug_triggered()
{
    click = 0;
    select_click = 0;

    mode_arc = 0;
    mode_circle_2p = 0;
    mode_circle_3p = 0;
    mode_cubic_hermite_spline = 0;
    mode_ellipse = 0;
    mode_point = 0;
    mode_line = 0;
    mode_linestrip = 0;
    mode_polygon = 0;
    mode_cubic_bezier_curve = 0;
    mode_rectangular = 0;
    mode_text = 0;
    mode_text_edit = 0;
    mode_chamfer = 0;
    mode_copy = 0;
    mode_delete = 0;
    mode_extend = 0;
    mode_fillet = 0;
    mode_mirror = 0;
    mode_move = 0;
    mode_offset = 0;
    mode_rotate = 0;
    mode_scale = 0;
    mode_stretch = 0;
    mode_trim = 0;
    mode_dimension = 0;
    mode_contour_recognize = 0;
    mode_contour_offset = 0;
    mode_contour_autonest = 0;
    mode_print = 0;
    mode_match_properties = 0;

    purge_array();
    cad_array();
    cam_array();

    messagebox_text = "<b><i>purge done ! </i></b> purge reduced the array to : " + QString::number(cad_counter) + " items !, try a next purge to reduce more !";
}

void MainWindow::on_action_new_file_triggered()
{
    empty_cad_array();
    empty_cam_array();
    empty_triangle_array();
}

void MainWindow::on_action_zoom_extend_triggered()
{
    zoom_extends();
}

void MainWindow::on_action_zoom_window_triggered()
{
    zoom_click = 0;
    mode_zoom_window = 1;
}

void MainWindow::on_action_zoom_plus_triggered()
{
    if(zoom_cad_right - zoom_cad_left > 5 && zoom_cad_top - zoom_cad_bottom > 5){ //same as mouse scroll function..
        zoom_in();
    }

}

void MainWindow::on_action_zoom_min_triggered()
{
    zoom_out();
}

void MainWindow::on_action_snap_endpoint_toggled(bool arg1)
{
    if(arg1){
        mode_endpoint = 1;
    }
    if(!arg1){
        mode_endpoint = 0;
    }
}

void MainWindow::on_action_snap_midpoint_toggled(bool arg1)
{
    if(arg1){
        mode_midpoint = 1;
    }
    if(!arg1){
        mode_midpoint = 0;
    }
}

void MainWindow::on_action_snap_intersection_toggled(bool arg1)
{
    if(arg1){
        mode_snap_intersection = 1;
    }
    if(!arg1){
        mode_snap_intersection = 0;
    }
}

void MainWindow::on_action_snap_nearest_toggled(bool arg1)
{
    if(arg1){
        mode_nearest = 1;
    }
    if(!arg1){
        mode_nearest = 0;
    }
}


void MainWindow::on_action_snap_perpendicular_toggled(bool arg1)
{
    if(arg1){
        mode_perpendicular = 1;
    }
    if(!arg1){
        mode_perpendicular = 0;
    }
}

void MainWindow::on_action_snap_circlecenter_toggled(bool arg1)
{
    if(arg1){
        mode_centerpoint = 1;
    }
    if(!arg1){
        mode_centerpoint = 0;
    }
}

void MainWindow::on_action_snap_tangent_toggled(bool arg1)
{
    if(arg1){
        mode_tangent = 1;
    }
    if(!arg1){
        mode_tangent = 0;
    }
}

void MainWindow::on_action_ortho_toggled(bool arg1)
{
    if(arg1){
        mode_ortho = 1;
    }
    if(!arg1){
        mode_ortho = 0;
    }
}

void MainWindow::on_action_snap_4p_circle_toggled(bool arg1)
{
    if(arg1){
        mode_snap_circle_4p = 1;
    }
    if(!arg1){
        mode_snap_circle_4p  = 0;
    }
}

void MainWindow::on_action_view_cad_opengl_toggled(bool arg1)
{
    if(arg1){
        mode_cad = 1;
        mode_cam = 0;
        ui->action_view_cam_opengl->setChecked(0);
    }
}

void MainWindow::on_action_view_cam_opengl_toggled(bool arg1)
{
    if(arg1){
        //show cam side screen
        ui->dockWidget->show();
        ui->action_view_cad_opengl->setChecked(false);
    }
}

void MainWindow::on_toolButton_produce_gcode_clicked()
{
    mode_cad = 0;
    mode_cam = 1; //used for display opengl..
    ui->action_view_cad_opengl->setChecked(0);

    loop_times = 0;
    click = 0;
    select_click = 0;

    mode_arc = 0;
    mode_circle_2p = 0;
    mode_circle_3p = 0;
    mode_cubic_hermite_spline = 0;
    mode_ellipse = 0;
    mode_point = 0;
    mode_line = 0;
    mode_linestrip = 0;
    mode_polygon = 0;
    mode_cubic_bezier_curve = 0;
    mode_rectangular = 0;
    mode_text = 0;
    mode_text_edit = 0;
    mode_chamfer = 0;
    mode_copy = 0;
    mode_delete = 0;
    mode_extend = 0;
    mode_fillet = 0;
    mode_mirror = 0;
    mode_move = 0;
    mode_offset = 0;
    mode_rotate = 0;
    mode_scale = 0;
    mode_stretch = 0;
    mode_trim = 0;
    mode_dimension = 0;
    mode_contour_recognize = 0;
    mode_contour_offset = 1;
    mode_contour_autonest = 0;
    mode_print = 0;
    mode_match_properties = 0;

    gcode_startblock = ui->plainTextEdit_tool_start_block->toPlainText();
    gcode_offblock = ui->plainTextEdit_tool_off_block->toPlainText();
    gcode_intro = ui->plainTextEdit_gcode_intro->toPlainText();
    gcode_outtro = ui->plainTextEdit_gcode_outtro->toPlainText();
    travelheight = ui->lineEdit_travelheight->text().toDouble();
    leadin = ui->lineEdit_lead_in->text().toDouble();
}

void MainWindow::on_action_tools_triggered()
{
    Dialog_tools dialog2;
    dialog2.setModal(true);
    dialog2.exec();
}

void MainWindow::on_action_postprocessor_triggered()
{
    //Dialog_postprocessor dialog3;
    //dialog3.setModal(true);
    //dialog3.exec();
}

void MainWindow::on_action_axis_triggered()
{
    Dialog_axis dialog4;
    dialog4.setModal(true);
    dialog4.exec();
}

void MainWindow::on_toolButton_save_gcode_clicked()
{
    gcode_filename = ui->lineEdit_gcode_filename->text();
    g_code();
    //load_treewidget();
}

void MainWindow::load_treewidget()
{
    ui->treeWidget_cam->clear();

    QList<int> contour_nr;
    QList<int>::iterator it;

    //setup treewidget
    QStringList list { "contour" , "id"};
    ui->treeWidget_cam->setHeaderLabels(list);
    ui->treeWidget_cam->setColumnCount(2);

    //fill treewidget
    //for(int i=0; i<cam_counter; i++){

    //        if(((double_cam_array[i][56]==0 && double_cam_array[i][57]==0 && double_cam_array[i][58]==1) || (double_cam_array[i][56]==0.6 && double_cam_array[i][57]==0.6 && double_cam_array[i][58]==0.6)) && int_cam_array[i][0] != 0 ){ //color blue.. //color grey..  //no empty id's

    //            if(!contour_nr.contains(int_cam_array[i][14]) ){
    //                contour_nr.push_back(int_cam_array[i][14]);

    //                //parent
    //                QTreeWidgetItem * itm = new QTreeWidgetItem(ui->treeWidget_cam);
    //                itm->setText(0, "contour : ");
    //                itm->setText(1, QString::number(int_cam_array[i][14]));
    //                itm->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    //                ui->treeWidget_cam->addTopLevelItem(itm);

    //                //child
    //                if(int_cam_array[i][12]==1){ //cw
    //                    QTreeWidgetItem * child0 = new QTreeWidgetItem();
    //                    child0->setText(0, "cw");
    //                    itm->addChild(child0);
    //                }

    //                if(int_cam_array[i][13]==1){ //ccw
    //                    QTreeWidgetItem * child1 = new QTreeWidgetItem();
    //                    child1->setText(0, "ccw");
    //                    itm->addChild(child1);
    //                }
    //            }
    //        }
    //    }
    //contour_nr.clear();
    //qDebug()<< "load treewidget";


    QList<int> contourlist;
    QList<int> open_contour;
    for(int i = 0; i < cam_counter; i++){

        if(!contourlist.contains(int_cam_array[i][14]) && int_cam_array[i][0]!=0){ //no empty id..
            contourlist.append(int_cam_array[i][14]);

            //parent
            QTreeWidgetItem * itm = new QTreeWidgetItem(ui->treeWidget_cam);
            itm->setText(0, "contour : ");
            itm->setText(1, QString::number(int_cam_array[i][14]));
            itm->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
            ui->treeWidget_cam->addTopLevelItem(itm);
        }
    }
}

void MainWindow::on_treeWidget_cam_itemClicked(QTreeWidgetItem *item, int column)
{
    //qDebug()<< "clicked item : " << item->text(1).toInt();

    //try to highlight the treewidget selected contour..
    for(int i=0; i<cam_counter; i++){

        //qDebug()<< "cam counter search : " << i;

        if(int_cam_array[i][14]==item->text(1).toInt() && double_cam_array[i][56]==0 && double_cam_array[i][57]==0 & double_cam_array[i][58]==1){

            //qDebug()<< "item highlight";
            int_cam_array[i][4] = 1;
        } else {int_cam_array[i][4] = 0;}
    }
}

void MainWindow::on_action_edit_color_triggered()
{
    Dialog_color dialog;
    dialog.setModal(true);
    dialog.exec();
}

void MainWindow::on_action_edit_linetype_triggered()
{
    Dialog_linetype dialog;
    dialog.setModal(true);
    dialog.exec();
}

void MainWindow::on_action_linewidth_triggered()
{
    Dialog_linewidth dialog;
    dialog.setModal(true);
    dialog.exec();
}

void MainWindow::gcode_preview()
{
    ui->plainTextEdit_gcode_preview->clear();

    QFile file_in1(QDir::currentPath() + "/cadcam/" + "gcode_preview.txt");
    if(!file_in1.open(QIODevice::ReadOnly)) {
        qDebug() << "error reading file" << file_in1.errorString();
    }
    QTextStream in1(&file_in1);    // file to read

    while(!in1.atEnd()) {
        QString line = in1.readLine();

        ui->plainTextEdit_gcode_preview->appendPlainText(line);

    }
    file_in1.close();
}

void MainWindow::on_action_dimension_horizontal_triggered()
{
    dimension_type = "horizontal";

    click = 0;
    select_click = 0;

    mode_arc = 0;
    mode_circle_2p = 0;
    mode_circle_3p = 0;
    mode_cubic_hermite_spline = 0;
    mode_ellipse = 0;
    mode_point = 0;
    mode_line = 0;
    mode_linestrip = 0;
    mode_polygon = 0;
    mode_cubic_bezier_curve = 0;
    mode_rectangular = 0;
    mode_text = 0;
    mode_text_edit = 0;
    mode_chamfer = 0;
    mode_copy = 0;
    mode_delete = 0;
    mode_extend = 0;
    mode_fillet = 0;
    mode_mirror = 0;
    mode_move = 0;
    mode_offset = 0;
    mode_rotate = 0;
    mode_scale = 0;
    mode_stretch = 0;
    mode_trim = 0;
    mode_dimension = 1;
    mode_contour_recognize = 0;
    mode_contour_offset = 0;
    mode_contour_autonest = 0;
    mode_print = 0;
    mode_match_properties = 0;
}

void MainWindow::on_action_dimension_vertical_triggered()
{
    dimension_type = "vertical";

    click = 0;
    select_click = 0;

    mode_arc = 0;
    mode_circle_2p = 0;
    mode_circle_3p = 0;
    mode_cubic_hermite_spline = 0;
    mode_ellipse = 0;
    mode_point = 0;
    mode_line = 0;
    mode_linestrip = 0;
    mode_polygon = 0;
    mode_cubic_bezier_curve = 0;
    mode_rectangular = 0;
    mode_text = 0;
    mode_text_edit = 0;
    mode_chamfer = 0;
    mode_copy = 0;
    mode_delete = 0;
    mode_extend = 0;
    mode_fillet = 0;
    mode_mirror = 0;
    mode_move = 0;
    mode_offset = 0;
    mode_rotate = 0;
    mode_scale = 0;
    mode_stretch = 0;
    mode_trim = 0;
    mode_dimension = 1;
    mode_contour_recognize = 0;
    mode_contour_offset = 0;
    mode_contour_autonest = 0;
    mode_print = 0;
    mode_match_properties = 0;
}

void MainWindow::on_action_dimension_non_ortho_triggered()
{
    dimension_type = "non_ortho";

    click = 0;
    select_click = 0;

    mode_arc = 0;
    mode_circle_2p = 0;
    mode_circle_3p = 0;
    mode_cubic_hermite_spline = 0;
    mode_ellipse = 0;
    mode_point = 0;
    mode_line = 0;
    mode_linestrip = 0;
    mode_polygon = 0;
    mode_cubic_bezier_curve = 0;
    mode_rectangular = 0;
    mode_text = 0;
    mode_text_edit = 0;
    mode_chamfer = 0;
    mode_copy = 0;
    mode_delete = 0;
    mode_extend = 0;
    mode_fillet = 0;
    mode_mirror = 0;
    mode_move = 0;
    mode_offset = 0;
    mode_rotate = 0;
    mode_scale = 0;
    mode_stretch = 0;
    mode_trim = 0;
    mode_dimension = 1;
    mode_contour_recognize = 0;
    mode_contour_offset = 0;
    mode_contour_autonest = 0;
    mode_print = 0;
    mode_match_properties = 0;
}

void MainWindow::on_action_dimension_diameter_triggered()
{
    dimension_type = "diameter";

    click = 0;
    select_click = 0;

    mode_arc = 0;
    mode_circle_2p = 0;
    mode_circle_3p = 0;
    mode_cubic_hermite_spline = 0;
    mode_ellipse = 0;
    mode_point = 0;
    mode_line = 0;
    mode_linestrip = 0;
    mode_polygon = 0;
    mode_cubic_bezier_curve = 0;
    mode_rectangular = 0;
    mode_text = 0;
    mode_text_edit = 0;
    mode_chamfer = 0;
    mode_copy = 0;
    mode_delete = 0;
    mode_extend = 0;
    mode_fillet = 0;
    mode_mirror = 0;
    mode_move = 0;
    mode_offset = 0;
    mode_rotate = 0;
    mode_scale = 0;
    mode_stretch = 0;
    mode_trim = 0;
    mode_dimension = 1;
    mode_contour_recognize = 0;
    mode_contour_offset = 0;
    mode_contour_autonest = 0;
    mode_print = 0;
    mode_match_properties = 0;
}

void MainWindow::on_action_dimenstion_radius_triggered()
{
    dimension_type = "radius";

    click = 0;
    select_click = 0;

    mode_arc = 0;
    mode_circle_2p = 0;
    mode_circle_3p = 0;
    mode_cubic_hermite_spline = 0;
    mode_ellipse = 0;
    mode_point = 0;
    mode_line = 0;
    mode_linestrip = 0;
    mode_polygon = 0;
    mode_cubic_bezier_curve = 0;
    mode_rectangular = 0;
    mode_text = 0;
    mode_text_edit = 0;
    mode_chamfer = 0;
    mode_copy = 0;
    mode_delete = 0;
    mode_extend = 0;
    mode_fillet = 0;
    mode_mirror = 0;
    mode_move = 0;
    mode_offset = 0;
    mode_rotate = 0;
    mode_scale = 0;
    mode_stretch = 0;
    mode_trim = 0;
    mode_dimension = 1;
    mode_contour_recognize = 0;
    mode_contour_offset = 0;
    mode_contour_autonest = 0;
    mode_print = 0;
    mode_match_properties = 0;
}

void MainWindow::on_action_dimension_angle_2p_triggered()
{
    dimension_type = "angle_2p";

    click = 0;
    select_click = 0;

    mode_arc = 0;
    mode_circle_2p = 0;
    mode_circle_3p = 0;
    mode_cubic_hermite_spline = 0;
    mode_ellipse = 0;
    mode_point = 0;
    mode_line = 0;
    mode_linestrip = 0;
    mode_polygon = 0;
    mode_cubic_bezier_curve = 0;
    mode_rectangular = 0;
    mode_text = 0;
    mode_text_edit = 0;
    mode_chamfer = 0;
    mode_copy = 0;
    mode_delete = 0;
    mode_extend = 0;
    mode_fillet = 0;
    mode_mirror = 0;
    mode_move = 0;
    mode_offset = 0;
    mode_rotate = 0;
    mode_scale = 0;
    mode_stretch = 0;
    mode_trim = 0;
    mode_dimension = 1;
    mode_contour_recognize = 0;
    mode_contour_offset = 0;
    mode_contour_autonest = 0;
    mode_print = 0;
    mode_match_properties = 0;
}

void MainWindow::on_action_dimension_angle_3p_triggered()
{
    dimension_type = "angle_3p";

    click = 0;
    select_click = 0;

    mode_arc = 0;
    mode_circle_2p = 0;
    mode_circle_3p = 0;
    mode_cubic_hermite_spline = 0;
    mode_ellipse = 0;
    mode_point = 0;
    mode_line = 0;
    mode_linestrip = 0;
    mode_polygon = 0;
    mode_cubic_bezier_curve = 0;
    mode_rectangular = 0;
    mode_text = 0;
    mode_text_edit = 0;
    mode_chamfer = 0;
    mode_copy = 0;
    mode_delete = 0;
    mode_extend = 0;
    mode_fillet = 0;
    mode_mirror = 0;
    mode_move = 0;
    mode_offset = 0;
    mode_rotate = 0;
    mode_scale = 0;
    mode_stretch = 0;
    mode_trim = 0;
    mode_dimension = 1;
    mode_contour_recognize = 0;
    mode_contour_offset = 0;
    mode_contour_autonest = 0;
    mode_print = 0;
    mode_match_properties = 0;
}

void MainWindow::on_action_print_pdf_triggered()
{
    click = 0;
    select_click = 0;

    mode_arc = 0;
    mode_circle_2p = 0;
    mode_circle_3p = 0;
    mode_cubic_hermite_spline = 0;
    mode_ellipse = 0;
    mode_point = 0;
    mode_line = 0;
    mode_linestrip = 0;
    mode_polygon = 0;
    mode_cubic_bezier_curve = 0;
    mode_rectangular = 0;
    mode_text = 0;
    mode_text_edit = 0;
    mode_chamfer = 0;
    mode_copy = 0;
    mode_delete = 0;
    mode_extend = 0;
    mode_fillet = 0;
    mode_mirror = 0;
    mode_move = 0;
    mode_offset = 0;
    mode_rotate = 0;
    mode_scale = 0;
    mode_stretch = 0;
    mode_trim = 0;
    mode_dimension = 0;
    mode_contour_recognize = 0;
    mode_contour_offset = 0;
    mode_contour_autonest = 0;
    mode_print = 1;
    mode_match_properties = 0;
    mode_background_white = 1;
    ui->action_background_color->setChecked(1);

    //    QPrinter printer(QPrinter::HighResolution); //https://stackoverflow.com/questions/45467942/how-can-i-print-a-qwidget-in-qt
    //    printer.setOutputFormat(QPrinter::PdfFormat);

    //    printer.setOutputFileName(QDir::currentPath() + "/" + "test.pdf");
    //    printer.setPageMargins(12, 16, 12, 20, QPrinter::Millimeter);
    //    printer.setPaperSize(QSizeF(297, 210), QPrinter::Millimeter);   //a4 210x297 //a1 594x841
    //    printer.setFullPage(false);

    //    QPainter painter(&printer);

    //    double xscale = printer.pageRect().width() / double(ui->openGLWidget->width());
    //    double yscale = printer.pageRect().height() / double(ui->openGLWidget->height());
    //    double scale = qMin(xscale, yscale);
    //    painter.translate(printer.paperRect().center());
    //    painter.scale(scale, scale);
    //    painter.translate(-ui->openGLWidget->width()/ 2, -ui->openGLWidget->height()/ 2);
    //    ui->openGLWidget->render(&painter);
}

void MainWindow::on_action_background_color_toggled(bool arg1)
{
    if(arg1){
        mode_background_white = 1;
    } else {mode_background_white = 0;}
}

void MainWindow::on_action_text_edit_triggered()
{
    click = 0;
    select_click = 0;

    mode_arc = 0;
    mode_circle_2p = 0;
    mode_circle_3p = 0;
    mode_cubic_hermite_spline = 0;
    mode_ellipse = 0;
    mode_point = 0;
    mode_line = 0;
    mode_linestrip = 0;
    mode_polygon = 0;
    mode_cubic_bezier_curve = 0;
    mode_rectangular = 0;
    mode_text = 0;
    mode_text_edit = 1;
    mode_chamfer = 0;
    mode_copy = 0;
    mode_delete = 0;
    mode_extend = 0;
    mode_fillet = 0;
    mode_mirror = 0;
    mode_move = 0;
    mode_offset = 0;
    mode_rotate = 0;
    mode_scale = 0;
    mode_stretch = 0;
    mode_trim = 0;
    mode_dimension = 0;
    mode_contour_recognize = 0;
    mode_contour_offset = 0;
    mode_contour_autonest = 0;
    mode_print = 0;
    mode_match_properties = 0;
}

void MainWindow::on_action_dimension_edit_triggered()
{
    messagebox_text = "<b><i>mode dimension format</i></b>";
    Dialog_dimension_edit().exec();
}

void MainWindow::on_toolButton_clear_gcode_clicked()
{
    ui->treeWidget_cam->clear();
    ui->plainTextEdit_gcode_preview->clear();
    //clean cam
    empty_triangle_array();
    empty_cam_array();

    contournumbers.clear();
    object_list.clear();
    master.clear();
    slave.clear();
    inside.clear();
    templist.clear();
    templist1.clear();
    solid_outside.clear();
    solid_inside.clear();

    mode_cad = 1;
    mode_cam = 0;

    for(int i=0; i<cad_counter; i++){
        if(int_cad_array[i][26] == 1){
            (emtpy_current_cad_counter(i));
        }
    }

    purge_array();
}

void MainWindow::on_action_grid_toggled(bool arg1)
{
    if(arg1){
        mode_grid = 1;
    } else {mode_grid = 0;}
}

void MainWindow::on_action_point_triggered()
{
    click = 0;
    select_click = 0;

    mode_arc = 0;
    mode_circle_2p = 0;
    mode_circle_3p = 0;
    mode_cubic_hermite_spline = 0;
    mode_ellipse = 0;
    mode_point = 1;
    mode_line = 0;
    mode_linestrip = 0;
    mode_polygon = 0;
    mode_cubic_bezier_curve = 0;
    mode_rectangular = 0;
    mode_text = 0;
    mode_text_edit = 0;
    mode_chamfer = 0;
    mode_copy = 0;
    mode_delete = 0;
    mode_extend = 0;
    mode_fillet = 0;
    mode_mirror = 0;
    mode_move = 0;
    mode_offset = 0;
    mode_rotate = 0;
    mode_scale = 0;
    mode_stretch = 0;
    mode_trim = 0;
    mode_dimension = 0;
    mode_contour_recognize = 0;
    mode_contour_offset = 0;
    mode_contour_autonest = 0;
    mode_print = 0;
    mode_match_properties = 0;
}

void MainWindow::on_action_match_properties_triggered()
{
    click = 0;
    select_click = 0;

    mode_arc = 0;
    mode_circle_2p = 0;
    mode_circle_3p = 0;
    mode_cubic_hermite_spline = 0;
    mode_ellipse = 0;
    mode_point = 0;
    mode_line = 0;
    mode_linestrip = 0;
    mode_polygon = 0;
    mode_cubic_bezier_curve = 0;
    mode_rectangular = 0;
    mode_text = 0;
    mode_text_edit = 0;
    mode_chamfer = 0;
    mode_copy = 0;
    mode_delete = 0;
    mode_extend = 0;
    mode_fillet = 0;
    mode_mirror = 0;
    mode_move = 0;
    mode_offset = 0;
    mode_rotate = 0;
    mode_scale = 0;
    mode_stretch = 0;
    mode_trim = 0;
    mode_dimension = 0;
    mode_contour_recognize = 0;
    mode_contour_offset = 0;
    mode_contour_autonest = 0;
    mode_print = 0;
    mode_match_properties = 1;
}
