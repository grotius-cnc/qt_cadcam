#include "dialog_print.h"
#include "ui_dialog_print.h"
#include <QPrinter>
#include <QDir>
#include <QPainter>
#include <mainwindow.h>
#include <core_functions/variables.h>

Dialog_print::Dialog_print(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_print)
{
    ui->setupUi(this);

    ui->lineEdit_x_start->setText(QString::number(print_x0));
    ui->lineEdit_y_start->setText(QString::number(print_y0));
    ui->lineEdit_x_end->setText(QString::number(print_x1));
    ui->lineEdit_y_end->setText(QString::number(print_y1));

    ui->lineEdit_papersize_width->setText(QString("841"));
    ui->lineEdit_papersize_height->setText(QString("1189"));
}

Dialog_print::~Dialog_print()
{
    delete ui;
}

void Dialog_print::on_buttonBox_accepted()
{
    print_x0=ui->lineEdit_x_start->text().toInt();
    print_y0=ui->lineEdit_y_start->text().toInt();
    print_x1=ui->lineEdit_x_end->text().toInt();
    print_y1=ui->lineEdit_y_end->text().toInt();

    filename_out = ui->lineEdit_filename_out->text();

    if(ui->comboBox_file_extension->currentIndex()==0){
        file_type = "pdf";
        qDebug()<< "file extension : " << file_type;
    } else if(ui->comboBox_file_extension->currentIndex()==1){
        file_type = "png";
        qDebug()<< "file extension : " << file_type;
    }

    margin_top = ui->lineEdit_margin_top->text().toInt();
    margin_bottom = ui->lineEdit_margin_bottom->text().toInt();
    margin_left = ui->lineEdit_margin_left->text().toInt();
    margin_right = ui->lineEdit_margin_right->text().toInt();

    print_now = 1; //activates printer in mainwindow.. it has another timer thread..
    mode_print = 0;
    close();
}

void Dialog_print::on_buttonBox_rejected()
{
    mode_print = 0;
    close();
}

void Dialog_print::on_comboBox_currentIndexChanged(int index)
{
    papersize.clear();
    if(index == 0){ //A0S
        ui->lineEdit_papersize_width->setText(QString("841"));
        ui->lineEdit_papersize_height->setText(QString("1189"));
        papersize.append(ui->lineEdit_papersize_width->text().toInt());
        papersize.append(ui->lineEdit_papersize_height->text().toInt());
    }
    if(index == 1){ //A0L
        ui->lineEdit_papersize_width->setText(QString("1189"));
        ui->lineEdit_papersize_height->setText(QString("841"));
        papersize.append(ui->lineEdit_papersize_width->text().toInt());
        papersize.append(ui->lineEdit_papersize_height->text().toInt());
    }

    if(index == 2){ //A1S
        ui->lineEdit_papersize_width->setText(QString("594"));
        ui->lineEdit_papersize_height->setText(QString("841"));
        papersize.append(ui->lineEdit_papersize_width->text().toInt());
        papersize.append(ui->lineEdit_papersize_height->text().toInt());
    }
    if(index == 3){ //A1L
        ui->lineEdit_papersize_width->setText(QString("841"));
        ui->lineEdit_papersize_height->setText(QString("594"));
        papersize.append(ui->lineEdit_papersize_width->text().toInt());
        papersize.append(ui->lineEdit_papersize_height->text().toInt());
    }

    if(index == 4){ //A2S
        ui->lineEdit_papersize_width->setText(QString("420"));
        ui->lineEdit_papersize_height->setText(QString("594"));
        papersize.append(ui->lineEdit_papersize_width->text().toInt());
        papersize.append(ui->lineEdit_papersize_height->text().toInt());
    }
    if(index == 5){ //A2L
        ui->lineEdit_papersize_width->setText(QString("594"));
        ui->lineEdit_papersize_height->setText(QString("420"));
        papersize.append(ui->lineEdit_papersize_width->text().toInt());
        papersize.append(ui->lineEdit_papersize_height->text().toInt());
    }

    if(index == 6){ //A3S
        ui->lineEdit_papersize_width->setText(QString("297"));
        ui->lineEdit_papersize_height->setText(QString("420"));
        papersize.append(ui->lineEdit_papersize_width->text().toInt());
        papersize.append(ui->lineEdit_papersize_height->text().toInt());
    }
    if(index == 7){ //A3L
        ui->lineEdit_papersize_width->setText(QString("420"));
        ui->lineEdit_papersize_height->setText(QString("297"));
        papersize.append(ui->lineEdit_papersize_width->text().toInt());
        papersize.append(ui->lineEdit_papersize_height->text().toInt());
    }

    if(index == 8){ //A4S
        ui->lineEdit_papersize_width->setText(QString("210"));
        ui->lineEdit_papersize_height->setText(QString("297"));
        papersize.append(ui->lineEdit_papersize_width->text().toInt());
        papersize.append(ui->lineEdit_papersize_height->text().toInt());
    }
    if(index == 9){ //A4L
        ui->lineEdit_papersize_width->setText(QString("297"));
        ui->lineEdit_papersize_height->setText(QString("210"));
        papersize.append(ui->lineEdit_papersize_width->text().toInt());
        papersize.append(ui->lineEdit_papersize_height->text().toInt());
    }

    if(index == 10){ //A5S
        ui->lineEdit_papersize_width->setText(QString("148"));
        ui->lineEdit_papersize_height->setText(QString("210"));
        papersize.append(ui->lineEdit_papersize_width->text().toInt());
        papersize.append(ui->lineEdit_papersize_height->text().toInt());
    }
    if(index == 11){ //A5L
        ui->lineEdit_papersize_width->setText(QString("210"));
        ui->lineEdit_papersize_height->setText(QString("148"));
        papersize.append(ui->lineEdit_papersize_width->text().toInt());
        papersize.append(ui->lineEdit_papersize_height->text().toInt());
    }

    if(index == 12){ //A6S
        ui->lineEdit_papersize_width->setText(QString("105"));
        ui->lineEdit_papersize_height->setText(QString("148"));
        papersize.append(ui->lineEdit_papersize_width->text().toInt());
        papersize.append(ui->lineEdit_papersize_height->text().toInt());
    }
    if(index == 13){ //A6L
        ui->lineEdit_papersize_width->setText(QString("148"));
        ui->lineEdit_papersize_height->setText(QString("105"));
        papersize.append(ui->lineEdit_papersize_width->text().toInt());
        papersize.append(ui->lineEdit_papersize_height->text().toInt());
    }
}

void Dialog_print::on_comboBox_file_extension_currentIndexChanged(int index)
{
    if(index == 0){
        file_type = "pdf";
        qDebug()<< "file extension : " << file_type;
    }
    if(index == 1){
        file_type = "png";
        qDebug()<< "file extension : " << file_type;
    }
}
