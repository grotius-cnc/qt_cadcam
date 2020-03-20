#include "dialog_color.h"
#include "ui_dialog_color.h"
#include <QPixmap>
#include <qdebug.h>
#include <QColorDialog>
#include <QFile>
#include <QDir>

int red;
int green;
int blue;
int init = 0;

Dialog_color::Dialog_color(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_color)
{
    ui->setupUi(this);
    timerid = startTimer(500);

    ui->tableWidget->setAlternatingRowColors(true);
    ui->tableWidget->setColumnWidth(2,250);
    ui->tableWidget->setColumnWidth(8,250);
    load_table();

    //set color of the color preview label..
    ui->label_color_preview->setStyleSheet("background-color:rgb("+QString::number(ui->lineEdit_r->text().toInt())+","+QString::number(ui->lineEdit_g->text().toInt())+","+QString::number(ui->lineEdit_b->text().toInt())+")");
}

Dialog_color::~Dialog_color()
{
    load_table();
    killTimer(timerid);
    update_mainwindow = 1;
    delete ui;
}

void Dialog_color::timerEvent(QTimerEvent *)
{
    update_colors();
}

void Dialog_color::on_pushButton_new_clicked()
{
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());

    //create checkbox
    QTableWidgetItem* item;
    item = new QTableWidgetItem(true);
    item->setCheckState(Qt::Unchecked);
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0, item);                                              //hide
    ui->tableWidget->model()->setData(ui->tableWidget->model()->index(ui->tableWidget->rowCount()-1,1),0);        //layer nr.
    ui->tableWidget->model()->setData(ui->tableWidget->model()->index(ui->tableWidget->rowCount()-1,2),"");       //layer name
    ui->tableWidget->model()->setData(ui->tableWidget->model()->index(ui->tableWidget->rowCount()-1,3),"");       //color
    ui->tableWidget->model()->setData(ui->tableWidget->model()->index(ui->tableWidget->rowCount()-1,4),0);        //red
    ui->tableWidget->model()->setData(ui->tableWidget->model()->index(ui->tableWidget->rowCount()-1,5),0);        //green
    ui->tableWidget->model()->setData(ui->tableWidget->model()->index(ui->tableWidget->rowCount()-1,6),0);        //blue
    ui->tableWidget->model()->setData(ui->tableWidget->model()->index(ui->tableWidget->rowCount()-1,7),0);        //alpha
    ui->tableWidget->model()->setData(ui->tableWidget->model()->index(ui->tableWidget->rowCount()-1,8),"");       //comment
}

void Dialog_color::on_pushButton_insert_new_clicked()
{
    QModelIndexList selection = ui->tableWidget->selectionModel()->selectedIndexes();
    for(int i=0; i< selection.count(); i++)
    {
        QModelIndex index = selection.at(i);
        //qDebug() << index.row();
        ui->tableWidget->insertRow(index.row());

        //create checkbox
        QTableWidgetItem* item;
        item = new QTableWidgetItem(true);
        item->setCheckState(Qt::Unchecked);
        ui->tableWidget->setItem(index.row(),0, item);                                          //hide
        ui->tableWidget->model()->setData(ui->tableWidget->model()->index(index.row(),1),0);    //layer nr.
        ui->tableWidget->model()->setData(ui->tableWidget->model()->index(index.row(),2),"");   //layer name
        ui->tableWidget->model()->setData(ui->tableWidget->model()->index(index.row(),3),"");    //color
        ui->tableWidget->model()->setData(ui->tableWidget->model()->index(index.row(),4),0);    //red
        ui->tableWidget->model()->setData(ui->tableWidget->model()->index(index.row(),5),0);    //green
        ui->tableWidget->model()->setData(ui->tableWidget->model()->index(index.row(),6),0);    //blue
        ui->tableWidget->model()->setData(ui->tableWidget->model()->index(index.row(),7),0);    //alpha
        ui->tableWidget->model()->setData(ui->tableWidget->model()->index(index.row(),8),"");   //comment
        break; //one row each time..
    }
}

