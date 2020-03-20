#include "dialog_axis.h"
#include "ui_dialog_axis.h"
#include <core_functions/variables.h>

Dialog_axis::Dialog_axis(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_axis)
{
    ui->setupUi(this);

    ui->tableWidget->setColumnWidth(1,175);
    ui->tableWidget->setAlternatingRowColors(true);
    load_table(); //initialise tool library..

    ui->tableWidget_2->setColumnWidth(1,175);
    ui->tableWidget_2->setAlternatingRowColors(true);
    load_table2(); //initialise tool library..
}

Dialog_axis::~Dialog_axis()
{
    delete ui;
}

//machine base axis section
void Dialog_axis::on_pushButton_new_clicked()
{
    //qDebug() << ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());

    //create checkbox
    QTableWidgetItem* item;
    item = new QTableWidgetItem(true);
    item->setCheckState(Qt::Unchecked);
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0, item);                                              //select
    ui->tableWidget->model()->setData(ui->tableWidget->model()->index(ui->tableWidget->rowCount()-1,1),"name");   //description
    ui->tableWidget->model()->setData(ui->tableWidget->model()->index(ui->tableWidget->rowCount()-1,2),"");       //x axis letter
    ui->tableWidget->model()->setData(ui->tableWidget->model()->index(ui->tableWidget->rowCount()-1,3),"");       //y axis letter
    ui->tableWidget->model()->setData(ui->tableWidget->model()->index(ui->tableWidget->rowCount()-1,4),0.0);      //x home pos
    ui->tableWidget->model()->setData(ui->tableWidget->model()->index(ui->tableWidget->rowCount()-1,5),0.0);      //y home pos
}

void Dialog_axis::on_pushButton_insert_new_clicked()
{
    QModelIndexList selection = ui->tableWidget->selectionModel()->selectedIndexes();
    for(int i=0; i< selection.count(); i++)
    {
        QModelIndex index = selection.at(i);
        qDebug() << index.row();
        ui->tableWidget->insertRow(index.row());

        //create checkbox
        QTableWidgetItem* item;
        item = new QTableWidgetItem(true);
        item->setCheckState(Qt::Unchecked);
        ui->tableWidget->setItem(index.row(),0, item);                                              //select
        ui->tableWidget->model()->setData(ui->tableWidget->model()->index(index.row(),1),"name");   //description
        ui->tableWidget->model()->setData(ui->tableWidget->model()->index(index.row(),2),"");       //x axis letter
        ui->tableWidget->model()->setData(ui->tableWidget->model()->index(index.row(),3),"");       //y axis letter
        ui->tableWidget->model()->setData(ui->tableWidget->model()->index(index.row(),4),0.0);      //x home pos
        ui->tableWidget->model()->setData(ui->tableWidget->model()->index(index.row(),5),0.0);      //y home pos
        break; //one row each time..
    }
}

void Dialog_axis::on_pushButton_delete_clicked()
{
    QModelIndexList selection = ui->tableWidget->selectionModel()->selectedIndexes();
    for(int i=0; i< selection.count(); i++)
    {
        QModelIndex index = selection.at(i);
        //qDebug() << index.row();
        ui->tableWidget->removeRow(index.row());
    }
}

void Dialog_axis::save_table()
{
    QFile file_out(QDir::currentPath() + "/cadcam/" + "axis_base.txt");
    if(!file_out.open(QIODevice::WriteOnly | QIODevice::Append)) {
        qDebug() << "error writing file" << file_out.errorString();
    }
    file_out.resize(0); //empty file
    QTextStream stream(&file_out);
    for(int i=0; i<ui->tableWidget->rowCount(); i++){

        //tools
        stream << "select" << endl;
        stream << ui->tableWidget->item(i,0)->checkState() << endl; //0 is off, 2 is on..
        stream << "description" << endl;
        stream << ui->tableWidget->item(i,1)->text() << endl;
        stream << "x axis" << endl;
        stream << ui->tableWidget->item(i,2)->text() << endl;
        stream << "y axis" << endl;
        stream << ui->tableWidget->item(i,3)->text() << endl;
        stream << "x home pos" << endl;
        stream << ui->tableWidget->item(i,4)->text() << endl;
        stream << "y home pos" << endl;
        stream << ui->tableWidget->item(i,5)->text() << endl;
        stream << "" << endl;
    }
    file_out.close();
}

