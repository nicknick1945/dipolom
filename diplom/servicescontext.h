#ifndef SERVICESCONTEXT_H
#define SERVICESCONTEXT_H

#include <diplom/filters/binarizer.h>
#include <diplom/filters/blackwhitefilte.h>
#include <diplom/filters/mysuperfilter.h>
#include <diplom/recognizers/attributerecognizser.h>
#include <diplom/recognizers/recongnizerschain.h>
#include <diplom/database/da/idataaccess.h>
#include "diplom/recognizers/gistogrammrecognizer.h"

class ServicesContext
{
public:

    ServicesContext();
    static QImage * image;
    static BlackWhiteFilte * getBlackWhiteFilter();
    static MySuperFilter * getMySuperFiler();
    static Binarizer* getBiarizer();
    static RecongnizersChain* getRecognizerChain();
    static AttributeRecognizser* getAttribyteREcognizer();
    static IDataAccess* getDataAccess();
    static GistogrammRecognizer* getGistogrammRecognizer();
    static void init();

//    static AbstractCancerRegonizer * getRcognizer();
private:
    static BlackWhiteFilte * blackWhiteFilter;
    static MySuperFilter * mySuperFilter;
    static Binarizer * binarizer;
    static RecongnizersChain *recongnizerChain;
    static IDataAccess *dataAccess;
    static AttributeRecognizser* attributeRecognizser;
    static GistogrammRecognizer* gistogrammRecognizer;
//       static AbstractCancerRegonizer *recognizer;
};

#endif // SERVICESCONTEXT_H
