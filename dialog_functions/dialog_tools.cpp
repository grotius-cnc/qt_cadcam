#include "dialog_tools.h"
#include "ui_dialog_tools.h"
#include <QStandardItemModel>
#include <QStringList>
#include <QTreeWidget>
#include <QList>
#include <QStringList>
#include <QComboBox>
#include <QDebug>
#include <QDir>
#include <QItemSelectionModel>
#include <stdio.h>
#include <QCheckBox>
#include <core_functions/variables.h>

Dialog_tools::Dialog_tools(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_tools)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnWidth(1,175);
    ui->tableWidget->setAlternatingRowColors(true);
    load_table(); //initialise tool library..
}

Dialog_tools::~Dialog_tools()
{
    delete ui;
}

void Dialog_tools::on_pushButton_delete_clicked()
{
    QModelIndexList selection = ui->tableWidget->selectionModel()->selectedIndexes();
    for(int i=0; i< selection.count(); i++)
    {
        QModelIndex index = selection.at(i);
        //qDebug() << index.row();
        ui->tableWidget->removeRow(index.row());
    }
}

void Dialog_tools::on_pushButton_new_clicked()
{
    //qDebug() << ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());

    //create checkbox
    QTableWidgetItem* item;
    item = new QTableWidgetItem(true);
    item->setCheckState(Qt::Unchecked);
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0, item);                                              //select
    ui->tableWidget->model()->setData(ui->tableWidget->model()->index(ui->tableWidget->rowCount()-1,1),"name");   //description
    ui->tableWidget->model()->setData(ui->tableWidget->model()->index(ui->tableWidget->rowCount()-1,2),0.0);      //diameter
    ui->tableWidget->model()->setData(ui->tableWidget->model()->index(ui->tableWidget->rowCount()-1,3),0.0);      //power - rpm
    ui->tableWidget->model()->setData(ui->tableWidget->model()->index(ui->tableWidget->rowCount()-1,4),0.0);      //speed
    ui->tableWidget->model()->setData(ui->tableWidget->model()->index(ui->tableWidget->rowCount()-1,5),0.0);      //start delay
    ui->tableWidget->model()->setData(ui->tableWidget->model()->index(ui->tableWidget->rowCount()-1,6),0.0);      //start height
    ui->tableWidget->model()->setData(ui->tableWidget->model()->index(ui->tableWidget->rowCount()-1,7),0.0);      //cut height
    ui->tableWidget->model()->setData(ui->tableWidget->model()->index(ui->tableWidget->rowCount()-1,8),0.0);      //end delay
    ui->tableWidget->model()->setData(ui->tableWidget->model()->index(ui->tableWidget->rowCount()-1,9),0.0);      //plunge speed

}

void Dialog_tools::on_pushButton_save_clicked()
{
     save_table();
}

void Dialog_tools::on_pushButton_load_clicked()
{
    load_table();
}

void Dialog_tools::save_table()
{
    QFile file_out(QDir::currentPath() + "/cadcam/" + "tools.txt");
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
        stream << "diameter" << endl;
        stream << ui->tableWidget->item(i,2)->text() << endl;
        stream << "power - rpm" << endl;
        stream << ui->tableWidget->item(i,3)->text() << endl;
        stream << "cutspeed" << endl;
        stream << ui->tableWidget->item(i,4)->text() << endl;
        stream << "start delay" << endl;
        stream << ui->tableWidget->item(i,5)->text() << endl;
        stream << "start height" << endl;
        stream << ui->tableWidget->item(i,6)->text() << endl;
        stream << "cut height" << endl;
        stream << ui->tableWidget->item(i,7)->text() << endl;
        stream << "end delay" << endl;
        stream << ui->tableWidget->item(i,8)->text() << endl;
        stream << "plunge speed" << endl;
        stream << ui->tableWidget->item(i,9)->text() << endl;
        stream << "" << endl;
    }
    file_out.close();
}

