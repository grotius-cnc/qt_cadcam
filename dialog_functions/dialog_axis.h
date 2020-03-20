#ifndef DIALOG_AXIS_H
#define DIALOG_AXIS_H

#include <QDialog>

namespace Ui {
class Dialog_axis;
}

class Dialog_axis : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_axis(QWidget *parent = nullptr);
    ~Dialog_axis();

    void load_table();
    void save_table();
    void load_table2();
    void save_table2();
    void load_selected_data();
    void load_selected_data2();

private slots:
    void on_pushButton_new_clicked();

    void on_pushButton_insert_new_clicked();

    void on_pushButton_delete_clicked();

    void on_pushButton_load_clicked();

    void on_pushButton_save_clicked();

    void on_toolButton_move_up_clicked();

    void on_toolButton_move_down_clicked();

    void on_pushButton_new_2_clicked();

    void on_pushButton_insert_new_2_clicked();

    void on_pushButton_delete_2_clicked();

    void on_pushButton_load_2_clicked();

    void on_pushButton_save_2_clicked();

    void on_toolButton_move_up_2_clicked();

    void on_toolButton_move_down_2_clicked();

    void on_pushButton_save_and_close_clicked();

private:
    Ui::Dialog_axis *ui;
};

#endif // DIALOG_AXIS_H
