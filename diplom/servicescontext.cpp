#include "servicescontext.h"
#include <diplom/recognizers/formrecognizer.h>
#include <diplom/recognizers/sizerognizer.h>
#include <diplom/database/da/csvdataaccess.h>
#include <diplom/database/da/sqllitedataaccess.h>
#include <diplom/database/da/dataaccessfactory.h>


BlackWhiteFilte* ServicesContext::blackWhiteFilter = new BlackWhiteFilte();
MySuperFilter* ServicesContext::mySuperFilter = new MySuperFilter();
Binarizer* ServicesContext::binarizer = new Binarizer();
RecongnizersChain* ServicesContext::recongnizerChain = new RecongnizersChain();
IDataAccess* ServicesContext::dataAccess = DataAccessFactory::getDataAccess();
GistogrammRecognizer* ServicesContext::gistogrammRecognizer= new GistogrammRecognizer();
AttributeRecognizser* ServicesContext::attributeRecognizser = new AttributeRecognizser();

ServicesContext::ServicesContext(){

}

BlackWhiteFilte *ServicesContext::getBlackWhiteFilter(){
    return blackWhiteFilter;
}

MySuperFilter *ServicesContext::getMySuperFiler(){
    return mySuperFilter;
}

Binarizer *ServicesContext::getBiarizer()
{
    return binarizer;
}

RecongnizersChain *ServicesContext::getRecognizerChain()
{
    return recongnizerChain;
}

AttributeRecognizser *ServicesContext::getAttribyteREcognizer()
{
    attributeRecognizser;
}

IDataAccess *ServicesContext::getDataAccess()
{
    return dataAccess;
}

GistogrammRecognizer *ServicesContext::getGistogrammRecognizer()
{
    return gistogrammRecognizer;
}


void ServicesContext::init()
{
    FormRecognizer *circlRecognizer = new FormRecognizer();
    SizeRognizer *sizeRecognizer = new SizeRognizer();
    recongnizerChain->recognizers->append(sizeRecognizer);
    recongnizerChain->recognizers->append(circlRecognizer);
}


