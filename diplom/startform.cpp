#include "startform.h"
#include "ui_startform.h"
#include "QString"
#include "platform/utils.h"
#include "QGraphicsScene"
#include "qfiledialog.h"
#include "qpixmap.h"
#include "servicescontext.h"
#include "platform/utils.h"

StartForm::StartForm(QWidget *parent) :
    DefaultWidget(parent),
    ui(new Ui::StartForm)
{
    ui->setupUi(this);
}

QString *StartForm::getWidgetName()
{
    return new QString("startFrom");
}

StartForm::~StartForm()
{
    delete ui;
}

void StartForm::on_downloadImageButton_clicked()
{
    QString imagePath = QFileDialog::getOpenFileName();
    QImage *originalImage = Utils::loadImage(imagePath); 
    ui->resultLable->setText("");
    cache->setOriginalImage(originalImage);
    QGraphicsScene* scene = new QGraphicsScene();
    scene->addPixmap(QPixmap::fromImage(*originalImage));
    ui->graphicsView->setScene(scene);
    cache->setOriginalImage(originalImage);
}


void StartForm::on_fileterButton_clicked()
{
    QGraphicsScene* scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);
    int filterTreshold = ui->tresholdSpinBox->value();
    QImage *image  = cache->getTempImage();
    vector<QHash<int,PixelType>*>* objects =  ServicesContext::getMySuperFiler()->doFilter(*cache->getTempImage(),filterTreshold);
    Utils::doDelatation(cache->getTempImage());
    objects =  ServicesContext::getMySuperFiler()->doFilter(*cache->getTempImage(),filterTreshold);
    QList<Acinus*> *acinusList = ServicesContext::getRecognizerChain()->doChain(objects,image);
    ImageDbModel* imageDbModel = ServicesContext::getAttribyteREcognizer()->findAttributes(cache->getOriginalImage(),acinusList);
    delete cache->getImageDbModel();
    cache->setImageDbModel(imageDbModel);
    cache->setAcinusList(acinusList);
    QString results = "";
    results.append("стадия рака:")
            .append(imageDbModel->cancerstady).append("\n")
            .append("процент клеток первой:").append(QString::number(imageDbModel->firstStadyAcinusPersent)).append("\n")
            .append("процент клеток второй:").append(QString::number(imageDbModel->secondStadyAcinusPersont)).append("\n")
            .append("процент клеток третей:").append(QString::number(imageDbModel->threadStadyAcinusPersent)).append("\n")
            .append("процент клеток четвертой:").append(QString::number(imageDbModel->forthStadyAcinusPersent)).append("\n")
            .append("процент клеток пятой:").append(QString::number(imageDbModel->fiftStudyAcinusPersent)).append("\n");
    ui->resultLable->setText(results);
    scene->addPixmap(QPixmap::fromImage(*cache->getTempImage()));

}

void StartForm::on_binarizationButton_clicked()
{
    QImage *image = new QImage(*cache->getOriginalImage());
    int filterTreshold = ui->binarizationSpinBox->value();
    ServicesContext::getBiarizer()->doBinary(image,filterTreshold);
    cache->setTempImage(image);
    QGraphicsScene* scene = new QGraphicsScene();
    scene->addPixmap(QPixmap::fromImage(*cache->getTempImage()));
    ui->graphicsView->setScene(scene);
}

void StartForm::on_allAcinusButton_clicked()
{
    prepareAcinusToImage(new QString("all"),true);
}

void StartForm::on_healthAcinusButton_clicked()
{
    prepareAcinusToImage(RecongnizersChain::FIRST);
}

void StartForm::on_threadGlissonButton_clicked()
{
    prepareAcinusToImage(RecongnizersChain::THREARD);
}

void StartForm::on_forthGlissonButton_clicked()
{
    prepareAcinusToImage(RecongnizersChain::FORTH);
}

void StartForm::prepareAcinusToImage(QString *type,bool all)
{
    QGraphicsScene* scene = new QGraphicsScene();
    QList<Acinus*> *acinusList = cache->getAcinusList();
    QImage image(*cache->getOriginalImage());
    for (int i = 0 ; i < acinusList->size() ; i++){
        if (all||acinusList->at(i)->acinusSign->contains(type)){
        Utils::prepareColorByCordsToImage(image,000,acinusList->at(i)->acunusArea);
        }
    }
    scene->addPixmap(QPixmap::fromImage(image));
    ui->graphicsView->setScene(scene);
}

void StartForm::on_findAnalogInDb_clicked()
{
    goToSubProcess("result form");
}

void StartForm::onReturnFromSubProcess()
{
    QGraphicsScene* scene = new QGraphicsScene();
    scene->addPixmap(QPixmap::fromImage(*cache->getOriginalImage()));
    ui->graphicsView->setScene(scene);
}

void StartForm::on_pushButton_clicked()
{
    ServicesContext::getDataAccess()->saveModel(cache->getImageDbModel());
}

void StartForm::on_gistButton_clicked()
{
    goToSubProcess("gist form");
}