void Dialog_axis::load_table()
{
    //empty tableview
    while(ui->tableWidget->rowCount() != 0){
        ui->tableWidget->removeRow(0);
    }

    //define ammount of tabble rows in file..
    int index_count = 0;
    QFile file_in(QDir::currentPath() + "/cadcam/" + "axis_base.txt");
    if(!file_in.open(QIODevice::ReadOnly)) {
        qDebug() << "error reading file" << file_in.errorString();
    }
    QTextStream in(&file_in);    // file to read

    while(!in.atEnd()) {
        QString line = in.readLine();

        if(line.contains("select", Qt::CaseSensitive)){ //random input, just count the tools..
            index_count++;
        }
    }
    file_in.close();

    //create the ammount of table rows..
    for(int i=0; i<index_count; i++){
        ui->tableWidget->insertRow(i);
        //set initial value's, prevent saving empty cells..
        ui->tableWidget->model()->setData(ui->tableWidget->model()->index(i,0), 0);         //select
        ui->tableWidget->model()->setData(ui->tableWidget->model()->index(i,1), "name");    //description
        ui->tableWidget->model()->setData(ui->tableWidget->model()->index(i,2), "");        //x axis letter
        ui->tableWidget->model()->setData(ui->tableWidget->model()->index(i,3), "");        //y axis letter
        ui->tableWidget->model()->setData(ui->tableWidget->model()->index(i,4), 0.0);       //x home pos
        ui->tableWidget->model()->setData(ui->tableWidget->model()->index(i,5), 0.0);       //y home pos
    }

    //overwrite data from file to tableview..
    int linenumber = 0;
    int row = -1;
    int select_line = 0;
    int description_line = 0;
    int x_axis_line = 0;
    int y_axis_line = 0;
    int x_homepos_line = 0;
    int y_homepos_line = 0;

    QFile file_in1(QDir::currentPath() + "/cadcam/" + "axis_base.txt");
    if(!file_in1.open(QIODevice::ReadOnly)) {
        qDebug() << "error reading file" << file_in1.errorString();
    }
    QTextStream in1(&file_in1);    // file to read

    while(!in1.atEnd()) {
        QString line = in1.readLine();

        //checkbox..
        if(line.contains("select", Qt::CaseSensitive)){
            select_line = linenumber + 1;
        }
        if(linenumber == select_line){
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

        //description..
        if(line.contains("description", Qt::CaseSensitive)){
            description_line = linenumber + 1;
        }
        if(linenumber == description_line){
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(row,1),line);
        }
        //x axis..
        if(line.contains("x axis", Qt::CaseSensitive)){
            x_axis_line = linenumber + 1;
        }
        if(linenumber == x_axis_line){
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(row,2),line);
        }
        //y axis..
        if(line.contains("y axis", Qt::CaseSensitive)){
            y_axis_line = linenumber + 1;
        }
        if(linenumber == y_axis_line){
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(row,3),line);
        }
        //x home pos..
        if(line.contains("x home pos", Qt::CaseSensitive)){
            x_homepos_line = linenumber + 1;
        }
        if(linenumber == x_homepos_line){
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(row,4),line);
        }
        //y home pos..
        if(line.contains("y home pos", Qt::CaseSensitive)){
            y_homepos_line = linenumber + 1;
        }
        if(linenumber == y_homepos_line){
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(row,5),line);

            //row increase after last tool item read in..
            row++;
        }
        linenumber++;

    }
    file_in1.close();
}

