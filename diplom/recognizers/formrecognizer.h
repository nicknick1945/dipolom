#ifndef FORMRECOGNIZER_H
#define FORMRECOGNIZER_H
#include "abstractrecognizer.h"

class FormRecognizer : public AbstractRecognizer
{
public:
    FormRecognizer();
    void doRecognize(Acinus *acinus,QImage* image);
private:


};

#endif // FORMRECOGNIZER_H