void Dialog_tools::load_selected_data()  //load selected tool into extern program variable..
{
    int state = 0;
    int linenumber = 0;
    int select_line = 0;
    int description_line = 0;
    int diameter_line = 0;
    int power_rpm_line = 0;
    int cutspeed_line = 0;
    int start_delay_line = 0;
    int start_height_line = 0;
    int cut_height_line = 0;
    int end_delay_line = 0;
    int plunge_speed_line = 0;

    QFile file_in(QDir::currentPath() + "/cadcam/" + "tools.txt");
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
            extern_tool_description = line;
        }
        //diameter..
        if(line.contains("diameter", Qt::CaseSensitive) && state==2){
            diameter_line = linenumber + 1;
        }
        if(linenumber == diameter_line){
            extern_diameter = line;
        }
        //power rpm..
        if(line.contains("power - rpm", Qt::CaseSensitive) && state==2){
            power_rpm_line = linenumber + 1;
        }
        if(linenumber == power_rpm_line){
            extern_power_rpm = line;
        }
        //power speed..
        if(line.contains("cutspeed", Qt::CaseSensitive) && state==2){
            cutspeed_line = linenumber + 1;
        }
        if(linenumber == cutspeed_line){
            extern_cutspeed = line;
        }
        //start delay..
        if(line.contains("start delay", Qt::CaseSensitive) && state==2){
            start_delay_line = linenumber + 1;
        }
        if(linenumber == start_delay_line){
            extern_start_delay = line;
        }
        //start height..
        if(line.contains("start height", Qt::CaseSensitive) && state==2){
            start_height_line = linenumber + 1;
        }
        if(linenumber == start_height_line){
            extern_start_height = line;
        }
        //cut height..
        if(line.contains("cut height", Qt::CaseSensitive) && state==2){
            cut_height_line = linenumber + 1;
        }
        if(linenumber == cut_height_line){
            extern_cut_height = line;
        }
        //end delay..
        if(line.contains("end delay", Qt::CaseSensitive) && state==2){
            end_delay_line = linenumber + 1;
        }
        if(linenumber == end_delay_line){
            extern_end_delay = line;
        }
        //plunge speed..
        if(line.contains("plunge speed", Qt::CaseSensitive) && state==2){
            plunge_speed_line = linenumber + 1;
        }
        if(linenumber == plunge_speed_line){
            extern_plunge_speed = line;
        }
        linenumber++;
    }
    file_in.close();
}

void Dialog_tools::load_table()
{
    //qDebug() << "load tools";

    //empty tableview
    while(ui->tableWidget->rowCount() != 0){
        ui->tableWidget->removeRow(0);
    }

    //define ammount of tabble rows in file..
    int index_count = 0;
    QFile file_in(QDir::currentPath() + "/cadcam/" + "tools.txt");
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
        ui->tableWidget->model()->setData(ui->tableWidget->model()->index(i,0), 0);
        ui->tableWidget->model()->setData(ui->tableWidget->model()->index(i,1), "name");
        ui->tableWidget->model()->setData(ui->tableWidget->model()->index(i,2), 0.0);
        ui->tableWidget->model()->setData(ui->tableWidget->model()->index(i,3), 0.0);
        ui->tableWidget->model()->setData(ui->tableWidget->model()->index(i,4), 0.0);
        ui->tableWidget->model()->setData(ui->tableWidget->model()->index(i,5), 0.0);
        ui->tableWidget->model()->setData(ui->tableWidget->model()->index(i,6), 0.0);
        ui->tableWidget->model()->setData(ui->tableWidget->model()->index(i,7), 0.0);
        ui->tableWidget->model()->setData(ui->tableWidget->model()->index(i,8), 0.0);
        ui->tableWidget->model()->setData(ui->tableWidget->model()->index(i,9), 0.0);
    }

    //overwrite data from file to tableview..
    int linenumber = 0;
    int row = -1;
    int select_line = 0;
    int description_line = 0;
    int diameter_line = 0;
    int power_rpm_line = 0;
    int cutspeed_line = 0;
    int start_delay_line = 0;
    int start_height_line = 0;
    int cut_height_line = 0;
    int end_delay_line = 0;
    int plunge_speed_line = 0;

    QFile file_in1(QDir::currentPath() + "/cadcam/" + "tools.txt");
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
        //diameter..
        if(line.contains("diameter", Qt::CaseSensitive)){
            diameter_line = linenumber + 1;
        }
        if(linenumber == diameter_line){
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(row,2),line);
        }
        //power rpm..
        if(line.contains("power - rpm", Qt::CaseSensitive)){
            power_rpm_line = linenumber + 1;
        }
        if(linenumber == power_rpm_line){
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(row,3),line);
        }
        //power speed..
        if(line.contains("cutspeed", Qt::CaseSensitive)){
            cutspeed_line = linenumber + 1;
        }
        if(linenumber == cutspeed_line){
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(row,4),line);
        }
        //start delay..
        if(line.contains("start delay", Qt::CaseSensitive)){
            start_delay_line = linenumber + 1;
        }
        if(linenumber == start_delay_line){
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(row,5),line);
        }
        //start height..
        if(line.contains("start height", Qt::CaseSensitive)){
            start_height_line = linenumber + 1;
        }
        if(linenumber == start_height_line){
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(row,6),line);
        }
        //cut height..
        if(line.contains("cut height", Qt::CaseSensitive)){
            cut_height_line = linenumber + 1;
        }
        if(linenumber == cut_height_line){
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(row,7),line);
        }
        //end delay..
        if(line.contains("end delay", Qt::CaseSensitive)){
            end_delay_line = linenumber + 1;
        }
        if(linenumber == end_delay_line){
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(row,8),line);
        }
        //plunge speed..
        if(line.contains("plunge speed", Qt::CaseSensitive)){
            plunge_speed_line = linenumber + 1;
        }
        if(linenumber == plunge_speed_line){
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(row,9),line);

            //row increase after last tool item read in..
            row++;
        }
        linenumber++;

    }
    file_in1.close();
}