void Dialog_axis::load_selected_data()
{
    int state = 0;
    int linenumber = 0;
    int select_line = 0;
    int description_line = 0;
    int x_axis_line = 0;
    int y_axis_line = 0;
    int x_homepos_line = 0;
    int y_homepos_line = 0;

    QFile file_in(QDir::currentPath() + "/cadcam/" + "axis_base.txt");
    if(!file_in.open(QIODevice::ReadOnly)) {
        qDebug() << "error reading file" << file_in.errorString();
    }
    QTextStream in1(&file_in);    // file to read

    while(!in1.atEnd()) {
        QString line = in1.readLine();

        //checkbox..
        if(line.contains("select", Qt::CaseSensitive)){
            select_line = linenumber + 1;
        }
        if(linenumber == select_line){
            state = line.toInt();
            //create checkbox
            QTableWidgetItem* item;
            item = new QTableWidgetItem(true);
            if(state == 0){
            }
            if(state == 2){
                //our trigger..
            }
        }
        //description..
        if(line.contains("description", Qt::CaseSensitive) && state==2){
            description_line = linenumber + 1;
        }
        if(linenumber == description_line){
            extern_axis_base_description = line;
        }
        //x axis..
        if(line.contains("x axis", Qt::CaseSensitive) && state==2){
            x_axis_line = linenumber + 1;
        }
        if(linenumber == x_axis_line){
            extern_x_axis_sign = line;
        }
        //y axis..
        if(line.contains("y axis", Qt::CaseSensitive) && state==2){
            y_axis_line = linenumber + 1;
        }
        if(linenumber == y_axis_line){
            extern_y_axis_sign = line;
        }
        //x home pos..
        if(line.contains("x home pos", Qt::CaseSensitive) && state==2){
            x_homepos_line = linenumber + 1;
        }
        if(linenumber == x_homepos_line){
            extern_x_home_pos = line;
        }
        //y home pos..
        if(line.contains("y home pos", Qt::CaseSensitive) && state==2){
            y_homepos_line = linenumber + 1;
        }
        if(linenumber == y_homepos_line){
            extern_y_home_pos = line;
        }
        linenumber++;
    }
    file_in.close();
}


void Dialog_axis::on_pushButton_load_clicked()
{
    load_table();
    load_selected_data();
}

void Dialog_axis::on_pushButton_save_clicked()
{
    save_table();
    load_selected_data();
}

void Dialog_axis::on_toolButton_move_up_clicked()
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
            QString a = ui->tableWidget->item(selected_row,1)->text();
            QString b = ui->tableWidget->item(selected_row,2)->text();
            QString c = ui->tableWidget->item(selected_row,3)->text();
            QString d = ui->tableWidget->item(selected_row,4)->text();
            QString e = ui->tableWidget->item(selected_row,5)->text();

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
            ui->tableWidget->setItem(selected_row-1,0, item);                                        //select
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(selected_row-1,1),a);  //description
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(selected_row-1,2),b);  //x axis
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(selected_row-1,3),c);  //y axis
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(selected_row-1,4),d);  //x home pos
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(selected_row-1,5),e);  //y home pos

            //keep the moved line selected..
            QModelIndex next_index = ui->tableWidget->model()->index(selected_row-1, 0);
            ui->tableWidget->setCurrentIndex(next_index);
            }

        }
        break; //take first selection..
    }
}

void Dialog_axis::on_toolButton_move_down_clicked()
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
            QString a = ui->tableWidget->item(selected_row,1)->text();
            QString b = ui->tableWidget->item(selected_row,2)->text();
            QString c = ui->tableWidget->item(selected_row,3)->text();
            QString d = ui->tableWidget->item(selected_row,4)->text();
            QString e = ui->tableWidget->item(selected_row,5)->text();

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
            ui->tableWidget->setItem(selected_row+1,0, item);                                        //select
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(selected_row+1,1),a);  //description
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(selected_row+1,2),b);  //x axis
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(selected_row+1,3),c);  //y axis
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(selected_row+1,4),d);  //x home pos
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(selected_row+1,5),e);  //y home pos

            //keep the moved line selected..
            QModelIndex next_index = ui->tableWidget->model()->index(selected_row+1, 0);
            ui->tableWidget->setCurrentIndex(next_index);

        }
        break; //take first selection..
    }
}

//machine head axis section

