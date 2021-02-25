#include "resultfrom.h"
#include "ui_resultfrom.h"
#include "qstring.h"
#include "servicescontext.h"

ResultFrom::ResultFrom(QWidget *parent) :
    DefaultWidget(parent),
    ui(new Ui::ResultFrom)
{
    ui->setupUi(this);
}

void ResultFrom::onLoad()
{
    fromDbList = ServicesContext::getDataAccess()->getNearestModel(cache->getImageDbModel());
    iter= 0;
    if(!fromDbList->isEmpty()){
        setImageToSceneFromBd(fromDbList->at(0)->image);
        setImageToScene();
    }
}

QString *ResultFrom::getWidgetName()
{
    return new QString("result form");
}

ResultFrom::~ResultFrom()
{
    delete ui;
}

void ResultFrom::on_pushButton_clicked()
{
    returnFromSubProcess();
}

void ResultFrom::on_nextImageButton_clicked(){
    if((iter+1)<fromDbList->size()){
        iter = iter+1;
        setImageToSceneFromBd(fromDbList->at(iter)->image);
    }
}

void ResultFrom::setImageToSceneFromBd(QImage *image){
    QGraphicsScene* scene = new QGraphicsScene();
    scene->addPixmap(QPixmap::fromImage(*image));
    ui->graphicsView_2->setScene(scene);
}

void ResultFrom::setImageToScene(){
    QGraphicsScene* scene = new QGraphicsScene();
    scene->addPixmap(QPixmap::fromImage(*cache->getOriginalImage()));
    ui->graphicsView->setScene(scene);
}



void ResultFrom::on_previousImageButton_clicked()
{
    if(iter-1>=0){
        iter = iter-1;
        setImageToSceneFromBd(fromDbList->at(iter)->image);
    }
}
