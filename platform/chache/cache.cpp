#include "cache.h"
#include "QHash"
#include "qimage.h"
using namespace std;

Cache::Cache()
{
}

QImage *Cache::getOriginalImage()
{
    return originalImage;
}

QImage *Cache::getTempImage(){
    return tempImage;
}

void Cache::setOriginalImage(QImage *image)
{
    this->originalImage = image;
}

void Cache::setTempImage(QImage *image)
{
    this->tempImage = image;
}

void Cache::setAcinusList(QList<Acinus *> *acinusList)
{
    this->acinusList = acinusList;
}

QList<Acinus *> *Cache::getAcinusList()
{
    return acinusList;
}

ImageDbModel *Cache::getImageDbModel()
{
    return imageDbModel;
}

void Cache::setImageDbModel(ImageDbModel *imageDbModel)
{
    this->imageDbModel = imageDbModel;
}

