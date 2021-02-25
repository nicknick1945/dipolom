#include "sizerognizer.h"
#include <diplom/constants.h>
#include <diplom/recognizers/recongnizerschain.h>
SizeRognizer::SizeRognizer(){}

void SizeRognizer::doRecognize(Acinus *acinus,QImage* image)
{
    if(acinus->acunusArea->size()>BIG_ACINUS){
        acinus->acinusSign->append(RecongnizersChain::FIRST);
    }else {
        acinus->acinusSign->append(RecongnizersChain::FORTH);
        acinus->acinusSign->append(RecongnizersChain::THREARD);
    }
}
