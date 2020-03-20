#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QSpinBox>
#include <QComboBox>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QStringList>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void load_treewidget();
    //test..
    QComboBox *colors = new QComboBox;
    QComboBox *layer = new QComboBox;
    QComboBox *linetype = new QComboBox;
    QComboBox *linewidth = new QComboBox;

    QComboBox *contour = new QComboBox;
    QTreeWidget *tree = new QTreeWidget(contour);

private slots:

    void on_action_view_3d_toggled(bool arg1);

    void on_action_view_top_toggled(bool arg1);

    void on_action_line_triggered();

    void on_action_delete_triggered();

    void on_action_move_triggered();

    void on_action_copy_triggered();

    void on_action_rotate_triggered();

    void on_action_mirror_triggered();

    void on_action_scale_triggered();

    void on_action_stretch_triggered();

    void on_action_offset_triggered();

    void on_action_undo_triggered();

    void on_action_extend_triggered();

    void on_action_trim_triggered();

    void on_action_arc_triggered();

    void on_action_open_file_triggered();

    void on_action_save_as_triggered();

    void on_action_debug_triggered();

    void on_action_new_file_triggered();

    void on_action_zoom_extend_triggered();

    void on_action_zoom_window_triggered();

    void on_action_zoom_plus_triggered();

    void on_action_zoom_min_triggered();

    void on_action_2p_circle_triggered();

    void on_action_3p_circle_triggered();

    void on_action_rectangular_triggered();

    void on_action_linestrip_triggered();

    void on_action_ellipse_triggered();

    void on_action_polygon_triggered();

    void on_action_spline_triggered();

    void on_action_cubic_bezier_curve_triggered();

    void on_action_chamfer_triggered();

    void on_action_fillet_triggered();

    void on_lineEdit_insertbox_returnPressed();

    void on_action_text_triggered();

    void on_lineEdit_insertbox_textChanged(const QString &arg1);

    void on_action_snap_endpoint_toggled(bool arg1);

    void on_action_snap_midpoint_toggled(bool arg1);

    void on_action_snap_perpendicular_toggled(bool arg1);

    void on_action_snap_nearest_toggled(bool arg1);

    void on_action_snap_circlecenter_toggled(bool arg1);

    void on_action_snap_tangent_toggled(bool arg1);

    void on_action_snap_4p_circle_toggled(bool arg1);

    void on_action_ortho_toggled(bool arg1);

    void on_action_view_cad_opengl_toggled(bool arg1);

    void on_action_view_cam_opengl_toggled(bool arg1);

    void on_action_tools_triggered();

    void on_action_postprocessor_triggered();

    void on_action_axis_triggered();

    void on_toolButton_save_gcode_clicked();

    void on_treeWidget_cam_itemClicked(QTreeWidgetItem *item, int column);

    void on_action_edit_color_triggered();

    void on_action_edit_linetype_triggered();

    void on_action_linewidth_triggered();

    void on_action_dimension_horizontal_triggered();

    void on_action_dimension_vertical_triggered();

    void on_action_dimension_non_ortho_triggered();

    void on_action_dimension_diameter_triggered();

    void on_action_dimenstion_radius_triggered();

    void on_action_dimension_angle_2p_triggered();

    void on_action_dimension_angle_3p_triggered();

    void on_action_print_pdf_triggered();

    void on_action_background_color_toggled(bool arg1);

    void on_action_text_edit_triggered();

    void on_action_dimension_edit_triggered();

    void on_action_snap_intersection_toggled(bool arg1);

    void on_toolButton_produce_gcode_clicked();

    void on_toolButton_clear_gcode_clicked();



    void on_action_grid_toggled(bool arg1);

    void on_action_point_triggered();

    void on_action_match_properties_triggered();

public slots:

protected:

    void timerEvent(QTimerEvent *);
    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);

    //toolbar text..
    QLineEdit *textheight_LineEdit = new QLineEdit;
    QComboBox *textfonts_ComboBox = new QComboBox;

    //toolbar linetype..
    QLineEdit *linetype_scale = new QLineEdit;

    //grid..
    QLineEdit *LineEdit_gridsize = new QLineEdit;
    QLineEdit *LineEdit_gridspace = new QLineEdit;

    void gcode_preview();


private:
    Ui::MainWindow *ui;
    int timerId;


};

#endif // MAINWINDOW_H
