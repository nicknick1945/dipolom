#ifndef BINARIZESR_H
#define BINARIZESR_H
#include <platform/logger/haslogger.h>
#include "qimage.h"


class Binarizer : public HasLogger{
public:
    Binarizer();
    void doBinary(QImage *image,int treshold);
private:

    int imagePixel = 255;
    int noImagePixel = 0 ;
};

#endif // BINARIZESR_H
