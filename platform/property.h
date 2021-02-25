#ifndef PROPERTY_H
#define PROPERTY_H

#include <QFile>
#include <QTextStream>
#include <qvariant.h>
#include <qdir.h>

class Property
{
public:
    Property();
    static QString readProperty(QString properyName,QString propertyFileName){
        QString filePath = QDir::currentPath()+ "/" + propertyFileName +".property";
        QFile inputFile(filePath);
        if (inputFile.open(QIODevice::ReadWrite)){
           QTextStream in(&inputFile);
           while (!in.atEnd()){
              QString line = in.readLine();
              QStringList list = line.split("=");
              if( ((QString)list.at(0)).trimmed() == properyName){
                  return ((QString)list.at(1)).trimmed();
              }
           }
        }
    return "";
    }

};

#endif // PROPERTY_H
