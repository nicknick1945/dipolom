#ifndef ABSTRACTRECOGNIZER_H
#define ABSTRACTRECOGNIZER_H

#include <platform/logger/haslogger.h>
#include "acinus.h"
#include "qimage.h"

class Acinus;

class AbstractRecognizer :public HasLogger
{
public:
    AbstractRecognizer();
    virtual void doRecognize(Acinus *acinus,QImage* image)=0;
};

#endif // ABSTRACTRECOGNIZER_H
