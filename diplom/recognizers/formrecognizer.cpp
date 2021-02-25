#include "formrecognizer.h"
#include "recongnizerschain.h"
FormRecognizer::FormRecognizer()
{

}


void FormRecognizer::doRecognize(Acinus *acinus, QImage *image)
{
    logger->debug("вход в распознаватель формы круга");
    int y_top = 0;
    int y_buttom = image->height()-1;
    int x_left = image->width()-1;
    int x_right = 0;

    QHashIterator<int,PixelType> iter(*acinus->acunusArea);
    while(iter.hasNext()){
        iter.next();
        int coordX = iter.key()%10000;
        int coordY = iter.key()/10000;
        if(coordY > y_top )y_top = coordY;
        if(coordY < y_buttom) y_buttom = coordY;
        if(coordX < x_left) x_left = coordX;
        if(coordX > x_right) x_right = coordX;
    }

    double width = x_right - x_left;
    double height = y_top - y_buttom;
    double like_elips_area = width*height*3.14;
    QString msg = "отношение площади к площади элипса для данной штукении:";
    double acunusAreaSize = acinus->acunusArea->size();
    double testValue = like_elips_area/acunusAreaSize;
    msg.append(QString::number(testValue));
    QString msg2 = "отношение длины к ширене описано прямоугольника:";
    double testValue2= width/height ;
    msg2.append(QString::number(testValue2));
    logger->debug(msg2);
    logger->debug(msg);
    if(!acinus->acinusSign->contains(RecongnizersChain::FIRST)){
        if(testValue > 0.4 ){
            if(testValue < 4.0){
                if(testValue2>0.4){
                    if(testValue2 <2){
                        logger->debug("finded circle acinus");
                        if(!acinus->acinusSign->contains(RecongnizersChain::THREARD)){
                            acinus->acinusSign->append(RecongnizersChain::THREARD);
                        }
                        if(acinus->acinusSign->contains(RecongnizersChain::FORTH)){
                            int index = acinus->acinusSign->indexOf(RecongnizersChain::FORTH);
                            acinus->acinusSign->removeAt(index);
                        }
                        return;
                    }
                }
            }
        }


    }
    if(acinus->acinusSign->contains(RecongnizersChain::THREARD)){
        int index = acinus->acinusSign->indexOf(RecongnizersChain::THREARD);
        acinus->acinusSign->removeAt(index);
    }

}


