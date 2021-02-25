#ifndef CSVDATAACCESS_H
#define CSVDATAACCESS_H

#include "idataaccess.h"

#include <platform/logger/haslogger.h>

/**
 * @brief The CsvDataAccess class
 * структура бд  id(int )/cancerStudy(int)/firstStadyAcinusPersent(int)/threadStadyAcinusPersent(int)/forthStadyAcinusPersent(int)/pathToImage(QString)
 */
class CsvDataAccess: public IDataAccess
{
public:
    CsvDataAccess();
    QHash<QString,QImage*>* getGists();
    virtual void saveModel(ImageDbModel* imageDbModel);
    virtual QList<ImageDbModel*>* getImageModel(ImageDbModel* imageDbModel);
    virtual QList<ImageDbModel*>* getNearestModel(ImageDbModel* imageDbModel);
private :

};

#endif // CSVDATAACCESS_H
