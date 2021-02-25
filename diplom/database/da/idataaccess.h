#ifndef IDATAACCESS_H
#define IDATAACCESS_H
#include "diplom/database/vo/imagedbmodel.h"
#include <platform/logger/haslogger.h>
#include <platform/property.h>
#include "qmap.h"
#include "qhash.h"

class IDataAccess: public HasLogger{
public:
    IDataAccess();
    virtual void saveModel(ImageDbModel* imageDbModel) = 0 ;
    virtual QList<ImageDbModel*>* getImageModel(ImageDbModel* imageDbModel) = 0;
    virtual QList<ImageDbModel*>* getNearestModel(ImageDbModel* imageDbModel) = 0;
    virtual QHash<QString,QImage*>* getGists() = 0;
};

#endif // IDATAACCESS_H