void Dialog_color::update_colors()
{
    for(int i = 0; i<ui->tableWidget->rowCount(); i++){
        int r = ui->tableWidget->item(i,4)->text().toInt();
        int g = ui->tableWidget->item(i,5)->text().toInt();
        int b = ui->tableWidget->item(i,6)->text().toInt();
        int a = ui->tableWidget->item(i,7)->text().toInt();
        ui->tableWidget->item(i,3)->setData(Qt::BackgroundRole, QColor (r,g,b,a));
    }
}

void Dialog_color::on_pushButton_save_clicked()
{
    save_table();
}

void Dialog_color::on_pushButton_load_clicked()
{
    load_table();
}

void Dialog_color::on_pushButton_delete_clicked()
{
    QModelIndexList selection = ui->tableWidget->selectionModel()->selectedIndexes();
    for(int i=0; i< selection.count(); i++)
    {
        QModelIndex index = selection.at(i);
        //qDebug() << index.row();
        ui->tableWidget->removeRow(index.row());
    }
}

void Dialog_color::save_table()
{
    QFile file_out(QDir::currentPath() + "/cadcam/" + "layer.txt");
    if(!file_out.open(QIODevice::WriteOnly | QIODevice::Append)) {
        qDebug() << "error writing file" << file_out.errorString();
    }
    file_out.resize(0); //empty file
    QTextStream stream(&file_out);
    for(int i=0; i<ui->tableWidget->rowCount(); i++){

        stream << "hide" << endl;
        stream << ui->tableWidget->item(i,0)->checkState() << endl; //0 is off, 2 is on..
        stream << "layer nr" << endl;
        stream << ui->tableWidget->item(i,1)->text() << endl;
        stream << "layer name" << endl;
        stream << ui->tableWidget->item(i,2)->text() << endl;
        stream << "color" << endl;
        stream << ui->tableWidget->item(i,3)->text() << endl;
        stream << "red" << endl;
        stream << ui->tableWidget->item(i,4)->text() << endl;
        stream << "green" << endl;
        stream << ui->tableWidget->item(i,5)->text() << endl;
        stream << "blue" << endl;
        stream << ui->tableWidget->item(i,6)->text() << endl;
        stream << "alpha" << endl;
        stream << ui->tableWidget->item(i,7)->text() << endl;
        stream << "comment" << endl;
        stream << ui->tableWidget->item(i,8)->text() << endl;
        stream << " " << endl;
    }
    file_out.close();
}

