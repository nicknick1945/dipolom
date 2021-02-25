#ifndef IAPPENDER_H
#define IAPPENDER_H

#include "qstring.h"
class IAppender
{
public:
    IAppender();
    virtual void write(QString str);
};

#endif // IAPPENDER_H
