#include "dialog_textedit.h"
#include "ui_dialog_textedit.h"
#include <core_functions/variables.h>

Dialog_textedit::Dialog_textedit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_textedit)
{
    ui->setupUi(this);

    if(mode_text_edit){
        text_edit_string.replace("new_line","\n");
        ui->plainTextEdit->setPlainText(text_edit_string);
    }
}

Dialog_textedit::~Dialog_textedit()
{
    delete ui;
}

void Dialog_textedit::on_buttonBox_accepted()
{
    if(mode_text_edit){

        //write new text to selected array item..
        for(int i = 0; i < cad_counter; i++){
            if(int_cad_array[i][3] == 1){ //select
                QString string = ui->plainTextEdit->toPlainText();
                string.replace("\n","new_line");
                string_cad_array[i][0] = string;

            }
        }
    } else {
        text_edit_string = ui->plainTextEdit->toPlainText();
    }
    close();
}

void Dialog_textedit::on_buttonBox_rejected()
{
    close();
}