void Dialog_tools::on_pushButton_insert_clicked()
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
        ui->tableWidget->model()->setData(ui->tableWidget->model()->index(index.row(),2),0.0);      //diameter
        ui->tableWidget->model()->setData(ui->tableWidget->model()->index(index.row(),3),0.0);      //power - rpm
        ui->tableWidget->model()->setData(ui->tableWidget->model()->index(index.row(),4),0.0);      //cutspeed
        ui->tableWidget->model()->setData(ui->tableWidget->model()->index(index.row(),5),0.0);      //start delay
        ui->tableWidget->model()->setData(ui->tableWidget->model()->index(index.row(),6),0.0);      //start height
        ui->tableWidget->model()->setData(ui->tableWidget->model()->index(index.row(),7),0.0);      //cut height
        ui->tableWidget->model()->setData(ui->tableWidget->model()->index(index.row(),8),0.0);      //end delay
        ui->tableWidget->model()->setData(ui->tableWidget->model()->index(index.row(),9),0.0);      //plunge speed

        break; //one row each time..
    }
}

void Dialog_tools::on_toolButton_move_up_clicked()
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
            QString temp_description = ui->tableWidget->item(selected_row,1)->text();
            QString temp_diameter = ui->tableWidget->item(selected_row,2)->text();
            QString temp_power = ui->tableWidget->item(selected_row,3)->text();
            QString temp_cutspeed = ui->tableWidget->item(selected_row,4)->text();
            QString temp_start_delay = ui->tableWidget->item(selected_row,5)->text();
            QString temp_start_height = ui->tableWidget->item(selected_row,6)->text();
            QString temp_cut_height = ui->tableWidget->item(selected_row,7)->text();
            QString temp_end_delay = ui->tableWidget->item(selected_row,8)->text();
            QString temp_plunge_speed = ui->tableWidget->item(selected_row,9)->text();

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
            ui->tableWidget->setItem(selected_row-1,0, item);                                                       //select
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(selected_row-1,1),temp_description);  //description
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(selected_row-1,2),temp_diameter);     //diameter
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(selected_row-1,3),temp_power);        //power - rpm
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(selected_row-1,4),temp_cutspeed);     //cutspeed
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(selected_row-1,5),temp_start_delay);  //start delay
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(selected_row-1,6),temp_start_height); //start height
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(selected_row-1,7),temp_cut_height);   //cut height
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(selected_row-1,8),temp_end_delay);    //end delay
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(selected_row-1,9),temp_plunge_speed); //plunge speed

            //keep the moved line selected..
            QModelIndex next_index = ui->tableWidget->model()->index(selected_row-1, 0);
            ui->tableWidget->setCurrentIndex(next_index);
            }

        }
        break; //take first selection..
    }
}

void Dialog_tools::on_toolButton_move_down_clicked()
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
            QString temp_description = ui->tableWidget->item(selected_row,1)->text();
            QString temp_diameter = ui->tableWidget->item(selected_row,2)->text();
            QString temp_power = ui->tableWidget->item(selected_row,3)->text();
            QString temp_cutspeed = ui->tableWidget->item(selected_row,4)->text();
            QString temp_start_delay = ui->tableWidget->item(selected_row,5)->text();
            QString temp_start_height = ui->tableWidget->item(selected_row,6)->text();
            QString temp_cut_height = ui->tableWidget->item(selected_row,7)->text();
            QString temp_end_delay = ui->tableWidget->item(selected_row,8)->text();
            QString temp_plunge_speed = ui->tableWidget->item(selected_row,9)->text();

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
            ui->tableWidget->setItem(selected_row+1,0, item);                                                       //select
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(selected_row+1,1),temp_description);  //description
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(selected_row+1,2),temp_diameter);     //diameter
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(selected_row+1,3),temp_power);        //power - rpm
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(selected_row+1,4),temp_cutspeed);     //cutspeed
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(selected_row+1,5),temp_start_delay);  //start delay
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(selected_row+1,6),temp_start_height); //start height
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(selected_row+1,7),temp_cut_height);   //cut height
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(selected_row+1,8),temp_end_delay);    //end delay
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(selected_row+1,9),temp_plunge_speed); //plunge speed

            //keep the moved line selected..
            QModelIndex next_index = ui->tableWidget->model()->index(selected_row+1, 0);
            ui->tableWidget->setCurrentIndex(next_index);

        }
        break; //take first selection..
    }
}

void Dialog_tools::on_pushButton_save_and_close_clicked()
{
    save_table();
    load_selected_data();
    qDebug()<< "tools saved";
    Dialog_tools::close();
}
