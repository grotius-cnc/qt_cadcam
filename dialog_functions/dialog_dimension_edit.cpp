#include "dialog_dimension_edit.h"
#include "ui_dialog_dimension_edit.h"
#include <core_functions/variables.h>

Dialog_dimension_edit::Dialog_dimension_edit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_dimension_edit)
{
    ui->setupUi(this);
}

Dialog_dimension_edit::~Dialog_dimension_edit()
{
    delete ui;
}

void Dialog_dimension_edit::on_buttonBox_accepted()
{
    arrow_lenght = ui->lineEdit_arrow_lenght->text().toDouble();
    arrow_height = ui->lineEdit_arrow_height->text().toDouble();
    dimension_text_height = ui->lineEdit_dimension_text_height->text().toDouble();
    close();
}

void Dialog_dimension_edit::on_buttonBox_rejected()
{
    close();
}

