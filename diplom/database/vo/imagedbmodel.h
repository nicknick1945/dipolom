#ifndef IMAGEDBMODEL_H
#define IMAGEDBMODEL_H
#include "qimage.h"

class ImageDbModel
{
public:
    ImageDbModel();
    QImage *image;
    int id;
    double secondStadyAcinusPersont;
    double threadStadyAcinusPersent;
    double firstStadyAcinusPersent;
    double forthStadyAcinusPersent;
    double fiftStudyAcinusPersent;
    QString cancerstady;

};

#endif // IMAGEDBMODEL_H
