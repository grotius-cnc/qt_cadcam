#include "dialog_linetype.h"
#include "ui_dialog_linetype.h"
#include <qdebug.h>
#include <core_functions/variables.h>
#include <math.h>

//    The line stipple pattern is just a 16-bit integer. So to get 6 dots followed by a short line, the pattern in binary could look like this:
//    0101010101010111
//    Splitting this into 4-bit groups gives:
//    0101 0101 0101 0111
//    And then converting each group to its hex digit:
//    0x5557
//    Which gives us the following call:
//    glLineStipple(1, 0x5557);

Dialog_linetype::Dialog_linetype(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_linetype)
{
    ui->setupUi(this);
    ui->tableWidget->setAlternatingRowColors(true);
    ui->tableWidget->setColumnWidth(1,200);

    load_table();
}

Dialog_linetype::~Dialog_linetype()
{
    delete ui;
}

int Dialog_linetype::binaryToDecimal(long n)
{
    //linetype_binary_to_dec = binaryToDecimal(ui->lineEdit->text().toLong());
    long num = n;
    int dec_value = 0;

    // Initializing base value to 1, i.e 2^0
    int base = 1;

    long temp = num;
    while (temp) {
        int last_digit = temp % 10;
        temp = temp / 10;

        dec_value += last_digit * base;

        base = base * 2;
    }

    return dec_value;
}

void Dialog_linetype::extern_toolbar_load()
{
    linetype_scale_list.clear();
    linetype_pattern_list.clear();
    linetype_comment_list.clear();

    for(int i=0; i<ui->tableWidget->rowCount(); i++){

        linetype_scale_list.append(ui->tableWidget->item(i,0)->text().toDouble());
        linetype_pattern_list.append(ui->tableWidget->item(i,1)->text());
        linetype_comment_list.append(ui->tableWidget->item(i,2)->text());
    }
}

void Dialog_linetype::on_pushButton_new_clicked()
{
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    ui->tableWidget->model()->setData(ui->tableWidget->model()->index(ui->tableWidget->rowCount()-1,0),0.0);      //scale
    ui->tableWidget->model()->setData(ui->tableWidget->model()->index(ui->tableWidget->rowCount()-1,1),"");        //pattern
    ui->tableWidget->model()->setData(ui->tableWidget->model()->index(ui->tableWidget->rowCount()-1,2),"");       //comment
}

void Dialog_linetype::on_pushButton_insert_new_clicked()
{
    QModelIndexList selection = ui->tableWidget->selectionModel()->selectedIndexes();
    for(int i=0; i< selection.count(); i++)
    {
        QModelIndex index = selection.at(i);
        //qDebug() << index.row();
        ui->tableWidget->insertRow(index.row());

        ui->tableWidget->model()->setData(ui->tableWidget->model()->index(index.row(),0),0.0);   //scale
        ui->tableWidget->model()->setData(ui->tableWidget->model()->index(index.row(),1),"");    //pattern
        ui->tableWidget->model()->setData(ui->tableWidget->model()->index(index.row(),2),"");   //comment
        break; //one row each time..
    }
}

void Dialog_linetype::on_pushButton_load_clicked()
{
   load_table();
}

void Dialog_linetype::on_pushButton_save_clicked()
{
   save_table();
   update_mainwindow = 1;
}

void Dialog_linetype::load_table()
{
    //empty tableview
    while(ui->tableWidget->rowCount() != 0){
        ui->tableWidget->removeRow(0);
    }

    //define ammount of tabble rows in file..
    int index_count = 0;
    QFile file_in(QDir::currentPath() + "/cadcam/" + "linetype.txt");
    if(!file_in.open(QIODevice::ReadOnly)) {
        qDebug() << "error reading file" << file_in.errorString();
    }
    QTextStream in(&file_in);    // file to read

    while(!in.atEnd()) {
        QString line = in.readLine();

        if(line.contains("scale", Qt::CaseSensitive)){ //random input, just count the blocks..
            index_count++;
        }
    }
    file_in.close();

    //create the ammount of table rows..
    for(int i=0; i<index_count; i++){
        ui->tableWidget->insertRow(i);
        //set initial value's, prevent saving empty cells..
        ui->tableWidget->model()->setData(ui->tableWidget->model()->index(i,0), 0.0);        //scale
        ui->tableWidget->model()->setData(ui->tableWidget->model()->index(i,1), "");         //pattern
        ui->tableWidget->model()->setData(ui->tableWidget->model()->index(i,2), "");        //comment
    }

    //overwrite data from file to tableview..
    int linenumber = 0;
    int row = -1;
    int scale_line = 0;
    int pattern_line = 0;
    int comment_line = 0;

    QFile file_in1(QDir::currentPath() + "/cadcam/" + "linetype.txt");
    if(!file_in1.open(QIODevice::ReadOnly)) {
        qDebug() << "error reading file" << file_in1.errorString();
    }
    QTextStream in1(&file_in1);    // file to read

    while(!in1.atEnd()) {
        QString line = in1.readLine();

        //scale..
        if(line.contains("scale", Qt::CaseSensitive)){
            scale_line = linenumber + 1;
        }
        if(linenumber == scale_line){
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(row,0),line);
        }
        //pattern..
        if(line.contains("pattern", Qt::CaseSensitive)){
            pattern_line = linenumber + 1;
        }
        if(linenumber == pattern_line){
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(row,1),line);
        }
        //comment..
        if(line.contains("comment", Qt::CaseSensitive)){
            comment_line = linenumber + 1;
        }
        if(linenumber == comment_line){
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(row,2),line);

            //row increase after last tool item read in..
            row++;
        }
        linenumber++;

    }
    file_in1.close();
}