void Dialog_color::load_table()
{
    //empty tableview
    while(ui->tableWidget->rowCount() != 0){
        ui->tableWidget->removeRow(0);
    }

    //define ammount of tabble rows in file..
    int index_count = 0;
    QFile file_in(QDir::currentPath() + "/cadcam/" + "layer.txt");
    if(!file_in.open(QIODevice::ReadOnly)) {
        qDebug() << "error reading file" << file_in.errorString();
    }
    QTextStream in(&file_in);    // file to read

    while(!in.atEnd()) {
        QString line = in.readLine();

        if(line.contains("hide", Qt::CaseSensitive)){ //random input, just count the tools..
            index_count++;
        }
    }
    file_in.close();

    //create the ammount of table rows..
    for(int i=0; i<index_count; i++){
        ui->tableWidget->insertRow(i);
        //set initial value's, prevent saving empty cells..
        ui->tableWidget->model()->setData(ui->tableWidget->model()->index(i,0), 0);         //hide
        ui->tableWidget->model()->setData(ui->tableWidget->model()->index(i,1), 0);         //layer nr
        ui->tableWidget->model()->setData(ui->tableWidget->model()->index(i,2), "");        //layer name
        ui->tableWidget->model()->setData(ui->tableWidget->model()->index(i,3), 0);         //color
        ui->tableWidget->model()->setData(ui->tableWidget->model()->index(i,4), 0);         //red
        ui->tableWidget->model()->setData(ui->tableWidget->model()->index(i,5), 0);         //green
        ui->tableWidget->model()->setData(ui->tableWidget->model()->index(i,6), 0);         //blue
        ui->tableWidget->model()->setData(ui->tableWidget->model()->index(i,7), 0);         //alpha
        ui->tableWidget->model()->setData(ui->tableWidget->model()->index(i,8), "");        //comment
    }

    //overwrite data from file to tableview..
    int linenumber = 0;
    int row = -1;
    int hide_line = 0;
    int layer_nr_line = 0;
    int layer_name_line = 0;
    int color_line = 0;
    int red_line = 0;
    int green_line = 0;
    int blue_line = 0;
    int alpha_line = 0;
    int comment_line = 0;

    QFile file_in1(QDir::currentPath() + "/cadcam/" + "layer.txt");
    if(!file_in1.open(QIODevice::ReadOnly)) {
        qDebug() << "error reading file" << file_in1.errorString();
    }
    QTextStream in1(&file_in1);    // file to read

    while(!in1.atEnd()) {
        QString line = in1.readLine();

        //hide..
        if(line.contains("hide", Qt::CaseSensitive)){
            hide_line = linenumber + 1;
        }
        if(linenumber == hide_line){
            int state = line.toInt();
            //create checkbox
            QTableWidgetItem* item;
            item = new QTableWidgetItem(true);
            if(state == 0){
                item->setCheckState(Qt::Unchecked);
            }
            if(state == 2){
                item->setCheckState(Qt::Checked);
            }
            ui->tableWidget->setItem(row,0, item);
        }
        //layer_nr_line..
        if(line.contains("layer nr", Qt::CaseSensitive)){
            layer_nr_line = linenumber + 1;
        }
        if(linenumber == layer_nr_line){
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(row,1),line);
        }
        //layer_name_line..
        if(line.contains("layer name", Qt::CaseSensitive)){
            layer_name_line = linenumber + 1;
        }
        if(linenumber == layer_name_line){
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(row,2),line);
        }
        //color..
        if(line.contains("color", Qt::CaseSensitive)){
            color_line = linenumber + 1;
        }
        if(linenumber == color_line){
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(row,3),line);
        }
        //red..
        if(line.contains("red", Qt::CaseSensitive)){
            red_line = linenumber + 1;
        }
        if(linenumber == red_line){
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(row,4),line);
        }
        //green..
        if(line.contains("green", Qt::CaseSensitive)){
            green_line = linenumber + 1;
        }
        if(linenumber == green_line){
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(row,5),line);
        }
        //blue..
        if(line.contains("blue", Qt::CaseSensitive)){
            blue_line = linenumber + 1;
        }
        if(linenumber == blue_line){
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(row,6),line);
        }
        //blue..
        if(line.contains("alpha", Qt::CaseSensitive)){
            alpha_line = linenumber + 1;
        }
        if(linenumber == alpha_line){
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(row,7),line);
        }
        //comment..
        if(line.contains("comment", Qt::CaseSensitive)){
            comment_line = linenumber + 1;
        }
        if(linenumber == comment_line){
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(row,8),line);

            //row increase after last tool item read in..
            row++;
        }
        linenumber++;

    }
    file_in1.close();
}

void Dialog_color::on_toolButton_save_and_close_clicked()
{
    save_table();
    load_table();
    killTimer(timerid);
    update_mainwindow = 1;
    Dialog_color::close();

}