void Dialog_axis::on_pushButton_new_2_clicked()
{
    //qDebug() << ui->tableWidget->rowCount();
    ui->tableWidget_2->insertRow(ui->tableWidget_2->rowCount());

    //create checkbox
    QTableWidgetItem* item;
    item = new QTableWidgetItem(true);
    item->setCheckState(Qt::Unchecked);
    ui->tableWidget_2->setItem(ui->tableWidget_2->rowCount()-1,0, item);                                                //select
    ui->tableWidget_2->model()->setData(ui->tableWidget_2->model()->index(ui->tableWidget_2->rowCount()-1,1),"name");   //description
    ui->tableWidget_2->model()->setData(ui->tableWidget_2->model()->index(ui->tableWidget_2->rowCount()-1,2),"");       //z axis letter
    ui->tableWidget_2->model()->setData(ui->tableWidget_2->model()->index(ui->tableWidget_2->rowCount()-1,3),0.0);      //z travelheight
    ui->tableWidget_2->model()->setData(ui->tableWidget_2->model()->index(ui->tableWidget_2->rowCount()-1,4),0.0);      //z home pos
    ui->tableWidget_2->model()->setData(ui->tableWidget_2->model()->index(ui->tableWidget_2->rowCount()-1,5),0.0);      //x offset
    ui->tableWidget_2->model()->setData(ui->tableWidget_2->model()->index(ui->tableWidget_2->rowCount()-1,6),0.0);      //y offset
    ui->tableWidget_2->model()->setData(ui->tableWidget_2->model()->index(ui->tableWidget_2->rowCount()-1,7),0.0);      //z offset
}

void Dialog_axis::on_pushButton_insert_new_2_clicked()
{
    QModelIndexList selection = ui->tableWidget_2->selectionModel()->selectedIndexes();
    for(int i=0; i< selection.count(); i++)
    {
        QModelIndex index = selection.at(i);
        qDebug() << index.row();
        ui->tableWidget_2->insertRow(index.row());

        //create checkbox
        QTableWidgetItem* item;
        item = new QTableWidgetItem(true);
        item->setCheckState(Qt::Unchecked);
        ui->tableWidget_2->setItem(index.row(),0, item);                                                //select
        ui->tableWidget_2->model()->setData(ui->tableWidget_2->model()->index(index.row(),1),"name");   //description
        ui->tableWidget_2->model()->setData(ui->tableWidget_2->model()->index(index.row(),2),"");       //z axis letter
        ui->tableWidget_2->model()->setData(ui->tableWidget_2->model()->index(index.row(),3),0.0);      //z travelheight
        ui->tableWidget_2->model()->setData(ui->tableWidget_2->model()->index(index.row(),4),0.0);      //z home pos
        ui->tableWidget_2->model()->setData(ui->tableWidget_2->model()->index(index.row(),5),0.0);      //x offset
        ui->tableWidget_2->model()->setData(ui->tableWidget_2->model()->index(index.row(),6),0.0);      //y offset
        ui->tableWidget_2->model()->setData(ui->tableWidget_2->model()->index(index.row(),7),0.0);      //z offset
        break; //one row each time..
    }
}

void Dialog_axis::on_pushButton_delete_2_clicked()
{
    QModelIndexList selection = ui->tableWidget_2->selectionModel()->selectedIndexes();
    for(int i=0; i< selection.count(); i++)
    {
        QModelIndex index = selection.at(i);
        //qDebug() << index.row();
        ui->tableWidget_2->removeRow(index.row());
    }
}

void Dialog_axis::save_table2()
{
    QFile file_out(QDir::currentPath() + "/cadcam/" + "axis_head.txt");
    if(!file_out.open(QIODevice::WriteOnly | QIODevice::Append)) {
        qDebug() << "error writing file" << file_out.errorString();
    }
    file_out.resize(0); //empty file
    QTextStream stream(&file_out);
    for(int i=0; i<ui->tableWidget_2->rowCount(); i++){

        //tools
        stream << "select" << endl;
        stream << ui->tableWidget_2->item(i,0)->checkState() << endl; //0 is off, 2 is on..
        stream << "description" << endl;
        stream << ui->tableWidget_2->item(i,1)->text() << endl;
        stream << "z axis" << endl;
        stream << ui->tableWidget_2->item(i,2)->text() << endl;
        stream << "z travelheight" << endl;
        stream << ui->tableWidget_2->item(i,3)->text() << endl;
        stream << "z home pos" << endl;
        stream << ui->tableWidget_2->item(i,4)->text() << endl;
        stream << "x offset" << endl;
        stream << ui->tableWidget_2->item(i,5)->text() << endl;
        stream << "y offset" << endl;
        stream << ui->tableWidget_2->item(i,6)->text() << endl;
        stream << "z offset" << endl;
        stream << ui->tableWidget_2->item(i,7)->text() << endl;
        stream << "" << endl;
    }
    file_out.close();
}

