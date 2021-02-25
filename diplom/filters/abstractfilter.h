#ifndef ABSTRACTFILTER_H
#define ABSTRACTFILTER_H
#include "qimage.h"
#include <platform/logger/haslogger.h>

class AbstractFilter : public HasLogger
{
public:
    AbstractFilter();
    virtual void doFilter(QImage &image) = 0;
    virtual QString* getDescription() = 0;
};

#endif // ABSTRACTFILTER_H
