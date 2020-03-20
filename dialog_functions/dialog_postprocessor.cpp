#include "dialog_postprocessor.h"
#include "ui_dialog_postprocessor.h"
#include <core_functions/variables.h>

Dialog_postprocessor::Dialog_postprocessor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_postprocessor)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnWidth(1,175);
    ui->tableWidget->setAlternatingRowColors(true);
    load_table(); //initialise postprocessor library..
}

Dialog_postprocessor::~Dialog_postprocessor()
{
    delete ui;
}

void Dialog_postprocessor::on_pushButton_new_clicked()
{
    //qDebug() << ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    ui->tableWidget->setRowHeight(ui->tableWidget->rowCount()-1,50);

    //create checkbox
    QTableWidgetItem* item;
    item = new QTableWidgetItem(true);
    item->setCheckState(Qt::Unchecked);
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0, item);                                                                    //select
    ui->tableWidget->model()->setData(ui->tableWidget->model()->index(ui->tableWidget->rowCount()-1,1),"name");                         //description
    //create checkbox
    QTableWidgetItem* item1;
    item1 = new QTableWidgetItem(true);
    item1->setCheckState(Qt::Unchecked);
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,2, item1);                                                                   //display line nr
    ui->tableWidget->model()->setData(ui->tableWidget->model()->index(ui->tableWidget->rowCount()-1,3),"G21 G40 G90 G64P01 F1 S1");     //gcode intro
    ui->tableWidget->model()->setData(ui->tableWidget->model()->index(ui->tableWidget->rowCount()-1,4),"M30");                          //gcode outro
    ui->tableWidget->model()->setData(ui->tableWidget->model()->index(ui->tableWidget->rowCount()-1,5),"G0");                           //rapid move
    ui->tableWidget->model()->setData(ui->tableWidget->model()->index(ui->tableWidget->rowCount()-1,6),"G1");                           //lineair move
    ui->tableWidget->model()->setData(ui->tableWidget->model()->index(ui->tableWidget->rowCount()-1,7),"G2");                           //circle cw
    ui->tableWidget->model()->setData(ui->tableWidget->model()->index(ui->tableWidget->rowCount()-1,8),"G3");                           //circle ccw
    ui->tableWidget->model()->setData(ui->tableWidget->model()->index(ui->tableWidget->rowCount()-1,9),"G5.1");                         //quadratic spline
    ui->tableWidget->model()->setData(ui->tableWidget->model()->index(ui->tableWidget->rowCount()-1,10),"G4 P");                        //spindle delay
    ui->tableWidget->model()->setData(ui->tableWidget->model()->index(ui->tableWidget->rowCount()-1,11),"T");                           //tool
    ui->tableWidget->model()->setData(ui->tableWidget->model()->index(ui->tableWidget->rowCount()-1,12),"F");                           //feedrate
}

void Dialog_postprocessor::on_pushButton_insert_new_clicked()
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
        ui->tableWidget->setItem(index.row(),0, item);                                                                      //select
        ui->tableWidget->model()->setData(ui->tableWidget->model()->index(index.row(),1),"name");                           //description
        //create checkbox
        QTableWidgetItem* item1;
        item1 = new QTableWidgetItem(true);
        item1->setCheckState(Qt::Unchecked);
        ui->tableWidget->setItem(index.row(),2, item1);                                                                     //display line nr
        ui->tableWidget->model()->setData(ui->tableWidget->model()->index(index.row(),3),"G21 G40 G90 G64P01 F1 S1");       //gcode intro
        ui->tableWidget->model()->setData(ui->tableWidget->model()->index(index.row(),4),"M30");                            //gcode outro
        ui->tableWidget->model()->setData(ui->tableWidget->model()->index(index.row(),5),"G0");                             //rapid move
        ui->tableWidget->model()->setData(ui->tableWidget->model()->index(index.row(),6),"G1");                             //lineair move
        ui->tableWidget->model()->setData(ui->tableWidget->model()->index(index.row(),7),"G2");                             //circle cw
        ui->tableWidget->model()->setData(ui->tableWidget->model()->index(index.row(),8),"G3");                             //circle ccw
        ui->tableWidget->model()->setData(ui->tableWidget->model()->index(index.row(),9),"G5.1");                           //quadratic spline
        ui->tableWidget->model()->setData(ui->tableWidget->model()->index(index.row(),10),"G4 P");                          //spindle delay
        ui->tableWidget->model()->setData(ui->tableWidget->model()->index(index.row(),11),"T");                             //tool
        ui->tableWidget->model()->setData(ui->tableWidget->model()->index(index.row(),12),"F");                             //feedrate
        break; //one row each time..
    }
}

