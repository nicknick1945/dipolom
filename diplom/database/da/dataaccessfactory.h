#ifndef DATAACCESSFACTORY_H
#define DATAACCESSFACTORY_H

#include "idataaccess.h"

#include <platform/logger/haslogger.h>



class DataAccessFactory
{
public:
    DataAccessFactory();
    static IDataAccess* getDataAccess();
private:
    static IDataAccess* dataAccess;
};

#endif // DATAACCESSFACTORY_H
