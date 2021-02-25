#include "form.h"
#include "ui_form.h"
#include "QMap"
#include "servicescontext.h"
Form::Form(QWidget *parent) :
    DefaultWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
}

void Form::onLoad()
{
    QHash<QString , QImage *> *map = ServicesContext::getDataAccess()->getGists();
    QGraphicsScene* sceneYour = new QGraphicsScene();
    int green[255]={0};
    //создание гистограммы
    for (int y =0 ; y < cache->getOriginalImage()->height() ; y ++){
        for (int x = 0 ; x < cache->getOriginalImage()->width() ; x++) {
            green[cache->getOriginalImage()->pixelColor(x,y).green()]++;
        }
    }

    //найдем максимальное  гистограммы
    int maxGreen =0 ;
    for (int i = 0 ; i < 255; i++){
        if(maxGreen<green[i]) maxGreen = green[i];

    }

    //нормализация гитограммы нормализуем от 0 до 500
    for(int i = 0 ; i < 255 ;i++){
        green[i] = green[i]*500;
        green[i] = green[i]/maxGreen;
    }

    QImage greenGist = QPixmap(510,500).toImage();

    for (int x = 0 ; x  < greenGist.width() ; x++){
        for (int y = 0 ; y < greenGist.height(); y++){
            greenGist.setPixelColor(x,y,QColor(0,0,0,255));
        }
    }

    for (int i = 0 ; i < 500 ; i= i+2){
        for (int y = 0 ; y < green[i/2] ; y++ ){
            greenGist.setPixelColor(i,y,QColor(0,255,0,255));
            greenGist.setPixelColor(i+1,y,QColor(0,255,0,255));
        }
    }
    sceneYour->addPixmap(QPixmap::fromImage(greenGist));
    ui->yourt->setScene(sceneYour);
    QGraphicsScene* sceneNorm = new QGraphicsScene();
    sceneNorm->addPixmap(QPixmap::fromImage(*map->take("0")));
    ui->firstStury->setScene(sceneNorm);

    QGraphicsScene* sceneThread = new QGraphicsScene();
    sceneThread->addPixmap(QPixmap::fromImage(*map->take("3")));
    ui->threadStudy->setScene(sceneThread);

    QGraphicsScene* sceneForth= new QGraphicsScene();
    sceneForth->addPixmap(QPixmap::fromImage(*map->take("4")));
    ui->fortStudy->setScene(sceneForth);
}

QString *Form::getWidgetName()
{
    return new QString("gist form");
}

Form::~Form()
{
    delete ui;
}

void Form::on_returnButton_clicked()
{
    returnFromSubProcess();
}