void Dialog_color::on_toolButton_move_up_clicked()
{
    QModelIndexList selection = ui->tableWidget->selectionModel()->selectedIndexes();
    for(int i=0; i< selection.count(); i++)
    {
        if(selection.count()>0){

            if(ui->tableWidget->currentIndex().row() > 0){ //prevent shoothing row to position -1...

                int selected_row = ui->tableWidget->currentIndex().row();
                //qDebug()<< "selected row : " << selected_row;

                //add current selected row to temp..
                int temp_state = ui->tableWidget->item(selected_row,0)->checkState();
                QString b = ui->tableWidget->item(selected_row,1)->text();
                QString c = ui->tableWidget->item(selected_row,2)->text();
                QString d = ui->tableWidget->item(selected_row,3)->text();
                QString e = ui->tableWidget->item(selected_row,4)->text();
                QString f = ui->tableWidget->item(selected_row,5)->text();
                QString g = ui->tableWidget->item(selected_row,6)->text();
                QString h = ui->tableWidget->item(selected_row,7)->text();
                QString m = ui->tableWidget->item(selected_row,8)->text();

                //remove the current selected row..
                ui->tableWidget->removeRow(selected_row);

                //insert the row to above..
                ui->tableWidget->insertRow(selected_row-1);
                //qDebug()<< "insert row : " << selected_row-1;

                //fill the empty row with the temp data..
                QTableWidgetItem* item;
                item = new QTableWidgetItem(true);
                if(temp_state==0){
                    item->setCheckState(Qt::Unchecked);
                }
                if(temp_state==2){
                    item->setCheckState(Qt::Checked);
                }
                ui->tableWidget->setItem(selected_row-1,0, item);                                        //hide
                ui->tableWidget->model()->setData(ui->tableWidget->model()->index(selected_row-1,1),b);  //layer nr
                ui->tableWidget->model()->setData(ui->tableWidget->model()->index(selected_row-1,2),c);  //layer name
                ui->tableWidget->model()->setData(ui->tableWidget->model()->index(selected_row-1,3),d);  //color
                ui->tableWidget->model()->setData(ui->tableWidget->model()->index(selected_row-1,4),e);  //red
                ui->tableWidget->model()->setData(ui->tableWidget->model()->index(selected_row-1,5),f);  //green
                ui->tableWidget->model()->setData(ui->tableWidget->model()->index(selected_row-1,6),g);  //blue
                ui->tableWidget->model()->setData(ui->tableWidget->model()->index(selected_row-1,7),h);  //alpha
                ui->tableWidget->model()->setData(ui->tableWidget->model()->index(selected_row-1,8),m);  //comment

                //keep the moved line selected..
                QModelIndex next_index = ui->tableWidget->model()->index(selected_row-1, 0);
                ui->tableWidget->setCurrentIndex(next_index);
            }

        }
        break; //take first selection..
    }
}

void Dialog_color::on_toolButton_move_down_clicked()
{
    QModelIndexList selection = ui->tableWidget->selectionModel()->selectedIndexes();
    for(int i=0; i< selection.count(); i++)
    {
        int j = ui->tableWidget->rowCount();
        if(selection.count()>0 && ui->tableWidget->currentIndex().row() < j-1){ //prevent deleting last table line..

            int selected_row = ui->tableWidget->currentIndex().row();
            //qDebug()<< "selected row : " << selected_row;

            //add current selected row to temp..
            int temp_state = ui->tableWidget->item(selected_row,0)->checkState();
            QString b = ui->tableWidget->item(selected_row,1)->text();
            QString c = ui->tableWidget->item(selected_row,2)->text();
            QString d = ui->tableWidget->item(selected_row,3)->text();
            QString e = ui->tableWidget->item(selected_row,4)->text();
            QString f = ui->tableWidget->item(selected_row,5)->text();
            QString g = ui->tableWidget->item(selected_row,6)->text();
            QString h = ui->tableWidget->item(selected_row,7)->text();
            QString m = ui->tableWidget->item(selected_row,8)->text();

            //remove the current selected row..
            ui->tableWidget->removeRow(selected_row);

            //insert the row below..
            ui->tableWidget->insertRow(selected_row+1);
            //qDebug()<< "insert row : " << selected_row+1;

            //fill the empty row with the temp data..
            QTableWidgetItem* item;
            item = new QTableWidgetItem(true);
            if(temp_state==0){
                item->setCheckState(Qt::Unchecked);
            }
            if(temp_state==2){
                item->setCheckState(Qt::Checked);
            }
            ui->tableWidget->setItem(selected_row+1,0, item);                                        //hide
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(selected_row+1,1),b);  //layer nr
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(selected_row+1,2),c);  //layer name
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(selected_row+1,3),d);  //color
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(selected_row+1,4),e);  //red
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(selected_row+1,5),f);  //green
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(selected_row+1,6),g);  //blue
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(selected_row+1,7),h);  //alpha
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(selected_row+1,8),m);  //comment

            //keep the moved line selected..
            QModelIndex next_index = ui->tableWidget->model()->index(selected_row+1, 0);
            ui->tableWidget->setCurrentIndex(next_index);

        }
        break; //take first selection..
    }
}

