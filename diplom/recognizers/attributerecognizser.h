#ifndef ATTRIBUTERECOGNIZSER_H
#define ATTRIBUTERECOGNIZSER_H

#include "acinus.h"

#include <diplom/database/vo/imagedbmodel.h>
#include "gistogrammrecognizer.h"



class AttributeRecognizser:public HasLogger
{
public:
    AttributeRecognizser();
    ImageDbModel* findAttributes(QImage* image,QList<Acinus*> *acinusList);
private:
    bool isMax(int target,int v1,int v2,int v3,int v4);
};

#endif // ATTRIBUTERECOGNIZSER_H