void Dialog_axis::load_table2()
{
    //empty tableview
    while(ui->tableWidget_2->rowCount() != 0){
        ui->tableWidget_2->removeRow(0);
    }

    //define ammount of tabble rows in file..
    int index_count = 0;
    QFile file_in(QDir::currentPath() + "/cadcam/" + "axis_head.txt");
    if(!file_in.open(QIODevice::ReadOnly)) {
        qDebug() << "error reading file" << file_in.errorString();
    }
    QTextStream in(&file_in);    // file to read

    while(!in.atEnd()) {
        QString line = in.readLine();

        if(line.contains("select", Qt::CaseSensitive)){ //random input, just count the tools..
            index_count++;
        }
    }
    file_in.close();

    //create the ammount of table rows..
    for(int i=0; i<index_count; i++){
        ui->tableWidget_2->insertRow(i);
        //set initial value's, prevent saving empty cells..
        ui->tableWidget_2->model()->setData(ui->tableWidget_2->model()->index(i,0), 0);         //select
        ui->tableWidget_2->model()->setData(ui->tableWidget_2->model()->index(i,1), "name");    //description
        ui->tableWidget_2->model()->setData(ui->tableWidget_2->model()->index(i,2), "");        //z axis letter
        ui->tableWidget_2->model()->setData(ui->tableWidget_2->model()->index(i,3), 0.0);       //z travelheight
        ui->tableWidget_2->model()->setData(ui->tableWidget_2->model()->index(i,4), 0.0);       //z home pos
        ui->tableWidget_2->model()->setData(ui->tableWidget_2->model()->index(i,5), 0.0);       //x offset
        ui->tableWidget_2->model()->setData(ui->tableWidget_2->model()->index(i,6), 0.0);       //y offset
        ui->tableWidget_2->model()->setData(ui->tableWidget_2->model()->index(i,7), 0.0);       //z offset
    }

    //overwrite data from file to tableview..
    int linenumber = 0;
    int row = -1;
    int select_line = 0;
    int description_line = 0;
    int z_axis_line = 0;
    int z_travelheight_line = 0;
    int z_homepos_line = 0;
    int x_offset_line = 0;
    int y_offset_line = 0;
    int z_offset_line = 0;

    QFile file_in1(QDir::currentPath() + "/cadcam/" + "axis_head.txt");
    if(!file_in1.open(QIODevice::ReadOnly)) {
        qDebug() << "error reading file" << file_in1.errorString();
    }
    QTextStream in1(&file_in1);    // file to read

    while(!in1.atEnd()) {
        QString line = in1.readLine();

        //checkbox..
        if(line.contains("select", Qt::CaseSensitive)){
            select_line = linenumber + 1;
        }
        if(linenumber == select_line){
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
            ui->tableWidget_2->setItem(row,0, item);
        }

        //description..
        if(line.contains("description", Qt::CaseSensitive)){
            description_line = linenumber + 1;
        }
        if(linenumber == description_line){
            ui->tableWidget_2->model()->setData(ui->tableWidget_2->model()->index(row,1),line);
        }
        //z axis..
        if(line.contains("z axis", Qt::CaseSensitive)){
            z_axis_line = linenumber + 1;
        }
        if(linenumber == z_axis_line){
            ui->tableWidget_2->model()->setData(ui->tableWidget_2->model()->index(row,2),line);
        }
        //z travelheight..
        if(line.contains("z travelheight", Qt::CaseSensitive)){
            z_travelheight_line = linenumber + 1;
        }
        if(linenumber == z_travelheight_line){
            ui->tableWidget_2->model()->setData(ui->tableWidget_2->model()->index(row,3),line);
        }
        //z home pos..
        if(line.contains("z home pos", Qt::CaseSensitive)){
            z_homepos_line = linenumber + 1;
        }
        if(linenumber == z_homepos_line){
            ui->tableWidget_2->model()->setData(ui->tableWidget_2->model()->index(row,4),line);
        }
        //x offset..
        if(line.contains("x offset", Qt::CaseSensitive)){
            x_offset_line = linenumber + 1;
        }
        if(linenumber == x_offset_line){
            ui->tableWidget_2->model()->setData(ui->tableWidget_2->model()->index(row,5),line);
        }
        //y offset..
        if(line.contains("y offset", Qt::CaseSensitive)){
            y_offset_line = linenumber + 1;
        }
        if(linenumber == y_offset_line){
            ui->tableWidget_2->model()->setData(ui->tableWidget_2->model()->index(row,6),line);
        }
        //z offset..
        if(line.contains("z offset", Qt::CaseSensitive)){
            z_offset_line = linenumber + 1;
        }
        if(linenumber == z_offset_line){
            ui->tableWidget_2->model()->setData(ui->tableWidget_2->model()->index(row,7),line);

            //row increase after last tool item read in..
            row++;
        }
        linenumber++;
    }
    file_in1.close();
}

