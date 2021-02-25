#ifndef HASLOGGER_H
#define HASLOGGER_H

#include "loggerfactory.h"
#include "logger.h"



class HasLogger
{
public:
    HasLogger();
    LoggerFactory *loggerFactory = new LoggerFactory();
    Logger *logger = loggerFactory->getInstance();
};

#endif // HASLOGGER_H
