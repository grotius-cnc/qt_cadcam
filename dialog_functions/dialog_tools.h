#ifndef DIALOG_TOOLS_H
#define DIALOG_TOOLS_H

#include <QDialog>
#include <QTreeWidget>

namespace Ui {
class Dialog_tools;
}

class Dialog_tools : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_tools(QWidget *parent = nullptr);
    ~Dialog_tools();

    Ui::Dialog_tools *ui;

     void load_table();
     void save_table();
     void load_selected_data();

private slots:

    void on_pushButton_delete_clicked();

    void on_pushButton_new_clicked();

    void on_pushButton_load_clicked();

    void on_pushButton_save_clicked();

    void on_pushButton_insert_clicked();

    void on_toolButton_move_up_clicked();

    void on_toolButton_move_down_clicked();

    void on_pushButton_save_and_close_clicked();

private:

};

#endif // DIALOG_TOOLS_H
