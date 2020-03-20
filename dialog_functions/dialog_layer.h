#ifndef DIALOG_LAYER_H
#define DIALOG_LAYER_H

#include <QDialog>

namespace Ui {
class Dialog_layer;
}

class Dialog_layer : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_layer(QWidget *parent = nullptr);
    ~Dialog_layer();

private slots:

    void on_pushButton_new_5_clicked();

private:
    Ui::Dialog_layer *ui;
};

#endif // DIALOG_LAYER_H