void Dialog_axis::load_selected_data2()
{
    int state = 0;
    int linenumber = 0;
    int select_line = 0;
    int description_line = 0;
    int z_axis_line = 0;
    int z_travelheight_line = 0;
    int z_homepos_line = 0;
    int x_offset_line = 0;
    int y_offset_line = 0;
    int z_offset_line = 0;

    QFile file_in(QDir::currentPath() + "/cadcam/" + "axis_head.txt");
    if(!file_in.open(QIODevice::ReadOnly)) {
        qDebug() << "error reading file" << file_in.errorString();
    }
    QTextStream in1(&file_in);    // file to read

    while(!in1.atEnd()) {
        QString line = in1.readLine();

        //checkbox..
        if(line.contains("select", Qt::CaseSensitive)){
            select_line = linenumber + 1;
        }
        if(linenumber == select_line){
            state = line.toInt();
            //create checkbox
            QTableWidgetItem* item;
            item = new QTableWidgetItem(true);
            if(state == 0){
            }
            if(state == 2){
                //our trigger..
            }
        }
        //description..
        if(line.contains("description", Qt::CaseSensitive) && state==2){
            description_line = linenumber + 1;
        }
        if(linenumber == description_line){
            extern_axis_head_description = line;
        }
        //x axis..
        if(line.contains("z axis", Qt::CaseSensitive) && state==2){
            z_axis_line = linenumber + 1;
        }
        if(linenumber == z_axis_line){
            extern_z_axis_sign = line;
        }
        //y axis..
        if(line.contains("z travelheight", Qt::CaseSensitive) && state==2){
            z_travelheight_line = linenumber + 1;
        }
        if(linenumber == z_travelheight_line){
            extern_z_travelheight = line;
        }
        //z home pos..
        if(line.contains("z home pos", Qt::CaseSensitive) && state==2){
            z_homepos_line = linenumber + 1;
        }
        if(linenumber == z_homepos_line){
            extern_z_home_pos = line;
        }
        //x offset..
        if(line.contains("x offset", Qt::CaseSensitive) && state==2){
            x_offset_line = linenumber + 1;
        }
        if(linenumber == x_offset_line){
            extern_x_offset = line;
        }
        //y offset..
        if(line.contains("y offset", Qt::CaseSensitive) && state==2){
            y_offset_line = linenumber + 1;
        }
        if(linenumber == y_offset_line){
            extern_y_offset = line;
        }
        //z offset..
        if(line.contains("z offset", Qt::CaseSensitive) && state==2){
            z_offset_line = linenumber + 1;
        }
        if(linenumber == z_offset_line){
            extern_z_offset = line;
        }
        linenumber++;
    }
    file_in.close();
}

void Dialog_axis::on_pushButton_load_2_clicked()
{
    load_table2();
    load_selected_data2();
}

void Dialog_axis::on_pushButton_save_2_clicked()
{
    save_table2();
    load_selected_data2();
}

