#ifndef DIALOG_LINEWIDTH_H
#define DIALOG_LINEWIDTH_H

#include <QDialog>

namespace Ui {
class Dialog_linewidth;
}

class Dialog_linewidth : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_linewidth(QWidget *parent = nullptr);
    ~Dialog_linewidth();

    void save_table();
    void load_table();
    void extern_toolbar_load();

private slots:
    void on_pushButton_new_clicked();

    void on_pushButton_save_clicked();

    void on_pushButton_load_clicked();

    void on_pushButton_insert_new_clicked();

    void on_toolButton_move_up_clicked();

    void on_toolButton_move_down_clicked();

    void on_toolButton_save_and_close_clicked();

    void on_pushButton_delete_clicked();

private:
    Ui::Dialog_linewidth *ui;
};

#endif // DIALOG_LINEWIDTH_H
