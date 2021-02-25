#ifndef SQLLITEDATAACCESS_H
#define SQLLITEDATAACCESS_H

#include "idataaccess.h"
#include <QtSql>




class SqlLiteDataAccess: public IDataAccess
{
public:
    SqlLiteDataAccess();
    void saveModel(ImageDbModel* imageDbModel);
    QList<ImageDbModel*>* getImageModel(ImageDbModel* imageDbModel);
    QList<ImageDbModel*>* getNearestModel(ImageDbModel* imageDbModel);
    QHash<QString,QImage*>* getGists();
    static bool canOpenConnect();

private :
    QString host;
    QString dbName=Property::readProperty("dbName","dbproperty");
    QString userName;
    QString password;
    void createTables();
    void fillDb();
    bool gistogramsExist();
};

#endif // SQLLITEDATAACCESS_H
