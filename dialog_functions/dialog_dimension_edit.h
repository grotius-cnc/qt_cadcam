#ifndef DIALOG_DIMENSION_EDIT_H
#define DIALOG_DIMENSION_EDIT_H

#include <QDialog>

namespace Ui {
class Dialog_dimension_edit;
}

class Dialog_dimension_edit : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_dimension_edit(QWidget *parent = nullptr);
    ~Dialog_dimension_edit();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::Dialog_dimension_edit *ui;
};

#endif // DIALOG_DIMENSION_EDIT_H
