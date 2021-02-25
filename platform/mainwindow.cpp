#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "logger/loggerfactory.h"
#include "logger/logger.h"
#include "QFileDialog"
#include "qpixmap.h"
#include "defaultwidget.h"
#include "QGraphicsPixmapItem"
#include "qfiledialog.h"
#include "defaultwidgetmodel.h"
#include <functional>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    ui->setupUi(this);
    ui->previous->hide();
    ui->nextButton->hide();
    widgets = new QList<DefaultWidgetModel*>();
    subProcesses = new QHash<QString,DefaultWidgetModel*>();
}

void MainWindow::lockNextNutton()
{
    ui->nextButton->setEnabled(false);
}

void MainWindow::unlockNextButton()
{
    ui->nextButton->setEnabled(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::goToSubProcess(QString subProcessName)
{
    if(subProcesses->contains(subProcessName)){
        widgets->at(currentWidgetNumber)->close();
        QString message = "sub Process name ";
        message.append(subProcessName);
        logger->debug(message);
        currentSubProcessName = new QString(subProcessName);
        subProcesses->value(subProcessName)->show();

    }else {
        logger->error("sub process not found");
    }
}

void MainWindow::returnFromSubProcess()
{
    if(subProcesses->contains(*currentSubProcessName)){
        subProcesses->value(*currentSubProcessName)->close();
        QString message = "return form subprocess name ";
        message.append(*currentSubProcessName);
        logger->debug(message);
        widgets->at(currentWidgetNumber)->onReturnFromSubProcess();
    }else {
        logger->error("mega error nu vse trendec");
    }
}

void MainWindow::setWidgetsGeometry(DefaultWidgetModel &widget){
    widget.widget->setMainWindow(this);
    widget.setGeometry(30,30,900,560);
    widget.close();
}

void MainWindow::next()
{
    for(int i = 0 ; i < widgets->size() ; i ++ ){
        widgets->at(i)->close();
    }
    ui->previous->show();
    widgets->at(currentWidgetNumber+1)->show();
    if(currentWidgetNumber+1 == widgets->size()-1){
        ui->nextButton->hide();
    }
    currentWidgetNumber = currentWidgetNumber+1;
    this->update();
}

MainWindow *MainWindow::addWidgets(DefaultWidgetModel *model){
     widgets->append(model);
     setWidgetsGeometry(*model);
     if(widgets->size()==1){
         model->show();
     }

     if(widgets->size()==2){
         ui->nextButton->show();
     }


}

MainWindow *MainWindow::addSupProcess(DefaultWidgetModel *model)
{
    subProcesses->insert(*model->widget->getWidgetName(),model);
    setWidgetsGeometry(*model);
}



void MainWindow::on_nextButton_clicked(){
    next();
}

void MainWindow::on_previous_clicked(){
    for(int i = 0 ; i < widgets->size() ; i ++ ){
        widgets->at(i)->close();
    }
    ui->nextButton->show();
    widgets->at(currentWidgetNumber-1)->show();
    if(currentWidgetNumber-1 == 0){
        ui->previous->close();
    }
    currentWidgetNumber = currentWidgetNumber-1;
    this->update();
}

