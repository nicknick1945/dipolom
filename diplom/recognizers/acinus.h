#ifndef ACINUS_H
#define ACINUS_H

#include "qhash.h"
#include <diplom/filters/mysuperfilter.h>"
#include "qlist.h"

class Acinus
{
public:
    Acinus();
    QHash<int,PixelType> *acunusArea;
    QList<QString*> *acinusSign  = new QList<QString*>();
};

#endif // ACINUS_H
