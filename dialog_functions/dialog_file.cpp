#include "dialog_file.h"
#include "ui_dialog_file.h"
#include <core_functions/variables.h>
#include <file_functions/write_line.h>
#include <file_functions/write_circle.h>
#include <file_functions/write_arc.h>
#include <file_functions/read_line.h>
#include <file_functions/read_circle.h>
#include <file_functions/read_arc.h>
#include <file_functions/read_spline.h>
#include <interface_functions/zoom_extends.h>

QString sPath;

Dialog_file::Dialog_file(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_file)
{
    ui->setupUi(this);

    //setup the header file first..
    QString sPath = "C:/";
    dirmodel = new QFileSystemModel(this);
    dirmodel->setRootPath(sPath);
    dirmodel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    ui->dirview->setModel(dirmodel);
    ui->dirview->hideColumn(1);
    ui->dirview->hideColumn(2);
    ui->dirview->hideColumn(3);

    filemodel = new QFileSystemModel(this);
    filemodel->setFilter(QDir::NoDotAndDotDot | QDir::Files);
    ui->fileview->setModel(filemodel);
    ui->fileview->setColumnWidth(0,500);
    //ui->fileview->hideColumn(1);
    //ui->fileview->hideColumn(2);
    //ui->fileview->hideColumn(3);


}

Dialog_file::~Dialog_file()
{
    delete ui;
}

void Dialog_file::on_dirview_clicked(const QModelIndex &index)
{
    //https://www.youtube.com/watch?v=92biLZST6Vg
    sPath = dirmodel->fileInfo(index).absoluteFilePath();
    ui->fileview->setRootIndex(filemodel->setRootPath(sPath));
}

void Dialog_file::on_fileview_clicked(const QModelIndex &index)
{
    sPath = filemodel->fileInfo(index).absoluteFilePath();
    ui->lineEdit->setText(sPath);
}

void Dialog_file::on_buttonBox_open_accepted()
{
    filename_in = ui->lineEdit->text();
    read_line();
    read_circle();
    read_arc();
    //read_spline();
    close();

    //calculate line midpoints for the whole imported array..
    for(int i=0 ; i < cad_counter ; i++) {

       double_cad_array[i][15] = (double_cad_array[i][0] + double_cad_array[i][3])/2;
       double_cad_array[i][16] = (double_cad_array[i][1] + double_cad_array[i][4])/2;
       double_cad_array[i][17] = (double_cad_array[i][2] + double_cad_array[i][5])/2;
    }

    zoom_extends();
}

void Dialog_file::on_buttonBox_save_accepted()
{
    filename_out = sPath + "/" + ui->lineEdit->text();
    qDebug() << "filename out.. : " << filename_out;
    write_line();
    write_circle();
    write_arc();
    Dialog_file::close();
}
