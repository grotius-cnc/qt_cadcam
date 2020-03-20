#ifndef DIALOG_FILE_H
#define DIALOG_FILE_H

#include <QDialog>
#include <QFileSystemModel>

extern QString sPath;

namespace Ui {
class Dialog_file;
}

class Dialog_file : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_file(QWidget *parent = nullptr);
    ~Dialog_file();

private slots:
    void on_dirview_clicked(const QModelIndex &index);

    void on_fileview_clicked(const QModelIndex &index);

    void on_buttonBox_open_accepted();

    void on_buttonBox_save_accepted();

private:
    Ui::Dialog_file *ui;
    QFileSystemModel *dirmodel;
    QFileSystemModel *filemodel;
};

#endif // DIALOG_FILE_H
