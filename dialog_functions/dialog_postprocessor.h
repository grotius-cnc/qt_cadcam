#ifndef DIALOG_POSTPROCESSOR_H
#define DIALOG_POSTPROCESSOR_H

#include <QDialog>

namespace Ui {
class Dialog_postprocessor;
}

class Dialog_postprocessor : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_postprocessor(QWidget *parent = nullptr);
    ~Dialog_postprocessor();

    void save_table();
    void load_table();
    void load_selected_data();

private slots:
    void on_pushButton_new_clicked();

    void on_pushButton_insert_new_clicked();

    void on_toolButton_move_up_clicked();

    void on_toolButton_move_down_clicked();

    void on_pushButton_delete_clicked();

    void on_pushButton_save_and_close_clicked();

    void on_pushButton_load_clicked();

    void on_pushButton_save_clicked();

private:
    Ui::Dialog_postprocessor *ui;
};

#endif // DIALOG_POSTPROCESSOR_H
