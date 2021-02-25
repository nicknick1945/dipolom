#include "csvdataaccess.h"
#include <QtCore/qdir.h>
#include <QBuffer>
#include <QTextStream>
#include <fstream>
#include <iostream>

CsvDataAccess::CsvDataAccess(){}

QHash<QString , QImage *> *CsvDataAccess::getGists()
{
    return NULL;
}

void CsvDataAccess::saveModel(ImageDbModel *imageDbModel)
{
        QString filePath = QDir::currentPath() + "/cancer.csv";
        QString row=QString::number(imageDbModel->id);
        row.append(";");
        row.append(imageDbModel->cancerstady);
        row.append(";");
        row.append(QString::number(imageDbModel->firstStadyAcinusPersent));
        row.append(";");
        row.append(QString::number(imageDbModel->threadStadyAcinusPersent));
        row.append(";");
        row.append(QString::number(imageDbModel->forthStadyAcinusPersent));
        row.append(";");

        QByteArray byteArray;
        QBuffer buffer(&byteArray);
        imageDbModel->image->save(&buffer, "JPEG");
        QString iconBase64 = QString::fromLatin1(byteArray.toBase64().data());
        row.append(iconBase64);
        row.append("\n");
        std::ofstream file;
        file.open(filePath.toStdString(),std::fstream::in | std::fstream::out | std::fstream::app);
        file<<row.toStdString();
        file.close();
        delete imageDbModel;
}

QList<ImageDbModel*> *CsvDataAccess::getImageModel(ImageDbModel *imageDbModel)
{

}
/** структура бд  id(int )/cancerStudy(int)/firstStadyAcinusPersent(int)/threadStadyAcinusPersent(int)/forthStadyAcinusPersent(int)/image(QString::base64)
 * @brief CsvDataAccess::getNearestModel
 * @param imageDbModel
 * @return
 */
QList<ImageDbModel*> *CsvDataAccess::getNearestModel(ImageDbModel *imageDbModel)
{
    QList<ImageDbModel*> * result = new QList<ImageDbModel*>();
    QString filePath = QDir::currentPath() + "/cancer.csv";
    QFile inputFile(filePath);
    if (inputFile.open(QIODevice::ReadOnly)){
       QTextStream in(&inputFile);
       while (!in.atEnd())
       {
          QString line = in.readLine();
          QStringList list = line.split(";");
          if(list.at(1) == imageDbModel->cancerstady){
              logger->info("Найдено совпадение по стадии ");
              ImageDbModel *imageDbModel = new ImageDbModel();
              imageDbModel->cancerstady = list.at(1);
              imageDbModel->firstStadyAcinusPersent=list.at(2).toDouble();
              imageDbModel->threadStadyAcinusPersent = list.at(3).toDouble();
              imageDbModel->forthStadyAcinusPersent= list.at(4).toDouble();

              QByteArray by = QByteArray::fromBase64(list.at(5).toLatin1());
              QImage *img = new QImage();
              img->loadFromData(by,"JPEG");
              imageDbModel->image =img;
              result->append(imageDbModel);
          }
       }
       inputFile.close();
    }

    QString log= "найдено совпадений в базе данныйх:";
    log.append(QString::number(result->size()));
    return result;
}