void Dialog_postprocessor::on_toolButton_move_up_clicked()
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
            int temp_state1 = ui->tableWidget->item(selected_row,2)->checkState();
            QString temp_intro = ui->tableWidget->item(selected_row,3)->text();
            QString temp_outro = ui->tableWidget->item(selected_row,4)->text();
            QString temp_rapid = ui->tableWidget->item(selected_row,5)->text();
            QString temp_linear = ui->tableWidget->item(selected_row,6)->text();
            QString temp_cw = ui->tableWidget->item(selected_row,7)->text();
            QString temp_ccw = ui->tableWidget->item(selected_row,8)->text();
            QString temp_spline = ui->tableWidget->item(selected_row,9)->text();
            QString temp_delay = ui->tableWidget->item(selected_row,10)->text();
            QString temp_tool = ui->tableWidget->item(selected_row,11)->text();
            QString temp_feedrate = ui->tableWidget->item(selected_row,12)->text();

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

            QTableWidgetItem* item1;
            item1 = new QTableWidgetItem(true);
            if(temp_state1==0){
                item1->setCheckState(Qt::Unchecked);
            }
            if(temp_state1==2){
                item1->setCheckState(Qt::Checked);
            }
            ui->tableWidget->setItem(selected_row-1,2, item1);                                                      //display line nr

            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(selected_row-1,3),temp_intro);        //gcode intro
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(selected_row-1,4),temp_outro);        //gcode outro
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(selected_row-1,5),temp_rapid);        //rapid move
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(selected_row-1,6),temp_linear);       //lineair move
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(selected_row-1,7),temp_cw);           //circle cw
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(selected_row-1,8),temp_ccw);          //circle ccw
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(selected_row-1,9),temp_spline);       //quadratic spline
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(selected_row-1,10),temp_delay);       //spindle delay
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(selected_row-1,11),temp_tool);        //tool
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(selected_row-1,12),temp_feedrate);     //feedrate

            //keep the moved line selected..
            QModelIndex next_index = ui->tableWidget->model()->index(selected_row-1, 0);
            ui->tableWidget->setCurrentIndex(next_index);
            }

        }
        break; //take first selection..
    }
}

