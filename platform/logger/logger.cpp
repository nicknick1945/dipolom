#include "logger.h"
#include "iostream"
#include "qstringlist.h"
#include "QFile"
#include "QTextStream"
#include "QTime"
#include "loggerthread.h"
#include "conseleappneder.h"
using namespace std;

QList<IAppender*> *Logger::appenders ;
QQueue<QString> *Logger::msgToWriteQueue;

Logger::Logger()
{    
    appenders = new QList<IAppender*>();
    msgToWriteQueue = new QQueue<QString>();
    Logger::appenders->append(new ConseleAppneder());
    LoggerThread *t = new LoggerThread();
    t->start();
}

void Logger::write()
{
    while(true){
        if(!Logger::getMsgToWriteQueue()->isEmpty()){
            QString msq = Logger::getMsgToWriteQueue()->dequeue();
            for(int i = 0 ; i < Logger::appenders->size() ; i++){
                IAppender *appender = Logger::appenders->at(i);
                appender->write(msq);
            }
        }
    }
}

void Logger::info(QString message)
{
    LogLevel logLevel = getLogLevel();
    if ( logLevel != LogLevel::ERROR){
        Logger::msgToWriteQueue->append(getTime().append(" INFO:").append(message));
    }
}

void Logger::debug(QString message){
    LogLevel logLevel = getLogLevel();
    if ( logLevel != LogLevel::INFO && logLevel != ERROR){
        Logger::msgToWriteQueue->append(getTime().append(" DEBUG:").append(message));

    }
}

void Logger::error(QString message){
    Logger::msgToWriteQueue->append(getTime().append(" ERROR:").append(message));
}

QQueue<QString> *Logger::getMsgToWriteQueue()
{
    return msgToWriteQueue;
}

QString Logger::getTime()
{
    QDateTime dateTime = dateTime.currentDateTime();
    QString dateTimeString = dateTime.toString("yyyy-MM-dd hh:mm:ss");
    return dateTimeString;
}

LogLevel Logger::getLogLevel()
{
    if(workRegim==LOAD_ON_START && !firstStart){
        return logLevell;
    } else if(workRegim==LOAD_BY_MASSEG){
        QString line;
        QFile logLevel("logLevel.txt");// обьявляем
        if (!logLevel.open(QIODevice::ReadOnly | QIODevice::Text)){// открываем
            cout<<"can't open logLevel"<<endl;//на всякий случай
            return LogLevel::DEBUG;
        }
        QTextStream accIn(&logLevel), lineIn(&line);// первый - стрим файла, второй - читаемой строки
        line = accIn.readLine();
        QStringList property = line.split("=");
        if(property.at(1).contains("debug")){
            return LogLevel::DEBUG;
        }else if (property.at(1).contains("info")){
            return LogLevel::INFO;
        }else if (property.at(1).contains("error")){
            return LogLevel::ERROR;
        }
        logLevel.close();
        firstStart = false;
        return LogLevel::INFO;
    }
    else{
        return logLevell;
    }
}
