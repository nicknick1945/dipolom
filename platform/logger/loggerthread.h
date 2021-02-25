#ifndef LOGGERTHREAD_H
#define LOGGERTHREAD_H
#include "QThread"
#include "iostream"

class LoggerThread : public QThread
{
public:
  LoggerThread();
protected :
    void run();
};

#endif // LOGGERTHREAD_H
