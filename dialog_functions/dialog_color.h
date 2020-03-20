#ifndef DIALOG_COLOR_H
#define DIALOG_COLOR_H

#include <QDialog>
#include <mainwindow.h>
#include <ui_mainwindow.h>
#include <QList>

namespace Ui {
class Dialog_color;
}

class Dialog_color : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_color(QWidget *parent = nullptr);
    ~Dialog_color();

    void save_table();
    void load_table();
    void extern_toolbar_load();

private slots:

    void on_pushButton_new_clicked();

    void on_pushButton_insert_new_clicked();

    void on_pushButton_save_clicked();

    void on_pushButton_load_clicked();

    void on_pushButton_delete_clicked();

    void on_toolButton_move_up_clicked();

    void on_toolButton_move_down_clicked();

    void on_toolButton_color_window_clicked();

    void on_toolButton_save_and_close_clicked();

    void on_lineEdit_r_returnPressed();

    void on_lineEdit_g_returnPressed();

    void on_lineEdit_b_returnPressed();

    void on_lineEdit_a_returnPressed();

    void on_toolButton_clicked();

private:
    Ui::Dialog_color *ui;

    QComboBox *test = new QComboBox;

    void update_colors();
    void timerEvent(QTimerEvent *);
    int timerid;


};

#endif // DIALOG_COLOR_H
