#ifndef GISTOGRAMMRECOGNIZER_H
#define GISTOGRAMMRECOGNIZER_H

#include <qimage.h>

#include <platform/logger/haslogger.h>





class GistogrammRecognizer :HasLogger
{
public:
    GistogrammRecognizer();
    //функция которая анализирует гистограмму для зеленого цвета
    QString * doRecognize(QImage* image);
};

#endif // GISTOGRAMMRECOGNIZER_H