void Dialog_axis::on_toolButton_move_up_2_clicked()
{
    QModelIndexList selection = ui->tableWidget_2->selectionModel()->selectedIndexes();
    for(int i=0; i< selection.count(); i++)
    {
        if(selection.count()>0){

            if(ui->tableWidget_2->currentIndex().row() > 0){ //prevent shoothing row to position -1...

            int selected_row = ui->tableWidget_2->currentIndex().row();
            //qDebug()<< "selected row : " << selected_row;

            //add current selected row to temp..
            int temp_state = ui->tableWidget_2->item(selected_row,0)->checkState();
            QString a = ui->tableWidget_2->item(selected_row,1)->text();
            QString b = ui->tableWidget_2->item(selected_row,2)->text();
            QString c = ui->tableWidget_2->item(selected_row,3)->text();
            QString d = ui->tableWidget_2->item(selected_row,4)->text();
            QString e = ui->tableWidget_2->item(selected_row,5)->text();
            QString f = ui->tableWidget_2->item(selected_row,6)->text();
            QString g = ui->tableWidget_2->item(selected_row,7)->text();

            //remove the current selected row..
            ui->tableWidget_2->removeRow(selected_row);

            //insert the row to above..
            ui->tableWidget_2->insertRow(selected_row-1);
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
            ui->tableWidget_2->setItem(selected_row-1,0, item);                                          //select
            ui->tableWidget_2->model()->setData(ui->tableWidget_2->model()->index(selected_row-1,1),a);  //description
            ui->tableWidget_2->model()->setData(ui->tableWidget_2->model()->index(selected_row-1,2),b);  //z axis
            ui->tableWidget_2->model()->setData(ui->tableWidget_2->model()->index(selected_row-1,3),c);  //z travelheight
            ui->tableWidget_2->model()->setData(ui->tableWidget_2->model()->index(selected_row-1,4),d);  //z home pos
            ui->tableWidget_2->model()->setData(ui->tableWidget_2->model()->index(selected_row-1,5),e);  //x offset
            ui->tableWidget_2->model()->setData(ui->tableWidget_2->model()->index(selected_row-1,6),f);  //y offset
            ui->tableWidget_2->model()->setData(ui->tableWidget_2->model()->index(selected_row-1,7),g);  //z offset

            //keep the moved line selected..
            QModelIndex next_index = ui->tableWidget_2->model()->index(selected_row-1, 0);
            ui->tableWidget_2->setCurrentIndex(next_index);
            }

        }
        break; //take first selection..
    }
}

void Dialog_axis::on_toolButton_move_down_2_clicked()
{
    QModelIndexList selection = ui->tableWidget_2->selectionModel()->selectedIndexes();
    for(int i=0; i< selection.count(); i++)
    {
        int j = ui->tableWidget_2->rowCount();
        if(selection.count()>0 && ui->tableWidget_2->currentIndex().row() < j-1){ //prevent deleting last table line..

            int selected_row = ui->tableWidget_2->currentIndex().row();
            //qDebug()<< "selected row : " << selected_row;

            //add current selected row to temp..
            int temp_state = ui->tableWidget_2->item(selected_row,0)->checkState();
            QString a = ui->tableWidget_2->item(selected_row,1)->text();
            QString b = ui->tableWidget_2->item(selected_row,2)->text();
            QString c = ui->tableWidget_2->item(selected_row,3)->text();
            QString d = ui->tableWidget_2->item(selected_row,4)->text();
            QString e = ui->tableWidget_2->item(selected_row,5)->text();
            QString f = ui->tableWidget_2->item(selected_row,6)->text();
            QString g = ui->tableWidget_2->item(selected_row,7)->text();

            //remove the current selected row..
            ui->tableWidget_2->removeRow(selected_row);

            //insert the row below..
            ui->tableWidget_2->insertRow(selected_row+1);
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
            ui->tableWidget_2->setItem(selected_row+1,0, item);                                        //select
            ui->tableWidget_2->model()->setData(ui->tableWidget_2->model()->index(selected_row+1,1),a);  //description
            ui->tableWidget_2->model()->setData(ui->tableWidget_2->model()->index(selected_row+1,2),b);  //z axis
            ui->tableWidget_2->model()->setData(ui->tableWidget_2->model()->index(selected_row+1,3),c);  //z travelheight
            ui->tableWidget_2->model()->setData(ui->tableWidget_2->model()->index(selected_row+1,4),d);  //z home pos
            ui->tableWidget_2->model()->setData(ui->tableWidget_2->model()->index(selected_row+1,5),e);  //x offset
            ui->tableWidget_2->model()->setData(ui->tableWidget_2->model()->index(selected_row+1,6),f);  //y offset
            ui->tableWidget_2->model()->setData(ui->tableWidget_2->model()->index(selected_row+1,7),g);  //z offset

            //keep the moved line selected..
            QModelIndex next_index = ui->tableWidget_2->model()->index(selected_row+1, 0);
            ui->tableWidget_2->setCurrentIndex(next_index);

        }
        break; //take first selection..
    }
}

void Dialog_axis::on_pushButton_save_and_close_clicked()
{
    save_table();
    save_table2();
    load_selected_data();
    load_selected_data2();
    qDebug()<< "tools saved";
    Dialog_axis::close();
}