void Dialog_postprocessor::on_toolButton_move_down_clicked()
{
    QModelIndexList selection = ui->tableWidget->selectionModel()->selectedIndexes();
    for(int i=0; i< selection.count(); i++)
    {
        int j = ui->tableWidget->rowCount();
        if(selection.count()>0 && ui->tableWidget->currentIndex().row() < j-1){ //prevent deleting last table line..

            int selected_row = ui->tableWidget->currentIndex().row();
            //qDebug()<< "selected row : " << selected_row;

            //add current selected row to temp..
            //add current selected row to temp..
            int temp_state = ui->tableWidget->item(selected_row,0)->checkState();
            QString temp_description = ui->tableWidget->item(selected_row,1)->text();
            int temp_state1 = ui->tableWidget->item(selected_row,2)->checkState();
            QString temp_intro = ui->tableWidget->item(selected_row,3)->text();
            QString temp_outro = ui->tableWidget->item(selected_row,4)->text();
            QString temp_rapid = ui->tableWidget->item(selected_row,5)->text();
            QString temp_linear = ui->tableWidget->item(selected_row,6)->text();
            QString temp_cw = ui->tableWidget->item(selected_row,7)->text();
            QString temp_ccw = ui->tableWidget->item(selected_row,8)->text();
            QString temp_spline = ui->tableWidget->item(selected_row,9)->text();
            QString temp_delay = ui->tableWidget->item(selected_row,10)->text();
            QString temp_tool = ui->tableWidget->item(selected_row,11)->text();
            QString temp_feedrate = ui->tableWidget->item(selected_row,12)->text();

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

            QTableWidgetItem* item1;
            item1 = new QTableWidgetItem(true);
            if(temp_state1==0){
                item1->setCheckState(Qt::Unchecked);
            }
            if(temp_state1==2){
                item1->setCheckState(Qt::Checked);
            }
            ui->tableWidget->setItem(selected_row+1,2, item1);                                                      //display line nr

            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(selected_row+1,3),temp_intro);        //gcode intro
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(selected_row+1,4),temp_outro);        //gcode outro
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(selected_row+1,5),temp_rapid);        //rapid move
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(selected_row+1,6),temp_linear);       //lineair move
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(selected_row+1,7),temp_cw);           //circle cw
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(selected_row+1,8),temp_ccw);          //circle ccw
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(selected_row+1,9),temp_spline);       //quadratic spline
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(selected_row+1,10),temp_delay);       //spindle delay
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(selected_row+1,11),temp_tool);        //tool
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(selected_row+1,12),temp_tool);        //feedrate

            //keep the moved line selected..
            QModelIndex next_index = ui->tableWidget->model()->index(selected_row+1, 0);
            ui->tableWidget->setCurrentIndex(next_index);

        }
        break; //take first selection..
    }
}

void Dialog_postprocessor::on_pushButton_delete_clicked()
{
    QModelIndexList selection = ui->tableWidget->selectionModel()->selectedIndexes();
    for(int i=0; i< selection.count(); i++)
    {
        QModelIndex index = selection.at(i);
        //qDebug() << index.row();
        ui->tableWidget->removeRow(index.row());
    }
}

void Dialog_postprocessor::save_table()
{
    QFile file_out(QDir::currentPath() + "/cadcam/" + "postprocessor.txt");
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

        stream << "display line nr" << endl;
        stream << ui->tableWidget->item(i,2)->checkState() << endl; //0 is off, 2 is on..

        stream << "gcode intro" << endl;
        stream << ui->tableWidget->item(i,3)->text() << endl;
        stream << "gcode outro" << endl;
        stream << ui->tableWidget->item(i,4)->text() << endl;
        stream << "rapid move" << endl;
        stream << ui->tableWidget->item(i,5)->text() << endl;
        stream << "lineair move" << endl;
        stream << ui->tableWidget->item(i,6)->text() << endl;
        stream << "circle cw" << endl;
        stream << ui->tableWidget->item(i,7)->text() << endl;
        stream << "circle ccw" << endl;
        stream << ui->tableWidget->item(i,8)->text() << endl;
        stream << "quadratic spline" << endl;
        stream << ui->tableWidget->item(i,9)->text() << endl;
        stream << "spindle delay" << endl;
        stream << ui->tableWidget->item(i,10)->text() << endl;
        stream << "tool" << endl;
        stream << ui->tableWidget->item(i,11)->text() << endl;
        stream << "feedrate" << endl;
        stream << ui->tableWidget->item(i,12)->text() << endl;
        stream << "" << endl;
    }
    file_out.close();
}