void Dialog_color::extern_toolbar_load()
{
    red_list.clear();
    green_list.clear();
    blue_list.clear();
    alpha_list.clear();
    comments.clear();
    red_list_gl.clear();
    green_list_gl.clear();
    blue_list_gl.clear();
    alpha_list_gl.clear();

    for(int i=0; i<ui->tableWidget->rowCount(); i++){

        //colors 0-255
        red_list.append(ui->tableWidget->item(i,4)->text().toInt());
        green_list.append(ui->tableWidget->item(i,5)->text().toInt());
        blue_list.append(ui->tableWidget->item(i,6)->text().toInt());
        alpha_list.append(ui->tableWidget->item(i,7)->text().toInt());
        comments.append(ui->tableWidget->item(i,2)->text()); //layer name..

        //colors 0-1 (opengl direct interface)
        red_list_gl.append(ui->tableWidget->item(i,4)->text().toDouble()/255);
        green_list_gl.append(ui->tableWidget->item(i,5)->text().toDouble()/255);
        blue_list_gl.append(ui->tableWidget->item(i,6)->text().toDouble()/255);
        alpha_list_gl.append(ui->tableWidget->item(i,7)->text().toDouble()/255);
    }
}

void Dialog_color::on_toolButton_color_window_clicked()
{
    QColor color = QColorDialog::getColor(Qt::black | QColorDialog::DontUseNativeDialog);

    ui->lineEdit_r->setText(QString::number(color.redF()*255));
    ui->lineEdit_g->setText(QString::number(color.greenF()*255));
    ui->lineEdit_b->setText(QString::number(color.blueF()*255));
    ui->lineEdit_a->setText(QString::number(color.alphaF()*255));

    ui->label_color_preview->setStyleSheet("background-color:rgb("+QString::number(color.redF()*255)+","+QString::number(color.greenF()*255)+","+QString::number(color.blueF()*255)+")");
}

void Dialog_color::on_lineEdit_r_returnPressed()
{
    ui->label_color_preview->setStyleSheet("background-color:rgb("+QString::number(ui->lineEdit_r->text().toInt())+","+QString::number(ui->lineEdit_g->text().toInt())+","+QString::number(ui->lineEdit_b->text().toInt())+")");
}

void Dialog_color::on_lineEdit_g_returnPressed()
{
    ui->label_color_preview->setStyleSheet("background-color:rgb("+QString::number(ui->lineEdit_r->text().toInt())+","+QString::number(ui->lineEdit_g->text().toInt())+","+QString::number(ui->lineEdit_b->text().toInt())+")");
}

void Dialog_color::on_lineEdit_b_returnPressed()
{
    ui->label_color_preview->setStyleSheet("background-color:rgb("+QString::number(ui->lineEdit_r->text().toInt())+","+QString::number(ui->lineEdit_g->text().toInt())+","+QString::number(ui->lineEdit_b->text().toInt())+")");
}

void Dialog_color::on_lineEdit_a_returnPressed()
{
    ui->label_color_preview->setStyleSheet("background-color:rgb("+QString::number(ui->lineEdit_r->text().toInt())+","+QString::number(ui->lineEdit_g->text().toInt())+","+QString::number(ui->lineEdit_b->text().toInt())+")");
}

void Dialog_color::on_toolButton_clicked()
{
    int red = ui->lineEdit_r->text().toInt();
    int green = ui->lineEdit_g->text().toInt();
    int blue = ui->lineEdit_b->text().toInt();
    int alpha = ui->lineEdit_a->text().toInt();

    int selected_row = ui->tableWidget->currentIndex().row();

    ui->tableWidget->item(selected_row, 4)->setText(QString::number(red));
    ui->tableWidget->item(selected_row, 5)->setText(QString::number(green));
    ui->tableWidget->item(selected_row, 6)->setText(QString::number(blue));
    ui->tableWidget->item(selected_row, 7)->setText(QString::number(alpha));
}
























