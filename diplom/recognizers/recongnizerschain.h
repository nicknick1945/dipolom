#ifndef RECONGNIZERSCHAIN_H
#define RECONGNIZERSCHAIN_H

#include "abstractrecognizer.h"
#include "qimage.h"




class RecongnizersChain : public HasLogger
{
public:
    static QString* FIRST;
    static QString* SECOND;
    static QString* THREARD;
    static QString* FORTH;
    static QString* FIFT;

    RecongnizersChain();
    QList<Acinus*>* doChain(vector<QHash<int,PixelType>*> *objects,QImage* image);
    Acinus* doRecognize(QHash<int,PixelType> *acunusArea,QImage* image);
    QList<AbstractRecognizer*> *recognizers = new QList<AbstractRecognizer*>();
};

#endif // RECONGNIZERSCHAIN_H