void Dialog_postprocessor::load_table()
{
    //qDebug() << "load tools";

    //empty tableview
    while(ui->tableWidget->rowCount() != 0){
        ui->tableWidget->removeRow(0);
    }

    //define ammount of tabble rows in file..
    int index_count = 0;
    QFile file_in(QDir::currentPath() + "/cadcam/" + "postprocessor.txt");
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
        ui->tableWidget->model()->setData(ui->tableWidget->model()->index(i,1), "");
        ui->tableWidget->model()->setData(ui->tableWidget->model()->index(i,2), 0);
        ui->tableWidget->model()->setData(ui->tableWidget->model()->index(i,3), "");
        ui->tableWidget->model()->setData(ui->tableWidget->model()->index(i,4), "");
        ui->tableWidget->model()->setData(ui->tableWidget->model()->index(i,5), "");
        ui->tableWidget->model()->setData(ui->tableWidget->model()->index(i,6), "");
        ui->tableWidget->model()->setData(ui->tableWidget->model()->index(i,7), "");
        ui->tableWidget->model()->setData(ui->tableWidget->model()->index(i,8), "");
        ui->tableWidget->model()->setData(ui->tableWidget->model()->index(i,9), "");
        ui->tableWidget->model()->setData(ui->tableWidget->model()->index(i,10), 0.0);
        ui->tableWidget->model()->setData(ui->tableWidget->model()->index(i,11), 0);
        ui->tableWidget->model()->setData(ui->tableWidget->model()->index(i,12), 0.0);
    }

    //overwrite data from file to tableview..
    int linenumber = 0;
    int row = -1;
    int select_line = 0;
    int description_line = 0;
    int select1_line = 0;
    int intro_line = 0;
    int outro_line = 0;
    int rapid_line = 0;
    int lineair_line = 0;
    int cw_line = 0;
    int ccw_line = 0;
    int spline_line = 0;
    int delay_line = 0;
    int tool_line = 0;
    int feedrate_line = 0;

    QFile file_in1(QDir::currentPath() + "/cadcam/" + "postprocessor.txt");
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

        //checkbox1..
        if(line.contains("display line nr", Qt::CaseSensitive)){
            select1_line = linenumber + 1;
        }
        if(linenumber == select1_line){
            int state = line.toInt();
            //create checkbox
            QTableWidgetItem* item1;
            item1 = new QTableWidgetItem(true);
            if(state == 0){
                item1->setCheckState(Qt::Unchecked);
            }
            if(state == 2){
                item1->setCheckState(Qt::Checked);
            }
            ui->tableWidget->setItem(row,2, item1);
        }


        //gcode intro..
        if(line.contains("gcode intro", Qt::CaseSensitive)){
            intro_line = linenumber + 1;
        }
        if(linenumber == intro_line){
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(row,3),line);
        }
        //gcode outro..
        if(line.contains("gcode outro", Qt::CaseSensitive)){
            outro_line = linenumber + 1;
        }
        if(linenumber == outro_line){
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(row,4),line);
        }
        //rapid move..
        if(line.contains("rapid move", Qt::CaseSensitive)){
            rapid_line = linenumber + 1;
        }
        if(linenumber == rapid_line){
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(row,5),line);
        }
        //lineair move..
        if(line.contains("lineair move", Qt::CaseSensitive)){
            lineair_line = linenumber + 1;
        }
        if(linenumber == lineair_line){
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(row,6),line);
        }
        //circle cw..
        if(line.contains("circle cw", Qt::CaseSensitive)){
            cw_line = linenumber + 1;
        }
        if(linenumber == cw_line){
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(row,7),line);
        }
        //circle ccw.
        if(line.contains("circle ccw", Qt::CaseSensitive)){
            ccw_line = linenumber + 1;
        }
        if(linenumber == ccw_line){
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(row,8),line);
        }
        //quadratic spline..
        if(line.contains("quadratic spline", Qt::CaseSensitive)){
            spline_line = linenumber + 1;
        }
        if(linenumber == spline_line){
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(row,9),line);
        }
        //spindle delay..
        if(line.contains("spindle delay", Qt::CaseSensitive)){
            delay_line = linenumber + 1;
        }
        if(linenumber == delay_line){
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(row,10),line);
        }
        //tool..
        if(line.contains("tool", Qt::CaseSensitive)){
            tool_line = linenumber + 1;
        }
        if(linenumber == tool_line){
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(row,11),line);
        }
        //feedrate..
        if(line.contains("feedrate", Qt::CaseSensitive)){
            feedrate_line = linenumber + 1;
        }
        if(linenumber == feedrate_line){
            ui->tableWidget->model()->setData(ui->tableWidget->model()->index(row,12),line);

            //row increase after last tool item read in..
            row++;
        }
        linenumber++;
    }
    file_in1.close();
}

