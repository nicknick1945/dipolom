#include "attributerecognizser.h"
#include "recongnizerschain.h"
#include "diplom/servicescontext.h"

AttributeRecognizser::AttributeRecognizser()
{

}

ImageDbModel *AttributeRecognizser::findAttributes(QImage* image,QList<Acinus*> *acinusList){

    int firstStudyArea = 0;
    int secondStudyArea = 0;
    int threadStudyArea = 0;
    int forthStudyArea = 0;
    int fiftStudyArea = 0;

    ImageDbModel *imageDbModel = new ImageDbModel();
    for(int i = 0 ; i < acinusList->size(); i++){
        if(acinusList->at(i)->acinusSign->contains(RecongnizersChain::FIRST)){
            firstStudyArea =firstStudyArea + acinusList->at(i)->acunusArea->size();
        }
        if(acinusList->at(i)->acinusSign->contains(RecongnizersChain::SECOND)){
            secondStudyArea = secondStudyArea + acinusList->at(i)->acunusArea->size();
        }
        if(acinusList->at(i)->acinusSign->contains(RecongnizersChain::THREARD)){
             threadStudyArea = threadStudyArea + acinusList->at(i)->acunusArea->size();
        }
        if(acinusList->at(i)->acinusSign->contains(RecongnizersChain::FORTH)){
             forthStudyArea = forthStudyArea  + acinusList->at(i)->acunusArea->size();
        }
        if(acinusList->at(i)->acinusSign->contains(RecongnizersChain::FIFT)){
             fiftStudyArea = fiftStudyArea + acinusList->at(i)->acunusArea->size();
        }
    }

    if(isMax(firstStudyArea,secondStudyArea,threadStudyArea,forthStudyArea,fiftStudyArea)){
        imageDbModel->cancerstady = *RecongnizersChain::FIRST;
    }

    if(isMax(secondStudyArea,firstStudyArea,threadStudyArea,forthStudyArea,fiftStudyArea)){
           imageDbModel->cancerstady = *RecongnizersChain::SECOND;
    }
    if(isMax(threadStudyArea,secondStudyArea,firstStudyArea,forthStudyArea,fiftStudyArea)){
           imageDbModel->cancerstady = *RecongnizersChain::THREARD;
    }
    if(isMax(forthStudyArea,secondStudyArea,threadStudyArea,firstStudyArea,fiftStudyArea)){
           imageDbModel->cancerstady = *RecongnizersChain::FORTH;
    }
    if(isMax(fiftStudyArea,secondStudyArea,threadStudyArea,forthStudyArea,firstStudyArea)){
           imageDbModel->cancerstady = *RecongnizersChain::FIFT;
    }

    imageDbModel->image = image;
    imageDbModel->cancerstady =*ServicesContext::getGistogrammRecognizer()->doRecognize(image);
    imageDbModel->firstStadyAcinusPersent = ((double)firstStudyArea)/((double)(image->width()*image->height()));
    imageDbModel->secondStadyAcinusPersont = ((double)secondStudyArea)/((double)(image->width()*image->height()));
    imageDbModel->threadStadyAcinusPersent = ((double)threadStudyArea)/((double)(image->width()*image->height()));
    imageDbModel->forthStadyAcinusPersent = ((double)forthStudyArea)/((double)(image->width()*image->height()));
    imageDbModel->fiftStudyAcinusPersent = ((double)fiftStudyArea)/((double)(image->width()*image->height()));
    QString logMsg = "определена стадия рака";
    logMsg.append(imageDbModel->cancerstady);
    return imageDbModel;

}



bool AttributeRecognizser::isMax(int target, int v1, int v2, int v3, int v4)
{
    return target>v1&&target>v2&&target>v3&&target>v4;
}
