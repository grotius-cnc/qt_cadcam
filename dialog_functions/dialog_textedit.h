#ifndef DIALOG_TEXTEDIT_H
#define DIALOG_TEXTEDIT_H

#include <QDialog>

namespace Ui {
class Dialog_textedit;
}

class Dialog_textedit : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_textedit(QWidget *parent = nullptr);
    ~Dialog_textedit();

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

public slots:


private:
    Ui::Dialog_textedit *ui;
};

#endif // DIALOG_TEXTEDIT_H
