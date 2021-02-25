#include "recongnizerschain.h"


QString* RecongnizersChain::FIRST   = new QString("1");
QString* RecongnizersChain::SECOND  =new QString("2");
QString* RecongnizersChain::THREARD = new QString("3");
QString* RecongnizersChain::FORTH   = new QString("4");
QString* RecongnizersChain::FIFT    =new QString("5");

RecongnizersChain::RecongnizersChain()
{
}

QList<Acinus*> *RecongnizersChain::doChain(vector<QHash<int, PixelType> *> *objects,QImage* image)
{
    logger->info("enter to object recognizers");
    QList<Acinus*> *acinusList = new QList<Acinus*>();
    for(int i = 0 ; i < objects->size(); i++){
        acinusList->append(doRecognize(objects->at(i),image));
    }
    return acinusList;
}

Acinus *RecongnizersChain::doRecognize(QHash<int, PixelType> *acunusArea,QImage* image)
{
    Acinus *acinus = new Acinus();
    acinus->acunusArea = acunusArea;
    for(int i = 0 ; i < recognizers->size(); i++){
        recognizers->at(i)->doRecognize(acinus,image);
    }
    return acinus;
}
