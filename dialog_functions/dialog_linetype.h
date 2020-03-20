#ifndef DIALOG_LINETYPE_H
#define DIALOG_LINETYPE_H

#include <QDialog>

namespace Ui {
class Dialog_linetype;
}

class Dialog_linetype : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_linetype(QWidget *parent = nullptr);
    ~Dialog_linetype();

    int binaryToDecimal(long n);
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

    void on_toolButton_save_and_close_clicked();

private:
    Ui::Dialog_linetype *ui;
};

#endif // DIALOG_LINETYPE_H
