#include "sqllitedataaccess.h"

#include <QImageWriter>
#include "stdio.h"
#include <iostream>
#include <platform/property.h>

SqlLiteDataAccess::SqlLiteDataAccess(){
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(Property::readProperty("dbName","dbproperty"));
    bool ok = db.open();
    QSqlQuery tableQuery;
    tableQuery.prepare("SELECT name FROM my_db.sqlite_master WHERE type='table' ");
    tableQuery.exec();
    bool tableExists = false;
    while(tableQuery.next()){
        if(QString("carncerTabel") == tableQuery.value(0).toString()){
            tableExists = true;
        }
    }
    db.close();
    if(!tableExists) createTables();
}

void SqlLiteDataAccess::saveModel(ImageDbModel *imageDbModel)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName(host);
    db.setDatabaseName(dbName);
    db.setUserName(userName);
    db.setPassword(password);
    bool ok = db.open();

    QBuffer buffer;
    QImageWriter writer(&buffer, "JPEG");
    writer.write(*imageDbModel->image);
    QByteArray data = buffer.data();
    QSqlQuery my_query;
    my_query.prepare("INSERT INTO carncerTabel (id,cancerstady,   firstStadyAcinusPersent,threadStadyAcinusPersent,forthStadyAcinusPersent,image)"
                                  "VALUES (:id,   :cancerstady,  :firstStadyAcinusPersent,:threadStadyAcinusPersent,:forthStadyAcinusPersent,:image);");
    my_query.bindValue(":id",imageDbModel->id);
    my_query.bindValue(":cancerstady",imageDbModel->cancerstady);
    my_query.bindValue(":firstStadyAcinusPersent",imageDbModel->firstStadyAcinusPersent);
    my_query.bindValue(":threadStadyAcinusPersent",imageDbModel->threadStadyAcinusPersent);
    my_query.bindValue(":forthStadyAcinusPersent",imageDbModel->forthStadyAcinusPersent);
    my_query.bindValue(":image",data);
    bool saveSuccess = my_query.exec();
    if(saveSuccess)logger->debug("изображение сохранено успешно");

    else{
        std::cout<<my_query.lastError().text().toStdString()<<std::endl;
    }


}

QList<ImageDbModel *> *SqlLiteDataAccess::getImageModel(ImageDbModel *imageDbModel)
{
    return NULL;
}

QList<ImageDbModel *> *SqlLiteDataAccess::getNearestModel(ImageDbModel *imageDbModel){

    QList<ImageDbModel*> *results = new QList<ImageDbModel*>();
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbName);
    bool ok = db.open();
    QSqlQuery query;
    query.prepare("SELECT * FROM carncerTabel WHERE cancerstady = :cancerstudy");
    query.bindValue(":cancerstudy",imageDbModel->cancerstady);
    bool saveSuccess = query.exec();
    if(saveSuccess)logger->debug("запрос на поиск выполнен успешно");

    else{
        std::cout<<query.lastError().text().toStdString()<<std::endl;
    }
    while(query.next()){
        ImageDbModel* row = new ImageDbModel();
        row->id= query.value(0).toInt();
        row->cancerstady = query.value(1).toString();
        row->firstStadyAcinusPersent = query.value(2).toDouble();
        row->threadStadyAcinusPersent = query.value(3).toDouble();
        row->forthStadyAcinusPersent = query.value(4).toDouble();
        QByteArray imageByteArray = query.value(5).toByteArray();
        QImage *image = new QImage();
        image->loadFromData(imageByteArray,"JPEG");
        row->image = image;
        if(row->cancerstady ==imageDbModel->cancerstady){
            results->append(row);
        }else{
            delete row;
        }
    }
    return results;
}

QHash<QString, QImage *> *SqlLiteDataAccess::getGists()
{
    QHash<QString,QImage*> *results = new QHash<QString,QImage*>();
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbName);
    bool ok = db.open();
    QSqlQuery query;
    query.prepare("SELECT cancerstady,image FROM gistogrammsTable");
    query.exec();
    while(query.next()){

        QByteArray imageByteArray = query.value(1).toByteArray();
        QImage *image = new QImage();
        image->loadFromData(imageByteArray,"JPEG");
        results->insert(query.value(0).toString(),image);
    }
    return results;
}

bool SqlLiteDataAccess::canOpenConnect()
{

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    QString pathToDb = Property::readProperty("dbName","dbproperty");
    db.setDatabaseName(pathToDb);
    QFileInfo checkFile(pathToDb);
    if (checkFile.isFile()) {
        qDebug()<<"db sql lite success open ";
        return true;
    }else{
        qDebug()<<"path to sql lite in not correct. Use file";
        return false;
    }


}


void SqlLiteDataAccess::createTables()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(Property::readProperty("dbName","dbproperty"));
    bool ok = db.open();
    QSqlQuery query;
    if(db.isOpenError()){
        std::cout<<"ошибка при открытии базы данных"<<std::endl;
    }else {
         std::cout<<"коннект к базе установлен успешно"<<std::endl;
    }

    QString queryString  = "CREATE TABLE carncerTabel(id INT,cancerstady TEXT,firstStadyAcinusPersent real,threadStadyAcinusPersent real,forthStadyAcinusPersent real ,image BLOB );";
    query.prepare(queryString);
    bool saveSuccess = query.exec();
    QString createGistogrammTable = "CREATE TABLE gistogrammsTable(cancerstady TEXT ,image BLOB );";
    QSqlQuery createGistogrammTableQuery;
    bool successCreateGistTable = createGistogrammTableQuery.prepare(createGistogrammTable);
    createGistogrammTableQuery.exec();
    if(saveSuccess&& successCreateGistTable)logger->debug("таблицы созданы успешно");
    else{
        std::cout<<query.lastError().text().toStdString()<<std::endl;
    }
    fillDb();
    db.close();
}

void SqlLiteDataAccess::fillDb()
{
    if(!gistogramsExist()){
        std::cout<<"база данных пуста , приступить к заполнению"<<std::endl;
        QString path = QDir::currentPath();
        path.append("/gist");
        QDir dir(path);

        QStringList nameFilter; // имя фильтра
            // можно задать интересующие расширения nameFilter << "*.png" << "*.jpeg" << "*.gif";
        nameFilter << "*.jpeg" << "*.png" << "*jpg";// например такие
        QFileInfoList list = dir.entryInfoList( nameFilter, QDir::Files );// сказываем что нас интересуют только файлы
        QFileInfo fileinfo; // сюда будем считывать эжлементы
        foreach (fileinfo, list) {
            QImage image;
            image.load(fileinfo.absoluteFilePath());
            QBuffer buffer;
            QImageWriter writer(&buffer, "JPEG");
            writer.write(image);
            QByteArray data = buffer.data();
            QSqlQuery my_query;

            QString cancerstady = fileinfo.baseName();
            my_query.prepare("INSERT INTO gistogrammsTable(cancerstady,image) VALUES (:cancerstady,:image);");
            my_query.bindValue(":cancerstady",cancerstady);
            my_query.bindValue(":image",data);
            my_query.exec();
        }
    }
}

bool SqlLiteDataAccess::gistogramsExist()
{
    QSqlQuery my_query;
    my_query.prepare("select * from gistogrammsTable");
    my_query.exec();
    return my_query.next();
}
