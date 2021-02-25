#ifndef LOGGER_H
#define LOGGER_H
#include "iappender.h"
#include "qstring.h"
#include "QQueue"
#undef INFO
#undef DEBUG
#undef ERROR
#undef UNDEFINED
enum LogLevel{INFO,DEBUG,ERROR,UNDEFIEND};

enum WorkRegim{
    LOAD_BY_MASSEG,LOAD_ON_START
};

class Logger
{
public:
    Logger();
    static QList<IAppender*> *appenders;
    void static write();
    void info(QString messege);
    void debug(QString messege);
    void error(QString messege);
    static QQueue<QString> *msgToWriteQueue;
private :
   static QQueue<QString>* getMsgToWriteQueue();
   bool firstStart = true;
   LogLevel logLevell = LogLevel::DEBUG;
   QString getTime();
   WorkRegim workRegim=WorkRegim::LOAD_ON_START;
   LogLevel getLogLevel();
};




#endif // LOGGER_H
