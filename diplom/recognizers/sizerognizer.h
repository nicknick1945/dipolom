#ifndef SIZEROGNIZER_H
#define SIZEROGNIZER_H
#include "abstractrecognizer.h"

class SizeRognizer : public AbstractRecognizer
{
public:
    SizeRognizer();
    void doRecognize(Acinus *acinus,QImage* image);
};

#endif // SIZEROGNIZER_H
