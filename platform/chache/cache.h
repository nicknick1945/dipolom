#ifndef CACHE_H
#define CACHE_H
#include "qhash.h"
#include "qimage.h"
#include <diplom/recognizers/acinus.h>
#include <diplom/database/vo/imagedbmodel.h>
class Cache
{
public:
    Cache();
    int result=0;
    QImage * getOriginalImage();
    QImage * getTempImage();
    void setOriginalImage(QImage * image);
    void setTempImage(QImage* image);
    void setAcinusList(QList<Acinus*> *acinusList);
    QList<Acinus*> * getAcinusList();
    ImageDbModel* getImageDbModel();
    void setImageDbModel(ImageDbModel* imageDbModel);
private:
    QList<Acinus*> *acinusList=NULL;
    QImage * tempImage=NULL;
    QImage *originalImage=NULL;
    ImageDbModel* imageDbModel=NULL;
};

#endif // CACHE_H
