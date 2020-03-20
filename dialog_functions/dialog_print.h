#ifndef DIALOG_PRINT_H
#define DIALOG_PRINT_H

#include <QDialog>
#include <mainwindow.h>

namespace Ui {
class Dialog_print;
}

class Dialog_print : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_print(QWidget *parent = nullptr);
    ~Dialog_print();

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
    void on_comboBox_currentIndexChanged(int index);
    void on_comboBox_file_extension_currentIndexChanged(int index);

private:
    Ui::Dialog_print *ui;
};

#endif // DIALOG_PRINT_H