void Dialog_linetype::save_table()
{
    QFile file_out(QDir::currentPath() + "/cadcam/" + "linetype.txt");
    if(!file_out.open(QIODevice::WriteOnly | QIODevice::Append)) {
        qDebug() << "error writing file" << file_out.errorString();
    }
    file_out.resize(0); //empty file
    QTextStream stream(&file_out);
    for(int i=0; i<ui->tableWidget->rowCount(); i++){

        stream << "scale" << endl;
        stream << ui->tableWidget->item(i,0)->text() << endl;
        stream << "pattern" << endl;
        stream << ui->tableWidget->item(i,1)->text() << endl;
        stream << "comment" << endl;
        stream << ui->tableWidget->item(i,2)->text() << endl;
        stream << " " << endl;
    }
    file_out.close();
}

void Dialog_linetype::on_pushButton_delete_clicked()
{
    QModelIndexList selection = ui->tableWidget->selectionModel()->selectedIndexes();
    for(int i=0; i< selection.count(); i++)
    {
        QModelIndex index = selection.at(i);
        //qDebug() << index.row();
        ui->tableWidget->removeRow(index.row());
    }
}

void Dialog_linetype::on_toolButton_move_up_clicked()
{
    QModelIndexList selection = ui->tableWidget->selectionModel()->selectedIndexes();
    for(int i=0; i< selection.count(); i++)
    {
        if(selection.count()>0){

            if(ui->tableWidget->currentIndex().row() > 0){ //prevent shoothing row to position -1...

                int selected_row = ui->tableWidget->currentIndex().row();
                //qDebug()<< "selected row : " << selected_row;

                //add current selected row to temp..
                QString a = ui->tableWidget->item(selected_row,0)->text();
                QString b = ui->tableWidget->item(selected_row,1)->text();
                QString c = ui->tableWidget->item(selected_row,2)->text();

                //remove the current selected row..
                ui->tableWidget->removeRow(selected_row);

                //insert the row to above..
                ui->tableWidget->insertRow(selected_row-1);
                //qDebug()<< "insert row : " << selected_row-1;

                //fill the empty row with the temp data..
                ui->tableWidget->model()->setData(ui->tableWidget->model()->index(selected_row-1,0),a);  //scale
                ui->tableWidget->model()->setData(ui->tableWidget->model()->index(selected_row-1,1),b);  //pattern
                ui->tableWidget->model()->setData(ui->tableWidget->model()->index(selected_row-1,2),c);  //comment

                //keep the moved line selected..
                QModelIndex next_index = ui->tableWidget->model()->index(selected_row-1, 0);
                ui->tableWidget->setCurrentIndex(next_index);
            }

        }
        break; //take first selection..
    }
}

void Dialog_linetype::on_toolButton_move_down_clicked()
{
    QModelIndexList selection = ui->tableWidget->selectionModel()->selectedIndexes();
    for(int i=0; i< selection.count(); i++)
    {
        int j = ui->tableWidget->rowCount();
        if(selection.count()>0 && ui->tableWidget->currentIndex().row() < j-1){ //prevent deleting last table line..

            int selected_row = ui->tableWidget->currentIndex().row();
            //qDebug()<< "selected row : " << selected_row;

            //add current selected row to temp..
            QString a = ui->tableWidget->item(selected_row,0)->text();
            QString b = ui->tableWidget->item(selected_row,1)->text();
            QString c = ui->tableWidget->item(selected_row,2)->text();

            //remove the current selected row..
            ui->tableWidget->removeRow(selected_row);

            //insert the row below..
            ui->tableWidget->insertRow(selected_row+1);
            //qDebug()<< "insert row : " << selected_row+1;

            //fill the empty row with the temp data..
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(selected_row+1,0),a);  //scale
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(selected_row+1,1),b);  //pattern
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(selected_row+1,2),c);  //comment

            //keep the moved line selected..
            QModelIndex next_index = ui->tableWidget->model()->index(selected_row+1, 0);
            ui->tableWidget->setCurrentIndex(next_index);
        }
        break; //take first selection..
    }
}

void Dialog_linetype::on_toolButton_save_and_close_clicked()
{
    save_table();
    update_mainwindow = 1;
    Dialog_linetype::close();
}
