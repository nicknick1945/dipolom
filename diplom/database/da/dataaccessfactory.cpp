#include "csvdataaccess.h"
#include "dataaccessfactory.h"
#include "sqllitedataaccess.h"
#include "iostream"
IDataAccess* DataAccessFactory::dataAccess = NULL;

DataAccessFactory::DataAccessFactory()
{

}

IDataAccess *DataAccessFactory::getDataAccess()
{
    if (dataAccess==NULL){
        if(SqlLiteDataAccess::canOpenConnect()){
            std::cout<<"будет использована база данных sql lite"<<std::endl;
            dataAccess = new SqlLiteDataAccess();

        }else {
            std::cout<<"будет использована база данных в формате csv"<<std::endl;
            dataAccess = new CsvDataAccess();
        }
    }

    return dataAccess;
}
