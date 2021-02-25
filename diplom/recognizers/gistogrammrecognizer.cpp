#include "gistogrammrecognizer.h"

#include <QPixmap>
#include "recongnizerschain.h"

GistogrammRecognizer::GistogrammRecognizer()
{

}

QString *GistogrammRecognizer::doRecognize(QImage *image)
{
    int green[255]={0};
    //создание гистограммы
    for (int y =0 ; y < image->height() ; y ++){
        for (int x = 0 ; x < image->width() ; x++) {
            green[image->pixelColor(x,y).green()]++;
        }
    }

    //найдем максимальное  гистограммы
    int maxGreen =0 ;
    for (int i = 0 ; i < 255; i++){
        if(maxGreen<green[i]) maxGreen = green[i];

    }

    //нормализация гитограммы нормализуем от 0 до 500
    for(int i = 0 ; i < 255 ;i++){
        green[i] = green[i]*500;
        green[i] = green[i]/maxGreen;
    }

    QImage greenGist = QPixmap(510,500).toImage();

    for (int x = 0 ; x  < greenGist.width() ; x++){
        for (int y = 0 ; y < greenGist.height(); y++){
            greenGist.setPixelColor(x,y,QColor(0,0,0,255));
        }
    }

    for (int i = 0 ; i < 500 ; i= i+2){
        for (int y = 0 ; y < green[i/2] ; y++ ){
            greenGist.setPixelColor(i,y,QColor(0,255,0,255));
            greenGist.setPixelColor(i+1,y,QColor(0,255,0,255));
        }
    }

    //распознавание здоровый клеток
    bool forthStudy= true;
    for (int y = 470; y < 500 ; y ++) {
        for (int x =0 ; x  < 500 ; x++ ){
            if (greenGist.pixelColor(x,y).green()>254){
                forthStudy = false;

            }
        }
    }
    if(forthStudy){
        logger->info("по гисторамме получилось что первый тип рака");
        return RecongnizersChain::FIRST;
    }

    int countPixelsFree = 0 ;
    for (int y =140 ;  y < 500 ; y++){
        for (int x = 490 ; x < 500 ; x++){
            if (greenGist.pixelColor(x,y).green()>254) countPixelsFree ++;
        }
    }

    if (countPixelsFree > 6 && !forthStudy){
        logger->info("по гисторамме получилось что первый тип рака");
        return RecongnizersChain::FORTH;

    }else {
        logger->info("по гисторамме получилось что третий тип рака");
        return RecongnizersChain::THREARD;
    }

}