void Dialog_postprocessor::load_selected_data()  //load selected data into extern program variable..
{
    int state = 0;
    int state1 = 0;
    int linenumber = 0;
    int select_line = 0;
    int description_line = 0;
    int select1_line = 0;
    int intro_line = 0;
    int outro_line = 0;
    int rapid_line = 0;
    int lineair_line = 0;
    int cw_line = 0;
    int ccw_line = 0;
    int spline_line = 0;
    int delay_line = 0;
    int tool_line = 0;
    int feedrate_line = 0;

    QFile file_in(QDir::currentPath() + "/cadcam/" + "postprocessor.txt");
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

        //description..
        if(line.contains("description", Qt::CaseSensitive) && state==2){
            description_line = linenumber + 1;
        }
        if(linenumber == description_line){
            extern_post_description = line;
        }

        //checkbox1..
        if(line.contains("display line nr", Qt::CaseSensitive) && state==2){
            select1_line = linenumber + 1;
        }
        if(linenumber == select1_line){
            state1 = line.toInt();
            //create checkbox
            QTableWidgetItem* item1;
            item1 = new QTableWidgetItem(true);
            if(state1 == 0){
                extern_display_line_nr = 0;
            }
            if(state1 == 2){
                extern_display_line_nr = 1;
            }
        }

        //gcode intro..
        if(line.contains("gcode intro", Qt::CaseSensitive) && state==2){
            intro_line = linenumber + 1;
        }
        if(linenumber == intro_line){
            //extern_gcode_intro = line;
        }
        //gcode outro..
        if(line.contains("gcode outro", Qt::CaseSensitive) && state==2){
            outro_line = linenumber + 1;
        }
        if(linenumber == outro_line){
            //extern_gcode_outro = line;
        }
        //rapid move..
        if(line.contains("rapid move", Qt::CaseSensitive) && state==2){
            rapid_line = linenumber + 1;
        }
        if(linenumber == rapid_line){
            extern_rapid_move_sign = line;
        }
        //lineair move..
        if(line.contains("lineair move", Qt::CaseSensitive) && state==2){
            lineair_line = linenumber + 1;
        }
        if(linenumber == lineair_line){
            extern_lineair_move_sign = line;
        }
        //circle cw..
        if(line.contains("circle cw", Qt::CaseSensitive) && state==2){
            cw_line = linenumber + 1;
        }
        if(linenumber == cw_line){
            extern_circle_cw_sign = line;
        }
        //circle ccw.
        if(line.contains("circle ccw", Qt::CaseSensitive) && state==2){
            ccw_line = linenumber + 1;
        }
        if(linenumber == ccw_line){
            extern_circle_ccw_sign = line;
        }
        //quadratic spline..
        if(line.contains("quadratic spline", Qt::CaseSensitive) && state==2){
            spline_line = linenumber + 1;
        }
        if(linenumber == spline_line){
            extern_quadratic_spline_sign = line;
        }
        //spindle delay..
        if(line.contains("spindle delay", Qt::CaseSensitive) && state==2){
            delay_line = linenumber + 1;
        }
        if(linenumber == delay_line){
            extern_spindle_delay_sign = line;
        }
        //tool..
        if(line.contains("tool", Qt::CaseSensitive) && state==2){
            tool_line = linenumber + 1;
        }
        if(linenumber == tool_line){
            extern_tool_sign = line;
        }
        //feedrate..
        if(line.contains("feedrate", Qt::CaseSensitive) && state==2){
            feedrate_line = linenumber + 1;
        }
        if(linenumber == feedrate_line){
            extern_feedrate_sign = line;
        }
        linenumber++;
    }
    file_in.close();
}

void Dialog_postprocessor::on_pushButton_save_and_close_clicked()
{
    save_table();
    load_selected_data();
    Dialog_postprocessor::close();
}


void Dialog_postprocessor::on_pushButton_load_clicked()
{
    load_table();
}

void Dialog_postprocessor::on_pushButton_save_clicked()
{
    save_table();
    load_selected_data();
}
