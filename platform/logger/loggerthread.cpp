#include "loggerthread.h"
#include "logger.h"

LoggerThread::LoggerThread()
{

}

void LoggerThread::run()
{
       std::cout<<"logger successfull start in self thread"<<std::endl;
       Logger::write();
}
